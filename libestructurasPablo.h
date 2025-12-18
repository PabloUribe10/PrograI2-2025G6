#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

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

// limpiarTexto
void limpiarTexto(char texto[])
{
    for (int i = 0; texto[i] != '\0'; i++)
    {
        unsigned char c = texto[i];
        if (c < 32 || c > 126)
        {
            texto[i] = ' ';
        }
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
        {
            texto[i] = ' ';
        }
    }
}

// codigos
int generarCodigoAleatorio()
{
    return 10000000 + rand() % 90000000;
}

// fecha
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

// libro
void agregarlibro(string archivoLibros)
{
    fstream archLibros(archivoLibros, ios::binary | ios::app);

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
    normalizarEntrada(l.categoria_libro);

    cout << "Cantidad de ejemplares: ";
    cin >> l.ejemplares;
    cin.ignore();

    cout << "Idioma: ";
    cin.getline(l.idioma, 50);
    normalizarEntrada(l.idioma);

    cout << "Tipo (1 = prestamo, 2 = solo sala): ";
    cin >> l.tipo;

    archLibros.write((char*)&l, sizeof(libro));
    archLibros.close();

    cout << "\nLibro registrado correctamente.\n";
}

void listadoLibros(string archivoLibros)
{
    ifstream archLibros(archivoLibros, ios::binary);

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
        limpiarTexto(l.titulo);
        limpiarTexto(l.autor);
        limpiarTexto(l.categoria_libro);
        limpiarTexto(l.idioma);

        cout << "Libro #" << ++cont << "\n";
        cout << "ISBN: " << l.ISBN << "\n";
        cout << "Titulo: " << l.titulo << "\n";
        cout << "Autor: " << l.autor << "\n";
        cout << "Fecha publicacion: " << l.fecha_publicacion.dia << "/" << l.fecha_publicacion.mes << "/" << l.fecha_publicacion.anio << "\n";
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

void listadoLibrosImpresora(string archivoLibros)
{
    ifstream archLibros(archivoLibros, ios::binary);
    ofstream reporte("ReporteLibros.txt");

    if (!archLibros.is_open() || !reporte.is_open())
    {
        cout << "Error al abrir archivos.\n";
        return;
    }

    libro l;
    int total = 0;

    reporte << "=============================================\n";
    reporte << " REPORTE GENERAL DE LIBROS\n";
    reporte << "=============================================\n\n";

    while (archLibros.read((char*)&l, sizeof(libro)))
    {
        limpiarTexto(l.titulo);
        limpiarTexto(l.autor);
        limpiarTexto(l.categoria_libro);
        limpiarTexto(l.idioma);

        total++;

        reporte << "ISBN: " << l.ISBN << endl;
        reporte << "Titulo: " << l.titulo << endl;
        reporte << "Autor: " << l.autor << endl;
        reporte << "Fecha publicacion: " << l.fecha_publicacion.dia << "/" << l.fecha_publicacion.mes << "/" << l.fecha_publicacion.anio << endl;
        reporte << "Edicion: " << l.edicion << endl;
        reporte << "Categoria: " << l.categoria_libro << endl;
        reporte << "Ejemplares disponibles: " << l.ejemplares << endl;
        reporte << "Idioma: " << l.idioma << endl;

        if (l.tipo == 1)
            reporte << "Tipo: Prestamo\n";
        else
            reporte << "Tipo: Solo sala\n";

        reporte << "---------------------------------------------\n";
    }

    reporte << "\nTotal de libros registrados: " << total << endl;

    archLibros.close();
    reporte.close();

    cout << "\nReporte generado correctamente: ReporteLibros.txt\n";
}

// Prestamo
void NuevoPrestamo(string archivoprestamos, string archivoEstudiantes)
{
    fstream archPrestamos(archivoprestamos, ios::binary | ios::app);

    if (!archPrestamos.is_open())
    {
        cout << "Error al abrir archivo de prestamos\n";
        return;
    }

    Prestamo p;

    cout << "\n=== NUEVO PRESTAMO ===\n";
    p.codigo_prestamo = generarCodigoAleatorio();
    cout << "\nCodigo de prestamo generado: " << p.codigo_prestamo << endl;

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

// ================== REPORTE: LIBRO MAS PRESTADO ==================

void ReporteLibroMasPrestado(string archivoprestamos, string archivoLibros)
{
    ifstream archPrestamos(archivoprestamos, ios::binary);
    ifstream archLibros(archivoLibros, ios::binary);
    ofstream reporte("ReporteLibroMasPrestado.txt");

    if (!archPrestamos.is_open() || !archLibros.is_open() || !reporte.is_open())
    {
        cout << "Error al abrir archivos.\n";
        return;
    }

    Prestamo p;
    int isbn[100];
    int contador[100];
    int n = 0;

    for (int i = 0; i < 100; i++)
        contador[i] = 0;

    while (archPrestamos.read((char*)&p, sizeof(Prestamo)))
    {
        bool encontrado = false;
        for (int i = 0; i < n; i++)
        {
            if (isbn[i] == p.ISBN_libro)
            {
                contador[i]++;
                encontrado = true;
                break;
            }
        }
        if (!encontrado)
        {
            isbn[n] = p.ISBN_libro;
            contador[n] = 1;
            n++;
        }
    }

    if (n == 0)
    {
        reporte << "No hay prestamos registrados.\n";
        archPrestamos.close();
        archLibros.close();
        reporte.close();
        return;
    }

    int posMayor = 0;
    for (int i = 1; i < n; i++)
        if (contador[i] > contador[posMayor])
            posMayor = i;

    int isbnMasPrestado = isbn[posMayor];
    int totalPrestamos = contador[posMayor];

    libro l;
    bool encontradoLibro = false;

    while (archLibros.read((char*)&l, sizeof(libro)))
    {
        if (l.ISBN == isbnMasPrestado)
        {
            limpiarTexto(l.titulo);
            limpiarTexto(l.autor);
            limpiarTexto(l.categoria_libro);
            limpiarTexto(l.idioma);
            encontradoLibro = true;
            break;
        }
    }

    reporte << "=========================================\n";
    reporte << " REPORTE LIBRO MAS PRESTADO\n";
    reporte << "=========================================\n\n";

    if (encontradoLibro)
    {
        reporte << "ISBN: " << l.ISBN << endl;
        reporte << "Titulo: " << l.titulo << endl;
        reporte << "Autor: " << l.autor << endl;
        reporte << "Categoria: " << l.categoria_libro << endl;
        reporte << "Idioma: " << l.idioma << endl;
        reporte << "Total de prestamos: " << totalPrestamos << endl;
    }
    else
    {
        reporte << "Libro no encontrado en el archivo de libros.\n";
    }

    archPrestamos.close();
    archLibros.close();
    reporte.close();

    cout << "\nReporte generado: ReporteLibroMasPrestado.txt\n";
}

// ================== REPORTE: PRESTAMOS ACTIVOS ==================

bool fechaMayorOIgual(fecha f1, fecha f2)
{
    if (f1.anio > f2.anio) return true;
    if (f1.anio < f2.anio) return false;
    if (f1.mes > f2.mes) return true;
    if (f1.mes < f2.mes) return false;
    if (f1.dia >= f2.dia) return true;
    return false;
}

void ReportePrestamosActivos(string archivoprestamos)
{
    ifstream archPrestamos(archivoprestamos, ios::binary);
    ofstream reporte("ReportePrestamosActivos.txt");

    if (!archPrestamos.is_open() || !reporte.is_open())
    {
        cout << "Error al abrir archivos.\n";
        return;
    }

    Prestamo p;
    fecha fechaActual;
    int total = 0;

    cout << "Ingrese la fecha actual\n";
    cout << "Dia: ";
    cin >> fechaActual.dia;
    cout << "Mes: ";
    cin >> fechaActual.mes;
    cout << "Anio: ";
    cin >> fechaActual.anio;

    reporte << "=========================================\n";
    reporte << " REPORTE DE PRESTAMOS ACTIVOS\n";
    reporte << "=========================================\n\n";

    while (archPrestamos.read((char*)&p, sizeof(Prestamo)))
    {
        if (fechaMayorOIgual(p.fecha_devolucion, fechaActual))
        {
            total++;
            reporte << "Codigo Prestamo: " << p.codigo_prestamo << endl;
            reporte << "ISBN Libro: " << p.ISBN_libro << endl;
            reporte << "CI Usuario: " << p.CI_usuario << endl;
            reporte << "Fecha Prestamo: " << p.fecha_prestamo.dia << "/" << p.fecha_prestamo.mes << "/" << p.fecha_prestamo.anio << endl;
            reporte << "Fecha Devolucion: " << p.fecha_devolucion.dia << "/" << p.fecha_devolucion.mes << "/" << p.fecha_devolucion.anio << endl;
            reporte << "-----------------------------------------\n";
        }
    }

    reporte << "\nTotal de prestamos activos: " << total << endl;

    archPrestamos.close();
    reporte.close();

    cout << "\nReporte generado: ReportePrestamosActivos.txt\n";
}
