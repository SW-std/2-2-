#include <iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<stack>
#include<queue>
using namespace std;



//4번
//class circle {
//	double r;
//public:
//	circle(double ra) : r(ra) {}
//	double radius() const {
//		return r;
//	}
//	//priority_queue 떄문에 연산자 오버로딩이 필요했음
//	bool operator<(const circle& other) const {
//		return r < other.r;
//	}
//};
//int main() {
//	circle c1(1.0), c2(2.0), c3(3.0);
//	stack<circle> st;
//	queue<circle> qu;
//	priority_queue<circle> pr;
//	st.push(c1);
//	st.push(c2);
//	st.push(c3);
//	qu.push(c1);
//	qu.push(c2);
//	qu.push(c3);
//	pr.push(c1);
//	pr.push(c2);
//	pr.push(c3);
//	while (!st.empty()) {
//		cout << st.top().radius() << " ";// 맨 위(가장 나중에 들어간 것) 확인
//		st.pop();// 맨 위(가장 나중에 들어간 것) 제거
//	}
//	cout << "\n";
//	while (!qu.empty()) {
//		cout << qu.front().radius() << " ";// 맨 앞(가장 먼저 들어간 것) 확인
//		qu.pop();// 맨 앞(가장 먼저 들어간 것) 제거
//	}
//	cout << "\n";
//	while (!pr.empty()) {
//		cout << pr.top().radius() << " ";// 가장 우선순위가 높은 요소 확인
//		pr.pop();// 가장 우선순위가 높은 요소 ㅈ제
//	}
//	cout << "\n";
//}
//3번
//int main() {
//    map<string, string> m;   // key: 이름, value: 전화번호
//    int n;
//
//    cout << "저장할 사람 수: ";
//    cin >> n;
//
//    string name, number;
//
//    // 이름과 전화번호를 map에 저장
//    for (int i = 0; i < n; i++) {
//        cout << "\n이름 입력: ";
//        cin >> name;
//        cout << "전화번호 입력: ";
//        cin >> number;
//
//        m[name] = number;  // map은 key가 같으면 자동으로 덮어씀 이전의 정보는 저장되지않음
//    }
//
//    // 검색
//    cout << "\n검색할 이름을 입력하세요: ";
//    cin >> name;
//
//    // map에서 이름 찾기
//    auto it = m.find(name);
//
//    if (it != m.end()) {
//        cout << name << "의 전화번호는 " << it->second << " 입니다.\n";
//    }
//    else {
//        cout << "해당 이름은 전화번호부에 존재하지 않습니다.\n";
//    }
//
//    return 0;
//}
//2번
// int main() {
//    map<int, int> freq;       // key: 입력 정수, value: 등장 횟수
//    int n;
//
//    cout << "입력할 정수 개수: ";
//    cin >> n;
//
//    cout << n << "개의 정수를 입력하세요:\n";
//
//    int x;
//    for (int i = 0; i < n; i++) {
//        cin >> x;
//        freq[x]++;  // 같은 값이 나오면 자동으로 count 증가
//    }
//
//    // 1. map의 멤버를 이용하여 총 입력 정수 개수 구하기
//    int totalCount = 0;
//    long long sum = 0;
//
//    for (auto& p : freq) {
//        totalCount += p.second;   // 전체 입력 개수 = 모든 빈도수 합
//        sum += (long long)p.first * p.second; // 평균 계산을 위한 합
//    }
//
//    // 2. 평균 계산
//    double avg = (double)sum / totalCount;
//
//    // 3. 출력
//
//    cout << "총 입력된 정수 개수: " << totalCount << endl;
//    cout << "평균: " << avg << endl;
//
//    cout << "\n정수별 등장 횟수:\n";
//    for (auto& p : freq) {
//        cout << p.first << " : " << p.second << "개\n";
//    }
//
//    return 0;
//}
////1번
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
