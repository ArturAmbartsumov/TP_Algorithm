#include <iostream>
#include <vector>
#include <stdint.h>

using std::vector;
using std::cout;
using std::endl;
using std::cin;


typedef long long Sint64;

Sint64 number_of_the_pyramids(size_t n) {
    //Инициализация матрицы
    vector< vector<Sint64> > matrix;
    matrix.resize(n+1);
    for (size_t i = 0; i < n + 1; ++i) {
        matrix[i].resize(i+3);
    }

    //Диагональные элементы
    for (size_t i = 1; i < n + 1; ++i ) {
        matrix[i][i] = 1;
    }

    for (size_t i = 1; i < n + 1; ++i) {
        for (int j = i - 1; j >= 1; --j) {
            matrix[i][j] = matrix[i - j][j] // есть столбик k
            + matrix[i][j + 1]; // нет столбика k ;
        }
    }

    return matrix[n][1];
}

int main() {
    size_t n = 0;
    cin >> n;
    Sint64 var = 0;
    var = number_of_the_pyramids(n);
    cout << var << endl;
    return 0;
}
