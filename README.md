# Using-A-BST-Written-In-C-Plus-Plus
Design an object-oriented solution and implement the solution in C++ to solve the problem described below.

Historical data for solar radiation and wind speeds was obtained (along with other sensor information) from http://wwwmet.murdoch.edu.au/downloads1.  Weather data in the format we are after has been available from the middle of 1998 till the present day. Data is logged at intervals of 10 minutes. Sample data in comma-separated value text files is made available for this assignment. Each file contains a year’s worth of data for multiple sensors. Data for each date-time recording are on separate rows. Within each row, the value for each sensor is separated by a comma. The sensor codes are found at http://wwwmet.murdoch.edu.au/sensors.

Your program must be able to read data from multiple data files.

You should provide a suitable menu with an exit option in your main program. When designing the output, imagine yourself as the user of the program. You want the user interaction to be user friendly on the command line. Do not use GUI interaction.

To test your program we will be using the file data/met_index.txt and substitute the file names that you have there with our own test file names. If our test files do not get loaded or produce incorrect output, the program will be assessed as “not working”. Make sure that the program is tested against manually calculated results.

This menu option is to be attempted only when all other menu options are working as expected. Make sure the other menu options have been checked to ensure that they are working using manually calculated results.

Given a Date in the form d/m/yyyy, show the times for the highest solar radiation for that Date. Output to screen using this sample format: (There can be one or more time values that are output for the same date as the highest solar radiation value may be recorded more than once. The time values could be consecutive.)

Date: 11/1/2019
High solar radiation for the day: 1046 W/m2

Time:
10:40
11:30

Menu option 6:
Exit the program.

The date, month and/or year are specified by the user. Your program asks for these on the command line and the user types in the required values and presses the “Enter” key.

Processing:
Your program must first load the data from multiple files. After loading the data, a menu is displayed to the user.
The required data structures (see below) must be used to provide the functionality for the menu items.

A number of data files are already provided to you.

Data Structures:
STL data structures and algorithms can be used in this assignment.

The use of template BST and STL map is *mandatory*, so think very hard and do not start coding until you have thought through the issues. Hint: There are issues that you have to resolve before you code.

The data for the output in the various menu options must involve the use of the mandatory data structures. You may use other data structures together with the STL map and template BST.

You should be careful that you do not have data structure classes that do I/O. You may want to have dedicated I/O classes instead or let the main program deal with I/O. Make sure you modularise your main program.

You may use std::string and string stream classes in your program instead of using C like strings. You may use iostream and file handling classes and objects in C++.
