#include <iostream>
#include <cstring>
#include <cstdlib>
#include <thread> // 1. 스레딩을 위한 헤더 추가
#include <winsock2.h>
#include <ws2tcpip.h>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

const int PORT = 8080;
const int BUFFER_SIZE = 1024;

void error(const char* msg) {
    cerr << msg << " : Winsock Error Code: " << WSAGetLastError() << endl;
    WSACleanup();
    exit(1);
}

// ---------------------- 2. TCP 클라이언트 처리 함수 ----------------------
void HandleClient(SOCKET client_socket, struct sockaddr_in client_addr) {
    char buffer[BUFFER_SIZE];
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);

    cout << "Thread started for TCP client: " << client_ip << ":" << ntohs(client_addr.sin_port) << endl;

    // 이 루프를 통해 클라이언트가 연결을 끊을 때까지 계속 메시지를 받습니다.
    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        // recv를 사용하여 데이터 수신
        int n = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);

        if (n > 0) {
            buffer[n] = '\0';
            cout << "[" << client_ip << "] TCP Msg: " << buffer << endl;
            // Echo back (선택 사항: 모든 클라이언트에게 브로드캐스트하는 로직이 추가될 수 있음)
            send(client_socket, "Server got your TCP message.", 29, 0);
        }
        else if (n == 0) {
            // 클라이언트가 정상적으로 연결을 닫았을 때 (exit 입력 등)
            cout << "TCP client disconnected: " << client_ip << endl;
            break;
        }
        else {
            // 오류 발생
            // cerr << "TCP recv failed. Error code: " << WSAGetLastError() << endl;
            break;
        }
    }

    // 클라이언트와의 통신이 끝났으므로 소켓을 닫고 스레드 종료
    closesocket(client_socket);
}

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        error("WSAStartup failed");
    }

    SOCKET tcp_sockfd, udp_sockfd;
    int clilen;
    struct sockaddr_in serv_addr, cli_addr;
    char buffer[BUFFER_SIZE];

    // TCP 소켓 생성
    tcp_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (tcp_sockfd == INVALID_SOCKET) error("ERROR opening TCP socket");

    // UDP 소켓 생성
    udp_sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (udp_sockfd == INVALID_SOCKET) error("ERROR opening UDP socket");

    // 소켓 구조체 초기화 및 바인딩 (이전과 동일)
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    if (bind(tcp_sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
        error("ERROR on binding TCP");
    if (bind(udp_sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
        error("ERROR on binding UDP");

    if (listen(tcp_sockfd, 5) == SOCKET_ERROR) error("ERROR on TCP listen");
    clilen = sizeof(cli_addr);

    cout << "Server listening on port " << PORT << " for TCP and UDP..." << endl;

    fd_set readfds;

    while (true) {
        FD_ZERO(&readfds);
        FD_SET(tcp_sockfd, &readfds); // TCP 수신 대기
        FD_SET(udp_sockfd, &readfds); // UDP 수신

        if (select(0, &readfds, NULL, NULL, NULL) == SOCKET_ERROR) {
            error("ERROR on select");
        }

        // A. TCP 연결 요청 처리
        if (FD_ISSET(tcp_sockfd, &readfds)) {
            SOCKET newsockfd = accept(tcp_sockfd, (struct sockaddr*)&cli_addr, &clilen);
            if (newsockfd != INVALID_SOCKET) {
                // 3. 새 연결이 들어오면 별도의 스레드를 생성하여 처리
                thread client_thread(HandleClient, newsockfd, cli_addr);
                // 스레드를 분리하여 메인 스레드가 다음 연결을 대기하도록 함
                client_thread.detach();
            }
            else {
                cerr << "ERROR on TCP accept : Winsock Error Code: " << WSAGetLastError() << endl;
            }
        }

        // B. UDP 데이터그램 수신 처리
        if (FD_ISSET(udp_sockfd, &readfds)) {
            memset(buffer, 0, BUFFER_SIZE);
            int n = recvfrom(udp_sockfd, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr*)&cli_addr, &clilen);

            if (n > 0) {
                buffer[n] = '\0';
                char client_ip[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &cli_addr.sin_addr, client_ip, INET_ADDRSTRLEN);

                cout << "[" << client_ip << "] UDP Msg: " << buffer << endl;

                // Echo back
                sendto(udp_sockfd, "Server got your UDP message.", 29, 0, (struct sockaddr*)&cli_addr, clilen);
            }
            else if (n == SOCKET_ERROR) {
                cerr << "ERROR on UDP recvfrom : Winsock Error Code: " << WSAGetLastError() << endl;
            }
        }
    }

    closesocket(tcp_sockfd);
    closesocket(udp_sockfd);
    WSACleanup();
    return 0;
}