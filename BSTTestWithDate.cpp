#include <iostream>
#include <fstream>
#include <sstream>
#include "BST.h"
#include "Date.h"

using namespace std;

void ProcessNode(Date &data);
void Test1(BST<Date> &dateTree1);
void Test2(BST<Date> &dateTree1);
void Test3(BST<Date> &dateTree1);
void Test4(BST<Date> &dateTree1);
void Test5(BST<Date> &dateTree1, BST<Date> &dateTree2);
void Test6(BST<Date> &dateTree1, BST<Date> &dateTree2);
void Test7(BST<Date> &dateTree1);
void Test8(BST<Date> &dateTree1);


int main()
{
    cout << "Unit Test for BST<Date>" << endl;
    cout << "==========================" << endl << endl;

    BST<Date> dateTree1;
    Test1(dateTree1); //Test constructor
    Test2(dateTree1); //Test Insert()
    Test3(dateTree1); //Test SmallestValue()
    Test4(dateTree1); //Test LargestValue()
    BST<Date> dateTree2(dateTree1);
    Test5(dateTree1, dateTree2); //Test copy constructor
    Test6(dateTree1, dateTree2); //Test Remove() and also test for deep copy
    Test7(dateTree1); //Test Search()
    Test8(dateTree1); //Test Remove() when tree is empty

    return 0;
}

void ProcessNode(Date &data)
{
    cout << data << endl;
}

void Test1(BST<Date> &dateTree1)
{
    cout << "Test 1" << endl;
    cout << "======" << endl;
    cout << "Initializing dateTree1..." << endl;
    cout << "In-order traversal: " << endl;
    dateTree1.PrintInOrder(ProcessNode);
    cout << "Pre-order traversal: " << endl;
    dateTree1.PrintPreOrder(ProcessNode);
    cout << "Post-order traversal: " << endl;
    dateTree1.PrintPostOrder(ProcessNode);
    cout << endl;
}

void Test2(BST<Date> &dateTree1)
{
    cout << "Test 2" << endl;
    cout << "======" << endl;
    cout << "Inserting data into dateTree1..." << endl;
    Date dateObj;
    string line;
    string token;
    string::size_type sz;
    stringstream ss;
    ifstream inputFile("data/date.txt");
    while(!inputFile.eof())
    {
        getline(inputFile, line); //Get each line even if it is empty
        if(line != "")
        {
            ss.clear(); //Clear stringstream before any input to avoid errors
            ss << line; //Convert line to streamstring so that it can be used in getline()
            getline(ss,token,'/');
            dateObj.SetDay(stoi(token,&sz));
            getline(ss,token,'/');
            dateObj.SetMonth(stoi(token,&sz));
            getline(ss,token);
            dateObj.SetYear(stoi(token,&sz));
            dateTree1.Insert(dateObj);
        }
    }
    inputFile.close();
    cout << "In-order traversal: " << endl;
    dateTree1.PrintInOrder(ProcessNode);
    cout << "Pre-order traversal: " << endl;
    dateTree1.PrintPreOrder(ProcessNode);
    cout << "Post-order traversal: " << endl;
    dateTree1.PrintPostOrder(ProcessNode);
}

void Test3(BST<Date> &dateTree1)
{
    cout << "Test 3" << endl;
    cout << "======" << endl;
    cout << "The smallest value is " << dateTree1.SmallestValue() << endl << endl;
}

void Test4(BST<Date> &dateTree1)
{
    cout << "Test 4" << endl;
    cout << "======" << endl;
    cout << "The largest value is " << dateTree1.LargestValue() << endl << endl;
}

void Test5(BST<Date> &dateTree1, BST<Date> &dateTree2)
{
    cout << "Test 5" << endl;
    cout << "======" << endl;
    cout << "Copying dateTree1 to dateTree2..." << endl;
    cout << "In-order traversal for dateTree1:" << endl;
    dateTree1.PrintInOrder(ProcessNode);
    cout << "In-order traversal for dateTree2:" << endl;
    dateTree2.PrintInOrder(ProcessNode);
}

void Test6(BST<Date> &dateTree1, BST<Date> &dateTree2)
{
    cout << "Test 6" << endl;
    cout << "======" << endl;
    cout << "Removing 6/6/2004 from dateTree1..." << endl;
    Date dateObj(6,6,2004);
    dateTree1.Remove(dateObj);
    cout << "In-order traversal for dateTree1 is now: " << endl;
    dateTree1.PrintInOrder(ProcessNode);
    cout << "In-order traversal for dateTree2 is now: " << endl;
    dateTree2.PrintInOrder(ProcessNode);
}

void Test7(BST<Date> &dateTree1)
{
    cout << "Test 7" << endl;
    cout << "======" << endl;
    Date dateObj1(1,9,1980);
    cout << "Is 1/9/1980 found in dateTree1? " << dateTree1.Search(dateObj1) << endl;
    Date dateObj2(6,6,2004);
    cout << "Is 6/6/2004 found in dateTree1? " << dateTree1.Search(dateObj2) << endl << endl;
}

void Test8(BST<Date> &dateTree1)
{
    cout << "Test 8" << endl;
    cout << "======" << endl;
    cout << "Removing 28/10/1999 from dateTree1..." << endl;
    Date dateObj1(28,10,1999);
    dateTree1.Remove(dateObj1);
    cout << "Removing 10/3/2002 from dateTree1..." << endl;
    Date dateObj2(10,3,2002);
    dateTree1.Remove(dateObj2);
    cout << "Removing 1/9/1980 from dateTree1..." << endl;
    Date dateObj3(1,9,1980);
    dateTree1.Remove(dateObj3);
    cout << "Removing 4/5/2020 from dateTree1..." << endl;
    Date dateObj4(4,5,2020);
    dateTree1.Remove(dateObj4);
    cout << "Removing 17/4/1995 from dateTree1..." << endl;
    Date dateObj5(17,4,1995);
    dateTree1.Remove(dateObj5);
    cout << "Removing 5/5/2012 from dateTree1..." << endl;
    Date dateObj6(5,5,2012);
    dateTree1.Remove(dateObj6);
    cout << "Removing 28/2/2018 from dateTree1..." << endl;
    Date dateObj7(28,2,2018);
    dateTree1.Remove(dateObj7);
    cout << "Removing 16/10/1999 from dateTree1..." << endl;
    Date dateObj8(16,10,1999);
    dateTree1.Remove(dateObj8);
    cout << "In-order traversal: " << endl;
    dateTree1.PrintInOrder(ProcessNode);
}
