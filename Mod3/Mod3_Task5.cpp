#include <stdio.h>
#include <vector>
#include <limits.h>

struct  Couple{
    int A;
    int B;

    Couple(int a = INT_MAX, int b = INT_MAX) {
        if (a > b) {
            A = b;
            B = a;
        } else {
            A = a;
            B = b;
        }
    }

};

std::vector <std::vector<Couple> > SparseTable;
std::vector<int> logs;


Couple min_couple(Couple m1, Couple m2) {
    Couple m;
    if (m1.A == m2.A) {
        m.A = m1.A;
        m.B = m1.B < m2.B ? m1.B : m2.B;
    }
    else {
        if (m1.A < m2.A) {
            m.A = m1.A;
            m.B = m1.B < m2.A ? m1.B : m2.A;
        } else {
            m.A = m2.A;
            m.B = m2.B < m1.A ? m2.B : m1.A;
        }
    }

    return m;
}

void buildSparseTable(const std::vector<int> arr) {
    int size = arr.size();

    std::vector<Couple> buf;
    for (int i = 0; i < size; ++i) {
        int log = 0;
        for (int j = i; j >>=1 ; log++);
        logs.push_back(log);

        Couple m(arr[i]);
        buf.push_back(m);
    }

    int log = 0;
    for (int i = size; i >>= 1; log++);
    logs.push_back(log);

    SparseTable.push_back(buf);

    int t = 1;
    for (int k = 1; t <= size; ++k, t <<= 1) {
        std::vector<Couple> sparse_str;
        for (int i = 0; i + t <= size; ++i) {
            sparse_str.push_back(min_couple(SparseTable[k-1][i], SparseTable[k-1][i + t]));
        }
        SparseTable.push_back(sparse_str);
    }
}

Couple RMQ(int l, int r) {
    int k = logs[r - l + 1];
    int t = 1; t <<= k;
    return min_couple(SparseTable[k][l], SparseTable[k][r - t + 1]);
}

int main() {
    int n, m;
    std::vector<int> arr;
    scanf("%d%d", &n, &m);

    for (int i =0; i < n; ++i) {
        int a;
        scanf("%d", &a);
        arr.push_back(a);
    }

    buildSparseTable(arr);

    for (int i = 0; i < m; ++i) {
        int l, r;
        scanf("%d%d", &l, &r);

        printf("%d\n", RMQ(l - 1, r - 1).B);
    }

    return 0;
}
