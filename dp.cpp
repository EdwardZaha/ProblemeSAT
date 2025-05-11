#include <iostream>
#include <cstring>
using namespace std;

const int MAX_CLAUZE = 1000;
const int MAX_LUNGIME = 1000;

int clauze[MAX_CLAUZE][MAX_LUNGIME]={0};
int numarClauze;
int numarVariabile;

bool suntEgale(int a[], int b[]) {
    for (int i = 0; i < MAX_LUNGIME; i++) {
        if (a[i] != b[i]) return false;
        if (a[i] == 0 && b[i] == 0) return true;
    }
    return true;
}

bool existaClauza(int rezolventa[]) {
    for (int i = 0; i < numarClauze; i++) {
        if (suntEgale(clauze[i], rezolventa)) return true;
    }
    return false;
}

bool esteVid(int c[]) {
    return c[0] == 0;
}

bool dp() {
    bool modificat = true;

    while (modificat) {
        modificat = false;

        for (int i = 0; i < numarClauze; i++) {
            for (int j = i + 1; j < numarClauze; j++) {
                for (int k = 0; clauze[i][k] != 0; k++) {
                    for (int l = 0; clauze[j][l] != 0; l++) {
                        if (clauze[i][k] == -clauze[j][l]) {
                            int rezolventa[MAX_LUNGIME] = {0};
                            int idx = 0;
                            bool folosit[2001] = {0};

                            for (int m = 0; clauze[i][m] != 0; m++) {
                                int lit = clauze[i][m];
                                if (lit != clauze[i][k] && !folosit[lit + 1000]) {
                                    rezolventa[idx++] = lit;
                                    folosit[lit + 1000] = true;
                                }
                            }

                            for (int m = 0; clauze[j][m] != 0; m++) {
                                int lit = clauze[j][m];
                                if (lit != clauze[j][l] && !folosit[lit + 1000]) {
                                    rezolventa[idx++] = lit;
                                    folosit[lit + 1000] = true;
                                }
                            }

                            rezolventa[idx] = 0;

                            if (esteVid(rezolventa)) return false;

                            if (!existaClauza(rezolventa) && numarClauze < MAX_CLAUZE) {
                                for (int y = 0; y < MAX_LUNGIME; y++) {
                                    clauze[numarClauze][y] = rezolventa[y];
                                    if (rezolventa[y] == 0) break;
                                }
                                numarClauze++;
                                modificat = true;
                            }
                        }
                    }
                }
            }
        }
    }

    if (numarClauze == 0) return true;

    return false;
}

int main() {
    cout << "nr var: ";
    cin >> numarVariabile;
    cout << "nr clauze: ";
    cin >> numarClauze;
    int lng=0;
    cout << "nr lungime: ";
    cin >> lng;

    for (int i = 0; i < numarClauze; i++) {
        for (int j = 0; j < lng; j++) {
            cin >> clauze[i][j];
        }
    }

    clock_t start = clock();

    bool rezultat = dp();

    if (rezultat)
        cout << "SAT\n";
    else
        cout << "NESAT\n";

    clock_t stop = clock();
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    printf("\nTime elapsed: %.5f\n", elapsed);
    return 0;
}