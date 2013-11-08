//============================================================================
// Name        : Task52.cpp
// Author      : Artur Ambartsumov
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Дек с динамическим массивом
//============================================================================

#define SIMPLE_BUFFER 5
#include <iostream>
using namespace std;


class Dek {
public:
     Dek(void);
    ~Dek();

    //Возможности дека
    void PushBack(int a);
    void PushFront(int a);
    int PopBack();
    int PopFront();
    void PrintElements();

    //Работа с массивом
    void buffGrow();

private:
    int back; //номер элемента массива, который является концом стека
    int front; //номер элемента массива, который является началом стека
    int *buffer; //указатель на массив стека
    int bufferSize; //размер буфера
    int number_of_elements; //текущее число элементов
};

Dek::Dek() {
    bufferSize = SIMPLE_BUFFER;
    back = 0;
    front = 0;
    number_of_elements = 0;
    buffer = new int[bufferSize];
}

Dek::~Dek() {
    delete[] buffer;
}

void Dek::PushBack(int a) {
    buffer[back] = a;
    number_of_elements++;
    back++;
    if (back == bufferSize) back = 0;
    if (back == front) buffGrow();
}

int Dek::PopBack() {
    if (number_of_elements == 0) return -1;
    back--;
    if (back == -1) back = bufferSize - 1;
    int result = buffer[back];
    number_of_elements--;
    return result;
}

void Dek::PushFront(int a) {
    front--;
    if (front == -1) front = bufferSize - 1;
    buffer[front] = a;
    number_of_elements++;
    if (back == front) buffGrow();
}

int Dek::PopFront() {
    if (number_of_elements == 0) return -1;
    int result = buffer[front];
    front++;
    if (front == bufferSize) front = 0;
    number_of_elements--;
    return result;
}

void Dek::buffGrow() {
    int *temp = new int[bufferSize + SIMPLE_BUFFER];
    for (int i = 0; i < (number_of_elements); i++) {
        temp[i] = buffer[(front + i) % bufferSize];
    }
    bufferSize += SIMPLE_BUFFER;
    delete[] buffer;
    buffer = temp;
    front = 0;
    back = number_of_elements;
}

void Dek::PrintElements() {
    for (int i = 0; i < number_of_elements; i++)
        cout << buffer[(front + i) % bufferSize] << " ";
    cout << endl;
    for (int i = 0; i < bufferSize; i++)
        cout << buffer[i] << " ";
    cout << endl;
}

int main() {
    int number_of_instructions;
    int command_A = 0;
    int command_B = 0;
    int res = 1;


    cin >> number_of_instructions;

    Dek newDek;
    for (int i = 0; i < number_of_instructions; i++) {
        cin >> command_A >> command_B;
        switch (command_A) {
        case 1:
            newDek.PushBack(command_B);
            break;
        case 2:
            if (newDek.PopBack() != command_B)
                res = 0;
            break;
        case 3:
            newDek.PushFront(command_B);
            break;
        case 4:
            if (newDek.PopFront() != command_B)
                res = 0;
            break;
        }
    }
    if (res == 1) cout << "YES" << endl;
    if (res == 0) cout << "NO" << endl;

    return 0;
}
