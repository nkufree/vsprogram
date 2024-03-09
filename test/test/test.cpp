#include <iostream>
#include <cstring>

using namespace std;
class Student
{
    string m_num;
    string m_name;
    int m_score;
public:
    Student(string num, string name) :m_num(num), m_name(name) {}
    Student operator=(const int s2) { m_score = s2; return *this; }
    void display() 
    {
        cout << m_num << " " << m_name << " " << m_score;
    }
};


int main()
{
    Student s("01234", "ÕÅÈý");
    s = 95;
    s.display();
}

