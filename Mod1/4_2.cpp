//============================================================================
// Name        : Task42.cpp
// Author      : Artur Ambartsumov
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int topSearch(int *array, int n);
int maximum_of_three(int a, int b, int c);

int main() {
    int arrSize = 0;
    cin >> arrSize;
    int *array = new int(arrSize);

    for (int i = 0; (i < arrSize); i++)
        cin >> array[i];
    cout << (topSearch(&array[0], arrSize)) << endl;
    delete array;
    return 0;
}

int topSearch(int *array, int arrSize) {
    int m = arrSize / 2; //текущий элемент

    switch (arrSize) {
    case 1: return 0;
    case 2: //если осталось только 2 элемента
        if (array[0] > array[1]) m = 0; else m = 1;
        break;
    case 3: //если осталось только 3 элемента
        switch (maximum_of_three(array[m - 1], array[m], array[m + 1])) {
        case 1: m = 0;
            break;
        case 2: m = 2;
            break;
        case 0: m = 1;
            break;
        }
        return m;
        break;
    case 4: //если осталось только 4 элемента
        switch (maximum_of_three(array[m - 1], array[m], array[m + 1])) {
        case 1: m = topSearch(array, 2);
            break;
        case 2: m = 3;
            break;
        case 0:
            break;
        }
        return m;
        break;
    }

    switch (maximum_of_three(array[m - 1], array[m], array[m + 1]))
    {
        case 1: m = topSearch(array, m);
            break;
        case 2: m = m + topSearch(array + m + 1, arrSize - m - 1) + 1;
            break;
        case 0: return m;
            break;
    }
    return m;
}

//Возвращает 1 - если убывает, 2 - если возрастает, 0 - если вершина поцентру, -1 - если что-то пошло не так :)
int maximum_of_three(int a, int b, int c) {
    if (a > b) return 1;
    if (b < c) return 2;
    if ((b > c) && (b > a)) return 0;
    return -1;
}
