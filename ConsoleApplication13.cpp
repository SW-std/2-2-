// server.cpp : list → 파일 목록 전송 + END 토큰 / 파일명 → 해당 파일 전송
// 빌드: cl /EHsc server.cpp ws2_32.lib

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <iostream>
#include <fstream>
#include <filesystem>

#pragma comment(lib, "ws2_32.lib")
namespace fs = std::filesystem;

#define BUFSIZE 512
#define PORT 9000

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "[서버] WSAStartup 실패\n";
        return 1;
    }

    SOCKET serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSock == INVALID_SOCKET) {
        std::cerr << "[서버] 소켓 생성 실패: " << WSAGetLastError() << "\n";
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "[서버] bind 실패: " << WSAGetLastError() << "\n";
        closesocket(serverSock);
        WSACleanup();
        return 1;
    }

    if (listen(serverSock, 1) == SOCKET_ERROR) {
        std::cerr << "[서버] listen 실패: " << WSAGetLastError() << "\n";
        closesocket(serverSock);
        WSACleanup();
        return 1;
    }

    std::cout << "[서버] 클라이언트 접속 대기 중...\n";

    sockaddr_in clientAddr{};
    int clientAddrSize = sizeof(clientAddr);
    SOCKET clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &clientAddrSize);
    if (clientSock == INVALID_SOCKET) {
        std::cerr << "[서버] accept 실패: " << WSAGetLastError() << "\n";
        closesocket(serverSock);
        WSACleanup();
        return 1;
    }
    std::cout << "[서버] 클라이언트 접속!\n";

    //  명령 처리 루프
    while (true) {
        char cmd[BUFSIZE] = { 0 };
        // 버퍼 오버플로우 방지를 위해 BUFSIZE - 1만큼만 받습니다.
        int recvBytes = recv(clientSock, cmd, BUFSIZE - 1, 0);

        if (recvBytes <= 0) {
            std::cout << "[서버] 클라이언트 종료\n";
            break;
        }

        cmd[recvBytes] = '\0'; // ★ 널 종료 문자 추가
        std::string input = cmd;

        // list 처리
        if (input == "list") {
            std::cout << "[서버] list 명령 수신 → 파일 목록 전송\n";

            for (auto& p : fs::directory_iterator(".")) {
                if (p.is_regular_file()) {
                    // 파일명 뒤에 개행 문자 추가
                    std::string name = p.path().filename().string() + "\n";
                    send(clientSock, name.c_str(), name.size(), 0);
                }
            }

            // 목록 끝 표시
            send(clientSock, "END", 3, 0);

            std::cout << "[서버] 파일 목록 + END 전송 완료\n";
            continue;
        }
        //파일 전송 처리
        std::string filename = input;
        
        // 경로 공격 방지 등을 위해 유효성 검사를 추가할 수 있습니다.

        std::ifstream file(filename, std::ios::binary);

        if (!file.is_open()) {
            std::cout << "[서버] 요청한 파일 없음: " << filename << "\n";
            send(clientSock, "NOFILE", 6, 0);
            continue;
        }

        // 파일 크기 가져오기
        file.seekg(0, std::ios::end);
        long filesize = file.tellg();
        file.seekg(0, std::ios::beg);

        // 파일 크기 전송
        std::string sizeStr = std::to_string(filesize);
        send(clientSock, sizeStr.c_str(), sizeStr.size(), 0);
        std::cout << "[서버] 파일 크기 전송 (" << filesize << " bytes): " << filename << "\n";


        // 파일 내용 전송
        std::cout << "[서버] 파일 내용 전송 시작: " << filename << "\n";

        char buffer[BUFSIZE];
        long sent = 0;

        while (!file.eof()) {
            file.read(buffer, BUFSIZE);
            int r = file.gcount();

            if (r > 0) {
                if (send(clientSock, buffer, r, 0) == SOCKET_ERROR) {
                    std::cerr << "[서버] 전송 오류 발생: " << WSAGetLastError() << "\n";
                    break;
                }
                sent += r;
            }
        }

        file.close();
        std::cout << "[서버] 파일 전송 완료 (" << sent << " bytes): " << filename << "\n";
    }

    closesocket(clientSock);
    closesocket(serverSock);
    WSACleanup();
    return 0;

}
