#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

// 서버 설정
const int PORT = 8080;
const char* SERVER_IP = "127.0.0.1";
const int BUFFER_SIZE = 1024;

// 전역 또는 메인 함수에서 접근 가능한 상태 변수
SOCKET current_sockfd = INVALID_SOCKET;
bool is_tcp_mode = false;

void error(const char* msg) {
    // std:: 대신 cerr 사용
    cerr << msg << " : Winsock Error Code: " << WSAGetLastError() << endl;

    if (current_sockfd != INVALID_SOCKET) {
        closesocket(current_sockfd);
    }
    WSACleanup();
    exit(1);
}

void initialize_connection(const string& type) {
    struct sockaddr_in serv_addr;

    // 소켓 생성
    if (type == "tcp") {
        current_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        is_tcp_mode = true;
    }
    else if (type == "udp") {
        current_sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        is_tcp_mode = false;
    }
    else {
        cerr << "잘못된 프로토콜 타입입니다. 'tcp' 또는 'udp'를 사용하세요." << endl;
        return;
    }

    if (current_sockfd == INVALID_SOCKET) {
        error("소켓이 이미 열려있습니다.");
    }

    // 서버 주소 설정
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        closesocket(current_sockfd);
        error("잘못된.지원하지 않는 주소");
    }

    if (is_tcp_mode) {
        // TCP: 연결 시도
        if (connect(current_sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
            closesocket(current_sockfd);
            current_sockfd = INVALID_SOCKET;
            error("ERROR connecting to TCP server");
        }
        cout << "tcp 설정 tcp로 송수신 합니다" << endl;
    }
    else {
        // UDP: send/recv 사용을 위해 서버 주소 연결
        if (connect(current_sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
        }
        cout << "udp 설정 udp로 송수신 합니다" << endl;
    }
}

void send_message(const string& message) {
    char buffer[BUFFER_SIZE];
    int n;

    if (current_sockfd == INVALID_SOCKET) {
        cout << "Connection not established. Please enter 'tcp' or 'udp' first." << endl;
        return;
    }

    if (is_tcp_mode) {
        // TCP: send/recv 사용

        // 1. 메시지 전송
        n = send(current_sockfd, message.c_str(), message.length(), 0);
        if (n == SOCKET_ERROR) {
            cout << "TCP Send Failed. Connection lost. Enter 'exit' or reconnect." << endl;
            closesocket(current_sockfd);
            current_sockfd = INVALID_SOCKET;
            return;
        }

        // 2. 응답 수신
        memset(buffer, 0, BUFFER_SIZE);
        n = recv(current_sockfd, buffer, BUFFER_SIZE - 1, 0);

        if (n > 0) {
            buffer[n] = '\0';
            cout << "\n[TCP Server Response]: " << buffer << endl;
        }
        else if (n == 0) {
            cout << "Server closed the TCP connection." << endl;
            closesocket(current_sockfd);
            current_sockfd = INVALID_SOCKET;
        }
        else {
            cout << "TCP Recv Failed. Connection error." << endl;
            closesocket(current_sockfd);
            current_sockfd = INVALID_SOCKET;
        }

    }
    else {
        // UDP: send/recv 사용 (서버 주소에 연결된 상태)

        // 1. 메시지 전송
        n = send(current_sockfd, message.c_str(), message.length(), 0);
        if (n == SOCKET_ERROR) {
            cout << "UDP Send Failed." << endl;
            return;
        }

        // 2. 응답 수신
        memset(buffer, 0, BUFFER_SIZE);
        n = recv(current_sockfd, buffer, BUFFER_SIZE - 1, 0);

        if (n > 0) {
            buffer[n] = '\0';
            cout << "\n[UDP Server Response]: " << buffer << endl;
        }
        else if (n == SOCKET_ERROR) {
            cout << "UDP Recv Failed." << endl;
        }
    }
}

int main() {
    // Winsock 초기화
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "WSAStartup failed with error: " << WSAGetLastError() << endl;
        return 1;
    }

    string input, message;

    cout << "윈속 채팅 클라이언트" << endl;
    cout << "1.tcp나 udp 중 프로토콜을 입력하세요" << endl;
    cout << "2. 한번 설정한 프로토콜은 변경 할 수 없습니다" << endl;

    while (true) {
        cout << "\n> ";
        getline(cin, input);

        if (input == "exit") {
            break;
        }

        if (current_sockfd == INVALID_SOCKET) {
            if (input == "tcp" || input == "udp") {
                initialize_connection(input);
                continue;
            }
            else {
                cout << "Please set the protocol first. Enter 'tcp' or 'udp'." << endl;
                continue;
            }
        }
        else {
            if (input.empty()) continue;
            send_message(input);
        }
    }

    // 종료 시 소켓 및 Winsock 해제
    if (current_sockfd != INVALID_SOCKET) {
        closesocket(current_sockfd);
    }
    WSACleanup();
    return 0;
}