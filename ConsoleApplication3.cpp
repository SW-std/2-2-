// server.cpp : 간단한 TCP PNG 파일 전송 서버
// 빌드 명령: cl /EHsc server.cpp ws2_32.lib

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <iostream>
#include <fstream>

#pragma comment(lib, "ws2_32.lib")
#include <filesystem>

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData); // WinSock 초기화

    std::cout << "현재 실행 경로: " << std::filesystem::current_path() << std::endl;
    SOCKET serverSock = socket(AF_INET, SOCK_STREAM, 0); // TCP 소켓 생성

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;  // 모든 IP에서 접속 허용
    serverAddr.sin_port = htons(9000);        // 포트 번호 9000 사용

    // 소켓에 주소 바인딩
    bind(serverSock, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

    // 클라이언트 접속 대기
    listen(serverSock, 1);
    std::cout << "클라이언트 접속 대기 중...\n";

    sockaddr_in clientAddr;
    int clientAddrSize = sizeof(clientAddr);
    SOCKET clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &clientAddrSize);
    std::cout << "클라이언트 접속!\n";

    // PNG 파일 열기
    std::ifstream file("test.png", std::ios::binary);
    if (!file) {
        std::cerr << "test.png 파일을 열 수 없습니다.\n";
        closesocket(clientSock);
        closesocket(serverSock);
        WSACleanup();
        return 1;
    }

    // 파일 크기 계산
    file.seekg(0, std::ios::end);
    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    std::cout << "파일 크기: " << fileSize << " 바이트\n";

    // 먼저 파일 크기를 클라이언트에 전송
    send(clientSock, reinterpret_cast<const char*>(&fileSize), sizeof(fileSize), 0);

    // 파일 데이터를 읽어서 전송
    char buffer[1024];
    while (!file.eof()) {
        file.read(buffer, sizeof(buffer));
        int bytesRead = file.gcount();
        send(clientSock, buffer, bytesRead, 0);
    }

    std::cout << "test.png 전송 완료!\n";

    // 정리
    file.close();
    closesocket(clientSock);
    closesocket(serverSock);
    WSACleanup();

    return 0;
}
