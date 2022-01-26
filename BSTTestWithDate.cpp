/*
Changelog dated 14 November 2020
===============================
Removed WindLogVector and added struct WindLogKey and struct WindLogValue which are the key and value of WindLogMap respectively
Added GetMultipleFiles() which inputs data from multiple files and store into WindLogMap
Added GetRadiationTree() which extracts data from WindLogMap based on date and store into BST
Added GetRadiationMap() which extracts data from WindLogMap based on date and store into multimap
Added RadiationToWattPerMSq() which converts radiation from kWh/m2 to W/m2
Changed GetMonthInString() which now makes use of an array rather than a switch-case statement
Added IsNumber() which checks if a string is a number
Added ResetTotalValue() which resets the global variable totalValue
Added ProcessNode() which calculates the total value of all nodes
Updated DisplayMenu() which now has 6 options
Added GetDateInput() which gets a string input from the user and converts it to int day, month, year
Added GetAverageWindSpeedUsingBST() which returns the average wind speed using a BST
Added GetAverageTemperatureUsingBST() which returns the average temperature using a BST
Added PrintAverageSpeedAndTemperatureForCase1() which has a slightly different print format from PrintAverageSpeedAndTemperatureForMonth()
Added PrintTotalRadiationForMonth() which prints the total radiation for a specified month
Added PrintTimeWithHighestRadiation() which prints the time(s) with the highest radiation for a specified date
Added PrintHighestRadiation() which prints the value and time(s) with the highest radiation for a specified date
Removed PrintAverageSpeedAndTemperatureForYear()
Removed PrintTotalRadiationForYear()
Added Case5() which displays the time(s) for the highest solar radiation for a specified day, month and year
Added Menu() which enters the menu loop and processes Case1 to Case5
*/

