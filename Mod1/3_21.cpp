//============================================================================
// Name        : Task21.cpp
// Author      : Artur Ambartsumov
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using std::cin;
using std::cout;

int count(int, int);

int main(void) {
    int peopleNumber = 0, //количество людей
        killNumber = 0;
    cin >> peopleNumber >> killNumber;
    cout << count(peopleNumber, killNumber);
    return 0;
}


int count(int peopleNumber, int killNumber) {
    int array[peopleNumber];
    for (int i = 0; i < peopleNumber; i++)
        array[i] = 0;
    int number = killNumber;
    int j = 0;

    for (int i = 0; i < peopleNumber; i++)   {
        array[number - 1] = 1;
        j = 0;
        while ((j < killNumber) && (i < peopleNumber - 1)) {
            if (array[number % peopleNumber] == 0) j++;
            number++;
        }
        number = number % peopleNumber;
        if (number == 0) number = peopleNumber;
    }

    return number;
}
