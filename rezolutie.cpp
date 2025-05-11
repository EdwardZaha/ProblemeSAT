#include <iostream>
#include <cstring>
using namespace std;

const int MAX_CLAUZE = 1000;
const int MAX_LUNGIME = 1000;
const int OFFSET = 1000;

int clauze[MAX_CLAUZE][MAX_LUNGIME] = {0};
int numarClauze;

bool suntEgale(int a[], int b[]) {
    for (int i = 0; i < MAX_LUNGIME; i++) {
        if (a[i] != b[i]) return false;
        if (a[i] == 0 && b[i] == 0) return true;
    }
    return true;
}

bool existaClauza(int clauzaNoua[]) {
    for (int i = 0; i < numarClauze; i++) {
        if (suntEgale(clauze[i], clauzaNoua)) return true;
    }
    return false;
}

bool esteVid(int clauza[]) {
    return clauza[0] == 0;
}

bool rezolutie() {
    bool modificat = true;

    while (modificat) {
        modificat = false;
        int numarCurent = numarClauze;

        for (int i = 0; i < numarCurent; i++) {
            for (int j = i + 1; j < numarCurent; j++) {
                for (int k = 0; clauze[i][k] != 0; k++) {
                    for (int l = 0; clauze[j][l] != 0; l++) {
                        if (clauze[i][k] == -clauze[j][l]) {
                            int nouaClauza[MAX_LUNGIME] = {0};
                            int index = 0;
                            bool folosit[2 * OFFSET + 1] = {0};

                            for (int m = 0; clauze[i][m] != 0; m++) {
                                int lit = clauze[i][m];
                                if (lit != clauze[i][k] && !folosit[lit + OFFSET]) {
                                    nouaClauza[index++] = lit;
                                    folosit[lit + OFFSET] = true;
                                }
                            }

                            for (int m = 0; clauze[j][m] != 0; m++) {
                                int lit = clauze[j][m];
                                if (lit != clauze[j][l] && !folosit[lit + OFFSET]) {
                                    nouaClauza[index++] = lit;
                                    folosit[lit + OFFSET] = true;
                                }
                            }

                            nouaClauza[index] = 0;

                            if (esteVid(nouaClauza)) return false;

                            if (!existaClauza(nouaClauza)) {
                                if (numarClauze >= MAX_CLAUZE) {
                                    return false;
                                }

                                for (int y = 0; y < MAX_LUNGIME; y++) {
                                    clauze[numarClauze][y] = nouaClauza[y];
                                    if (nouaClauza[y] == 0) break;
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

    return true;
}

int main() {
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

    bool rezultat = rezolutie();

    if (rezultat)
        cout << "SAT\n";
    else
        cout << "NESAT\n";

    clock_t stop = clock();
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    printf("\nTime elapsed: %.5f\n", elapsed);
    return 0;
}