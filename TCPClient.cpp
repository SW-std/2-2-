#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h> // inet_pton을 위해 필요
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib")

#define SERVERIP    "127.0.0.1"
#define SERVERPORT  9000
#define BUFSIZE     512

// 파일 다운로드 로직을 함수로 분리하여 가독성 높임
void DownloadFile(SOCKET sock, const std::string& filename);

int main()
{
    // 1. Winsock 초기화
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup 실패\n");
        return 1;
    }

    // 2. 소켓 생성
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("socket 생성 실패: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // 3. 서버 주소 설정
    sockaddr_in serveraddr{};
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERVERPORT);
    // inet_pton은 <ws2tcpip.h> 필요
    if (inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr) <= 0) {
        printf("잘못된 IP 주소\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // 4. 연결 시도
    if (connect(sock, (sockaddr*)&serveraddr, sizeof(serveraddr)) == SOCKET_ERROR) {
        printf("연결 실패: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    printf("서버에 연결되었습니다. (IP: %s, Port: %d)\n", SERVERIP, SERVERPORT);
    printf("사용 가능한 명령어: list, [파일명]\n\n");

    // 5. 메인 루프
    while (1)
    {
        printf("> ");
        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) continue;

        // 연결 종료 처리
        if (input == "quit" || input == "exit") {
            send(sock, input.c_str(), input.size(), 0);
            printf("클라이언트 종료.\n");
            break;
        }

        // 명령 전송
        send(sock, input.c_str(), input.size(), 0);

        // ==== LIST 요청 처리 ====
        if (input == "list")
        {
            char buf[BUFSIZE];
            printf("\n=== 서버 파일 목록 ===\n");

            // 서버가 보내는 "END" 문자열까지 목록을 수신
            while (1)
            {
                // 목록은 한 줄씩 수신되므로, BUFSIZE 만큼 받음
                int retval = recv(sock, buf, BUFSIZE - 1, 0);
                if (retval <= 0) {
                    printf("서버 연결 끊김.\n");
                    goto cleanup;
                }
                buf[retval] = '\0'; // 널 종료 문자 추가

                // 서버가 목록 전송을 완료했다는 신호 ("END" 가정)
                if (strcmp(buf, "END") == 0)
                    break;

                printf("%s\n", buf);
            }
            printf("======================\n\n");
            // list 요청 처리가 끝났으므로, 다음 명령을 받기 위해 루프 시작으로 돌아감
            continue;
        }

        // ==== 파일 요청 (list 이외의 모든 입력) 처리 ====
        DownloadFile(sock, input);
    }

cleanup:
    closesocket(sock);
    WSACleanup();
    return 0;
}


// 파일을 다운로드하는 함수
void DownloadFile(SOCKET sock, const std::string& filename)
{
    char buf[BUFSIZE];

    // 1. 파일 크기 수신 (서버가 NOFILE 또는 크기를 보냄)
    int retval = recv(sock, buf, BUFSIZE - 1, 0);
    if (retval <= 0) {
        printf("서버 연결 끊김.\n");
        return;
    }
    buf[retval] = '\0';

    // 2. 서버가 파일 없음 처리
    if (strcmp(buf, "NOFILE") == 0) {
        printf("[클라이언트] 서버에 '%s' 파일 없음.\n\n", filename.c_str());
        return;
    }

    // 3. 파일 크기 변환 및 출력
    int fileSize = atoi(buf);
    if (fileSize <= 0) {
        printf("[클라이언트] 서버로부터 유효하지 않은 파일 크기 (%d) 수신.\n\n", fileSize);
        return;
    }
    printf("[클라이언트] 파일 크기: %d bytes\n", fileSize);

    // 4. 파일 다운로드 및 저장
    FILE* fp = NULL;
    // 이진 모드 ('wb')로 파일 열기
    if (fopen_s(&fp, filename.c_str(), "wb") != 0 || fp == NULL) {
        printf("[클라이언트] 로컬 파일 '%s' 열기 실패.\n", filename.c_str());
        return;
    }

    int received = 0;
    while (received < fileSize)
    {
        // 남은 크기 또는 BUFSIZE 중 더 작은 크기만큼 수신 요청
        int receive_len = (fileSize - received) > BUFSIZE ? BUFSIZE : (fileSize - received);
        retval = recv(sock, buf, receive_len, 0);

        if (retval <= 0) {
            printf("[클라이언트] 파일 수신 중 오류 발생 또는 서버 연결 끊김.\n");
            break;
        }

        // 수신된 데이터를 파일에 기록
        fwrite(buf, 1, retval, fp);
        received += retval;
    }

    // 5. 완료 처리
    fclose(fp);

    if (received == fileSize) {
        printf("[클라이언트] 파일 저장 완료: %s (%d/%d bytes)\n\n", filename.c_str(), received, fileSize);
    }
    else {
        printf("[클라이언트] 파일 다운로드 불완전: %s (%d/%d bytes)\n\n", filename.c_str(), received, fileSize);
    }
}