/*
===========================
Author : Sim Jia Wei Melvin
Version: 02
Date: 14 November 2020
===========================

Brief description of the program
================================
This program reads from a file and stores the date, time, speed, radiation and temperature into a vector.
The user then selects a choice from the menu to display one of the following:
  - Average speed and temperature
  - Total radiation
  - Average speed, average temperature, and total radiation
  - Timing(s) with the highest radiation
*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <map>
#include "Date.h"
#include "Time.h"
#include "BST.h"

using namespace std;

//=================================================================================

typedef struct
{
  Date d;
  Time t;
}WindLogKey;

//This comparison operator is needed for WindLogKey to compare values
bool operator<(const WindLogKey &windLogKey1, const WindLogKey &windLogKey2)
{
    if(windLogKey1.d.GetYear() < windLogKey2.d.GetYear())
    {
        return true;
    }
    if(windLogKey1.d.GetYear() == windLogKey2.d.GetYear() && windLogKey1.d.GetMonth() < windLogKey2.d.GetMonth())
    {
        return true;
    }
    if(windLogKey1.d.GetYear() == windLogKey2.d.GetYear() && windLogKey1.d.GetMonth() == windLogKey2.d.GetMonth()
       && windLogKey1.d.GetDay() < windLogKey2.d.GetDay())
    {
        return true;
    }
    if(windLogKey1.d.GetYear() == windLogKey2.d.GetYear() && windLogKey1.d.GetMonth() == windLogKey2.d.GetMonth()
       && windLogKey1.d.GetDay() == windLogKey2.d.GetDay() && windLogKey1.t.GetHour() < windLogKey2.t.GetHour())
    {
        return true;
    }
    if(windLogKey1.d.GetYear() == windLogKey2.d.GetYear() && windLogKey1.d.GetMonth() == windLogKey2.d.GetMonth()
       && windLogKey1.d.GetDay() == windLogKey2.d.GetDay() && windLogKey1.t.GetHour() == windLogKey2.t.GetHour()
       && windLogKey1.t.GetMinute() < windLogKey2.t.GetMinute())
    {
        return true;
    }
    return false;
}

typedef struct
{
  float speed;
  float radiation;
  float temperature;
}WindLogValue;

typedef map<WindLogKey, WindLogValue> WindLogMap;

float totalValue; //Stores the total value of all nodes

//=================================================================================

//Extracts and stores the data
istream &operator >> (istream &input, WindLogMap &windLogMap);
void GetData(string fileName, WindLogMap &windLogMap);
void GetMultipleFiles(string file, WindLogMap &windLogMap);
void GetRadiationTree(Date &date, WindLogMap &windLogMap, BST<float> &tree);
void GetRadiationMap(Date &date, WindLogMap &windLogMap, multimap<float,Time> &multiMap);

//Converts to the appropriate units
float SpeedToKmPerHr(float mPerSecond);
float RadiationToKWHPerMSq(float wPerMSq);
float RadiationToWattPerMSq(float kWHPerMSq);
float ToOneDecimalPlace(float num);

//Converts month from int to string
string GetMonthInString(int month);

//Checks if a string is a number
bool IsNumber(const string &str);

//Resets the global variable totalValue
void ResetTotalValue();

//Calculates the total value of all nodes
void ProcessNode(float &data);

//Outputs data to file based on the year
void WriteData(string fileName, int year, WindLogMap &windLogMap);

//Used in the menu
void DisplayMenu();
int GetMenuInput();
int GetMonthInput();
int GetYearInput();
void GetDateInput(int &day, int &month, int &year);

//Returns the speed, temperature and radiation
float GetAverageWindSpeed(int year, int month, WindLogMap &windLogMap);
float GetAverageWindSpeedUsingBST(int year, int month, WindLogMap &windLogMap, BST<float> &tree);
float GetAverageTemperature(int year, int month, WindLogMap &windLogMap);
float GetAverageTemperatureUsingBST(int year, int month, WindLogMap &windLogMap, BST<float> &tree);
float GetTotalRadiation(int year, int month, WindLogMap &windLogMap);

//Prints the result
void PrintAverageSpeedAndTemperatureForCase1(int year, int month, float speed, float temperature);
void PrintAverageSpeedAndTemperatureForMonth(int month, float speed, float temperature);
void PrintTotalRadiationForMonth(int month, float radiation);
void PrintTimeWithHighestRadiation(BST<float> tree, multimap<float,Time> &multiMap);
void PrintHighestRadiation(Date dateObj, BST<float> tree, multimap<float,Time> &multiMap);

//Used in the switch-case statement
void Case1(WindLogMap &windLogMap);
void Case2(WindLogMap &windLogMap);
void Case3(WindLogMap &windLogMap);
void Case4(WindLogMap &windLogMap);
void Case5(WindLogMap &windLogMap);

//Enters the menu that contains Case1 to Case5
void Menu(WindLogMap &windLogMap);

//Informs the user that the program has terminated
void Exit();

//=================================================================================

int main()
{
    cout << "======================================================================" << endl;
    cout << "This program shows the average wind speed and ambient air temperature," << endl;
    cout << "or total solar radiation of a period of time as specified by the user." << endl;
    cout << "======================================================================" << endl;

    //Declaration of variable
    WindLogMap windlog;

    //Input from multiple CSV files to map
    GetMultipleFiles("data/met_index.txt", windlog);

    //Enter menu loop
    Menu(windlog);

    //Exit program
    Exit();

    return 0;
}

//===================================================================================

istream &operator >> (istream &input, WindLogMap &windLogMap)
{
    WindLogKey key;
    input >> key.d >> key.t;

    string str;
    //Skip 9 commas
    for(int i = 0; i < 9; i++)
    {
        getline(input,str,',');
    }

    WindLogValue value;
    string::size_type sz;
    string newSpeed;
    getline(input,newSpeed,',');
    if(IsNumber(newSpeed))
    {
        value.speed = stof(newSpeed,&sz);
    }
    else
    {
        value.speed = 0; //If data is erroneous, set to 0
    }

    string newRadiation;
    getline(input,newRadiation,',');
    if(IsNumber(newRadiation))
    {
        value.radiation = stof(newRadiation,&sz);
    }
    else
    {
        value.radiation = 0; //If data is erroneous, set to 0
    }

    //Skip 5 commas
    for(int i = 0; i < 5; i++)
    {
        getline(input,str,',');
    }

    string newTemperature;
    getline(input,newTemperature);
    if(IsNumber(newTemperature))
    {
        value.temperature = stof(newTemperature,&sz);
    }
    else
    {
        value.temperature = 0; //If data is erroneous, set to 0
    }

    windLogMap.insert(pair<WindLogKey, WindLogValue>(key, value));

  return input;
}

void GetData(string fileName, WindLogMap &windLogMap)
{
    ifstream inputFile(fileName);
    stringstream strStream;
    if(inputFile.is_open())
    {
        //To skip the first line
        string line;
        for(int i = 0; i < 1; i++)
        {
            inputFile >> line;
        }

        while(!inputFile.eof())
        {
            //Coded this way in order to read the whole file even if there are empty lines
            getline(inputFile,line); //Get each line even if it is empty
            if(line != "")
            {
                strStream.clear(); //Clear stringstream before any input to avoid errors
                strStream << line; //Convert line to streamstring so that it can be used in getline()
                strStream >> windLogMap;
            }
        }
    }
    else
    {
        cout << "Unable to open file " << fileName;
    }
    inputFile.close();
}

void GetMultipleFiles(string file, WindLogMap &windLogMap)
{
    ifstream inputFile(file);
    string filePath = "data/";
    string fileName;
    while(!inputFile.eof())
    {
        getline(inputFile,fileName);
        GetData(filePath + fileName, windLogMap);
    }
    inputFile.close();
}

void GetRadiationTree(Date &date, WindLogMap &windLogMap, BST<float> &tree)
{
    WindLogMap::iterator itr;
    for(itr = windLogMap.begin(); itr != windLogMap.end(); itr++)
    {
        if(itr->first.d == date)
        {
            tree.Insert(itr->second.radiation);
        }
    }
}

void GetRadiationMap(Date &date, WindLogMap &windLogMap, multimap<float,Time> &multiMap)
{
    WindLogMap::iterator itr;
    for(itr = windLogMap.begin(); itr != windLogMap.end(); itr++)
    {
        if(itr->first.d == date)
        {
            multiMap.insert(pair<float,Time>(itr->second.radiation,itr->first.t));
        }
    }
}

float SpeedToKmPerHr(float mPerSecond)
{
    return mPerSecond * 3.6;
}

float RadiationToKWHPerMSq(float wPerMSq)
{
    return wPerMSq / 6 / 1000;
}

float RadiationToWattPerMSq(float kWHPerMSq)
{
    return kWHPerMSq * 6 * 1000;
}

float ToOneDecimalPlace(float num)
{
    float result = (int)(num * 10 + 0.5);

    return (float)result / 10;
}

string GetMonthInString(int month)
{
    string monthArray[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

    return monthArray[month-1];
}

void ResetTotalValue()
{
    totalValue = 0;
}

void ProcessNode(float &data)
{
    totalValue += data;
}

void WriteData(string fileName, int year, WindLogMap &windLogMap)
{
    ofstream outputFile(fileName);
    if(outputFile.is_open())
    {
        outputFile << year << endl;
        for(int i = 1; i < 13; i++)
        {
            if(GetAverageWindSpeed(year, i, windLogMap) != 0) //To avoid writing those with no data
            {
                outputFile << GetMonthInString(i) << "," << ToOneDecimalPlace(SpeedToKmPerHr(GetAverageWindSpeed(year, i, windLogMap)))
                << "," << ToOneDecimalPlace(GetAverageTemperature(year, i, windLogMap))
                << "," << ToOneDecimalPlace(RadiationToKWHPerMSq(GetTotalRadiation(year, i, windLogMap))) << endl;
            }
        }
        cout << "Data have been written to " << fileName << endl;
    }
    else
    {
        cout << "Unable to open file " << fileName;
    }
    outputFile.close();
}

void DisplayMenu()
{
    cout << "Menu options are:" << endl;
    cout << "(1) Display the average wind speed and average ambient air temperature" << endl;
    cout << "    for a specified month and year." << endl;
    cout << "(2) Display the average wind speed and average ambient air temperature" << endl;
    cout << "    for each month of a specified year." << endl;
    cout << "(3) Display the total solar radiation in kWh/m2 for each month of a" << endl;
    cout << "    specified year." << endl;
    cout << "(4) Write the average wind speed (km/h), average ambient air temperature" << endl;
    cout << "    and total solar radiation in kWh/m2 for each month of a specified" << endl;
    cout << "    year to a file called \"WindTempSolar.csv\"." << endl;
    cout << "(5) Display the time(s) for the highest solar radiation for a specified" << endl;
    cout << "    day, month and year." << endl;
    cout << "(6) Exit the program." << endl;
}

int GetMenuInput()
{
    int userChoice = 0;
    while(!(userChoice >= 1 && userChoice <= 6))
    {
        cout << "\nSelect a choice on the menu by entering (1, 2, 3, 4, 5 or 6)." << endl;
        DisplayMenu();
        if(cin >> userChoice && (userChoice >= 1 && userChoice <= 6))
        {
            break;
        }
        else
        {
            cout << "Invalid input." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
    }
    return userChoice;
}

int GetMonthInput()
{
    int month = 0;
    while(!(month >= 1 && month <= 12))
    {
        cout << "Enter month (1-12), where 1=Jan, 2=Feb, etc: " << endl;
        if(cin >> month && (month >= 1 && month <= 12))
        {
            break;
        }
        else
        {
            cout << "Invalid input." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
    }
    return month;
}

int GetYearInput()
{
    int year = 0;
    while(!(year > 0))
    {
        cout << "Enter year: " << endl;
        if(cin >> year && year > 0)
        {
            break;
        }
        else
        {
            cout << "Invalid input." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
    }
    return year;
}

void GetDateInput(int &day, int &month, int &year)
{
    string line;
    string date;
    stringstream strStream;
    string::size_type sz;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    while(!(day >= 1 && day <= 31) || !(month >= 1 && month <= 12) || !(year > 0))
    {
        cout << "Enter a Date in the form d/m/yyyy: " << endl;
        getline(cin, line);
        strStream.clear(); //Clear stringstream before any input to avoid errors
        strStream << line; //Convert date to streamstring so that it can be used in getline()

        getline(strStream, date, '/');
        if(IsNumber(date))
        {
            day = stoi(date,&sz);
            if(!(day >= 1 && day <= 31))
            {
                day = 0;
                cout << "Invalid day." << endl;
            }
        }
        else
        {
            day = 0;
        }

        getline(strStream, date, '/');
        if(IsNumber(date))
        {
            month = stoi(date,&sz);
            if(!(month >= 1 && month <= 12))
            {
                month = 0;
                cout << "Invalid month." << endl;
            }
        }
        else
        {
            month = 0;
        }

        getline(strStream, date);
        if(IsNumber(date))
        {
            year = stoi(date,&sz);
            if(!(year > 0))
            {
                year = 0;
                cout << "Invalid year." << endl;
            }
        }
        else
        {
            year = 0;
        }
    }
}

float GetAverageWindSpeed(int year, int month, WindLogMap &windLogMap)
{
    float total = 0;
    int count = 0;
    WindLogMap::iterator itr;
    for(itr = windLogMap.begin(); itr != windLogMap.end(); itr++)
    {
        if(itr->first.d.GetYear() == year && itr->first.d.GetMonth() == month)
        {
            total += itr->second.speed;
            count++;
        }
    }

    if(count > 0)
    {
        return total/count;
    }
    else
    {
        return 0;
    }
}

float GetAverageWindSpeedUsingBST(int year, int month, WindLogMap &windLogMap, BST<float> &tree)
{
    int count = 0;
    WindLogMap::iterator itr;
    for(itr = windLogMap.begin(); itr != windLogMap.end(); itr++)
    {
        if(itr->first.d.GetYear() == year && itr->first.d.GetMonth() == month)
        {
            tree.Insert(itr->second.speed);
            count++;
        }
    }

    if(count > 0)
    {
        tree.AddAllNodes(ProcessNode); //Used for calculating the total value of all nodes in the BST
        return totalValue/count;
    }
    else
    {
        return 0;
    }
}

float GetAverageTemperature(int year, int month, WindLogMap &windLogMap)
{
    float total = 0;
    int count = 0;
    WindLogMap::iterator itr;
    for(itr = windLogMap.begin(); itr != windLogMap.end(); itr++)
    {
        if(itr->first.d.GetYear() == year && itr->first.d.GetMonth() == month)
        {
            total += itr->second.temperature;
            count++;
        }
    }

    if(count > 0)
    {
        return total/count;
    }
    else
    {
        return 0;
    }
}

float GetAverageTemperatureUsingBST(int year, int month, WindLogMap &windLogMap, BST<float> &tree)
{
    int count = 0;
    WindLogMap::iterator itr;
    for(itr = windLogMap.begin(); itr != windLogMap.end(); itr++)
    {
        if(itr->first.d.GetYear() == year && itr->first.d.GetMonth() == month)
        {
            tree.Insert(itr->second.temperature);
            count++;
        }
    }

        if(count > 0)
    {
        tree.AddAllNodes(ProcessNode); //Used for calculating the total value of all nodes in the BST
        return totalValue/count;
    }
    else
    {
        return 0;
    }
}

float GetTotalRadiation(int year, int month, WindLogMap &windLogMap)
{
    float total = 0;
    int count = 0;
    WindLogMap::iterator itr;
    for(itr = windLogMap.begin(); itr != windLogMap.end(); itr++)
    {
        if(itr->first.d.GetYear() == year && itr->first.d.GetMonth() == month)
        {
            total += itr->second.radiation;
            count++;
        }
    }

    if(count > 0)
    {
        return total;
    }
    else
    {
        return 0;
    }
}

void PrintAverageSpeedAndTemperatureForCase1(int year, int month, float speed, float temperature)
{
    //If average speed is 0, average temperature will also be 0, hence no need for && temperature == 0
    if(speed == 0)
    {
        cout << GetMonthInString(month) << " " << year << ": No Data" << endl;
    }
    else
    {
        cout << GetMonthInString(month) << " " << year << ": " <<ToOneDecimalPlace(SpeedToKmPerHr(speed)) << " km/h, "
        << ToOneDecimalPlace(temperature) << " degrees C" << endl;
    }
}

void PrintAverageSpeedAndTemperatureForMonth(int month, float speed, float temperature)
{
    //If average speed is 0, average temperature will also be 0, hence no need for && temperature == 0
    if(speed == 0)
    {
        cout << GetMonthInString(month) << ": No Data" << endl;
    }
    else
    {
        cout << GetMonthInString(month) << ": " <<ToOneDecimalPlace(SpeedToKmPerHr(speed)) << " km/h, " << ToOneDecimalPlace(temperature)
        << " degrees C" << endl;
    }
}

void PrintTotalRadiationForMonth(int month, float radiation)
{
    if(radiation == 0)
    {
        cout << GetMonthInString(month) << ": No Data" << endl;
    }
    else
    {
        cout << GetMonthInString(month) << ": " << ToOneDecimalPlace(RadiationToKWHPerMSq(radiation)) << " kWh/m2" << endl;
    }
}

void PrintTimeWithHighestRadiation(BST<float> tree, multimap<float,Time> &multiMap)
{
    typedef multimap<float,Time>::iterator mapItr;
    multimap<float,Time>::iterator itr;

    pair<mapItr,mapItr> result = multiMap.equal_range(tree.LargestValue()); //Find the time(s) with highest radiation and store into result
    for(itr = result.first; itr != result.second; itr++)
    {
        cout << itr->second << endl;
    }
}

void PrintHighestRadiation(Date dateObj, BST<float> tree, multimap<float,Time> &multiMap)
{
    //If multiMap is empty, tree will also be empty
    if(multiMap.empty())
    {
        cout << "\nDate: " << dateObj << endl;
        cout << "No Data" << endl;
    }
    else
    {
        cout << "\nDate: " << dateObj << endl;
        cout << "Highest solar radiation for the day: " << tree.LargestValue() << " W/m2" << endl << endl;
        cout << "Time:" << endl;
        PrintTimeWithHighestRadiation(tree, multiMap);
    }
}

void Case1(WindLogMap &windLogMap)
{
    int month = GetMonthInput();
    int year = GetYearInput();

    BST<float> speedTree;
    ResetTotalValue(); //Reset the global variable totalValue before using
    float averageSpeed = GetAverageWindSpeedUsingBST(year, month, windLogMap, speedTree);

    BST<float> temperatureTree;
    ResetTotalValue(); //Reset the global variable totalValue before using
    float averageTemperature = GetAverageTemperatureUsingBST(year, month, windLogMap, temperatureTree);

    PrintAverageSpeedAndTemperatureForCase1(year, month, averageSpeed, averageTemperature);
}

void Case2(WindLogMap &windLogMap)
{
    int year = GetYearInput();
    cout << year << endl;
    //Using a for loop causes the program to display erroneous data; it prints ": No Data" before displaying the results
/*
    float averageWindSpeed;
    float averageTemperature;
    for(int i = 0; i < 13; i++)
    {
        averageWindSpeed = GetAverageWindSpeed(year, i, w);
        averageTemperature = GetAverageTemperature(year, i, w);
        PrintAverageSpeedAndTemperatureForMonth(i, averageWindSpeed, averageTemperature);
    }
*/
    PrintAverageSpeedAndTemperatureForMonth(1, GetAverageWindSpeed(year, 1, windLogMap), GetAverageTemperature(year, 1, windLogMap));
    PrintAverageSpeedAndTemperatureForMonth(2, GetAverageWindSpeed(year, 2, windLogMap), GetAverageTemperature(year, 2, windLogMap));
    PrintAverageSpeedAndTemperatureForMonth(3, GetAverageWindSpeed(year, 3, windLogMap), GetAverageTemperature(year, 3, windLogMap));
    PrintAverageSpeedAndTemperatureForMonth(4, GetAverageWindSpeed(year, 4, windLogMap), GetAverageTemperature(year, 4, windLogMap));
    PrintAverageSpeedAndTemperatureForMonth(5, GetAverageWindSpeed(year, 5, windLogMap), GetAverageTemperature(year, 5, windLogMap));
    PrintAverageSpeedAndTemperatureForMonth(6, GetAverageWindSpeed(year, 6, windLogMap), GetAverageTemperature(year, 6, windLogMap));
    PrintAverageSpeedAndTemperatureForMonth(7, GetAverageWindSpeed(year, 7, windLogMap), GetAverageTemperature(year, 7, windLogMap));
    PrintAverageSpeedAndTemperatureForMonth(8, GetAverageWindSpeed(year, 8, windLogMap), GetAverageTemperature(year, 8, windLogMap));
    PrintAverageSpeedAndTemperatureForMonth(9, GetAverageWindSpeed(year, 9, windLogMap), GetAverageTemperature(year, 9, windLogMap));
    PrintAverageSpeedAndTemperatureForMonth(10, GetAverageWindSpeed(year, 10, windLogMap), GetAverageTemperature(year, 10, windLogMap));
    PrintAverageSpeedAndTemperatureForMonth(11, GetAverageWindSpeed(year, 11, windLogMap), GetAverageTemperature(year, 11, windLogMap));
    PrintAverageSpeedAndTemperatureForMonth(12, GetAverageWindSpeed(year, 12, windLogMap), GetAverageTemperature(year, 12, windLogMap));
}

