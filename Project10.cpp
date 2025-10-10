// Project10.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <iostream>
using namespace std;

template <typename T>

class con {
	T* Data;
	int a;//배열의 크기
public:
	con(int b) {//생성자 
		a = b;
		Data = new T[a]();
	}
	~con() {//가상 메모리 할당된 배열 제거
		delete[] Data;
	}
	T front() {//배열의 첫번쨰값
			return Data[0];
	}
	T back() {//배열의 마지막값
			return Data[a - 1];
	}
	int size(){//배열의 사이즈 출력
		return a;
	}
	bool empty(int idx) {//배열의 특정 요소에 값이 있는지 없는지 판별 
		if (idx < 0 || idx >= a) {
			cout << "잘못된 인덱스입니다." << endl;
			return false;
		}
		if (Data[idx] == T()) {
			cout << "값없음" << endl;
			return false;
		}
		else{
			cout << idx << "번쨰 요소는: " <<Data[idx]<< endl;
			return true;
		}

	}
	int capacity() {//배열의 크기 출력
		return sizeof(con);
	}
	T at(int idx) {
		if (idx < 0 || idx >= a) {//배열의 인덱스의 값이 올지않으면 기본값을 반환시키며 잘못된 인덱스 출력
			cout << idx << "은(는) 잘못된 인덱스입니다." << endl;
			return T();
		}
		else
		{
			if (Data[idx] != T())//기본값이 아니면 출력
			{
				cout << idx << "번째 요소는" << Data[idx] << endl;
				return Data[idx];
			}
			else {//기본값일 경우 비었음 출력
				cout << idx << "번째 요소는 비었음" << endl;
				return Data[idx];
			}
		}
	}
	void insert(int idx, T data) {//idx번째 에 data값을 넣어줌
		Data[idx] = data;
	}
	void push_back(T data) {//배열의 마지막 칸에 data값을 넣어줌
		Data[a - 1] = data;
	}
	void pop_back() {//마지막 요소를 빈값으로 만듦or 초기화 라고도함
		Data[a - 1] = T();
	}
	void showAll() {//모든 요소 출력
		for (int i = 0; i < a; i++)
		{
			if (empty(i))
				cout << i << "번째 요소: " << Data[i] << endl;
			else
				cout << i << "번째 요소: (값 없음)" << endl;
		}
		
		cout << "출력종료"<<endl;
	}
};
int main() {
	con<int> a(10);
	cout << "베열의 첫번째 요소" << a.front() << endl;
	a.push_back(50);
	cout << "배열의 마지막 요소 " << a.back() << endl;
	a.at(1);
	a.insert(5, 30);
	a.empty(5);
	a.showAll();
	a.pop_back();
	a.capacity();
	a.at(10);
	con<string> b(10);
	cout << "베열의 첫번째 요소" << b.front() << endl;
	b.push_back("안농");
	cout << "배열의 마지막 요소 " << b.back()  << endl;
	b.at(1);
	b.insert(5, "나는");
	b.empty(5);
	b.showAll();
	b.pop_back();
	b.capacity();
	b.at(10);
}
