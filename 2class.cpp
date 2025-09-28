//#include <iostream>
//#include <utility>
//using namespace std;
//
//class Player {
//    int HP = 100;
//    string name = "";
//    static int count;
//public:
//    Player() {
//        count++;
//        cout<<"플레이어가 생성되었습니다."<<endl;
//    }
//    ~Player() {
//        count--;
//        cout<< "플레이어가 나갔습니다." << endl;
//    }
//    Player(int hp, string n) {
//        count++;
//        name = n;
//        HP = hp;
//    }
//    Player(const Player& other): HP(other.HP),name(other.name) { count++; }
//    //복사생성자 기본형태  : HP(p.HP)는 클래스가생성될때 HP를 메모리에 자리를만듬과동시에 값을 가져옴 기본형태는 바디가 비워져있다
//    Player(Player&& other) noexcept : HP(move(other.HP)) , name(move(other.name)) { count++; }//이동생성자의 프로토타입 noexcept는 예외처리를 하지않는다를 컴파일러에게 알리는 키워드이다.
//    //또한 move함수는 스트링타입과같이 기본 자료형이 아닌 자료형에서 이동을 가능하게해주는함수이고 int와 같은 기본자료형에서는 복사생성자와 다르지않게작동한다. 기본형태는 바디가 비워져있다
//    int getHP() { return HP; }
//    
//    string getname() { return name; }
//
//    int getCount() { return count; }
//    friend int HPreset(int a);
//};
//
//int Player::count = 0;
//int HPreset(int a) {
//    return HP;
//}
//
//
//int main()
//{
//    Player a(80,"암살자");
//    cout << a.getHP() << ", " << a.getname() << endl;
//    Player b(150, "탱커");
//    Player c = b;
//    Player d = move(a);
//
//    cout << a.getCount() << endl;
//    cout << b.getCount() << endl;
//    cout << c.getCount() << endl;
//    cout << d.getCount() << endl;
//    cout << a.getHP() << ", " << a.getname() << endl;
//    cout << b.getHP() << ", " << b.getname() << endl;
//    cout << c.getHP() << ", " << c.getname() << endl;
//    cout << d.getHP() << ", " << d.getname() << endl;
//}
//#include <iostream>
//
//using namespace std;
//
//class Point
//{
//    int x, y;
//    Point(int a, int b) : x{ a }, y{ b } {}
//public:
//    void show() {
//        cout << x << ", " << y << endl;
//    }
//    static Point obj(int a, int b) {
//        return Point(a, b);
//    }
//};
//
//int main(int argc, char const* argv[])
//{
//    Point a = Point::obj(2, 3);
//    a.show();
//
//    return 0;
//}
//#include <iostream>
//using namespace std;
//
//
//class Point {
//	int x, y;
//public:
//	Point(int x =10, int y=20) : x{ x }, y{ y } {}
//	void show() {
//		cout << x << " , " << y << endl;
//	}
//};
//
//int main(int argc, char const* argv[])
//{
//	Point p1(10, 20);
//	Point points[10];
//	p1.show();
//	return 0;
//}
//#include <iostream>
//using namespace std;
//
//class Person {
//    string name;
//    int age;
//public:
//    Person(string n, int a) : name{ n }, age{ a } { //파러미터가 있는 생성자
//        cout << "Constructor with parameter" << endl;
//    }
//    explicit Person(const Person& ref) { //복사 생성자 익스플릭트로 명시된 복사생성자 
//        cout << "User defined Copy constructor" << endl;
//        name = ref.name;
//        age = ref.age;
//    }
//    void show() {
//        cout << name << ", " << age << endl;
//    }
//};
//
//int main(int argc, char const* argv[]) {
//    Person hong("Gil-Dong Hong", 28);  // 파러미터가 있는 생성자 호출
//    Person kim = { "Chul-soo Kim", 30 };   // 파러미터가 있는 생성자 호출
//
//    Person man(hong); // 북사 생성자 호출 (man 객체는 hong 객체의 내용을 복사하여 생성) 
//    Person m1{ kim };
//    man.show();
//    m1.show();
//
//    return 0;
//}
//#include <iostream>
//using namespace std;
//
//class Person {
//    string name;
//    int age;
//public:
//    Person(string n, int a) : name{ n }, age{ a } { //파러미터가 있는 생성자
//        cout << "Constructor with parameter" << endl;
//    }
//
//    void show() {
//        cout << name << ", " << age << endl;
//    }
//};
//
//int main(int argc, char const* argv[])
//{
//    Person hong("Gil-Dong Hong", 28);  // 파러미터가 있는 생성자 호출  
//
//    Person man = hong; // 북사 생성자 호출 (man 객체는 hong 객체의 내용을 복사하여 생성) 
//
//    return 0;
//}
//#include <iostream>
//using namespace std;
//
//class Rect {
//private:
//    int width, height;
//
//public:
//    Rect(int w, int h) : width(w), height(h) {}
//
//    // friend 함수 선언
//    friend int getArea(const Rect& r);
//};
//
//// friend 함수 정의
//int getArea(const Rect& r) {
//    // private 멤버 접근 가능
//    return r.width * r.height;
//}
//
//int main() {
//    Rect r1(3, 4);
//    cout << "넓이: " << getArea(r1) << endl;  // 12 출력
//    return 0;
//}
//#include <iostream>
//using namespace std;
//
//class Engine {
//private:
//    int horsepower;
//
//public:
//    Engine(int hp) : horsepower(hp) {
//        cout << "객체 생성 엔진" << endl;
//    }
//    int gethorsepower() { return horsepower; }
//    // Car 클래스가 Engine의 private 멤버에 접근할 수 있음
//    //friend class Car;
//};
//
//class Car {
//private:
//    Engine engine;
//public:
//    Car(int a) : engine(a) {
//        cout << "객체생성 자동차" << endl;
//    }
//
//    void showSpec() {
//        // Engine의 private 멤버 horsepower 접근 가능
//        cout << "엔진 출력: " << engine.gethorsepower() << " 마력" << endl;
//    }
//};
//
//int main() {
//    Car c1(200);
//    c1.showSpec();  // "엔진 출력: 200 마력"
//    return 0;
//}
#include <iostream>
#include <utility>  // std::move
using namespace std;

