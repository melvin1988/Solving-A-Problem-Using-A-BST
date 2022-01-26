/*
Changelog v02
=============
(1) Added IsNumber() which checks if a string is a number
    It is used in the input stream operator>> to check if the input is a number before converting the input into unsigned
(2) Added operator<() to allow using the operator< to compare if a Date object is less than another Date object
(3) Added operator==()to allow using the operator== to compare if a Date object is equals to another Date object
(4) Added operator<() to allow using the operator> to compare if a Date object is more than another Date object
*/

#ifndef DATE_H
#define DATE_H

#include <iostream>

using namespace std;

    /**
     * @class Date
	 * @brief Provides the format for the date in day/month/year
	 *
	 * @author Melvin Sim
	 * @version 02
	 * @date 1 November 2020
     *
     * @bug Hopefully this program has no bugs
	 */

class Date
{
    public:
        /**
         * @brief Default constructor
         *
         * Constructs a Date object from the default values
         */
        Date();

        /**
		 * @brief Parameterized constructor
		 *
		 * Constructs a Date object from the specified day, month and year
		 *
		 * @param newDay - the day of the date
		 * @param newMonth - the month of the date
		 * @param newYear - the year of the date
		 */
        Date(unsigned newDay, unsigned newMonth, unsigned newYear);

        /**
		 * @brief Gets the day
		 *
		 * @return unsigned
		 */
        unsigned GetDay() const;

        /**
		 * @brief Sets the day
		 *
		 * @param newDay - day
		 *
		 * @return void
		 */
        void SetDay(unsigned newDay);

        /**
		 * @brief Gets the month
		 *
		 * @return unsigned
		 */
        unsigned GetMonth() const;

        /**
		 * @brief Sets the month
		 *
		 * @param newMonth - month
		 *
		 * @return void
		 */
        void SetMonth(unsigned newMonth);

        /**
		 * @brief Gets the year
		 *
		 * @return unsigned
		 */
        unsigned GetYear() const;

        /**
		 * @brief Sets the year
		 *
		 * @param newYear - year
		 *
		 * @return void
		 */
        void SetYear(unsigned newYear);

        /**
		 * @brief Checks if the date is valid
		 *
		 * @return bool
		 */
        bool IsValid();

    private:
        /**
		 * @brief The day of the date
		 */
        unsigned m_day;

        /**
		 * @brief The month of the date
		 */
        unsigned m_month;

        /**
		 * @brief The year of the date
		 */
        unsigned m_year;
};

    /**
     * @brief Extraction operator for extracting data to store in a Date object
     */
    istream& operator>>(istream &input, Date &d);

    /**
     * @brief Insertion operator for printing data contained in a Date object
     */
    ostream& operator<<(ostream &output, const Date &d);

    /**
     * @brief Checks if a string is a number
     */
    bool IsNumber(const string &s);

    /**
     * @brief Comparison operator< which returns true if d1 is less than d2
     */
    bool operator<(const Date &d1, const Date &d2);

    /**
     * @brief Comparison operator== which returns true if d1 is equals to d2
     */
    bool operator==(const Date &d1, const Date &d2);

    /**
     * @brief Comparison operator> which returns true if d1 is more than d2
     */
    bool operator>(const Date &d1, const Date &d2);

#endif // DATE_H
