#include <iostream>
#include <string>
using namespace std;

int main() {
    const int N = 5; 
    string productos[N];
    int cantidades[N];
    int opcion, pos;
    int contador = 0;


    for (int i = 0; i < N; i++) {
        productos[i] = "";
        cantidades[i] = 0;
    }

    do {
        cout << "\n===== SISTEMA DE INVENTARIO =====" << "\n";
        cout << "1. Agregar producto" << "\n";
        cout << "2. Mostrar inventario" << "\n";
        cout << "3. Modificar cantidad" << "\n";
        cout << "4. Salir" << "\n";
        cout << "Elija una opcion: ";
        cin >> opcion;

        cin.ignore(); 

        switch (opcion) {
            case 1:
                if (contador < N) {
                    cout << "Ingrese el nombre del producto, por favor: ";
                    getline(cin, productos[contador]);  
                    cout << "Ingrese la cantidad, por favor: ";
                    cin >> cantidades[contador];
                    contador++;
                } else {
                    cout << "Inventario lleno" << "\n";
                }
                break;

            case 2:
                cout << "\n--- INVENTARIO ---" << "\n";
                if (contador == 0) {
                    cout << "Inventario vacío" << "\n";
                }
                for (int i = 0; i < contador; i++) {
                    cout << i << ". " << productos[i] << " - Cantidad: " << cantidades[i] << "\n";
                }
                break;

            case 3:
                cout << "Ingrese el número del producto a modificar: ";
                cin >> pos;
                if (pos >= 0 && pos < contador) {
                    cout << "Nueva cantidad para " << productos[pos] << ": ";
                    cin >> cantidades[pos];
                } else {
                    cout << "Producto no válido" << "\n";
                }
                break;

            case 4:
                cout << "Saliendo del sistema..." << "\n";
                break;

            default:
                cout << "Opcion invalida!" << "\n";
        }
    } while (opcion != 4);

    return 0;
}