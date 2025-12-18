#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "libestructurasPablo.h" 

using namespace std;


struct Carrera
{
    int ID_carrera;
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
    int dias_retraso;
    int ID_estudiante;
    Fecha fecha_registro; 
};


int generarCodigoAleatorio(int digitos = 6)
{
    int min = 1;
    for (int i = 1; i < digitos; i++)
        min *= 10;
    return min + rand() % (9 * min);
}


void agregarCarreras(vector<Carrera> &carreras)
{
    const char *nombres[] = {"Medicina", "Ingenieria", "Derecho"};
    for (int i = 0; i < 3; i++)
    {
        Carrera c;
        c.ID_carrera = i + 1;
        strcpy(c.nombre, nombres[i]);
        carreras.push_back(c);
    }
}

void listadoCarreras(vector<Carrera> &carreras)
{
    cout << "LISTADO DE CARRERAS\n";
    for (size_t i = 0; i < carreras.size(); i++)
    {
        cout << carreras[i].ID_carrera << " - "
             << carreras[i].nombre << endl;
    }
}


void agregarEstudiante(string archivoEstudiantes)
{
    fstream arch(archivoEstudiantes, ios::binary | ios::app);
    if (!arch.is_open())
        return;

    Estudiante e;
    e.ID_estudiante = generarCodigoAleatorio();
    e.habilitado = true;

    cin.ignore();
    cout << "Nombre: ";
    cin.getline(e.nombre, 50);
    cout << "Apellido: ";
    cin.getline(e.apellido, 50);
    cout << "Carrera: ";
    cin.getline(e.carrera, 50);

    arch.write((char *)&e, sizeof(Estudiante));
    arch.close();
}

void imprimirEstudiantesTXT(string archivoEstudiantes, string archivoSalida)
{
    ifstream arch(archivoEstudiantes, ios::binary);
    if (!arch.is_open()) return;

    ofstream archTXT(archivoSalida);
    if (!archTXT.is_open()) return;

    Estudiante e;
    while (arch.read((char*)&e, sizeof(Estudiante)))
    {
        archTXT << e.nombre << " " << e.apellido
                << " - " << e.carrera << "\n";
    }

    arch.close();
    archTXT.close();
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

    cout << "Fecha de registro:\n";
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
    cout << "LISTADO DE MULTAS\n";

    while (arch.read((char *)&m, sizeof(Multa)))
    {
        cout << "Codigo: " << m.codigo_multa << endl;
        cout << "ID Estudiante: " << m.ID_estudiante << endl;
        cout << "Dias retraso: " << m.dias_retraso << endl;
        cout << "Fecha: ";
        mostrarFecha(m.fecha_registro); 
        cout << "\n--------------------\n";
    }
    arch.close();
}

void imprimirMultasTXT(string archivoMultas, string archivoSalida)
{
    ifstream arch(archivoMultas, ios::binary);
    if (!arch.is_open()) return;

    ofstream archTXT(archivoSalida);
    if (!archTXT.is_open()) return;

    Multa m;
    while (arch.read((char*)&m, sizeof(Multa)))
    {
        archTXT << "Codigo: " << m.codigo_multa
                << ", ID Estudiante: " << m.ID_estudiante
                << ", Dias retraso: " << m.dias_retraso
                << ", Fecha: " << m.fecha_registro.dia
                << "/" << m.fecha_registro.mes
                << "/" << m.fecha_registro.anio
                << "\n";
    }

    arch.close();
    archTXT.close();
}

