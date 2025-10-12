#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <thread>

#pragma comment(lib, "ws2_32.lib")  // WinSock2 라이브러리 연결

using namespace std;

// 클라이언트 처리 스레드 함수
void clientHandler(SOCKET client) {
    char buf[1024];
    int recvLen;

    cout << "[+] 클라이언트 접속" << endl;

    while (true) {
        recvLen = recv(client, buf, sizeof(buf), 0);
        if (recvLen <= 0) break; // 연결 종료 또는 오류 발생

        send(client, buf, recvLen, 0); // Echo 응답
    }

    closesocket(client);
    cout << "[-] 클라이언트 연결 종료" << endl;
}

int main() {
    WSADATA wsa;
    SOCKET server, client;
    sockaddr_in serverAddr{}, clientAddr{};
    int clientSize = sizeof(clientAddr);

    // 1. WinSock 초기화
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        cerr << "WSAStartup 실패" << endl;
        return 1;
    }

    // 2. 서버 소켓 생성
    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == INVALID_SOCKET) {
        cerr << "소켓 생성 실패" << endl;
        WSACleanup();
        return 1;
    }

    // 3. 서버 주소 설정
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(9000);

    // 4. 바인드
    if (bind(server, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cerr << "바인드 실패" << endl;
        closesocket(server);
        WSACleanup();
        return 1;
    }

    // 5. 리슨
    listen(server, SOMAXCONN);
    cout << "서버가 포트 9000에서 실행 중..." << endl;

    // 6. 클라이언트 연결 수락
    while (true) {
        client = accept(server, (sockaddr*)&clientAddr, &clientSize);
        if (client == INVALID_SOCKET) {
            cerr << "accept 실패" << endl;
            continue;
        }

        // 클라이언트당 스레드 생성
        thread(clientHandler, client).detach();
    }

    // 7. 종료 처리
    closesocket(server);
    WSACleanup();
    return 0;
}
