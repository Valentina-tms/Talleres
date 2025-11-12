#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

// =========================
// Clase Habitacion
// =========================
class Habitacion {
private:
    int numero;
    string tipo;
    double precioPorNoche;
    bool disponible;

public:
    Habitacion(int num, string t, double precio)
        : numero(num), tipo(t), precioPorNoche(precio), disponible(true) {}

    int getNumero() const { return numero; }
    string getTipo() const { return tipo; }
    double getPrecioPorNoche() const { return precioPorNoche; }
    bool estaDisponible() const { return disponible; }

    void marcarOcupada() { disponible = false; }
    void marcarDisponible() { disponible = true; }

    void mostrarInfo() const {
        cout << "Habitación " << numero << " (" << tipo << ") - "
             << (disponible ? "Disponible" : "Ocupada")
             << " - $" << precioPorNoche << "/noche" << endl;
    }
};

// =========================
// Clase Cliente
// =========================
class Cliente {
private:
    string nombre;
    string email;
    string telefono;

public:
    Cliente(string n, string e, string t)
        : nombre(n), email(e), telefono(t) {}

    string getNombre() const { return nombre; }

    void mostrarInfo() const {
        cout << "Cliente: " << nombre << " (" << email << ", " << telefono << ")" << endl;
    }
};

// =========================
// Clase Reserva
// =========================
class Reserva {
private:
    Cliente cliente;
    Habitacion* habitacion;
    tm fechaEntrada;
    tm fechaSalida;

public:
    Reserva(Cliente c, Habitacion* h, tm entrada, tm salida)
        : cliente(c), habitacion(h), fechaEntrada(entrada), fechaSalida(salida) {}

    double calcularCostoTotal() const {
        time_t tEntrada = mktime(const_cast<tm*>(&fechaEntrada));
        time_t tSalida = mktime(const_cast<tm*>(&fechaSalida));
        double dias = difftime(tSalida, tEntrada) / (60 * 60 * 24);
        return dias * habitacion->getPrecioPorNoche();
    }

    void mostrarInfo() const {
        cout << "Reserva de " << cliente.getNombre()
             << " en habitación " << habitacion->getNumero()
             << " del " << fechaEntrada.tm_mday << "/" << (fechaEntrada.tm_mon + 1)
             << " al " << fechaSalida.tm_mday << "/" << (fechaSalida.tm_mon + 1)
             << " - Total: $" << calcularCostoTotal() << endl;
    }

    Habitacion* getHabitacion() const { return habitacion; }
};

// =========================
// Clase Hotel
// =========================
class Hotel {
private:
    string nombre;
    vector<Habitacion> habitaciones;
    vector<Cliente> clientes;
    vector<Reserva> reservas;

public:
    Hotel(string n) : nombre(n) {}

    void registrarHabitacion(const Habitacion& h) {
        habitaciones.push_back(h);
        cout << "Habitación registrada correctamente.\n";
    }

    void registrarCliente(const Cliente& c) {
        clientes.push_back(c);
        cout << "Cliente registrado correctamente.\n";
    }

    void mostrarHabitacionesDisponibles() {
        bool hayDisponibles = false;
        for (const auto& h : habitaciones) {
            if (h.estaDisponible()) {
                h.mostrarInfo();
                hayDisponibles = true;
            }
        }
        if (!hayDisponibles) cout << "No hay habitaciones disponibles.\n";
    }

    Habitacion* buscarHabitacionPorNumero(int numero) {
        for (auto& h : habitaciones) {
            if (h.getNumero() == numero) return &h;
        }
        return nullptr;
    }

    Cliente* buscarClientePorNombre(const string& nombre) {
        for (auto& c : clientes) {
            if (c.getNombre() == nombre) return &c;
        }
        return nullptr;
    }

    void hacerReserva(string nombreCliente, int numeroHabitacion, tm entrada, tm salida) {
        Cliente* cliente = buscarClientePorNombre(nombreCliente);
        Habitacion* habitacion = buscarHabitacionPorNumero(numeroHabitacion);

        if (!cliente) {
            cout << "Cliente no encontrado.\n";
            return;
        }
        if (!habitacion) {
            cout << "Habitación no encontrada.\n";
            return;
        }
        if (!habitacion->estaDisponible()) {
            cout << "La habitación ya está ocupada.\n";
            return;
        }

        habitacion->marcarOcupada();
        reservas.emplace_back(*cliente, habitacion, entrada, salida);
        cout << "Reserva realizada con éxito.\n";
    }

    void cancelarReserva(int numeroHabitacion) {
        for (auto it = reservas.begin(); it != reservas.end(); ++it) {
            if (it->getHabitacion()->getNumero() == numeroHabitacion) {
                it->getHabitacion()->marcarDisponible();
                reservas.erase(it);
                cout << " Reserva cancelada correctamente.\n";
                return;
            }
        }
        cout << "No se encontró la reserva.\n";
    }

    void mostrarReservas() {
        if (reservas.empty()) {
            cout << "No hay reservas registradas.\n";
        } else {
            for (const auto& r : reservas) r.mostrarInfo();
        }
    }
};

// =========================
// Función auxiliar para crear fecha
// =========================
tm crearFecha(int dia, int mes, int anio) {
    tm fecha = {0};
    fecha.tm_mday = dia;
    fecha.tm_mon = mes - 1;
    fecha.tm_year = anio - 1900;
    return fecha;
}

// =========================
// Función principal
// =========================
int main() {
    Hotel hotel("Hotel Sueñotel");
    cout<<"**********************\n";
    cout<<"Hotel Sueñotel\n";
    cout<<"**********************\n";
    
    // Registrar habitaciones
    hotel.registrarHabitacion(Habitacion(101, "Simple", 80.0));
    hotel.registrarHabitacion(Habitacion(102, "Doble", 120.0));
    hotel.registrarHabitacion(Habitacion(201, "Suite", 200.0));

    // Registrar clientes
    hotel.registrarCliente(Cliente("Nathy", "nathy@gmail.com", "3001234567"));
    hotel.registrarCliente(Cliente("Mason", "mason@gmail.com", "3109876543"));

    cout << "\n Habitaciones disponibles:\n";
    hotel.mostrarHabitacionesDisponibles();

    // Crear fechas
    tm entrada = crearFecha(12, 11, 2025);
    tm salida = crearFecha(15, 11, 2025);

    // Hacer reserva
    hotel.hacerReserva("Nathy", 101, entrada, salida);

    cout << "\n Reservas actuales:\n";
    hotel.mostrarReservas();

    // Cancelar reserva
    cout << "\n Cancelando reserva de la habitación 101...\n";
    hotel.cancelarReserva(101);

    cout << "\n Habitaciones disponibles nuevamente:\n";
    hotel.mostrarHabitacionesDisponibles();

    return 0;
}
