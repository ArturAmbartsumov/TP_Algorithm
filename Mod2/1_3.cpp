//============================================================================
// Name        : Mod2_Task1_3.cpp
// Author      : Artur Ambartsumov
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Замкнутая ломанная
//============================================================================

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct coordinate {
    double x; //координата начала прямоугольника
    double y; //высота прямоугольника

    coordinate() : x(0), y(0) {}
};

void read_array(vector<coordinate> &, int);
void print_array(vector<coordinate> &);
void broken_line(vector<coordinate> &);
int starting_point(vector<coordinate> &);
double calc_sin(coordinate, coordinate);



int main() {
    int N = 0;
    cin >> N;

    //Ввод точек
    vector<coordinate> points;
    read_array(points, N);

    broken_line(points);
    //Вывод отсортированных точек
    cout << endl;
    print_array(points);

    return 0;
}

void read_array(vector<coordinate> &data, int N) {
    coordinate temp;
    for (int i = 0; i < N; ++i) {
        coordinate temp;
        cin >> temp.x;
        cin >> temp.y;
        data.push_back(temp);
    }
}

void print_array(vector<coordinate> &data) {
    for (size_t i = 0; i < data.size(); i++)
        cout << data[i].x << " " << data[i].y << endl;
}

void broken_line(vector<coordinate> &points) {
    //Поиск начальной точки
    swap(points[0], points[starting_point(points)]);

    for (size_t i = 1; i < (points.size() - 1); i++) {
        size_t min = i;
        for (size_t j = i + 1; j < points.size(); j++) {
            double sin_min = calc_sin(points[0], points[min]);
            double sin_j = calc_sin(points[0], points[j]);
            if (sin_min < sin_j)
                min = j;
        }
    if (min != i)
        swap(points[i], points[min]);
    }
}

int starting_point(vector<coordinate> &points) {
    int min = 0;
    for (size_t i = 1; i < points.size(); ++i) {
        if ((points[i].x < points[min].x) || ((points[i].x == points[min].x) && (points[i].y < points[min].y)))
            min = i;
    }
    return min;
}

double calc_sin(coordinate a, coordinate b) {
    double radius = sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
    double mySin = (b.y - a.y) / radius;
    return mySin;
}
