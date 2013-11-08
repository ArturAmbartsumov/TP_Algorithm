//============================================================================
// Name        : 7_2.cpp
// Author      : Artur Ambartsumov
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Быстрое сложение
//============================================================================

#define SIMPLE_BUFFER 5
#include <iostream>

using namespace std;

int fastSum(int *, size_t);

class CHeap {
public:
    CHeap(int *arr, size_t arrSize);
   ~CHeap();

    //Возможности кучи
    void addArr(int *arr, size_t arrSize); //записывает в объект массив и применяет к нему buildHeap
    void heapify(size_t i);
    void buildHeap(void);
    void add(int element); //добавить элемент
    int extractMin(void);
    int readMin(void);

    //Работа с массивом
    void buffGrow(void);

    size_t elementsNumber;

private:
    int *buffer;
    size_t bufferSize;
};

CHeap::CHeap(int *arr = NULL, size_t arrSize = 0) {
    bufferSize = SIMPLE_BUFFER;
    elementsNumber = 0;
    buffer = new int[bufferSize];
    if (arr != NULL && arrSize != 0)
        addArr(arr, arrSize);
}

CHeap::~CHeap() {
    delete[] buffer;
}

void CHeap::buffGrow(void) {
    int *temp = new int[bufferSize + SIMPLE_BUFFER];
    if (elementsNumber != 0) {
        for (int i = 0; i < (bufferSize); i++) {
            temp[i] = buffer[i];
        }
    }
    bufferSize += SIMPLE_BUFFER;
    delete[] buffer;
    buffer = temp;
}

void CHeap::addArr(int *arr, size_t arrSize) {
    while (arrSize >= bufferSize)
        buffGrow();
    elementsNumber = arrSize;
    for (size_t i = 0; i < elementsNumber; i++)
        buffer[i] = arr[i];
    buildHeap();
}

void CHeap::heapify(size_t i) {
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    //Ищем маньшего сына
    size_t smallest = i;
    if (left < elementsNumber && buffer[left] < buffer[i])
        smallest = left;
    if (right < elementsNumber && buffer[right] < buffer[smallest])
        smallest = right;

    //Если есть меньший сын ...
    if (smallest != i) {
        swap(buffer[smallest], buffer[i]);
        CHeap::heapify(smallest);
    }
}

void CHeap::buildHeap(void) {
    for (int i = (elementsNumber / 2 - 1); i >= 0; --i)
        heapify(i);
}

void CHeap::add(int element) {
    buffer[elementsNumber] = element;
    elementsNumber++;
    if (elementsNumber >= bufferSize) CHeap::buffGrow();

    int i = elementsNumber - 1;
    while (i > 0) {
        int parent = (i-1) / 2;
        if (buffer[i] >= buffer[parent])
            return;
        swap(buffer[i], buffer[parent]);
        i = parent;
    }
}

int CHeap::readMin(void) {
    return buffer[0];
}

int CHeap::extractMin(void) {
    if (elementsNumber == 0) return 0;

    int result = buffer[0];
    buffer[0] = buffer[elementsNumber - 1];
    elementsNumber--;
    if (elementsNumber > 1) heapify(0);
    return result;
}

int main()
{
    size_t N = 5;
    cin >> N;

    int *arr;
    arr = new int[N];

    for (size_t i = 0; i < N; i++)
        cin >> arr[i];
    cout << fastSum(arr, N);

    delete[] arr;
    return 0;
}


int fastSum(int *arr, size_t arrSize) {
    if (arrSize <= 1) return 0;

    CHeap myHeap(arr, arrSize);
    int total_sum = 0;

    while (myHeap.elementsNumber > 1) {
        int min1 = myHeap.extractMin();
        int min2 = myHeap.extractMin();
        int sum = min1 + min2;
        total_sum += sum;
        myHeap.add(sum);
    }
    return total_sum;
}
