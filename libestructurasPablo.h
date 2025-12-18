#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <vector>
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

bool existeLibro(string archivoLibros, int isbn)
{
    ifstream arch(archivoLibros, ios::binary);
    if (!arch.is_open()) return false;

    libro l;
    while (arch.read((char*)&l, sizeof(libro)))
    {
        if (l.ISBN == isbn)
        {
            arch.close();
            return true;
        }
    }

    arch.close();
    return false;
}

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
void NuevoPrestamo(string archivoprestamos, string archivoEstudiantes, string archivoLibros)
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

    if (!existeLibro(archivoLibros, p.ISBN_libro))
    {
        cout << "El libro no existe.\n";
        archPrestamos.close();
        return;
    }

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

//LIBRO MAS PRESTADO 

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

// PRESTAMOS ACTIVOS 

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




//alesa

struct Carrera
{
    int ID_carrera;
    char nombre[50];
    char resumido[4];
    int codigo;
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
    fecha fecha_registro; 
};


int generarCodigoAleatori(int digitos = 6)
{
    int min = 1;
    for (int i = 1; i < digitos; i++)
        min *= 10;
    return min + rand() % (9 * min);
}


void CrearCarrera(string archivoCarreras)
{
    Carrera _carrera;
    ofstream archivo(archivoCarreras, ios::binary | ios::app);

    if (archivo.good())
    {
        cout << "Ingrese Codigo: ";
        cin >> _carrera.codigo;

        cin.ignore(); // limpiar ENTER del cin >>
        cout << "Ingrese Resumido: ";
        cin.getline(_carrera.resumido, 4);

        cout << "Ingrese Nombre: ";
        cin.getline(_carrera.nombre, 30);

        archivo.write((char*)&_carrera, sizeof(Carrera));
        cout << "Carrera creada exitosamente." << endl;
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }

    archivo.close();
}

