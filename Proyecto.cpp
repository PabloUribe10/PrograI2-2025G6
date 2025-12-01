#include <iostream>
#include <fstream>
#include <string>
#include "libestructurasPablo.h"

using namespace std;

int main()
{
    MenuOpciones();
    return 0;
}

void MenuOpciones()
{
    int opcion = 0;
    int subopcion = 0;
    do
    {
        system("cls");
        cout << "MENU DE OPCIONES" << endl;
        cout << "=============================" << endl;
        cout << "1. Nuevo Prestamo" << endl;
        cout << "2. Organizar Inventario" << endl;
        cout << "3. Datos Carreras" << endl;
        cout << "4. Nuevo Estudiante" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        switch (opcion)
        {
            case 1:
                NuevoPrestamo();
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
                            libro()
                            system("pause");
                            break;
                        case 2:
                            listadoLibros();
                            system("pause");
                            break;
                        case 3:
                            listdadoLibrosImpresora();
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
                    cout << "\t1. Crear Carrera" << endl;
                    cout << "\t2. Listado Carreras" << endl;
                    cout << "\t0. Salir" << endl;
                    cout << "Seleccione una opcion: ";
                    cin >> subopcion;
                    switch (subopcion)
                    {
                        case 1:
                            CrearCarrera(archivoCarreras);
                            system("pause");
                            break;
                        case 2:
                            ListadoCarreras(archivoCarreras);
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
                NuevoEstudiante();
                system("pause");
                break;
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

