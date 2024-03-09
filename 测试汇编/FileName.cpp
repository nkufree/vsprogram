#include <stdio.h>
#include<iostream>
using namespace std;

int main(int argc, char* argv[])
{
    char str[200];
    fgets(str, 200, stdin);
    printf(str);
    
    return 0;
}
/*
int formatstring_func2(int argc, char* argv[])
{
    char buffer[100];
    sprintf_s(buffer, argv[1]);
    return 0;
}

int main(int argc, char* argv[])
{
    char a[100] = "100%n";
    int b = 0;
    printf(a,&b);
    cout << a << endl;
    cout << b;
    //formatstring_func2(argc,argv);
    return 0;
}*/
/*
int add(int a, int b)
{
    int c = a + b;
    return c;
}

int main()
{
    int x;
    x = 1;
    cin >> x;
    x = add(x, x + 1);
    cout << hex << x << endl;
    
    return 0;
}*/
/*
class A {
public:
    int m_a;
    A(){}
    A(int a):m_a(a){}
    void virtual getA() { cout << "A::getA" << endl; }

};

class B: public A {
public:
    int m_b;
    B(){}
    B(int b):m_b(b){}
    //void getA() { cout << "B::getA" << endl; }
};

int main()
{
    B b;
    b.getA();
    return 0;
}*/