void ListadoCarreras(string archivoCarreras)
{
    Carrera _carrera;
    ifstream archivo;
    archivo.open(archivoCarreras, ios::binary);
    if (archivo.good())
    {
        cout << "CARRERAS" << endl;
        cout << "========" << endl;
        cout << "Codigo\tResumido\tNombre" << endl;
        cout << "------------------------------------------------" << endl;
        while (archivo.read((char*)&_carrera, sizeof(Carrera)))
        {
            cout << _carrera.codigo << "\t" << _carrera.resumido << "\t\t" << _carrera.nombre << endl;
        }
        cout << "------------------------------------------------" << endl;
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
    archivo.close();
}


void CrearEstudiante(string archivoEstudiantes, string archivoCarreras)
{
    Estudiante _estudiante;
    ofstream archivo;
    archivo.open(archivoEstudiantes, ios::binary | ios::app);
    if (archivo.good())
    {
        cin.ignore();
        cout << "Ingrese CI: ";
        cin >> _estudiante.ID_estudiante;
        cin.ignore(); 
        cout << "Ingrese Nombres: ";
        cin.getline(_estudiante.nombre, 30);
        cout << "Ingrese Apellidos: ";
        cin.getline(_estudiante.apellido, 30);
        ListadoCarreras(archivoCarreras);
        cout << "Ingrese Codigo de Carrera: ";
        cin >> _estudiante.carrera;
        archivo.write((char*)&_estudiante, sizeof(Estudiante));
        cout << "Estudiante creado exitosamente." << endl;
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
    archivo.close();
}

int calcularDiasRetraso(fecha devolucion, fecha actual)
{
    int d1 = devolucion.anio * 360 + devolucion.mes * 30 + devolucion.dia;
    int d2 = actual.anio * 360 + actual.mes * 30 + actual.dia;

    if (d2 > d1)
        return d2 - d1;

    return 0;
}

void generarMultas(string archivoprestamos, string archivoMultas)
{
    ifstream archPrestamos(archivoprestamos, ios::binary);
    fstream archMultas(archivoMultas, ios::binary | ios::app);

    if (!archPrestamos.is_open() || !archMultas.is_open())
    {
        cout << "Error al abrir archivos.\n";
        return;
    }

    Prestamo p;
    Multa m;
    fecha fechaActual;

    cout << "Ingrese fecha actual (registro de multas)\n";
    cout << "Dia: "; cin >> fechaActual.dia;
    cout << "Mes: "; cin >> fechaActual.mes;
    cout << "Anio: "; cin >> fechaActual.anio;

    int total = 0;

    while (archPrestamos.read((char*)&p, sizeof(Prestamo)))
    {
        int diasDev = p.fecha_devolucion.anio * 360
                    + p.fecha_devolucion.mes * 30
                    + p.fecha_devolucion.dia;

        int diasAct = fechaActual.anio * 360
                    + fechaActual.mes * 30
                    + fechaActual.dia;

        if (diasAct > diasDev)   
        {
            m.codigo_multa = generarCodigoAleatorio();
            m.ID_estudiante = p.CI_usuario;
            m.dias_retraso = diasAct - diasDev;
            m.fecha_registro = fechaActual;

            archMultas.write((char*)&m, sizeof(Multa));
            total++;
        }
    }

    archPrestamos.close();
    archMultas.close();

    cout << "Multas generadas correctamente: " << total << endl;
}

void ReporteEstudiantesMultadosTXT(string archivoMultas)
{
    ifstream arch(archivoMultas, ios::binary);
    ofstream reporte("ReporteEstudiantesMultados.txt");

    if (!arch.is_open() || !reporte.is_open())
        return;

    Multa m;
    int ids[100];
    int diasTotales[100];
    int n = 0;

    for (int i = 0; i < 100; i++)
        diasTotales[i] = 0;

    while (arch.read((char*)&m, sizeof(Multa)))
    {
        bool encontrado = false;

        for (int i = 0; i < n; i++)
        {
            if (ids[i] == m.ID_estudiante)
            {
                diasTotales[i] += m.dias_retraso;
                encontrado = true;
                break;
            }
        }

        if (!encontrado)
        {
            ids[n] = m.ID_estudiante;
            diasTotales[n] = m.dias_retraso;
            n++;
        }
    }

    reporte << "=====================================\n";
    reporte << "   REPORTE DE ESTUDIANTES MULTADOS\n";
    reporte << "=====================================\n\n";

    for (int i = 0; i < n; i++)
    {
        reporte << "ID Estudiante : " << ids[i] << "\n";
        reporte << "Dias de multa : " << diasTotales[i] << "\n";
        reporte << "-------------------------------------\n";
    }

    reporte << "\nTotal de estudiantes multados: " << n << endl;

    arch.close();
    reporte.close();

    cout << "Reporte generado: ReporteEstudiantesMultados.txt\n";
}

void ReporteEstudiantesMorososTXT(string archivoEstudiantes, string archivoMultas)
{
    ifstream archMultas(archivoMultas, ios::binary);
    ifstream archEst(archivoEstudiantes, ios::binary);
    ofstream reporte("ReporteEstudiantesMorosos.txt");

    if (!archMultas.is_open() || !archEst.is_open() || !reporte.is_open())
        return;

    int ids[100];
    int diasTotales[100];
    int n = 0;

    for (int i = 0; i < 100; i++)
        diasTotales[i] = 0;

    Multa m;
    while (archMultas.read((char*)&m, sizeof(Multa)))
    {
        bool encontrado = false;

        for (int i = 0; i < n; i++)
        {
            if (ids[i] == m.ID_estudiante)
            {
                diasTotales[i] += m.dias_retraso;
                encontrado = true;
                break;
            }
        }

        if (!encontrado)
        {
            ids[n] = m.ID_estudiante;
            diasTotales[n] = m.dias_retraso;
            n++;
        }
    }

    reporte << "=============================================\n";
    reporte << "      REPORTE DE ESTUDIANTES MOROSOS\n";
    reporte << "=============================================\n\n";

    Estudiante e;
    int totalMorosos = 0;

    while (archEst.read((char*)&e, sizeof(Estudiante)))
    {
        for (int i = 0; i < n; i++)
        {
            if (e.ID_estudiante == ids[i])
            {
                reporte << "ID Estudiante : " << e.ID_estudiante << "\n";
                reporte << "Nombre        : " << e.nombre << "\n";
                reporte << "Apellido      : " << e.apellido << "\n";
                reporte << "Carrera       : " << e.carrera << "\n";
                reporte << "Dias de multa : " << diasTotales[i] << "\n";
                reporte << "---------------------------------------------\n";
                totalMorosos++;
                break;
            }
        }
    }

    reporte << "\nTotal de estudiantes morosos: " << totalMorosos << endl;

    archMultas.close();
    archEst.close();
    reporte.close();

    cout << "Reporte generado: ReporteEstudiantesMorosos.txt\n";
}

void ReporteLibrosPorCarreraTXT(string archivoLibros, string archivoCarreras)
{
    ifstream archCarreras(archivoCarreras, ios::binary);
    ifstream archLibros(archivoLibros, ios::binary);
    ofstream reporte("ReporteLibrosPorCarrera.txt");

    if (!archCarreras.is_open() || !archLibros.is_open() || !reporte.is_open())
    {
        cout << "Error al abrir archivos.\n";
        return;
    }

    Carrera c;
    cout << "CARRERAS DISPONIBLES\n";
    cout << "Codigo\tNombre\n";
    cout << "-----------------------------\n";

    while (archCarreras.read((char*)&c, sizeof(Carrera)))
    {
        cout << c.codigo << "\t" << c.nombre << endl;
    }

    archCarreras.clear();
    archCarreras.seekg(0);

    int codigoElegido;
    cout << "\nIngrese el codigo de la carrera: ";
    cin >> codigoElegido;

    char carreraSeleccionada[50];
    bool encontrada = false;

    while (archCarreras.read((char*)&c, sizeof(Carrera)))
    {
        if (c.codigo == codigoElegido)
        {
            strcpy(carreraSeleccionada, c.nombre);
            encontrada = true;
            break;
        }
    }

    if (!encontrada)
    {
        cout << "Carrera no encontrada.\n";
        return;
    }

    libro l;
    int total = 0;

    reporte << "=============================================\n";
    reporte << "     REPORTE DE LIBROS POR CARRERA\n";
    reporte << "=============================================\n\n";
    reporte << "Carrera: " << carreraSeleccionada << "\n";
    reporte << "---------------------------------------------\n";

    while (archLibros.read((char*)&l, sizeof(libro)))
    {
        limpiarTexto(l.categoria_libro);

        if (strcmp(l.categoria_libro, carreraSeleccionada) == 0)
        {
            limpiarTexto(l.titulo);
            limpiarTexto(l.autor);

            reporte << "ISBN   : " << l.ISBN << "\n";
            reporte << "Titulo : " << l.titulo << "\n";
            reporte << "Autor  : " << l.autor << "\n";
            reporte << "---------------------------------------------\n";
            total++;
        }
    }

    reporte << "\nTotal de libros en esta carrera: " << total << endl;

    archCarreras.close();
    archLibros.close();
    reporte.close();

    cout << "Reporte generado: ReporteLibrosPorCarrera.txt\n";
}