void Case3(WindLogMap &windLogMap)
{
    int year = GetYearInput();
    cout << year << endl;
    //Using a for loop causes the program to display erroneous data; it prints ": No Data" before displaying the results
/*
    float totalRadiation;
    for(int i = 0; i < 13; i++)
    {
        totalRadiation = GetTotalRadiation(year, i, w);
        PrintTotalRadiationForMonth(i, totalRadiation);
    }
*/
    PrintTotalRadiationForMonth(1, GetTotalRadiation(year, 1, windLogMap));
    PrintTotalRadiationForMonth(2, GetTotalRadiation(year, 2, windLogMap));
    PrintTotalRadiationForMonth(3, GetTotalRadiation(year, 3, windLogMap));
    PrintTotalRadiationForMonth(4, GetTotalRadiation(year, 4, windLogMap));
    PrintTotalRadiationForMonth(5, GetTotalRadiation(year, 5, windLogMap));
    PrintTotalRadiationForMonth(6, GetTotalRadiation(year, 6, windLogMap));
    PrintTotalRadiationForMonth(7, GetTotalRadiation(year, 7, windLogMap));
    PrintTotalRadiationForMonth(8, GetTotalRadiation(year, 8, windLogMap));
    PrintTotalRadiationForMonth(9, GetTotalRadiation(year, 9, windLogMap));
    PrintTotalRadiationForMonth(10, GetTotalRadiation(year, 10, windLogMap));
    PrintTotalRadiationForMonth(11, GetTotalRadiation(year, 11, windLogMap));
    PrintTotalRadiationForMonth(12, GetTotalRadiation(year, 12, windLogMap));
}

