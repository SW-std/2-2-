//#include <iostream>
//using namespace std;
//
//class Animal {
//public:
//    virtual void speak() {
//        cout << "������ �Ҹ��� ���ϴ�." << endl;
//    }
//};
//
//class Dog : public Animal {
//public:
//    void speak() override {
//        cout << "�۸�!" << endl;
//    }
//};
//
//class Cat : public Animal {
//public:
//    void speak() override {
//        cout << "�߿�!" << endl;
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
//class Derived : public Base {//���� �����ڴ� �⺻������ �� ���ȼ����� ���� ���������ڸ��켱���ϸ� �ۺ����� ���������ڸ������� �θ��� public�� protected�� private���� �����Ѵ�
////private: ��� ���������ڰ� �����̺��� ���
////    int a;
////    int b;
////    int c;
////protected:��� ���������ڰ� ������Ʈ�� ���
////    int b;
////    int c;
////private:
////     int a;
////��� ���������ڰ� �ۺ��� ���
//private:
//    int a;
//protected:
//    int b;
//public:
//    int c;
//
//public:
//    void func() {
//        //a; //���� �Ұ���
//        b; //�ڽ� Ŭ������ ���� ��� (protected)
//        c; //���� ���
//    }
//};
//
//// �ڽ��� �ڽ� Ŭ����
//class Derived2 : public Derived {
//public:
//    void func() {
//        //a; //���� �Ұ���
//        b; //�ڽ� Ŭ������ ���� ��� (protected)
//        c; //���� ���
//    }
//};
////�ܺο��� ����
//int main() {
//    Derived A;
//    //A.a = 10; //�ܺο��� ���� �Ұ��� (private)
//    //A.b = 10; //�ܺο��� ���� �Ұ��� (protected)
//    A.c = 10; //���� ���
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
	Student k("����", 24, 'c', 2);
	k.get_info();
	//k.getinfo();�θ��Ǹ�� �Լ��� ���������ڰ� public�ϰ�쿡�� ��밡��
}
//#include <iostream>
//using namespace std;
//
//class Parent {
//public:
//    Parent() { cout << "Parent ������ ȣ��" << endl; }
//    ~Parent() { cout << "Parent �Ҹ��� ȣ��" << endl; }
//};
//
//class Child : public Parent {
//public:
//    Child() { cout << "Child ������ ȣ��" << endl; }
//    ~Child() { cout << "Child �Ҹ��� ȣ��" << endl; }
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
//        // ��ȣ���� �����Ƿ� :: �����ڷ� �θ� ������ ���
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
//        hello();   // ���� ��ȣ�� ����
//        x = 42;    // A�� �ϳ��� ���� > ���� ����
//        cout << "x = " << x << endl;
//    }
//};
//
//int main() {
//    D obj;
//    obj.show();
//    return 0;
//}