class MyVector {
private:
    int* data;
    size_t size;

public:
    // 생성자
    MyVector(size_t n) : size(n) {
        data = new int[n];
        cout << "Constructor: allocate " << size << " ints" << endl;
    }

    // 소멸자
    ~MyVector() {
        delete[] data;
        std::cout << "Destructor: release" << endl;;
    }

    // 복사 생성자
    MyVector(const MyVector& other) : size(other.size) {
        data = new int[size];
        std::copy(other.data, other.data + size, data);
    }

    // 이동 생성자
    MyVector(MyVector&& other) noexcept : data(nullptr), size(0) {
        // 자원 소유권 이전
        data = other.data;
        size = other.size;

        // 원본은 nullptr 상태로 초기화
        other.data = nullptr;
        other.size = 0;
    }

    // 디버그용 출력
    void print() const {
        std::cout << "Vector size: " << size << ", data: " << (void*)data << "\n";
    }
};

int main() {
    MyVector v1(5);      // (1)일반 생성자 로 파라미터값을 size_t에 저장
    MyVector v2 = v1;    // (2)복사생성자로 이미생성된 객체의 멤버변수들의 값을 복사해서 객체를 생성  
    MyVector v3 = std::move(v1);  // (3)이동생성자로 원본 객체의 멤버변수들의 메모리주소를 가져오고 원본을 nullptr로 초기화

    std::cout << "v1: "; v1.print();
    std::cout << "v2: "; v2.print();
    std::cout << "v3: "; v3.print();

    return 0;
}