void Case4(WindLogMap &windLogMap)
{
    string const fileName = "data/WindTempSolar.csv";
    int year = GetYearInput();
    WriteData(fileName, year ,windLogMap);
}

void Case5(WindLogMap &windLogMap)
{
    int day = 0;
    int month = 0;
    int year = 0;

    //Get Date input from user and convert to dateObj
    GetDateInput(day, month, year);
    Date dateObj(day, month, year);

    //Filter the data from WindLogMap based on the date and store into radiationTree
    BST<float> radiationTree;
    GetRadiationTree(dateObj, windLogMap, radiationTree);

    //Filter the data from WindLogMap based on the date and store into radiationMap
    multimap<float,Time> radiationMap;
    GetRadiationMap(dateObj, windLogMap, radiationMap);

    PrintHighestRadiation(dateObj, radiationTree, radiationMap);
}

void Menu(WindLogMap &windLogMap)
{
    int input = GetMenuInput();
    while(input != 6)
    {
        switch(input)
        {
            case 1:
                Case1(windLogMap);
                break;

            case 2:
                Case2(windLogMap);
                break;

            case 3:
                Case3(windLogMap);
                break;

            case 4:
                Case4(windLogMap);
                break;

            case 5:
                Case5(windLogMap);
        }
        input = GetMenuInput();
    }
}

void Exit()
{
    cout << "You quit." << endl;
    cout << "Goodbye." << endl;
}
