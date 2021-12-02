#include <cstdlib>
#include <iostream>
#include <assert.h>
#include "ManejadorDeVersiones.h"
#include "Constantes.h"
//#include "ManejadorDeVersiones.cpp"

using namespace std;


void menu();
void imprimirResultado(TipoRet retorno, Cadena error);
void leerLinea(Cadena linea);
void consumir();
int main()
{
    cin.tie(&cout); // Sincroniza la entrada y la salida para que aparezcan intercaladas
    Archivo archivo = NULL;
    int numOper = 0;
    bool salir = false;
    TipoRet retorno = NO_IMPLEMENTADA;
    char opcion = 'n';
    Cadena cadenaAux = NULL;
    Cadena linea = NULL;
    Cadena version = NULL;
    Cadena error = NULL;
    Posicion nroLinea;
    bool sonIguales = false;
    menu();
    do {
        cin >> numOper;
        consumir();
        switch (numOper){
            case 1:
                  cout << "Ingrese nombre del archivo a crear: ";
                  cadenaAux = new char [MAX_LARGO_LINEA];
                  // fflush(stdin);
                  cin >> cadenaAux;
                  consumir();
                  archivo = CrearArchivo(cadenaAux);
                  delete[] cadenaAux;
                  break;

            case 2:
                  cout << "Se va a borrar el archivo: ";
                  retorno = BorrarArchivo(archivo);
                  imprimirResultado(retorno, NULL);
                  break;

            case 3:
                  version = new char[MAX_LARGO_LINEA];
                  error = new char[MAX_LARGO_LINEA];
                  cout << "Ingrese nombre de la version a crear: ";
                  // fflush(stdin);
                  cin >> version;
                  consumir();
                  retorno = CrearVersion(archivo, version, error);
                  imprimirResultado(retorno, error);

                  delete[] version;
                  delete[] error;
                  break;

            case 4:
                  version = new char[MAX_LARGO_LINEA];
                  cout << "Ingrese el nombre de la version a borrar: ";
                 // fflush(stdin);
                  cin >> version;
                  consumir();
                  retorno = BorrarVersion(archivo, version);
                  imprimirResultado(retorno, NULL);

                  delete[] version;
                  break;

            case 5:
                  retorno = MostrarVersiones(archivo);
                  imprimirResultado(retorno, NULL);

                  break;

            case 6:
                  linea = new char [MAX_LARGO_LINEA];
                  version = new char [MAX_LARGO_LINEA];
                  error = new char [MAX_LARGO_LINEA];
                  cout << "Ingrese el numero de linea a insertar (debe ser >= 1 y <= cant lineas): ";
                  cin >>  nroLinea;
                  consumir();
                  cout << "Ingrese la linea a insertar: ";
                  cin >> linea;
                  consumir();
                  cout << "Ingrese version a modificar: ";
                  cin >> version;
                  consumir();

                  retorno = InsertarLinea(archivo, version, linea, nroLinea, error);
                  imprimirResultado(retorno, error);

                  delete[] linea;
                  delete[] version;
                  delete[] error;
                  break;

            case 7:
                  version = new char[MAX_LARGO_LINEA];
                  error = new char[MAX_LARGO_LINEA];
                  cout << "Ingrese el numero de linea a borrar (debe ser >= 1 y <= cant lineas): ";
                  cin >>  nroLinea;
                  consumir();
                  cout << "Ingrese version a modificar: ";
                  cin >> version;
                  consumir();

                  retorno = BorrarLinea(archivo, version, nroLinea, error);
                  imprimirResultado(retorno, error);

                  delete[] version;
                  delete[] error;
                  break;

            case 8:
                  version = new char[MAX_LARGO_LINEA];
                  cout << "Ingrese version a mostrar: ";
                  cin >> version;
                  consumir();

                  retorno = MostrarTexto(archivo, version);
                  imprimirResultado(retorno, NULL);

                  delete[] version;
                  break;

            case 9:
                  version = new char[MAX_LARGO_LINEA];
                  cout << "Ingrese version a mostrar sus cambios: ";
                  cin >> version;
                  consumir();

                  retorno = MostrarCambios(archivo, version);
                  imprimirResultado(retorno, NULL);

                  delete[] version;
                  break;

            case 10:
                  error = new char[MAX_LARGO_LINEA];
                  version = new char[MAX_LARGO_LINEA];
                  cadenaAux = new char[MAX_LARGO_LINEA];
                  cout << "Ingrese la primera version: ";
                  cin >> version;
                  consumir();
                  cout << "Ingrese la segunda version: ";
                  cin >> cadenaAux;
                  consumir();

                  retorno = Iguales(archivo, version, cadenaAux, sonIguales);
                  imprimirResultado(retorno, NULL);
                  if(retorno == OK){
                        if(sonIguales)
                            cout << "Son iguales" << endl;
                        else
                            cout << "No son iguales" << endl;
                  }
                  sonIguales = false;

                  delete[] version;
                  delete[] cadenaAux;
                  break;

            case 11:
                  version = new char[MAX_LARGO_LINEA];
                  cout << "Ingrese una version a partir de la cual quiere crear una version independiente: ";
                  cin >> version;
                  consumir();

                  retorno = VersionIndependiente(archivo, version);
                  imprimirResultado(retorno, NULL);

                  delete[] version;
                  break;

            case 12:
                  cout << "Esta seguro de que desea salir (s/n)?: ";
                  cin >> opcion;
                  if (opcion == 's' || opcion == 'S'){
                     cout << "\nSaliendo...\n";
                     salir = true;
                  }
                  break;

            case 13:
                  cout << "no implementado" << endl;
                  break;

            case 14:
                  system("clear || cls");
                  break;

            default:
                  cout <<"No ingreso una opcion valida, vuelva a intentarlo...\n";
                  consumir();
                  cin.clear(); // en caso que no se haya
                  system("clear || cls");
                  menu();

        }
        cout << "\n";
        cout << "Presione Enter Para continuar";
        consumir();
        system("clear || cls");
        menu();
    } while (!salir);
    return 0;
}

