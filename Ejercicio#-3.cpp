#include <iostream>
using namespace std;

int main() {
    const int N = 4;
    int matriz[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matriz[i][j] = i * N + j + 1;  
        }
    }
    //Mostrar matriz original
    cout << "Matriz original:" << "\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << matriz[i][j] << "\t";
        }
        cout << "\n\n";
    }
    //Mostrar matriz transpuesta
    cout << "Matriz transpuesta:" << "\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << matriz[j][i] << "\t";  
        }
        cout << "\n";
    }

    return 0;
}