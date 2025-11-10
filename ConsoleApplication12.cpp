// client.cpp : 간단한 TCP PNG 파일 수신 클라이언트
// 빌드: cl /EHsc client.cpp ws2_32.lib

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <iostream>
#include <fstream>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData); // WinSock 초기화

    SOCKET clientSock = socket(AF_INET, SOCK_STREAM, 0); // TCP 소켓 생성

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 서버 주소 (로컬)
    serverAddr.sin_port = htons(9000);                   // 서버 포트

    // 서버에 연결 시도
    if (connect(clientSock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "[클라이언트] 서버에 연결할 수 없습니다.\n";
        closesocket(clientSock);
        WSACleanup();
        return 1;
    }

    std::cout << "[클라이언트] 서버에 연결되었습니다.\n";

    // 먼저 파일 크기 받기
    std::streamsize fileSize = 0;
    int received = recv(clientSock, reinterpret_cast<char*>(&fileSize), sizeof(fileSize), 0);
    if (received != sizeof(fileSize)) {
        std::cerr << "[클라이언트] 파일 크기 수신 실패.\n";
        closesocket(clientSock);
        WSACleanup();
        return 1;
    }

    std::cout << "[클라이언트] 파일 크기: " << fileSize << " 바이트\n";

    // PNG 파일로 저장 (이제 txt 아님)
    std::ofstream outFile("received.png", std::ios::binary);

    char buffer[1024];
    std::streamsize totalReceived = 0;

    // 정확히 fileSize만큼 수신
    while (totalReceived < fileSize) {
        int bytesReceived = recv(clientSock, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) break;
        outFile.write(buffer, bytesReceived);
        totalReceived += bytesReceived;
    }

    std::cout << "[클라이언트] 파일 수신 완료! (" << totalReceived << " 바이트)\n";

    // 정리
    outFile.close();
    closesocket(clientSock);
    WSACleanup();

    return 0;
}
