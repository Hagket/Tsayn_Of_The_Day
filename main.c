// Version 1.0
// Created on: 1/6/2024 by Hagop Ketchedjian (Took ~8 hours to complete from scratch)
// Last Updated on: 1/6/2023
// Note: On Poon Paregentan (50th day before Easter) the tone automatically changes to ԴԿ and continues until the next year (thus making poon paregentan the pivot of this calculator)

//To do: turn pivot into poon paregentan instead of easter (poon paregentan is 50 days before easter)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Function Prototypes:
void gaussEaster(int year, int* monthOfEaster, int* dayOfEaster);
char* toneFinder(int monthOfEaster, int dayOfEaster, int month, int day, int year);

int main() {
    int inputYear = -1, inputMonth = -1, inputDay = -1; // Date given by user to find corresponding tone
    int daysInMonths[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // Holds the amount of days in each month

    while ((inputMonth < 1 || inputMonth > 12) || (inputDay < 1 || inputDay > daysInMonths[inputMonth]) || (inputYear < 33)) { // Makes sure the inputs are valid numbers (in terms of dates)
        printf("Enter a valid date in \"<Month> <Day> <Year>\" format (eg. 01 05 2024):\n");
        if (scanf("%d %d %d", &inputMonth, &inputDay, &inputYear) != 3) {printf("Please use the correct format."); exit(1);} // Takes user input and if any of the inputs were not integers the program asks for new input
        if ((inputYear%100 == 0 && inputYear%400 == 0) || (inputYear%4 == 0 && inputYear%100 != 0)) { // If the given year is a leap year:
            daysInMonths[2] = 29; // February has 29 days
        }
    }

    printf("Date inputted: %d-%d-%d\n\n", inputMonth, inputDay, inputYear);

    int monthOfEaster, dayOfEaster; // Date of Easter for the specified inputYear
    int* monthOfEasterPtr = &monthOfEaster; // Creates an integer pointer which points to the monthOfEaster variable
    int* dayOfEasterPtr = &dayOfEaster; // Creates an integer pointer which points to the dayOfEaster variable

    int monthOfParegentan = -1; // Will hold the month of poon paregentan which is our pivot
    int dayOfParegentan = -1; // Will hold the day of poon paregentan which is our pivot
    int yearOfParegentan = inputYear; // Creates a variable to hold the year of the easter to pivot off of

    gaussEaster(inputYear, monthOfEasterPtr, dayOfEasterPtr); // Runs the Guass Easter Algorithm to find the day of easter in the inputYear
    // Calculates poon paregentan for the inputYear
    int count = (50 - dayOfEaster); // Take off the days in the month of easter
    for (int m = (monthOfEaster - 1); m > 0; m--) { // Changes the month when the days run out in the current month
        for (int d = daysInMonths[m]; d > 0; d--) { // Loops the days back to reach Poon Paregentan
            if (count == 1) {
                dayOfParegentan = d;
                monthOfParegentan = m;
                m = 0; // To exit the 1st loop
                d = 0; // To exit the 2nd loop
            }
            else {count -= 1;}
        }
    }

    // If the input date is before poon paregentan do calculation based on the previous year's date of Easter/Poon Paregentan
    if ((inputMonth < monthOfParegentan) || (inputMonth == monthOfParegentan && inputDay < dayOfParegentan)) { // If the input date is before the date of poon paregentan of that year:
        gaussEaster((inputYear - 1), monthOfEasterPtr, dayOfEasterPtr); // Runs the Guass Easter Algorithm to find the day of easter from the previous the inputYear
        yearOfParegentan = (inputYear - 1);

        int count = (50 - dayOfEaster); // Take off the days in the month of easter
        for (int m = (monthOfEaster - 1); m > 0; m--) { // Changes the month when the days run out in the current month
            for (int d = daysInMonths[m]; d > 0; d--) { // Loops the days back to reach Poon Paregentan
                if (count == 1) {
                    dayOfParegentan = d;
                    monthOfParegentan = m;
                    m = 0; // To exit the 1st loop
                    d = 0; // To exit the 2nd loop
                }
                else {count -= 1;}
            }
        }
    }

    printf("Date of Poon Paregentan in the year %d: %d-%d-%d\n", yearOfParegentan, monthOfParegentan, dayOfParegentan, yearOfParegentan);
    printf("Date of Easter in the year %d: %d-%d-%d\n\n", yearOfParegentan, monthOfEaster, dayOfEaster, yearOfParegentan);

    char* tone; // Will hold the tone for the given input date
    tone = toneFinder(monthOfParegentan, dayOfParegentan, inputMonth, inputDay, inputYear); // Runs the toneFinder function to find the tone for the given input date
    printf("The tone for %d-%d-%d is: %s", inputMonth, inputDay, inputYear, tone);
    return 0;
}

void gaussEaster(int year, int* month, int* day) { // Taken & altered from: https://www.geeksforgeeks.org/how-to-calculate-the-easter-date-for-a-given-year-using-gauss-algorithm/
    float A, B, C, P, Q, M, N, D, E;

    // All calculations done on the basis of the Gauss Easter Algorithm
    A = year % 19;
    B = year % 4;
    C = year % 7;
    P = floor((float)year / 100.0);
    Q = floor((float)(13 + 8 * P) / 25.0);
    M = (int)(15 - Q + P - (floor)(P / 4)) % 30;
    N = (int)(4 + P - (floor)(P / 4)) % 7;
    D = (int)(19 * A + M) % 30;
    E = (int)(2 * B + 4 * C + 6 * D + N) % 7;

    int daysAfter = (int)(22 + D + E);

    // A corner case: when D is 29, the date of Easter is April 19th
    if ((D == 29) && (E == 6)) {
        *month = 4;
        *day = 19;
        return;
    }
    // Another corner case: when D is 28, the date of Easter is April 18th
    else if ((D == 28) && (E == 6)) {
        *month = 4;
        *day = 18;
        return;
    }
    else { // When corner cases are not met:
        if (daysAfter > 31) { // If days > 31, move to the month of April (April = 4th Month)
            *month = 4;
            *day = (daysAfter - 31);
            return;
        }
        else { // Otherwise, stay on the month of March (March = 3rd Month)
            *month = 3;
            *day = daysAfter;
            return;
        }
    }
}

char* toneFinder(int monthOfParegentan, int dayOfParegentan, int month, int day, int year) {
    char *tones[8] = {"ԴԿ - Ta Gen", "ԱՁ - Ayp Tsa", "ԱԿ - Ayp Gen", "ԲՁ - Pen Tsa", "ԲԿ - Pen Gen", "ԳՁ - Kim Tsa", "ԳԿ - Kim Gen", "ԴՁ - Ta Tsa"};
    int daysPastParegentan = 0; // Holds the total amount of days past Poon Paregentan
    int daysInMonths[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // Holds the amount of days in each month
    if ((year % 100 == 0 && year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) { // If the given year is a leap year:
        daysInMonths[2] = 29; // February has 29 days
    }

    if (day == dayOfParegentan && month == monthOfParegentan) {} // Corner Case: If given day is the day of Paregentan don't do anything (daysPastParegentan = 0)
    else if (month == monthOfParegentan && day > dayOfParegentan) {daysPastParegentan += (day - dayOfParegentan); printf("The date is %d days after Poon Paregentan\n", daysPastParegentan);} // Corner Case: If given day is in the same month of Paregentan but later in the month
    else if (month < monthOfParegentan || (month == monthOfParegentan && day < dayOfParegentan)) { // If given date is earlier than the date of paregentan
        // Loops through the months backwards (2 -> 1 -> 12 -> 11 -> ...) from the inputMonth to the month of paregentan and adds the days to daysPastParegentan
        for (int i = (month + 12); i != monthOfParegentan; i--) {
            daysPastParegentan += daysInMonths[i % 13];
        }
        daysPastParegentan += day; // Adds the days in the inputMonth
        daysPastParegentan += (daysInMonths[monthOfParegentan] - dayOfParegentan); // Adds the days in the monthOfParegentan
        printf("The date is %d days after Poon Paregentan\n", daysPastParegentan);
    }
    else { // If given date is later than the date of easter
        // Loops through the months after the month of easter and adds the days to daysPastParegentan
        for (int i = (month - 1); i != monthOfParegentan; i--) {
            daysPastParegentan += daysInMonths[i];
        }
        daysPastParegentan += day; // Adds the days in the inputMonth
        daysPastParegentan += (daysInMonths[monthOfParegentan] - dayOfParegentan); // Adds the remaining days after Easter from the monthOfParegentan
        printf("The date is %d days after Poon Paregentan\n", daysPastParegentan);
    }

    return tones[daysPastParegentan % 8]; // Loops through the 8 modes and outputs the corresponding mode for the given input date
}