#include "..\..\Common.h"
#include <string>
#include<algorithm>
#define SERVERPORT 9000
#define BUFSIZE    512
using namespace std;

class addrname {
	string name;
	string ipaddr;
public:
	addrname(string a,string b) :name(a),ipaddr(b)  {};
	addrname() {}
	string getname() { return name; }
	string getipaddr() { return ipaddr; }

};

int main(int argc, char* argv[])
{
	int retval;
	int count = 0;
	bool isfriend = false;

	//친구목록
	addrname friends[] = { addrname("김상우", "113.198.243.183"), addrname("김연우", "113.198.243.179"), addrname("김경건", " 113.198.243.181"), addrname("오지석", "113.198.243.174"), addrname("김주영", "113.198.243.195")};
	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// 소켓 생성
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	// bind()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(sock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// 데이터 통신에 사용할 변수
	struct sockaddr_in clientaddr;
	int addrlen;
	char buf[BUFSIZE + 1];

	// 클라이언트와 데이터 통신
	while (1) {
		// 데이터 받기
		addrlen = sizeof(clientaddr);
		retval = recvfrom(sock, buf, BUFSIZE, 0,
			(struct sockaddr *)&clientaddr, &addrlen);
		count++;
		if (retval == SOCKET_ERROR) {
			err_display("recvfrom()");
			break;
		}
		for (int i = 0; i < sizeof(friends); i++) {
			if (strcmp(buf, friends[i].getname().c_str()) == 0) {
				isfriend = true;
				break;
			}
			else {
				isfriend = false;
			}
		}
		if(isfriend)
		{
			retval = sendto(sock, buf, retval, 0,
				(struct sockaddr*)&clientaddr, sizeof(clientaddr));
			if (retval == SOCKET_ERROR) {
				err_display("sendto()");
				break;
			}
		}
		// 받은 데이터 출력
		buf[retval] = '\0';
		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
		printf("[UDP/%s:%d] %s %d번째\n", addr, ntohs(clientaddr.sin_port), buf,count);
	}

	// 소켓 닫기
	closesocket(sock);

	//친구목록 제거
	delete[] friends;
	// 윈속 종료
	WSACleanup();
	return 0;
}