void menu(){
    cout << "Estructuras de Datos y Algoritmos - Obligatorio 1\n";
    cout << "Manejador de versiones\n\n";
    cout << "Lista de operaciones disponibles:\n";
    cout << "1)  CrearArchivo\n";
    cout << "2)  BorrarArchivo\n";
    cout << "3)  CrearVersion\n";
    cout << "4)  BorrarVersion\n";
    cout << "5)  MostrarVersiones\n";
    cout << "6)  InsertarLinea\n";
    cout << "7)  BorrarLinea\n";
    cout << "8)  MostrarTexto\n";
    cout << "9)  MostrarCambios\n";
    cout << "10) Iguales\n";
    cout << "11) VersionIndependiente\n";
    cout << "12) Salir\n";
    cout << "13) Leer un archivo de comandos\n";
    cout << "14) Borrar pantalla\n\n";
    cout << "Ingrese el numero de la operacion a realizar: ";
}

void imprimirResultado(TipoRet retorno, Cadena error) {
     switch(retorno){
        case OK:
             cout << "Resultado: " << "OK" << endl;
             break;
        case ERROR:
             cout << "Resultado: " << "ERROR :" << error <<endl;
             break;
        case NO_IMPLEMENTADA:
             cout << "Resultado: " << "NO_IMPLEMENTADA"<< endl;
             break;
     }
}


void leerLinea (Cadena s)
// Ver 0.36
// Lee un string hasta un '\n'
{
    fflush(stdout);
	unsigned int i = 0;
	char c;
	do
	{
		c = getchar();
		s[i] = c;
		i++;
	}while (c != '\n');
	s[i-1] = '\0';
    printf("'%s'\n",s);
}

void consumir ()
// consume la entrada estandar hasta un "\n"
{
           char c;
           c = getchar();
           while (c != '\n')
           {
                 c = getchar();
           }
}
