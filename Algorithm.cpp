#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 1. sort를 위한 사용자 정의 비교 함수
bool compareDescending(int a, int b) {
    return a > b; // 내림차순 (a가 b보다 크면 true)
}

template <typename T>//템플릿으로 출력 구현
void print_vector(const vector<T> &v1) {
    for (auto a: v1) {
        cout << a << "  ";
    }
    cout << endl;
}
int main() {
    vector<int> v = {4, 1, 8, 3, 4, 7, 2};
    print_vector(v);

    // 1. sort (정렬)
    vector<int> v_sorted = v; // 복사본 생성 원본 형태 유지
    sort(v_sorted.begin(), v_sorted.end());
    cout << "1. sort (오름차순): ";
    for (int x : v_sorted) cout << x << " ";
    cout << endl;

    // sort (내림차순, 사용자 함수 사용(비교군이 기본 자료형이 아닌경우에도 사용해야함))
    sort(v_sorted.begin(), v_sorted.end(), compareDescending);
    cout << "   sort (내림차순): ";
    for (int x : v_sorted) cout << x << " ";
    cout << endl;

    // 2. find (검색)
    int findto = 8;
    auto it_find = find(v.begin(), v.end(), findto);//이터레이터 자동 삽입 
    if (it_find != v.end()) {
        cout << "2. find: 값 " << findto << "를 찾았습니다. 인덱스: " << distance(v.begin(), it_find) << endl;
    } else {
        cout << "2. find: 값을 찾지 못했습니다." << endl;
    }

    // 3. binary_search (이진 탐색)
    cout << "3. binary_search: 정렬된 벡터에 3이 존재? " << (binary_search(v_sorted.begin(), v_sorted.end(), 3) ? "Yes" : "No") << endl;

    // 4. count (개수 세기)
    int count_to = count(v.begin(), v.end(), 4);
    cout << "4. count: 벡터에 4는 " << count_to << "개 있습니다." << endl;

    // 5. for_each (범위 순회 및 함수 적용)
    cout << "5. for_each (출력): ";
    for_each(v.begin(), v.end(), [](int n) {
        cout << n * 2 << " "; // 모든 요소를 2배 하여 출력
    });
    cout << endl;

    // 6. reverse (순서 뒤집기)
    vector<int> v_reverse = {1, 2, 3, 4, 5};
    reverse(v_reverse.begin(), v_reverse.end());
    cout << "6. reverse: 1 2 3 4 5 -> ";
    for (int x : v_reverse) cout << x << " ";
    cout << endl;
    
    // 7. transform (요소 변환)
    vector<int> v_input = {1, 2, 3, 4};
    vector<int> v_output(v_input.size());
    // v_input의 모든 요소에 +10을 한 결과를 v_output에 저장
    transform(v_input.begin(), v_input.end(), v_output.begin(), [](int n) {
        return n + 10;
    });
    cout << "7. transform: 1 2 3 4 -> ";
    for (int x : v_output) cout << x << " ";
    cout << endl;

    return 0;
}