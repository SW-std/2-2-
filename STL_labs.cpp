//#include <iostream>
//#include <vector>
//using namespace std;
//int main(int argc, char const* argv[])
//{
//	vector <int> v1;
//	v1.push_back(10);
//	cout<<sizeof(v1)<<endl;
//	v1.push_back(11);
//	cout << sizeof(v1) << endl;
//	v1.push_back(12);
//	cout << sizeof(v1) << endl;
//	v1.push_back(13);
//	cout << sizeof(v1) << endl;
//	v1.push_back(14);
//	cout << sizeof(v1) << endl;
//}
//#include <vector>
//#include <iostream>
//using namespace std;
//int main()
//{
//    vector<int> v1, v2, v3;
//
//    v1.push_back(10);
//    v1.push_back(20);
//    v1.push_back(30);
//    v1.push_back(40);
//    v1.push_back(50);
//
//    cout << "v1 = ";
//    for (auto& v : v1) {
//        cout << v << " ";
//    }
//    cout << endl;
//
//    v2.assign(v1.begin(), v1.end());
//    cout << "v2 = ";
//    for (auto& v : v2) {
//        cout << v << " ";
//    }
//    cout << endl;
//
//    v3.assign(3, 6);
//    cout << "v3 = ";
//    for (auto& v : v3) {
//        cout << v << " ";
//    }
//    cout << endl;
//
//    v3.assign({ 5, 6, 7 });
//    for (auto& v : v3) {
//        cout << v << " ";
//    }
//    cout << endl;
//
//    int& i = v1.at(0);
//
//    cout << "v1 첫 번째 원소의 값:  " << i << endl;
//
//    if (v1 == v2) cout << "v1과 v2는 같다." << endl;
//    else cout << "v1과 v2는 다르다" << endl;
//
//    i = 80;
//    const int& j = v1.at(0);
//
//    cout << "값을 변경 후 v1 첫 번째 원소의 값:  " << j << endl;
//
//    if (v1 == v2) cout << "v1과 v2는 같다." << endl;
//    else cout << "v1과 v2는 다르다" << endl;
//}
//#include <vector>
//#include <iostream>
//using namespace std;
//
//class square {
//	double width;
//	double height;
//public:
//	square(double w,double h):width(w),height(h) {}
//	double getArea() {
//		return width * height;
//	}
//};
//int main()
//{
//		std::vector<square> squares;
//
//		squares.push_back(square(10.0, 5.0));
//		squares.push_back(square(3.0, 3.0));
//		squares.push_back(square(8.0, 4.0));
//		square &i = squares.at(0);
//		cout<< i.getArea()<<endl;
//}
#include <vector>
#include <iostream>
using namespace std;
int main()
{
	vector<int> v1(5);
	v1.push_back(3);

	*v1.begin() = 10;//v1의 시작점(포인터)을 반환하든 함수에 역참조연산자를통해 시작점에 10을삽입함
	cout << v1.capacity() << endl;
	cout << v1.size() << endl;
	cout << v1.at(0) << endl;
}