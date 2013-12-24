#include <iostream>
#include <vector>

using std::swap;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Request {
    int Begin;
    int End;
    Request(int b, int e) : Begin(b), End(e) {};
};

void read_request_arr(vector <Request> &requests) {
    while ( true ) {
        int begin = 0, end = 0;
        cin >> begin >> end;
        if ( cin.eof() )
            break;
        Request request(begin, end);
        requests.push_back(request);
    }
}

bool less_End(const Request &left, const Request &right) {
    if ( left.End < right.End ) return true;
    return false;
}

//Сортировка заявок по окончаниям
void qSort_End(vector <Request> &data, int low, int high) {
    int i = low;
    int j = high;
    Request x = data[(low + high) / 2];
    do {
        while (less_End( data[i], x)) ++i;
        while (less_End( x, data[j])) --j;
        if (i <= j) {
            swap(data[i], data[j]);
            i++;
            j--;
        }
    } while (i <= j);
    if (low < j) qSort_End(data, low, j);
    if (i < high) qSort_End(data, i, high);
}

int Count(vector <Request> request) {
    qSort_End(request, 0, request.size() - 1);
    int counter = 1;
    int j = 0;

    for (size_t i = 1; i < request.size(); ++i) {
        //сравниваем текущию встречу с той, ктоторая раньше всех (из оставшихся) закончится
        if (request[i].Begin >= request[j].End) {
            ++counter;
            j = i;
        }
    }

    return counter;
}

int main() {
    vector <Request> requests;
    read_request_arr(requests);
    int N = 0;
    N = Count(requests);
    cout << N << endl;
    return 0;
}
