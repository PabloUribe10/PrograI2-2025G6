#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "libestructurasPablo.h"

using namespace std;

struct Categoria
{
    int ID_categoria;
    char nombre[50];
};

struct Estudiante
{
    int ID_estudiante;
    char nombre[50];
    char apellido[50];
    char carrera[50];
    bool habilitado;
};

struct Multa
{
    int codigo_multa;
    int dias_multa;
    int dias_retraso;
    int ID_estudiante;
    fecha fecha_registro;
};

int generarCodigoAleatorio(int digitos = 6)
{
    int min = 1;
    for (int i = 1; i < digitos; i++)
        min *= 10;
    return min + rand() % (9 * min);
}

void limpiarTexto(char texto[])
{
    for (int i = 0; texto[i] != '\0'; i++)
    {
        unsigned char c = texto[i];
        if (c < 32 || c > 126)
            texto[i] = ' ';
    }
}

void normalizarEntrada(char texto[])
{
    for (int i = 0; texto[i] != '\0'; i++)
    {
        unsigned char c = texto[i];
        if (!((c >= 'A' && c <= 'Z') ||
              (c >= 'a' && c <= 'z') ||
              (c >= '0' && c <= '9') ||
              c == ' '))
            texto[i] = ' ';
    }
}

void ingresarFecha(fecha &f)
{
    cout << "Dia: ";
    cin >> f.dia;
    cout << "Mes: ";
    cin >> f.mes;
    cout << "Anio: ";
    cin >> f.anio;
}

void mostrarFecha(fecha f)
{
    cout << f.dia << "/" << f.mes << "/" << f.anio;
}

void agregarCategorias(vector<Categoria> &categorias)
{
    const char *nombres[] = {"Medicina", "Ingenieria", "Derecho"};
    for (int i = 0; i < 3; i++)
    {
        Categoria c;
        c.ID_categoria = i + 1;
        strcpy(c.nombre, nombres[i]);
        categorias.push_back(c);
    }
}

void agregarEstudiante(string archivoEstudiantes)
{
    fstream arch(archivoEstudiantes, ios::binary | ios::app);
    if (!arch.is_open())
        return;

    Estudiante e;
    e.ID_estudiante = generarCodigoAleatorio();
    cin.ignore();

    cout << "Nombre: ";
    cin.getline(e.nombre, 50);
    cout << "Apellido: ";
    cin.getline(e.apellido, 50);
    cout << "Carrera: ";
    cin.getline(e.carrera, 50);

    e.habilitado = true;

    arch.write((char *)&e, sizeof(Estudiante));
    arch.close();
}

void registrarMulta(string archivoMultas, int ID_estudiante, int dias)
{
    fstream arch(archivoMultas, ios::binary | ios::app);
    if (!arch.is_open())
        return;

    Multa m;
    m.codigo_multa = generarCodigoAleatorio();
    m.ID_estudiante = ID_estudiante;
    m.dias_retraso = dias;

    ingresarFecha(m.fecha_registro);

    arch.write((char *)&m, sizeof(Multa));
    arch.close();
}

void listadoMultas(string archivoMultas)
{
    ifstream arch(archivoMultas, ios::binary);
    if (!arch.is_open())
        return;

    Multa m;
    while (arch.read((char *)&m, sizeof(Multa)))
    {
        cout << "Codigo: " << m.codigo_multa << endl;
        cout << "ID Estudiante: " << m.ID_estudiante << endl;
        cout << "Dias retraso: " << m.dias_retraso << endl;
        cout << "Fecha: ";
        mostrarFecha(m.fecha_registro);
        cout << endl;
        cout << "--------------------" << endl;
    }
    arch.close();
}
