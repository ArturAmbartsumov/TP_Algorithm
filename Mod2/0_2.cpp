#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;


void reed_array(vector<int> &data) {
    while (!cin.eof()) {
        string line;
        getline(cin, line);

        if (!(line.empty() || cin.eof())) {
            int num = atoi(line.c_str());
            data.push_back(num);

        }
    }
}

void print_array(vector<int> &data) {
    for (size_t i; i < data.size(); i++)
        cout << data[i] << endl;
}


void selection_sort(vector<int> &data){
    for (size_t i = 0; i < (data.size() - 1); i++) {
        size_t min = i;
        for (size_t j = i + 1; j < data.size(); j++)
            if (data[min] > data[j])
                min = j;
    if (min != i)
        swap(data[i], data[min]);
    }
}

int main()
{
    vector<int> arr;
    //ввод данных
    reed_array(arr);
    selection_sort(arr);
    print_array(arr);
    return 0;
}

