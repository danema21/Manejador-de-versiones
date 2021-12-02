#ifndef MANEJADORDEVERSIONES_H_INCLUDED
#define MANEJADORDEVERSIONES_H_INCLUDED

enum _retorno{
OK, ERROR, NO_IMPLEMENTADA
};
typedef enum _retorno TipoRet;


struct _linea{
    char *line;
    unsigned int numLinea;
    _linea *sig;
    _linea *ant;
};
typedef _linea *Linea;


struct _version{
    char *nombre;
    Linea texto;
    Linea modificaciones;
    _version *sig;
    _version *ant;
    _version *subVersion;
    _version *padre;
};
typedef _version *Version;


struct _archivo{
    char *titulo;
    Version primerVersion;
};
typedef _archivo *Archivo;

//Funciones auxiliares privadas
Version getVersion(Version v, char *version);

int contarPuntos(char *version);

void mostrarVersionesRecursivo(Version v);

void incrementarVersion(Version v, int cantPuntos, char *nomVersion);

void decrementarVersion(Version v, int cantPuntos, char *nomVersion);

void correrVersiones(Version v, const char tipoCorrer, int cantPuntos, char *nomVersionDicho);

void borrarVersionesRecursivo(Version &v);

void copiarTexto(Linea &vHijo, Linea vPadre);
///////////////////////////////////////////////////////////////////////////////////////////////////////


//funciones exclusivas del obligatorio
Archivo CrearArchivo(char *nombre);

TipoRet BorrarArchivo(Archivo &a);

TipoRet CrearVersion(Archivo &a, char *version, char *error);

TipoRet BorrarVersion(Archivo &a, char *version);

TipoRet MostrarVersiones(Archivo a);

TipoRet InsertarLinea(Archivo &a, char *version, char *linea, unsigned int nroLinea, char *error);

TipoRet BorrarLinea(Archivo &a, char *version, unsigned int nroLinea, char *error);

TipoRet MostrarTexto(Archivo a, char *version);

TipoRet MostrarCambios(Archivo a, char *version);

TipoRet Iguales(Archivo a, char *version1, char *version2,  bool &iguales);

TipoRet VersionIndependiente(Archivo &a, char *version);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // MANEJADORDEVERSIONES_H_INCLUDED
