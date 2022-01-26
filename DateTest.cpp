#include <iostream>
#include "Date.h"

using namespace std;

void Test1(Date &d1);
void Test2(Date &d2);
void Test3(Date &d2);
void Test4(Date &d2);
void Test5(Date &d2);
void Test6(Date &d2);
void Test7(Date &d2);
void Test8(Date &d2);
void Test9(Date &d3, Date &d4);

int main()
{
    cout << "Unit Test for Date" << endl;
    cout << "==================" << endl << endl;

    Date date1;
    Test1(date1); //Test default constructor

    Date date2(9,8,2020);
    Test2(date2); //Test parameterized constructor
    Test3(date2); //Test SetDay()
    Test4(date2); //Test GetDay()
    Test5(date2); //Test SetMonth()
    Test6(date2); //Test GetMonth()
    Test7(date2); //Test SetYear()
    Test8(date2); //Test GetYear()

    Date date3(29,2,2020);
    Date date4(30,2,2020);
    Test9(date3, date4); //Test IsValid()

    return 0;
}

void Test1(Date &d1)
{
    cout << "Test 1" << endl;
    cout << "======" << endl;
    cout << "Initializing date1..." << endl;
    cout << "date1: " << d1 << endl << endl;
}

void Test2(Date &d2)
{
    cout << "Test 2" << endl;
    cout << "======" << endl;
    cout << "Initializing date2..." << endl;
    cout << "date2: " << d2 << endl << endl;
}

void Test3(Date &d2)
{
    cout << "Test 3" << endl;
    cout << "======" << endl;
    d2.SetDay(23);
    cout << "Setting the day of date2 to 23..." << endl;
    cout << "Date2 is now " << d2 << endl << endl;
}

void Test4(Date &d2)
{
    cout << "Test 4" << endl;
    cout << "======" << endl;
    cout << "The day of date2 is " << d2.GetDay() << endl << endl;
}

void Test5(Date &d2)
{
    cout << "Test 5" << endl;
    cout << "======" << endl;
    d2.SetMonth(1);
    cout << "Setting the month of date2 to 1..." << endl;
    cout << "Date2 is now " << d2 << endl << endl;
}

void Test6(Date &d2)
{
    cout << "Test 6" << endl;
    cout << "======" << endl;
    cout << "The month of date2 is " << d2.GetMonth() << endl << endl;
}

void Test7(Date &d2)
{
    cout << "Test 7" << endl;
    cout << "======" << endl;
    d2.SetYear(2015);
    cout << "Setting the year of date2 to 2015..." << endl;
    cout << "Date2 is now " << d2 << endl << endl;
}

void Test8(Date &d2)
{
    cout << "Test 8" << endl;
    cout << "======" << endl;
    cout << "The year of date2 is " << d2.GetYear() << endl << endl;
}

void Test9(Date &d3, Date &d4)
{
    cout << "Test 9" << endl;
    cout << "======" << endl;
    cout << "date3 has been set to 29/2/2020" << endl; //Year 2020 is a leap year
    cout << "date4 has been set to 30/2/2020" << endl;
    cout << "Is date3 valid? " << d3.IsValid() << endl;
    cout << "Is date4 valid? " << d4.IsValid() << endl;
}
