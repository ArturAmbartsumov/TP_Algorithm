#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#define SIMPLE_BUFFER 1000

using namespace std;

struct point{
    double coord; //координата
    bool id; //определяет является точка концим отрезка или началом (0, если это начало, 1, если это конец)
    point(): coord(0), id(0){}

};

void read_lines(vector<point> &, int);
void print_points(vector<point> &);
void heap_sort(vector<point> &);
double paint_lines(vector<point> &);

class CHeap {
public:
    CHeap(point *arr, size_t arrSize);
   ~CHeap();

    //Возможности кучи
    void addArr(point *arr, size_t arrSize); //записывает в объект массив и применяет к нему buildHeap
    void heapify(size_t i);
    void buildHeap(void);
    void add(point element); //добавить элемент
    point extractMin(void);
    point readMin(void);

    //Работа с массивом
    void buffGrow(void);

    size_t elementsNumber;

private:
    point *buffer;
    size_t bufferSize;
};

CHeap::CHeap(point *arr = NULL, size_t arrSize = 0) {
    bufferSize = SIMPLE_BUFFER;
    elementsNumber = 0;
    buffer = new point[bufferSize];
    if (arr != NULL && arrSize != 0)
        addArr(arr, arrSize);
}

CHeap::~CHeap() {
    delete[] buffer;
}

void CHeap::buffGrow(void) {
    point *temp = new point[bufferSize + SIMPLE_BUFFER];
    if (elementsNumber != 0) {
        for (int i = 0; i < (bufferSize); i++) {
            temp[i] = buffer[i];
        }
    }
    bufferSize += SIMPLE_BUFFER;
    delete[] buffer;
    buffer = temp;
}

void CHeap::addArr(point *arr, size_t arrSize) {
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
    if (left < elementsNumber && buffer[left].coord < buffer[i].coord)
        smallest = left;
    if (right < elementsNumber && buffer[right].coord < buffer[smallest].coord)
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

void CHeap::add(point element) {
    buffer[elementsNumber] = element;
    elementsNumber++;
    if (elementsNumber >= bufferSize) CHeap::buffGrow();

    int i = elementsNumber - 1;
    while (i > 0) {
        int parent = (i-1) / 2;
        if (buffer[i].coord >= buffer[parent].coord)
            return;
        swap(buffer[i].coord, buffer[parent].coord);
        i = parent;
    }
}

point CHeap::readMin(void) {
    return buffer[0];
}

point CHeap::extractMin(void) {
    point result;
    if (elementsNumber == 0) return result;

    result = buffer[0];
    buffer[0] = buffer[elementsNumber - 1];
    elementsNumber--;
    if (elementsNumber > 1) heapify(0);
    return result;
}

int main()
{
    int N = 0; //число отрезков
    vector<point> pointsArr;
    scanf("%d", &N);
    read_lines(pointsArr, N);
    cout << paint_lines(pointsArr);
    return 0;
}

double paint_lines(vector<point> &pointsArr) {
    heap_sort(pointsArr);
    double total_length = 0;
    int layer_counter = 0;
    for (size_t i = 0; i < (pointsArr.size() - 1); ++i) {

        if (!pointsArr[i].id) ++layer_counter;
        else --layer_counter;

        if (layer_counter == 1) total_length += pointsArr[i + 1].coord - pointsArr[i].coord;
    }
    return total_length;
}

void heap_sort(vector<point> &pointsArr) {
    CHeap myHeap(&pointsArr[0], pointsArr.size());
    for (size_t i = 0; i < pointsArr.size(); ++i) {
        pointsArr[i] = myHeap.extractMin();
    }
}

void read_lines(vector<point> &pointsArr, int N) {
    for (size_t i = 0; i < N; i++) {
        point dot;

        scanf("%lf", &dot.coord);
        dot.id = 0;
        pointsArr.push_back(dot);

        scanf("%lf", &dot.coord);
        dot.id = 1;
        pointsArr.push_back(dot);

    }
}

void print_points(vector<point> &pointsArr) {
    for (size_t i = 0; i < pointsArr.size(); i += 2)
        scanf("%lf %d/t%lf %d", pointsArr[i].coord, pointsArr[i].id, pointsArr[i + 1].coord, pointsArr[i + 1].id);
}
