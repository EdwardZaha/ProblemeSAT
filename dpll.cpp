#include <iostream>
using namespace std;

int main() {
    int formula[1000][3]={0};
    formula[0][0]=1;
    formula[0][1]=2;
    formula[0][2]=3;
    for (int i = 1; i < 999; i++) {
        formula[i][0] = -(i + 1);
        formula[i][1] = i + 2;
        formula[i][2] = 0;
    }
    formula[999][0] = -1000;
    formula[999][1] = 0;

    for (int i=0; i<=999; i++) {
        cout << "{";
        for (int j=0; j<=2; j++) {
            cout << formula[i][j];
            if (j<2) cout << ", ";
        }
        cout << "}";
        if (i<999) cout << ",";
        cout << "\n";
    }
    return 0;
}