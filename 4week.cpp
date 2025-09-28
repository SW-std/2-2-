//#include <iostream>
//using namespace std;
//
//class Animal {
//public:
//    virtual void speak() {
//        cout << "동물이 소리를 냅니다." << endl;
//    }
//};
//
//class Dog : public Animal {
//public:
//    void speak() override {
//        cout << "멍멍!" << endl;
//    }
//};
//
//class Cat : public Animal {
//public:
//    void speak() override {
//        cout << "야옹!" << endl;
//    }
//};
//
//int main() {
//
//    Animal a1;
//    Dog a2;
//    Cat a3;
//
//    a1.speak();
//    a2.speak();
//    a3.speak();
//
//    return 0;
//}
//#include <iostream>
//using namespace std;
//
//class Base {
//private:
//    int a;
//protected:
//    int b;
//public:
//    int c;
//};
//class Derived : public Base {//접근 지정자는 기본적으로 더 보안수준이 높은 접근지정자를우선시하며 퍼블릭으로 접근지정자를놓으면 부모의 public과 protected를 private으로 적용한다
////private: 상속 접근지정자가 프라이빗의 경우
////    int a;
////    int b;
////    int c;
////protected:상속 접근지정자가 프로텍트의 경우
////    int b;
////    int c;
////private:
////     int a;
////상속 접근지정자가 퍼블릭인 경우
//private:
//    int a;
//protected:
//    int b;
//public:
//    int c;
//
//public:
//    void func() {
//        //a; //접근 불가능
//        b; //자식 클래스는 접근 허용 (protected)
//        c; //접근 허용
//    }
//};
//
//// 자식의 자식 클래스
//class Derived2 : public Derived {
//public:
//    void func() {
//        //a; //접근 불가능
//        b; //자식 클래스는 접근 허용 (protected)
//        c; //접근 허용
//    }
//};
////외부에서 접근
//int main() {
//    Derived A;
//    //A.a = 10; //외부에서 접근 불가능 (private)
//    //A.b = 10; //외부에서 접근 불가능 (protected)
//    A.c = 10; //접근 허용
//    return 0;
//}
#include<iostream>

using namespace std;

class Person {
	string name;
	int age;

protected:
	Person(string na, int a) : name(na), age(a) {}
	void getinfo() {
		cout << name << ", " << age;
	}
};

class Student : public Person {
	char grade;
	int year;
public:
	Student(string na, int a, char g, int y) : Person(na, a), grade(g), year(y) {}
	void get_info() {
		getinfo();
		cout <<", " << grade << ", " << year << endl;
 	}
};

int main() {
	Student k("김상우", 24, 'c', 2);
	k.get_info();
	//k.getinfo();부모의멤버 함수의 접근지정자가 public일경우에만 사용가능
}
//#include <iostream>
//using namespace std;
//
//class Parent {
//public:
//    Parent() { cout << "Parent 생성자 호출" << endl; }
//    ~Parent() { cout << "Parent 소멸자 호출" << endl; }
//};
//
//class Child : public Parent {
//public:
//    Child() { cout << "Child 생성자 호출" << endl; }
//    ~Child() { cout << "Child 소멸자 호출" << endl; }
//};
//
//int main() {
//    Child c;
//}
//#include <iostream>
//using namespace std;
//
//class A {
//public:
//    void hello() { cout << "Hello from A" << endl; }
//};
//
//class B : public A {};
//class C : public A {};
//class D : public B, public C {
//public:
//    void show() {
//        // 모호성이 있으므로 :: 연산자로 부모 범위를 명시
//        B::hello();
//        C::hello();
//    }
//};
//
//int main() {
//    D obj;
//    obj.show();
//    return 0;
//}
//#include <iostream>
//using namespace std;
//
//class A {
//public:
//    int x;
//    void hello() { cout << "Hello from A" << endl; }
//};
//
//class B : virtual public A {};
//class C : virtual public A {};
//class D : public B, public C {
//public:
//    void show() {
//        hello();   // 이제 모호성 없음
//        x = 42;    // A는 하나만 존재 > 공유 가능
//        cout << "x = " << x << endl;
//    }
//};
//
//int main() {
//    D obj;
//    obj.show();
//    return 0;
//}
