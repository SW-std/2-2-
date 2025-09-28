#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_PORT 9000   
#define BUFSIZE     512

int main() {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup() 실패\n");
        return 1;
    }

    SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock == INVALID_SOCKET) {
        printf("socket() 실패: %d\n");
        WSACleanup();
        return 1;
    }

    //의 파라미터로 넣어주는값을 수동으로 정의
    sockaddr_in serveraddr;                           //ipv4 구조체
    memset(&serveraddr, 0, sizeof(serveraddr));       // 메모리에 있는값 0으로 초기화
    serveraddr.sin_family = AF_INET;                  // ip프로토콜버젼
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);   //  모든 IP
    serveraddr.sin_port = htons(SERVER_PORT);         //  #define 포트 사용
    
    //수동으로 넣어준 데이터를 바인드함수를 통해 확인 -1이 반환되면 에러로확인
    if (bind(listen_sock, (sockaddr*)&serveraddr, sizeof(serveraddr)) == SOCKET_ERROR) {
        printf("bind() 실패: %d\n");
        closesocket(listen_sock);
        WSACleanup();
        return 1;
    }
    else
        printf("바인드 성공\n");

    if (listen(listen_sock, SOMAXCONN) == SOCKET_ERROR) {
        printf("listen() 실패: %d\n");
        closesocket(listen_sock);
        WSACleanup();
        return 1;
    }
    else
        printf("클라이언트 대기중\n");

    sockaddr_in clientaddr;
    int addrlen = sizeof(clientaddr);
    SOCKET client_sock = accept(listen_sock, (sockaddr*)&clientaddr, &addrlen);
    if (client_sock == INVALID_SOCKET) {
        printf("accept() 실패: %d\n");
        closesocket(listen_sock);
        WSACleanup();
        return 1;
    }
    else
        printf("클라이언트 연결 완료\n");

    char addrbuf[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &clientaddr.sin_addr, addrbuf, sizeof(addrbuf));


    closesocket(client_sock);
    closesocket(listen_sock);
    WSACleanup();
    return 0;
}
