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
    char categoria_libro[50];
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

//fecha

void ingresarFechaPrestamo(fecha &f)
{
    cout << "Fecha del prestamo\n";
    cout << "Dia: ";
    cin >> f.dia;
    cout << "Mes: ";
    cin >> f.mes;
    cout << "Anio: ";
    cin >> f.anio;
}

void generarFechaDevolucion(fecha prestamo, fecha &devolucion)
{
    devolucion = prestamo;
    devolucion.dia = prestamo.dia + 3;
}

void mostrarFecha(fecha f)
{
    cout << f.dia << "/" << f.mes << "/" << f.anio;
}

//libro

void agregarlibro(string archivoLibros)
{
    fstream archLibros(archivoLibros,ios::binary | ios::app);

    if (!archLibros.is_open())
    {
        cout << "No se pudo abrir el archivo de libros.\n";
        return;
    }

    libro l;

    cout << "\n=== NUEVO LIBRO ===\n";

    cout << "ISBN: ";
    cin >> l.ISBN;
    cin.ignore();

    cout << "Titulo: ";
    cin.getline(l.titulo, 100);

    cout << "Autor: ";
    cin.getline(l.autor, 100);

    cout << "Fecha de publicacion:\n";
    cout << "Dia: ";
    cin >> l.fecha_publicacion.dia;
    cout << "Mes: ";
    cin >> l.fecha_publicacion.mes;
    cout << "Anio: ";
    cin >> l.fecha_publicacion.anio;

    cout << "Edicion: ";
    cin >> l.edicion;

    cin.ignore();
    cout << "Area del libro: ";
    cin.getline(l.categoria_libro, 50);

    cout << "Cantidad de ejemplares: ";
    cin >> l.ejemplares;

    cin.ignore();
    cout << "Idioma: ";
    cin.getline(l.idioma, 50);

    cout << "Tipo (1 = prestamo, 2 = solo sala): ";
    cin >> l.tipo;

    archLibros.write((char*)&l, sizeof(libro));
    archLibros.close();

    cout << "\nLibro registrado correctamente.\n";
}

void listadoLibros(string archivoLibros)
{
    ifstream archLibros(archivoLibros,ios::binary);

    if (!archLibros.is_open())
    {
        cout << "No se pudo abrir el archivo de libros.\n";
        return;
    }

    libro l;
    int cont = 0;

    cout << "\n=== LISTADO DE LIBROS ===\n\n";

    while (archLibros.read((char*)&l, sizeof(libro)))
    {
        cout << "Libro #" << ++cont << "\n";
        cout << "ISBN: " << l.ISBN << "\n";
        cout << "Titulo: " << l.titulo << "\n";
        cout << "Autor: " << l.autor << "\n";
        cout << "Fecha publicacion: "
             << l.fecha_publicacion.dia << "/"
             << l.fecha_publicacion.mes << "/"
             << l.fecha_publicacion.anio << "\n";
        cout << "Edicion: " << l.edicion << "\n";
        cout << "Categoria: " << l.categoria_libro << "\n";
        cout << "Ejemplares: " << l.ejemplares << "\n";
        cout << "Idioma: " << l.idioma << "\n";
        cout << "Tipo: " << l.tipo << "\n";
        cout << "-----------------------------\n";
    }

    if (cont == 0)
        cout << "No hay libros registrados.\n";

    archLibros.close();
}

void NuevoPrestamo(string archivoprestamos, string archivoEstudiantes)
{
    fstream archPrestamos(archivoprestamos,ios::binary | ios::app);

    if (!archPrestamos.is_open())
    {
        cout << "Error al abrir archivo de prestamos\n";
        return;
    }

    Prestamo p;

    cout << "\n=== NUEVO PRESTAMO ===\n";

    cout << "Codigo de prestamo: ";
    cin >> p.codigo_prestamo;

    cout << "ISBN del libro: ";
    cin >> p.ISBN_libro;

    cout << "CI del usuario: ";
    cin >> p.CI_usuario;

    ingresarFechaPrestamo(p.fecha_prestamo);
    generarFechaDevolucion(p.fecha_prestamo, p.fecha_devolucion);

    archPrestamos.write((char*)&p, sizeof(Prestamo));
    archPrestamos.close();

    cout << "\nPrestamo registrado correctamente\n";
    cout << "Fecha prestamo: ";
    mostrarFecha(p.fecha_prestamo);

    cout << "\nFecha devolucion: ";
    mostrarFecha(p.fecha_devolucion);
    cout << endl;
}
