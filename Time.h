/*
Changelog v02
=============
(1) Added IsNumber() which checks if a string is a number
    It is used in the input stream operator>> to check if the input is a number before converting the input into unsigned
*/

#ifndef TIME_H
#define TIME_H

#include <iostream>

using namespace std;

    /**
     * @class Time
	 * @brief Provides the 24-hour format for the time
	 *
	 * @author Melvin Sim
	 * @version 02
	 * @date 1 November 2020
     *
     * @bug Hopefully this program has no bugs
	 */

class Time
{
    public:
        /**
         * @brief Default constructor
         *
         * Constructs a Time object from the default values
         */
       Time();

        /**
		 * @brief Parameterized constructor
		 *
		 * Constructs a Time object from the specified hour and minute
		 *
		 * @param newHour - the hour of the day
		 * @param newMinute - the minute of the hour
		 */
       Time(unsigned newHour, unsigned newMinute);

        /**
		 * @brief Gets the hour of the day
		 *
		 * @return unsigned
		 */
       unsigned GetHour() const;

        /**
		 * @brief Sets the hour of the day
		 *
		 * @param newHour - hour
		 *
		 * @return void
		 */
       void SetHour(const unsigned newHour);

         /**
		 * @brief Gets the minute of the hour
		 *
		 * @return unsigned
		 */
       unsigned GetMinute() const;

        /**
		 * @brief Sets the minute of the day
		 *
		 * @param newMinute - minute
		 *
		 * @return void
		 */
       void SetMinute(const unsigned newMinute);

    private:
        /**
		 * @brief The hour of the day
		 */
       unsigned m_hour;

        /**
		 * @brief The minute of the hour
		 */
       unsigned m_minute;
};

    /**
     * @brief Extraction operator for extracting data to store in a Time object
     */
    istream& operator>>(istream &input, Time &t);

    /**
     * @brief Insertion operator for printing data contained in a Time object
     */
    ostream& operator<<(ostream &output, const Time &t);

    /**
     * @brief Checks if a string is a number
     *
     * @param &s - of type string
     *
     * @return bool
     */
    bool IsNumber(const string &s);

#endif // TIME_H
