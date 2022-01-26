#include <iostream>
#include <fstream>
#include <sstream>
#include "BST.h"

using namespace std;

void ProcessNode(int &data);
void Test1(BST<int> &intTree1);
void Test2(BST<int> &intTree1);
void Test3(BST<int> &intTree1);
void Test4(BST<int> &intTree1);
void Test5(BST<int> &intTree1, BST<int> &intTree2);
void Test6(BST<int> &intTree1, BST<int> &intTree2);
void Test7(BST<int> &intTree1);
void Test8(BST<int> &intTree1);

int main()
{
    cout << "Unit Test for BST<int>" << endl;
    cout << "==========================" << endl << endl;

    BST<int> intTree1;
    Test1(intTree1); //Test constructor
    Test2(intTree1); //Test Insert()
    Test3(intTree1); //Test SmallestValue()
    Test4(intTree1); //Test LargestValue()
    BST<int> intTree2(intTree1);
    Test5(intTree1, intTree2); //Test copy constructor
    Test6(intTree1, intTree2); //Test Remove() and also test for deep copy
    Test7(intTree1); //Test Search()
    Test8(intTree1); //Test Remove() when tree is empty

    return 0;
}

void ProcessNode(int &data)
{
    cout << data << " ";
}

void Test1(BST<int> &intTree1)
{
    cout << "Test 1" << endl;
    cout << "======" << endl;
    cout << "Initializing intTree1..." << endl;
    cout << "In-order traversal: " << endl;
    intTree1.PrintInOrder(ProcessNode);
    cout << "Pre-order traversal: " << endl;
    intTree1.PrintPreOrder(ProcessNode);
    cout << "Post-order traversal: " << endl;
    intTree1.PrintPostOrder(ProcessNode);
    cout << endl;
}

void Test2(BST<int> &intTree1)
{
    cout << "Test 2" << endl;
    cout << "======" << endl;
    cout << "Inserting data into intTree1..." << endl;
    string line;
    string::size_type sz;
    ifstream inputFile("data/int.txt");
    while(!inputFile.eof())
    {
        getline(inputFile, line);
        if(line != "")
        {
            intTree1.Insert(stoi(line,&sz));
        }
    }
    inputFile.close();
    cout << "In-order traversal: " << endl;
    intTree1.PrintInOrder(ProcessNode);
    cout << "Pre-order traversal: " << endl;
    intTree1.PrintPreOrder(ProcessNode);
    cout << "Post-order traversal: " << endl;
    intTree1.PrintPostOrder(ProcessNode);
    cout << endl;
}

void Test3(BST<int> &intTree1)
{
    cout << "Test 3" << endl;
    cout << "======" << endl;
    cout << "The smallest value is " << intTree1.SmallestValue() << endl << endl;
}

void Test4(BST<int> &intTree1)
{
    cout << "Test 4" << endl;
    cout << "======" << endl;
    cout << "The largest value is " << intTree1.LargestValue() << endl << endl;
}

void Test5(BST<int> &intTree1, BST<int> &intTree2)
{
    cout << "Test 5" << endl;
    cout << "======" << endl;
    cout << "Copying intTree1 to intTree2..." << endl;
    cout << "In-order traversal for intTree1:" << endl;
    intTree1.PrintInOrder(ProcessNode);
    cout << "In-order traversal for intTree2:" << endl;
    intTree2.PrintInOrder(ProcessNode);
    cout << endl;
}

void Test6(BST<int> &intTree1, BST<int> &intTree2)
{
    cout << "Test 6" << endl;
    cout << "======" << endl;
    cout << "Removing 71 from intTree1..." << endl;
    intTree1.Remove(71);
    cout << "In-order traversal for intTree1 is now: " << endl;
    intTree1.PrintInOrder(ProcessNode);
    cout << "In-order traversal for intTree2 is now: " << endl;
    intTree2.PrintInOrder(ProcessNode);
    cout << endl;
}

void Test7(BST<int> &intTree1)
{
    cout << "Test 7" << endl;
    cout << "======" << endl;
    cout << "Is 28 found in intTree1? " << intTree1.Search(28) << endl;
    cout << "Is 55 found in intTree1? " << intTree1.Search(55) << endl << endl;
}

void Test8(BST<int> &intTree1)
{
    cout << "Test 8" << endl;
    cout << "======" << endl;
    cout << "Removing 68 from intTree1..." << endl;
    intTree1.Remove(68);
    cout << "Removing 37 from intTree1..." << endl;
    intTree1.Remove(37);
    cout << "Removing 28 from intTree1..." << endl;
    intTree1.Remove(28);
    cout << "Removing 50 from intTree1..." << endl;
    intTree1.Remove(50);
    cout << "Removing 43 from intTree1..." << endl;
    intTree1.Remove(43);
    cout << "Removing 69 from intTree1..." << endl;
    intTree1.Remove(69);
    cout << "Removing 85 from intTree1..." << endl;
    intTree1.Remove(85);
    cout << "Removing 66 from intTree1..." << endl;
    intTree1.Remove(66);
    cout << "In-order traversal: " << endl;
    intTree1.PrintInOrder(ProcessNode);
}
