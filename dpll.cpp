#include <iostream>
using namespace std;

const int MAX_CLAUZE = 1000;
const int MAX_LUNGIME = 1000;
const int MAX_VARIABILE = 1000;

int clauze[MAX_CLAUZE][MAX_LUNGIME]={0};
int numarClauze;

bool satisfiabil(int nivel, int valori[]) {
    bool eliminat[MAX_CLAUZE] = {0};

    for (int i = 0; i < numarClauze; i++) {
        for (int j = 0; clauze[i][j] != 0; j++) {
            int lit = clauze[i][j];
            int val = valori[abs(lit)];
            if ((val == 1 && lit > 0) || (val == -1 && lit < 0)) {
                eliminat[i] = true;
                break;
            }
        }
    }

    for (int i = 0; i < numarClauze; i++) {
        if (eliminat[i]) continue;
        bool imposibil = true;
        for (int j = 0; clauze[i][j] != 0; j++) {
            int lit = clauze[i][j];
            int val = valori[abs(lit)];
            if (val == 0 || (val == 1 && lit > 0) || (val == -1 && lit < 0)) {
                imposibil = false;
                break;
            }
        }
        if (imposibil) return false;
    }

    bool toateEliminate = true;
    for (int i = 0; i < numarClauze; i++) {
        if (!eliminat[i]) {
            toateEliminate = false;
            break;
        }
    }
    if (toateEliminate) return true;

    for (int i = 0; i < numarClauze; i++) {
        if (eliminat[i]) continue;
        for (int j = 0; clauze[i][j] != 0; j++) {
            int lit = abs(clauze[i][j]);
            if (valori[lit] == 0) {
                valori[lit] = 1;
                if (satisfiabil(nivel + 1, valori)) return true;
                valori[lit] = -1;
                if (satisfiabil(nivel + 1, valori)) return true;
                valori[lit] = 0;
                return false;
            }
        }
    }

    return false;
}

int alegeVariabilaFrecventa(int valori[]) {
    int frecvente[MAX_VARIABILE] = {0};

    for (int i = 0; i < numarClauze; i++) {
        for (int j = 0; clauze[i][j] != 0; j++) {
            int lit = abs(clauze[i][j]);
            if (valori[lit] == 0) {
                frecvente[lit]++;
            }
        }
    }

    int maxVar = 0;
    for (int i = 1; i < MAX_VARIABILE; i++) {
        if (frecvente[i] > frecvente[maxVar]) {
            maxVar = i;
        }
    }

    return maxVar;
}

bool satisfiabilFrecventa(int nivel, int valori[]) {
    bool eliminat[MAX_CLAUZE] = {0};

    for (int i = 0; i < numarClauze; i++) {
        for (int j = 0; clauze[i][j] != 0; j++) {
            int lit = clauze[i][j];
            int val = valori[abs(lit)];
            if ((val == 1 && lit > 0) || (val == -1 && lit < 0)) {
                eliminat[i] = true;
                break;
            }
        }
    }

    for (int i = 0; i < numarClauze; i++) {
        if (eliminat[i]) continue;
        bool imposibil = true;
        for (int j = 0; clauze[i][j] != 0; j++) {
            int lit = clauze[i][j];
            int val = valori[abs(lit)];
            if (val == 0 || (val == 1 && lit > 0) || (val == -1 && lit < 0)) {
                imposibil = false;
                break;
            }
        }
        if (imposibil) return false;
    }

    bool toateEliminate = true;
    for (int i = 0; i < numarClauze; i++) {
        if (!eliminat[i]) {
            toateEliminate = false;
            break;
        }
    }
    if (toateEliminate) return true;

    int var = alegeVariabilaFrecventa(valori);
    if (var == 0) return false;

    valori[var] = 1;
    if (satisfiabilFrecventa(nivel + 1, valori)) return true;
    valori[var] = -1;
    if (satisfiabilFrecventa(nivel + 1, valori)) return true;
    valori[var] = 0;

    return false;
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

    int valori[MAX_VARIABILE] = {0};
    for (int i = 0; i < MAX_VARIABILE; i++) valori[i] = 0;

    cout << "\nDPLL cu primul literal gasit\n";
    if (satisfiabil(0, valori)) cout << "SAT\n";
    else cout << "NESAT\n";

    clock_t stop = clock();
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    printf("\nTime elapsed: %.5f\n", elapsed);
    start = clock();

    cout << "\nDPLL cu variabila cea mai frecventa\n";
    if (satisfiabilFrecventa(0, valori)) cout << "SAT\n";
    else cout << "NESAT\n";

    stop = clock();
    elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    printf("\nTime elapsed: %.5f\n", elapsed);
    return 0;
}
