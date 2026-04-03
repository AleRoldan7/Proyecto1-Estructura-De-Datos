//
// Created by alejandro on 29/3/26.
//

#include "CargarCSV.h"

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// ═════════════════════════════════════════════════════════════
//  Constructor
// ═════════════════════════════════════════════════════════════

CargarCSV::CargarCSV(const string &rutaArchivo, const string &rutaLog) {
    this->rutaArchivo = rutaArchivo;
    this->rutaLog = rutaLog;
}

// ═════════════════════════════════════════════════════════════
//  Auxiliares privados
// ═════════════════════════════════════════════════════════════

string CargarCSV::quitarComillas(const string &campo) {
    string s = campo;
    // Eliminar espacios al inicio/fin
    while (!s.empty() && (s.front() == ' ' || s.front() == '\r')) s.erase(s.begin());
    while (!s.empty() && (s.back() == ' ' || s.back() == '\r')) s.pop_back();
    // Quitar comillas dobles que envuelven el campo
    if (s.size() >= 2 && s.front() == '"' && s.back() == '"') {
        s = s.substr(1, s.size() - 2);
    }
    return s;
}

bool CargarCSV::parsearLinea(const string &linea, string campos[], int numCampos) {
    int col = 0;
    bool dentroComillas = false;
    string campo = "";

    for (size_t i = 0; i < linea.size(); i++) {
        char c = linea[i];

        if (c == '"') {
            // Comilla doble dentro de campo ("") → comilla literal
            if (dentroComillas && i + 1 < linea.size() && linea[i + 1] == '"') {
                campo += '"';
                i++;
            } else {
                dentroComillas = !dentroComillas;
            }
        } else if (c == ',' && !dentroComillas) {
            if (col >= numCampos) return false; // más campos de lo esperado
            campos[col++] = quitarComillas(campo);
            campo = "";
        } else {
            campo += c;
        }
    }

    // Último campo
    if (col < numCampos) {
        campos[col++] = quitarComillas(campo);
    }

    // Verificar que tengamos exactamente numCampos
    return (col == numCampos);
}

void CargarCSV::loggear(ofstream &log, int numLinea,
                        const string &mensaje, const string &linea) {
    log << "[Linea " << numLinea << "] " << mensaje << "\n";
    log << "  Contenido: " << linea << "\n\n";
    cerr << "[CSV ERROR linea " << numLinea << "] " << mensaje << endl;
}

bool CargarCSV::esNumerico(const string &s) {
    if (s.empty()) return false;
    bool puntoVisto = false;
    size_t inicio = 0;
    if (s[0] == '-' || s[0] == '+') inicio = 1;
    if (inicio == s.size()) return false;
    for (size_t i = inicio; i < s.size(); i++) {
        if (s[i] == '.') {
            if (puntoVisto) return false;
            puntoVisto = true;
        } else if (s[i] < '0' || s[i] > '9') {
            return false;
        }
    }
    return true;
}

bool CargarCSV::esEntero(const string &s) {
    if (s.empty()) return false;
    for (char c: s) {
        if (c < '0' || c > '9') return false;
    }
    return true;
}

// ─────────────────────────────────────────────────────────────
//  rollback — deshace inserciones parciales si alguna estructura falló
// ─────────────────────────────────────────────────────────────
void CargarCSV::rollback(const Producto &p,
                         ArbolB *arbolB,
                         ArbolAvl *avl,
                         ArbolBMas *arbolBMas,
                         ListaEnlazada *lista,
                         bool insertadoB,
                         bool insertadoBMas,
                         bool insertadoAVL,
                         bool insertadoHash,
                         bool insertadoLista) {
    // Cada estructura debe exponer un método eliminar(clave).
    // Ajusta los nombres según tu implementación de cada una.
    if (insertadoB) arbolB->eliminar(p.getFechaCaducidad());
    if (insertadoAVL) avl->eliminar(p.getNombre());
    if (insertadoBMas) arbolBMas->eliminar(p.getCategoria(), p.getCodigo());
    if (insertadoLista) lista->eliminar(p.getCodigo());
}

