#include "Time.h"

Time::Time()
{
    m_hour = 0;
    m_minute = 0;
}

Time::Time(unsigned newHour, unsigned newMinute)
{
    if(newHour >= 0 && newHour < 24)
    {
        m_hour = newHour;
        if(newMinute >= 0 && newMinute < 60)
        {
            m_minute = newMinute;
        }
        else
        {
            m_minute = 0;
            cout << "Invalid minute!" << endl;
        }
    }
    else
    {
        m_hour = 0;
        m_minute = 0;
        cout << "Invalid hour!" << endl;
    }
}

unsigned Time::GetHour() const
{
  return m_hour;
}

void Time::SetHour(const unsigned newHour)
{
    if(newHour >= 0 && newHour < 24)
    {
        m_hour = newHour;
    }
    else
    {
        m_hour = 0;
        cout << "Invalid hour!" << endl;
    }
}

unsigned Time::GetMinute() const
{
    return m_minute;
}

void Time::SetMinute(const unsigned newMinute)
{
    if(newMinute >= 0 && newMinute < 60)
    {
        m_minute = newMinute;
    }
    else
    {
        m_minute = 0;
        cout << "Invalid minute!" << endl;
    }
}

istream& operator>>(istream &input, Time &t)
{
    string::size_type sz;

    string newHour;
    getline(input,newHour,':');
    if(IsNumber(newHour))
    {
        t.SetHour(stoul(newHour,&sz));
    }

    string newMinute;
    getline(input,newMinute,',');
    if(IsNumber(newMinute))
    {
        t.SetMinute(stoul(newMinute,&sz));
    }

    return input;
}

ostream& operator<<(ostream &output, const Time &t)
{
    output << t.GetHour() << ":";
    if(t.GetMinute() == 0)
    {
        output << "00";
    }
    else
    {
        output << t.GetMinute();
    }

    return output;
}
