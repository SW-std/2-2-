// STL_problems.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;

int main() {
	map<int, int> m;
	int count = 0;
	int a;
	int b;
	do{
		cin >> a;
		m[a];
		cin >> b;
		if (m[a] == m[b]) {
			m[a]++;
		}
	} while (count < 10);
	cout << m[a] << endl;
}
//1번
//int average(const vector<int> &a) {
//	int all = 0;
//	for (auto i : a) { all += i; }
//	return all / a.size();
//}
//int same(vector<int>& a)
//{
//	int count = 0;
//	for (int i = 0; i < a.size(); i++) {
//		for (int j = i + 1; j < a.size(); j++) {
//			if (a[i] == a[j]) {
//				count++;
//			}
//		}
//	}
//	return count;
//}
//int main()
//{
//	vector<int> v;
//	int a;
//	do{
//		cin >> a;
//		if(a != 0)
//		{
//			v.push_back(a);
//		}
//	} while (a != 0);
//	cout << "입력된 정수의 갯수 :" << v.size()<<endl;
//	cout <<"같은 값 갯수: " << same(v) << endl;
//	cout<<"평균값은: " << average(v) <<"이다"<< endl;
//}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
