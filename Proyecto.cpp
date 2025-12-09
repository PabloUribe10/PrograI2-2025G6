#include <iostream>
#include <fstream>
#include <string>
#include "libestructurasPablo.h"

using namespace std;

void MenuOpciones(string archivoCarreras, string archivoEstudiantes, string archivoprestamos, string archivoLibros);
//void NuevoEstudiante(string archivoEstudiantes);
//void CrearCarrera(string archivoCarreras);
//void ListadoCarreras(string archivoCarreras);
void NuevoPrestamo(string archivoprestamos, string archivoEstudiantes);
void agregarlibro(string archivoLibros);
void listadoLibros(string archivoLibros);
//void listadoLibrosImpresora(string archivoLibros);
//void listadoEstudiantes(string archivoEstudiantes, string archivoCarreras);

int main()
{
    string archivoCarreras = "carreras.bin";
    string archivoEstudiantes = "estudiantes.bin";
    string archivoprestamos = "prestamos.bin";
    string archivoLibros = "libros.bin";
    MenuOpciones(archivoCarreras, archivoEstudiantes, archivoprestamos, archivoLibros);
    return 0;
}

void MenuOpciones(string archivoCarreras, string archivoEstudiantes, string archivoprestamos, string archivoLibros){
    int opcion = 0;
    int subopcion = 0;
    int subopcion2 = 0;
    do
    {
        system("cls");
        cout << "MENU DE OPCIONES" << endl;
        cout << "=============================" << endl;
        cout << "1. Nuevo Prestamo" << endl;
        cout << "2. Organizar Inventario" << endl;
        cout << "3. Datos Carreras" << endl;
        cout << "4. Nuevo Estudiante" << endl;
        cout << "5. Reportes" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        switch (opcion)
        {
            case 1:
                NuevoPrestamo(archivoprestamos, archivoEstudiantes);
                system("pause");          
                break;
            case 2:
                do
                {
                    system("cls");
                    cout << "Organizar Inventario" << endl;
                    cout << "================================" << endl;
                    cout << "1. Agregrar Libro" << endl;
                    cout << "2. Listado Libros" << endl;
                    cout << "3. Listado Libros (Impresora)" << endl;
                    cout << "0. Salir" << endl;
                    cout << "Seleccione una opcion: ";
                    cin >> subopcion;
                    switch (subopcion)
                    {
                        case 1:
                            agregarlibro(archivoLibros);
                            system("pause");
                            break;
                        case 2:
                            listadoLibros(archivoLibros);
                            system("pause");
                            break;
                        case 3:
                            //listadoLibrosImpresora(archivoLibros);
                            system("pause");
                            break;    
                        default:
                            if (subopcion != 0)
                            {
                                cout << "Opcion no valida." << endl;
                                system("pause");
                            }
                            break;
                    }
                } while (subopcion != 0);            
                break;
            case 3:
                do
                {
                    system("cls");
                    cout << "MENU CARRERAS" << endl;
                    cout << "=============" << endl;
                    cout << "1. Crear Carrera" << endl;
                    cout << "2. Listado Carreras" << endl;
                    cout << "0. Salir" << endl;
                    cout << "Seleccione una opcion: ";
                    cin >> subopcion;
                    switch (subopcion)
                    {
                        case 1:
                            //CrearCarrera(archivoCarreras);
                            system("pause");
                            break;
                        case 2:
                            //ListadoCarreras(archivoCarreras);
                            system("pause");
                            break;
                        default:
                            if (subopcion != 0)
                            {
                                cout << "Opcion no valida." << endl;
                                system("pause");
                            }
                            break;
                    }
                } while (subopcion != 0); 
                break;
            case 4:
                //NuevoEstudiante(archivoEstudiantes);
                system("pause");
                break;
            case 5:
                do
                {
                    system("cls");
                    cout << "MENU REPORTES (Impresora)" << endl;
                    cout << "=============" << endl;
                    cout << "1. Libro mas prestado" << endl;
                    cout << "2. Estudiantes con prestamos activos" << endl;
                    cout << "3. Libro menos prestado" << endl;
                    cout << "4. Estudiantes morosos" << endl;
                    cout << "5. Prestamos por carrera" << endl;
                    cout << "0. Salir" << endl;
                    cout << "Seleccione una opcion: ";
                    cin >> subopcion2;
                    switch (subopcion2)
                    {
                        case 1:
                            //listadoEstudiantes(archivoEstudiantes, archivoCarreras);
                            system("pause");
                            break;
                        case 2:
                            //listadoEstudiantes(archivoEstudiantes, archivoCarreras);
                            system("pause");
                            break;
                        case 3:
                            //listadoEstudiantes(archivoEstudiantes, archivoCarreras);
                            system("pause");
                            break;
                        case 4:
                            //listadoEstudiantes(archivoEstudiantes, archivoCarreras);
                            system("pause");
                            break;
                        default:
                            if (subopcion2 != 0)
                            {
                                cout << "Opcion no valida." << endl;
                                system("pause");
                            }
                            break;
                    }
                } while (subopcion2 != 0);
            
            default:
                if (opcion != 0)
                {
                    cout << "Opcion no valida." << endl;
                    system("pause");
                }
                break;
        }
    } while (opcion != 0);
    system("cls");
}

/*void CrearCarrera(string archivoCarreras)
{
    Carrera _carrera;
    ofstream archivo;
    archivo.open(archivoCarreras, ios::binary | ios::app);
    if (archivo.good())
    {
        cout << "Ingrese Codigo: ";
        cin >> _carrera.codigo;
        cin.ignore();
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
}       */
