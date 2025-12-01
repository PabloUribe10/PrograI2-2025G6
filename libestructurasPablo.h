#include <iostream>

using namespace std;

struct fecha
{
    int dia;
    int mes;
    int anio;
};

struct libro
{
    int ISBN;
    char titulo[100];
    char autor[100];
    fecha fecha_publicacion;
    int edicion;
    categoria categoria_libro;
    int ejemplares;
    char idioma[50];
    int tipo;
};

struct Prestamo
{
    int codigo_prestamo;
    int ISBN_libro;
    int CI_usuario;
    fecha fecha_prestamo;
    fecha fecha_devolucion;
};