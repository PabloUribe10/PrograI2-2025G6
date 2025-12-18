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
