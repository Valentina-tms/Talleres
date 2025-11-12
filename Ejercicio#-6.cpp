#include <iostream>
using namespace std;

int main() {
    
    int arr[] = {4, 7, 2, 4, 9, 7, 3, 1, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Lista de elementos:\n ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";

    cout << "Elementos duplicados en la lista:" << "\n";
    bool hayDuplicados = false;
    
    for (int i = 0; i < n; i++) {
        bool yaMostrado = false;
        for (int k = 0; k < i; k++) {
            if (arr[i] == arr[k]) {
                yaMostrado = true;
                break;
            }
        }

        if (yaMostrado) continue;

        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                cout << arr[i] << " ";
                hayDuplicados = true;
                break; 
            }
        }
    }

    if (!hayDuplicados) {
        cout << "No se encontraron duplicados.";
    }

    cout << "\n";
    return 0;
}