//============================================================================
// Name        : Task64.cpp
// Author      : Artur Ambartsumov
// Version     :
// Copyright   : Your copyright notice
// Description : Прямоугольники (задача на стеки)
//============================================================================

#define SIMPLE_BUFFER 5
#include <iostream>

using namespace std;

struct rect {
    int bedin; //координата начала прямоугольника
    int height; //высота прямоугольника

    rect() : bedin(0), height(0) {}
};

class CStack {
public:
     CStack(void);
    ~CStack();

    //Возможности дека
    void push(rect a);
    rect pop(void);
    void printElements(void);

    //Работа с массивом
    void buffGrow(void);

    //Для подсчёта площадей
    void calcMaxRect(rect &a); //вычисляет макс площадь для всех прямоульльников перед уманьшением и выкитывает их из стека
    int maxRect; //максимальная площадь прямоугольника, который можно вырезать


private:

    int back; //номер элемента массива, который является концом стека
    rect *buffer; //указатель на массив стека
    int bufferSize; //размер буфера

    //Для работы с прямоугольниками
    rect lastRect; //последнийэлемент стека
};

CStack::CStack() {
    bufferSize = SIMPLE_BUFFER;
    back = 0;
    buffer = new rect[bufferSize];
        buffer[0].bedin = 0;
        buffer[0].height = 0;
    maxRect = 0;
}

CStack::~CStack() {
    delete[] buffer;
}

void CStack::push(rect a) {
    if (a.height < lastRect.height) calcMaxRect(a);
    lastRect = a;
    buffer[back] = a;
    back++;
    if (back == bufferSize) buffGrow();
}

rect CStack::pop() {
    back--;
    rect result = buffer[back];
    lastRect = buffer[back - 1];
    return result;
}

void CStack::buffGrow() {
    rect *temp = new rect[bufferSize + SIMPLE_BUFFER];
    for (int i = 0; i < (back); i++) {
        temp[i] = buffer[i];
    }
    bufferSize += SIMPLE_BUFFER;
    delete[] buffer;
    buffer = temp;
}

void CStack::printElements() {
    cout << endl;
    for (int i = 0; i < back; i++)
        cout << buffer[i].bedin << " " << buffer[i].height << endl;
    cout << endl;
}

void CStack::calcMaxRect(rect &a) {
    rect temp;
    while (lastRect.height > a.height) {
        temp = pop();
        int rectSqr = temp.height * (a.bedin - temp.bedin);
        if (rectSqr > maxRect) maxRect = rectSqr;
    }
    a.bedin = temp.bedin;
}

int main()
{
    int rectN;
    cin >> rectN;

    int rectWidth = 0;
    rect a; //значение, которое закидываем в стек
    a.bedin = 0;
    a.height = 0;
    CStack myStack;

    myStack.push(a); //первый прямоуг. с нулевыми параметрами
    for (int i = 0; i < rectN; i++) {
        //ввод значения
        cin >> rectWidth >> a.height;
        myStack.push(a);
        a.bedin += rectWidth;
    }
    a.height = 0;
    myStack.push(a);
    cout << myStack.maxRect;
    return 0;
}
