#include "Date.h"

Date::Date()
{
    m_day = 1;
    m_month = 1;
    m_year = 2000;
}

Date::Date(unsigned newDay, unsigned newMonth, unsigned newYear)
{
    m_day = newDay;
    m_month = newMonth;
    m_year = newYear;
}

unsigned Date::GetDay() const
{
    return m_day;
}

void Date::SetDay(unsigned newDay)
{
    m_day = newDay;
}

unsigned Date::GetMonth() const
{
    return m_month;
}

void Date::SetMonth(unsigned newMonth)
{
    m_month = newMonth;
}

unsigned Date::GetYear() const
{
    return m_year;
}

void Date::SetYear(unsigned newYear)
{
    m_year = newYear;
}

bool Date::IsValid()
{
    unsigned minYear = 1800;
    unsigned maxYear = 2020;

    //Check if year is within the range of min and max year
    if(m_year>=minYear && m_year<=maxYear)
    {
        //Jan, Mar, May, Jul, Aug, Oct, Dec has 31 days
        if((m_month==1 || m_month==3 || m_month==5 || m_month==7 || m_month==8 || m_month==10 || m_month==12) && m_day>=1 && m_day<=31)
        {
            return true;
        }
        //Apr, Jun, Sep, Nov has 30 days
        else if((m_month==4 || m_month==6 || m_month==9 || m_month==11) && m_day>=1 && m_day<=30)
        {
            return true;
        }
        //Feb has either 28 or 29 days
        else if(m_month==2)
        {
            //Check for leap year; Feb with 29 days
            if( (m_year%400==0 || (m_year%100!=0 && m_year%4==0)) && m_day>=1 && m_day<=29)
            {
                return true;
            }
            //Feb with 28 days
            else if(m_day>=1 && m_day<=28)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}

istream& operator>>(istream &input, Date &d)
{
    string::size_type sz;

    string newDay;
    getline(input,newDay,'/');
    if(IsNumber(newDay))
    {
        d.SetDay(stoul(newDay,&sz));
    }

    string newMonth;
    getline(input,newMonth,'/');
    if(IsNumber(newMonth))
    {
        d.SetMonth(stoul(newMonth,&sz));
    }

    string newYear;
    getline(input,newYear,' ');
    if(IsNumber(newYear))
    {
        d.SetYear(stoul(newYear,&sz));
    }

    return input;
}

ostream& operator<<(ostream &output, const Date &d)
{
    output << d.GetDay() << "/" << d.GetMonth() << "/" << d.GetYear();

    return output;
}

bool IsNumber(const string &s)
{
    bool flag = false;
    for(char c : s) //Iterate through each character in the string to check using isdigit()
    {
        if(c == '.' && !flag) //Invalid if there are 2 '.' in the string
        {
            flag = true;
        }
        else if(!isdigit(c))
        {
            return false;
        }
    }
    return true;
}

bool operator<(const Date &d1, const Date &d2)
{
    if(d1.GetYear() < d2.GetYear())
    {
        return true;
    }
    if(d1.GetYear() == d2.GetYear() && d1.GetMonth() < d2.GetMonth())
    {
        return true;
    }
    if(d1.GetYear() == d2.GetYear() && d1.GetMonth() == d2.GetMonth() && d1.GetDay() < d2.GetDay())
    {
        return true;
    }
    return false;
}

bool operator==(const Date &d1, const Date &d2)
{
    if(d1.GetYear() == d2.GetYear() && d1.GetMonth() == d2.GetMonth() && d1.GetDay() == d2.GetDay())
    {
        return true;
    }
    return false;
}

bool operator>(const Date &d1, const Date &d2)
{
    if(d1.GetYear() > d2.GetYear())
    {
        return true;
    }
    if(d1.GetYear() == d2.GetYear() && d1.GetMonth() > d2.GetMonth())
    {
        return true;
    }
    if(d1.GetYear() == d2.GetYear() && d1.GetMonth() == d2.GetMonth() && d1.GetDay() > d2.GetDay())
    {
        return true;
    }
    return false;
}