// ═════════════════════════════════════════════════════════════
//  cargar — método principal
// ═════════════════════════════════════════════════════════════
int CargarCSV::cargar(ArbolB *arbolB,

                      ArbolAvl *avl,
                      ArbolBMas *arbolBMas,
                      ListaEnlazada *lista) {
    // ── 1. Verificar existencia y legibilidad ─────────────────
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cerr << "[CargadorCSV] ERROR: No se pudo abrir el archivo: "
                << rutaArchivo << endl;
        return 0;
    }

    // ── Abrir log de errores ──────────────────────────────────
    ofstream log(rutaLog);
    if (!log.is_open()) {
        cerr << "[CargadorCSV] ADVERTENCIA: No se pudo crear errors.log" << endl;
    }

    // ── Contadores ────────────────────────────────────────────
    int cargados = 0;
    int omitidos = 0;
    int numLinea = 0;

    // ── Set interno para detectar duplicados de CodigoBarra ──
    // (Sin std::unordered_set; usamos la propia TablaHash para verificar)

    string linea;
    const int NUM_CAMPOS = 7;

    // ── 2. Saltar la cabecera ─────────────────────────────────
    if (!getline(archivo, linea)) {
        cerr << "[CargadorCSV] El archivo esta vacio." << endl;
        archivo.close();
        return 0;
    }
    numLinea++;

    // ── 3. Procesar línea por línea ───────────────────────────
    while (getline(archivo, linea)) {
        numLinea++;

        // Ignorar líneas vacías o solo con retorno de carro
        if (linea.empty() || linea == "\r") continue;

        // ── 3a. Parsear la línea ──────────────────────────────
        string campos[NUM_CAMPOS];
        if (!parsearLinea(linea, campos, NUM_CAMPOS)) {
            loggear(log, numLinea, "Linea malformada (numero incorrecto de campos)", linea);
            omitidos++;
            continue;
        }

        string nombre = campos[0];
        string codigoBarra = campos[1];
        string categoria = campos[2];
        string fechaCaduc = campos[3];
        string marca = campos[4];
        string precioStr = campos[5];
        string stockStr = campos[6];

        // ── 3b. Validar campos no vacíos ──────────────────────
        if (nombre.empty() || codigoBarra.empty() || categoria.empty() ||
            fechaCaduc.empty() || marca.empty()) {
            loggear(log, numLinea, "Campo(s) obligatorio(s) vacios", linea);
            omitidos++;
            continue;
        }

        // ── 3c. Validar Precio numérico ───────────────────────
        if (!esNumerico(precioStr)) {
            loggear(log, numLinea, "Precio no es numerico: " + precioStr, linea);
            omitidos++;
            continue;
        }

        // ── 3d. Validar Stock entero ──────────────────────────
        if (!esEntero(stockStr)) {
            loggear(log, numLinea, "Stock no es entero: " + stockStr, linea);
            omitidos++;
            continue;
        }

        double precio = stod(precioStr);
        int stock = stoi(stockStr);


        // ── 3f. Crear el objeto Producto ──────────────────────
        Producto p(nombre, codigoBarra, categoria, fechaCaduc, marca, precio, stock);

        // ── 3g. Inserción atómica en todas las estructuras ────
        bool ok_B = false;
        bool ok_BMas = false;
        bool ok_AVL = false;
        bool ok_Hash = false;
        bool ok_Lista = false;

        // Árbol B (clave: fechaCaducidad)
        arbolB->insertar(p);
        ok_B = true;

        // Árbol B+ (clave: categoria)
        arbolBMas->insertar(p);
        ok_BMas = true;

        // Árbol AVL (clave: nombre)
        avl->insert(p);
        ok_AVL = true;


        // Lista enlazada
        lista->insert(p);
        ok_Lista = true;

        cargados++;
    }

    // ── 4. Cerrar archivos y reportar ─────────────────────────
    archivo.close();
    if (log.is_open()) log.close();

    cout << "\n[CargadorCSV] Carga completada." << endl;
    cout << "  Productos cargados : " << cargados << endl;
    cout << "  Productos omitidos : " << omitidos << endl;
    cout << "  Log de errores     : " << rutaLog << "\n" << endl;

    return cargados;
}
