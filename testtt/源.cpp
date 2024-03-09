#include <iostream>

using namespace std;

class B

{

public:

    ~B() { cout << "~B() is called!" << endl; }

};

class D1 :virtual public B

{

public:

    ~D1() { cout << "~D1() is called" << endl; }

};

class D2 : virtual public B

{

public:

    ~D2() { cout << "~D2() is called!" << endl; }

};

class DD : public D2, public D1

{

public:

    ~DD() { cout << "~DD() is called!" << endl; }

};

int main()

{

    DD dd;

    return 0;

}