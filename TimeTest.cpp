#include <iostream>
#include "Time.h"

using namespace std;

void Test1(Time &t1);
void Test2(Time &t2);
void Test3(Time &t2);
void Test4(Time &t2);
void Test5(Time &t2);
void Test6(Time &t2);

int main()
{
    cout << "Unit Test for Time" << endl;
    cout << "==================" << endl << endl;

    Time time1;
    Test1(time1); //Test default constructor

    Time time2(12,45);
    Test2(time2); //Test parameterized constructor
    Test3(time2); //Test SetHour()
    Test4(time2); //Test GetHour()
    Test5(time2); //Test SetMinute()
    Test6(time2); //Test GetMinute()

    return 0;
}

void Test1(Time &t1)
{
    cout << "Test 1" << endl;
    cout << "======" << endl;
    cout << "Initializing time1..." << endl;
    cout << "time1: " << t1 << endl << endl;
}

void Test2(Time &t2)
{
    cout << "Test 2" << endl;
    cout << "======" << endl;
    cout << "Initializing time2..." << endl;
    cout << "time2: " << t2 << endl << endl;
}

void Test3(Time &t2)
{
    cout << "Test 3" << endl;
    cout << "======" << endl;
    t2.SetHour(5);
    cout << "Setting the hour of time2 to 5..." << endl;
    cout << "Time2 is now " << t2 << endl << endl;
}

void Test4(Time &t2)
{
    cout << "Test 4" << endl;
    cout << "======" << endl;
    cout << "The hour of time2 is " << t2.GetHour() << endl << endl;
}

void Test5(Time &t2)
{
    cout << "Test 5" << endl;
    cout << "======" << endl;
    t2.SetMinute(59);
    cout << "Setting the minute of time2 to 59..." << endl;
    cout << "Time2 is now " << t2 << endl << endl;
}

void Test6(Time &t2)
{
    cout << "Test 6" << endl;
    cout << "======" << endl;
    cout << "The minute of time2 is " << t2.GetMinute() << endl;
}
