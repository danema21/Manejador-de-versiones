#include "ManejadorDeVersiones.h"
#include "constantes.h"
#include <iostream>
#include <string.h>

using namespace std;

//funciones auxiliares privadas
Version getVersion(Version v, char *version){
    Version resultado = NULL;

    if(v != NULL){
        if(v->subVersion != NULL)
            resultado = getVersion(v->subVersion, version);

        if(strcmp(v->nombre, version) == 0)
            return v;

        if(resultado == NULL && v->sig != NULL)
            resultado = getVersion(v->sig, version);
    }

    return resultado;
}

int contarPuntos(char *version){
    int i = 0;
    int cantPuntos = 0;
    while(version[i] != '\0'){
        if(version[i] == '.')
            cantPuntos++;
        i++;
    }
    return cantPuntos;
}

void mostrarVersionesRecursivo(Version v){
    if(v == NULL){
        return;
    }else{
        int tabs = contarPuntos(v->nombre);

        while(tabs != 0){
            cout << "\t";
            tabs--;
        }
        cout << v->nombre << endl;

        mostrarVersionesRecursivo(v->subVersion);

        mostrarVersionesRecursivo(v->sig);
    }
}

void incrementarVersion(Version v, int cantPuntos, char *nomVersion){
    int largoversion = strlen(v->nombre);
    int cont = 0;
    int i = 0;
    int j = 0;
    int posicion;
    bool estaEnPosicion = false;

    //cosigue que i apunte a la posicion siguiente al ultimo punto o si no entra al while deja i en cero
    while(cont != cantPuntos){
        if(nomVersion[i] == '.')
            cont++;

        i++;
    }

    posicion = i;
    cont = 0;
    ////////////////////////////////////////////////////////

    //Cuenta la cantidad de nueves antes del punto o del final que tiene la version
    while(i < largoversion && v->nombre[i] != '.'){
        if(v-> nombre[i] == '9')
            cont++;

        i++;
        j++;
    }
    ////////////////////////////////////////////////////////

    if(cont == j){//si todos son puros nueves entra al if
        char *nuevoarray = new char[largoversion + 20];
        i = 0;
        j = 0;

        //mientras i sea menor al largo de la version, va creando en nuevoarray el nuevo nombre de la version
        while (i < largoversion){
            if(i == posicion){
                estaEnPosicion = true;

                //pone en la primera posicion un 1 y todas a las demas posiciones le pone un 0 hasta que haya convertido todos los 9 antes del punto en 0
                nuevoarray[j] = '1';
                j++;

                for(int k = 0; k < cont ; k++){
                    nuevoarray[j] = '0';
                    j++;
                    i++;
                }
                ////////////////////////////////////////////////////////

            }else{
                //copia el nombre de la version actual nuevoarray
                if(estaEnPosicion){
                    estaEnPosicion = false;
                    nuevoarray[j] = v->nombre[i];

                }else
                    nuevoarray[j] = v->nombre[i];

                i++;
                j++;
                ////////////////////////////////////////////////////////
            }
        }
        ////////////////////////////////////////////////////////

        nuevoarray[j] = '\0';
        //borra el nombre original y le asigna el del nuevoarray
        delete[] v->nombre;
        v->nombre = new char[largoversion + 20];
        strcpy(v->nombre, nuevoarray);

        delete[] nuevoarray;
        ////////////////////////////////////////////////////////

    }else if(cont > 0){ //si no son todos nueve pero hay al menos un nueve entra al if
        i = 0;
        bool aumentar = false;

        //pone a i apuntando un lugar antes al primer punto despues de la posicion o antes del final
        while(i < posicion || (v->nombre[i] != '.' && i < largoversion))
            i++;
        i--;
        ////////////////////////////////////////////////////////

        //si el primer numero a chequear es un nueve, entonces lo convierto a cero, si no solo lo incrementa en 1
        if(v->nombre[i] == '9'){
            v->nombre[i] = '0';
            aumentar = true;
            i--;
        }else{
            v->nombre[i] = v->nombre[i] + 1;
            i--;
        }
        ////////////////////////////////////////////////////////

        //itera hasta que vuelve a la posicion
        while (i >= posicion){
            if(v->nombre[i] == '9' && aumentar)
                v->nombre[i] = '0';

            else if(v->nombre[i] != '9' && aumentar){
                v->nombre[i] = v->nombre[i] + 1;
                aumentar = false;

            }
            i--;
        }
        ////////////////////////////////////////////////////////

    }else{//Si no existen nueves entra al else
        i = 0;

        //pone a i apuntando un lugar antes al primer punto despues de la posicion o antes del final
        while(i < posicion || (v->nombre[i] != '.' && i < largoversion))
            i++;
        i--;
        ////////////////////////////////////////////////////////

        v->nombre[i] = v->nombre[i] + 1;
    }
}

void decrementarVersion(Version v, int cantPuntos, char *nomVersion){
    int largoversion = strlen(v->nombre);
    int i = 0;
    int j = 0;
    int posicion;
    bool decrementar = false;

    //cosigue que i apunte a la posicion siguiente al ultimo punto o si no entra al while deja i en cero
    while(j != cantPuntos){
        if(nomVersion[i] == '.')
            j++;

        i++;
    }

    posicion = i;
    ////////////////////////////////////////////////////////

    //pone a i apuntando un lugar antes al primer punto despues de la posicion o antes del final
    while(i < posicion || (v->nombre[i] != '.' && i < largoversion))
        i++;
    i--;
    ////////////////////////////////////////////////////////

    //si el primer numero a chequear es un cero, entonces lo convierto a nueve, si no solo lo decrementa en 1
    if(v->nombre[i] == '0'){
        v->nombre[i] = '9';
        decrementar = true;
        i--;
    }else{
        v->nombre[i] = v->nombre[i] - 1;
        i--;
    }
    ////////////////////////////////////////////////////////

    //itera hasta que vuelve a la posicion
    while (i >= posicion){
        if(v->nombre[i] == '0' && decrementar)
            v->nombre[i] = '9';

        else if(v->nombre[i] != '0' && decrementar){
            v->nombre[i] = v->nombre[i] - 1;
            decrementar = false;

        }
        i--;
    }
    ////////////////////////////////////////////////////////

    char *nuevoarray = new char[largoversion + 20];
    i = 0;
    j = 0;
    while(i < largoversion){
        if(i == posicion && v->nombre[i] == '0'){
            i++;
            nuevoarray[j] = v->nombre[i];
        }else
            nuevoarray[j] = v->nombre[i];

        i++;
        j++;
    }
    nuevoarray[j] = '\0';

    delete[] v->nombre;
    v->nombre = new char[largoversion + 20];
    strcpy(v->nombre, nuevoarray);

    delete[] nuevoarray;

}

void correrVersiones(Version v, const char tipoCorrer, int cantPuntos, char *nomVersionDicho){
    if(v == NULL)
        return;
    else{
        correrVersiones(v->subVersion, tipoCorrer, cantPuntos, nomVersionDicho);

        if(tipoCorrer == '+')
            incrementarVersion(v, cantPuntos, nomVersionDicho);
        else if(tipoCorrer == '-')
            decrementarVersion(v, cantPuntos, nomVersionDicho);

        correrVersiones(v->sig, tipoCorrer, cantPuntos, nomVersionDicho);
    }
}

void borrarVersionesRecursivo(Version &v){
    if(v == NULL)
        return;
    else{
        borrarVersionesRecursivo(v->subVersion);

        borrarVersionesRecursivo(v->sig);

        delete[] v->nombre;
        Linea aux = v->texto;
        while(aux != NULL){
            Linea tmp = aux;
            aux = aux->sig;
            delete[] tmp->line;
            delete tmp;
        }

        aux = v->modificaciones;
        while(aux != NULL){
            Linea tmp = aux;
            aux = aux->sig;
            delete[] tmp->line;
            delete tmp;
        }
        delete v;
        v = NULL;
    }
}

void copiarTexto(Linea &vHijo, Linea vPadre){
    if(vPadre == NULL)
        vHijo = NULL;

    else{
        int largolinea = strlen(vPadre->line);

        vHijo = new _linea;
        vHijo->line = new char[largolinea + 20];
        strcpy(vHijo->line, vPadre->line);
        vHijo->numLinea = vPadre->numLinea;
        vHijo->ant = NULL;

        Linea aux = vHijo;
        Linea tmp;
        if(vPadre->sig != NULL){
            aux->sig = new _linea;
            tmp = aux;
            aux = aux->sig;
        }else
            aux->sig = NULL;


        vPadre = vPadre->sig;

        while(vPadre != NULL){
            aux->line = new char[largolinea + 20];
            strcpy(aux->line, vPadre->line);
            aux->numLinea = vPadre->numLinea;

            if(vPadre->sig == NULL){
                aux->sig = NULL;
                aux->ant = tmp;

            }else{
                aux->sig = new _linea;
                aux->ant = tmp;
                tmp = aux;
                aux = aux->sig;
            }

            vPadre = vPadre->sig;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//funciones exclusivas del obligatorio
Archivo CrearArchivo(char *nombre){
    Archivo a = new _archivo;
    a->titulo = new char[strlen(nombre) + 20];
    strcpy(a->titulo, nombre);
    a->primerVersion = NULL;
    return a;
}

TipoRet BorrarArchivo(Archivo &a){
    if(a != NULL){
        borrarVersionesRecursivo(a->primerVersion);
        delete[] a->titulo;
        delete a;
        a = NULL;
    }
    return OK;
}

TipoRet CrearVersion(Archivo &a, char *version, char *error){
    if(a == NULL){
        strcpy(error, "El archivo aun no a sido creado");
        return ERROR;

    }else if(a->primerVersion == NULL && strcmp(version, "1") != 0){
        strcpy(error, "La version anterior a la version que quiere crear no existe");
        return ERROR;

    }else if(a->primerVersion == NULL && strcmp(version, "1") == 0){
        //si no existe la primera version agrego al comienzo la nueva version creada
        Version nueva = new _version;
        nueva->nombre = new char[strlen(version) + 20];
        strcpy(nueva->nombre, version);
        nueva->texto = NULL;
        nueva->modificaciones = NULL;
        nueva->sig = NULL;
        nueva->ant = NULL;
        nueva->subVersion = NULL;
        nueva->padre = NULL;

        a->primerVersion = nueva;

        return OK;
        ////////////////////////////////////////////////////////

    }else{
        //busco si la version tiene algun "."
        bool esSubversion = false;
        int i = 0;
        while(version[i] != '\0' && !esSubversion){
            if(version[i] == '.')
                esSubversion = true;
            i++;
        }
        ////////////////////////////////////////////////////////

        if(esSubversion){ //si la version tenia almenos un "." entra al if
            //guarda en char *versionPadre el nombre de la version padre de la version, ej: si tenemos la 1.1.2, en versionAnterior guarda 1.1
            char *versionPadre;
            int i = strlen(version) - 1;
            while(version[i] != '.')
                i--;

            versionPadre = new char[strlen(version) + 20];
            int j = 0;
            while(j < i){
                versionPadre[j] = version[j];
                j++;
            }
            versionPadre[j] = '\0';
            ////////////////////////////////////////////////////////

            //almacena la version padre en aux y libera la memoria que utilizaba versionPadre
            Version aux = getVersion(a->primerVersion, versionPadre);
            delete[] versionPadre;
            ////////////////////////////////////////////////////////
            if(aux != NULL){
                if(aux->subVersion == NULL){ //si la version padre no tiene subversiones entra al if
                    //usa cont para contar cuantas cifras tiene el numero despues del ultimo punto de la version
                    i = strlen(version) - 1;
                    int cont = 0;
                    while(version[i] != '.'){
                        i--;
                        cont++;
                    }
                    ////////////////////////////////////////////////////////

                    if(cont == 1 && version[strlen(version) - 1] == '1'){ //si las cifras del numero del ultimo punto de la version es igual a 1 y el ultimo caracter de la version es igual a '1' entra al if
                        //inserta la nueva version creada en lo que seria la subversion del padre
                        Version nueva = new _version;
                        nueva->nombre = new char[strlen(version) + 20];
                        strcpy(nueva->nombre, version);
                        copiarTexto(nueva->texto, aux->texto);
                        nueva->modificaciones = NULL;
                        nueva->sig = NULL;
                        nueva->ant = NULL;
                        nueva->subVersion = NULL;
                        nueva->padre = aux;
                        aux->subVersion = nueva;

                        return OK;
                        ////////////////////////////////////////////////////////
                    }else{
                        strcpy(error, "La subversion anterior a la version que quiere crear no existe");
                        return ERROR;
                    }

                }else{
                    //buscar entre las siguientes versiones hasta que una sea igual a la version que quiero crear o hasta que no haya encontrado esa version
                    aux = aux->subVersion;
                    while(strcmp(aux->nombre, version) != 0 && aux->sig != NULL){
                        aux = aux->sig;
                    }
                    ////////////////////////////////////////////////////////

                    if(strcmp(aux->nombre, version) == 0){ //si alguna de las versiones coincide con la que quiero crear entra al if
                        //crea la version
                        Version nueva = new _version;
                        nueva->nombre = new char[strlen(version) + 20];
                        strcpy(nueva->nombre, version);
                        copiarTexto(nueva->texto, aux->padre->texto);
                        nueva->modificaciones = NULL;
                        nueva->subVersion = NULL;
                        ////////////////////////////////////////////////////////

                        //asigna i para que se posicione en el ultimo punto de la version
                        i = strlen(version) - 1;
                        while(version[i] != '.'){
                            i--;
                        }
                        ////////////////////////////////////////////////////////

                        if(version[i+1] == '1' && version[i+2] == '\0'){ //si el caracter que esta despues del punto es igual a '1' y el otro caracter siguiente indica el final del string entra al if
                            //inserta la nueva version creada al principio de la lista
                            nueva->sig = aux;
                            nueva->ant = NULL;
                            nueva->padre = aux->padre;
                            aux->padre->subVersion = nueva;
                            aux->ant = nueva;
                            ////////////////////////////////////////////////////////


                            correrVersiones(nueva->sig, '+', contarPuntos(version), version);

                        }else{
                            //inserta la nueva version creada entre medio de la lista
                            nueva->ant = aux->ant;
                            aux->ant->sig = nueva;
                            nueva->sig = aux;
                            aux->ant = nueva;
                            nueva->padre = aux->padre;

                            correrVersiones(nueva->sig, '+', contarPuntos(version), version);
                            ////////////////////////////////////////////////////////
                        }
                        return OK;

                    }else{ //si la version no coincide con ninguna existente entra al if
                        //guarda en numFinalVer y numFinalAux2 los numeros a partir del ultimo punto de la version a crear y del ultimo punto de la version en la que estoy parado respectivamente
                        char *numFinalVer = new char[strlen(version) + 20];
                        char *numFinalAux2 = new char[strlen(version) + 20];
                        i = strlen(version) - 1;
                        while(version[i] != '.')
                            i--;

                        i++;
                        j = 0;
                        while(version[i] != '\0'){
                            numFinalVer[j] = version[i];
                            j++;
                            i++;
                        }
                        numFinalVer[j] = '\0';

                        i = strlen(aux->nombre) - 1;
                        while(aux->nombre[i] != '.')
                            i--;

                        i++;
                        j = 0;
                        while(aux->nombre[i] != '\0'){
                            numFinalAux2[j] = aux->nombre[i];
                            j++;
                            i++;
                        }
                        numFinalAux2[j] = '\0';
                        ////////////////////////////////////////////////////////

                        if(atoi(numFinalVer) - atoi(numFinalAux2) == 1){ //si la resta entre el ultimo numero de la version a crear y el ultimo numero de la ultima version es igual a 1 entra al if
                            //libera la memoria usada por las variables auxiliares, crea la version y la inserta al final de la lista
                            delete[] numFinalVer;
                            delete[] numFinalAux2;

                            Version nueva = new _version;
                            nueva->nombre = new char[strlen(version) + 20];
                            strcpy(nueva->nombre, version);
                            copiarTexto(nueva->texto, aux->padre->texto);
                            nueva->modificaciones = NULL;
                            nueva->subVersion = NULL;
                            nueva->padre = aux->padre;
                            nueva->sig = NULL;
                            nueva->ant = aux;

                            aux->sig = nueva;

                            return OK;
                            ////////////////////////////////////////////////////////
                        }else{
                            strcpy(error, "La subversion anterior a la version que quiere crear no existe");
                            return ERROR;
                        }
                    }
                }
            }else{
                strcpy(error, "La version padre no existe");
                return ERROR;
            }
        }else{ //es una version primerisa

            //busca en la lista de versiones hasta que alguna tenga igual nombre a la de la version que quiero crear o hasta que haya comprobado todas
            Version aux = a->primerVersion;
            while(strcmp(aux->nombre, version) != 0 && aux->sig != NULL)
                aux = aux->sig;
            ////////////////////////////////////////////////////////

            if(strcmp(aux->nombre, version) == 0){ //si el nombre de la version es igual al de la version que quiero crear entra al if
                //agrega version padre al principio o al medio de la lista y aumentar en una unidad las versiones siguientes
                Version nueva = new _version;
                nueva->nombre = new char[strlen(version) + 20];
                strcpy(nueva->nombre, version);
                nueva->texto = NULL;
                nueva->modificaciones = NULL;

                if(strcmp(version, "1") == 0){
                    //inserta la version al principio de la lista
                    a->primerVersion = nueva;
                    nueva->sig = aux;
                    nueva->ant = NULL;
                    aux->ant = nueva;
                    ////////////////////////////////////////////////////////
                }else{
                    //inserta la version entre el principio y el final de la lista
                    nueva->ant = aux->ant;
                    aux->ant->sig = nueva;
                    nueva->sig = aux;
                    aux->ant = nueva;
                    ////////////////////////////////////////////////////////
                }

                nueva->subVersion = NULL;
                nueva->padre = NULL;

                correrVersiones(nueva->sig, '+', contarPuntos(version), version);

                return OK;
                ////////////////////////////////////////////////////////
            }else if((atoi(version) - atoi(aux->nombre)) == 1){ //si la el numero de la version a crear es el siguiente numero que le sigue a la version existente
                //agrega la version padre al final de la lista
                Version nueva = new _version;
                nueva->nombre = new char[strlen(version) + 20];
                strcpy(nueva->nombre, version);
                nueva->texto = NULL;
                nueva->modificaciones = NULL;
                nueva->sig = NULL;
                nueva->ant = aux;
                nueva->subVersion = NULL;
                nueva->padre = NULL;

                aux->sig = nueva;
                return OK;
                ////////////////////////////////////////////////////////
            }else{
                strcpy(error, "La version anterior a la version que quiere crear no existe");
                return ERROR;
            }
        }
    }
}

TipoRet BorrarVersion(Archivo &a, char *version){
    if(a == NULL)
        return ERROR;

    else{
        Version actual = getVersion(a->primerVersion, version);
        if(actual != NULL){
            borrarVersionesRecursivo(actual->subVersion);

            if(actual->sig != NULL ){
                correrVersiones(actual->sig, '-', contarPuntos(actual->sig->nombre), actual->sig->nombre);

                if(actual->ant != NULL){
                    actual->ant->sig = actual->sig;
                    actual->sig->ant = actual->ant;

                }else{
                    if(actual->padre == NULL){
                        a->primerVersion = actual->sig;
                        a->primerVersion->ant = NULL;
                    }else{
                        actual->padre->subVersion = actual->sig;
                        actual->sig->ant = NULL;
                    }
                }
            }else{
                if(actual->padre == NULL){
                    if(actual->ant == NULL)
                        a->primerVersion = NULL;
                    else
                        actual->ant->sig = NULL;

                }else{
                    if(actual->ant == NULL)
                        actual->padre->subVersion = NULL;
                    else
                        actual->ant->sig = NULL;

                }
            }

            delete[] actual->nombre;
            Linea aux = actual->texto;
            while(aux != NULL){
                Linea tmp = aux;
                aux = aux->sig;
                delete[] tmp->line;
                delete tmp;
            }

            aux = actual->modificaciones;
            while(aux != NULL){
                Linea tmp = aux;
                aux = aux->sig;
                delete[] tmp->line;
                delete tmp;
            }

            delete actual;

            return OK;

        }else
            return ERROR;
    }
}

TipoRet MostrarVersiones(Archivo a){
    if(a != NULL){
        if(a->primerVersion == NULL){
            cout << a->titulo << "\n" << endl;
            cout << "No hay versiones creadas" << endl;
        }else{
            cout << a->titulo << "\n" << endl;
            mostrarVersionesRecursivo(a->primerVersion);
        }
    }

    return OK;
}

TipoRet InsertarLinea(Archivo &a, char *version, char *linea, unsigned int nroLinea, char *error){
    if(a == NULL){
        strcpy(error, "El archivo no existe");
        return ERROR;

    }else if(a->primerVersion == NULL){
        strcpy(error, "No hay versiones existentes");
        return ERROR;

    }else{
        Version actual = getVersion(a->primerVersion, version);
        if(actual != NULL){
            if(actual->subVersion != NULL){
                strcpy(error, "La version que quiere modificar tiene subversiones");
                return ERROR;

            }else if(actual->texto == NULL && nroLinea == 1){//Si la version no tiene lineas y el usuario ingresa en la linea 1
                Linea l = new _linea;
                actual->texto = l;
                l->line = new char[strlen(linea) + 20];
                strcpy(l->line, linea);
                l->numLinea = nroLinea;
                l->ant = NULL;
                l->sig = NULL;

                Linea mod = new _linea;
                mod->line = new char[strlen(linea) + 20];
                sprintf(mod->line, "IL\t%d\t%s", nroLinea, linea);
                mod->numLinea = 0;

                Linea auxMod = actual->modificaciones;
                while(auxMod != NULL && auxMod->sig != NULL)
                    auxMod = auxMod->sig;

                mod->ant = auxMod;
                mod->sig = NULL;

                if(auxMod != NULL)
                    auxMod->sig = mod;
                else
                    actual->modificaciones = mod;


                return OK;

            }else if(actual->texto != NULL){//Si el archivo tiene al menos una linea
                Linea aux = actual->texto;
                while(aux->sig != NULL && aux->numLinea != nroLinea)//busca una linea en el archivo que coincida con 1 o alguna linea en el rango de la cantidad de lineas totales
                    aux = aux->sig;

                Linea auxMod = actual->modificaciones;

                while(auxMod != NULL && auxMod->sig != NULL)
                    auxMod = auxMod->sig;


                if(aux->numLinea == nroLinea){//Si la linea que pidio el usuario coincide con una ya existente
                    Linea l = new _linea;
                    l->line = new char[strlen(linea) + 20];
                    strcpy(l->line, linea);
                    l->numLinea = nroLinea;
                    l->ant = aux->ant;

                    Linea mod = new _linea;
                    mod->line = new char[strlen(linea) + 20];
                    sprintf(mod->line, "IL\t%d\t%s", nroLinea, linea);
                    mod->numLinea = 0;

                    mod->ant = auxMod;
                    mod->sig = NULL;
                    if(auxMod != NULL)
                        auxMod->sig = mod;
                    else
                        actual->modificaciones = mod;

                    if(aux->sig == NULL && nroLinea != 1){//Si la linea a insertar es igual a la ultima linea
                        l->sig = aux->ant->sig;
                        aux->ant->sig = l;
                        l->ant->sig = l;
                        l->sig->ant = l;

                    }else if(aux->ant == NULL){//Si la linea a insertar es igual a la primera linea
                        l->sig = actual->texto;
                        actual->texto->ant = l;
                        actual->texto = l;

                    }else{//Si la linea a insertar se encuentra entre la primera y la ultima linea
                        l->sig = aux->ant->sig;
                        aux->ant->sig = l;
                        aux->sig->ant->ant = l;
                    }

                    while(aux != NULL){//aumenta el numero de linea de las siguientes lineas a la linea insertada
                        aux->numLinea++;
                        aux = aux->sig;
                    }

                    return OK;

                }else if(aux->sig == NULL && nroLinea == aux->numLinea + 1){//Si el numero de linea a insertar es una unidad mayor a la ultima linea
                    Linea l = new _linea;
                    l->line = new char[strlen(linea) + 20];
                    strcpy(l->line, linea);
                    l->numLinea = nroLinea;
                    l->sig = NULL;
                    l->ant = aux;
                    aux->sig = l;

                    Linea mod = new _linea;
                    mod->line = new char[strlen(linea) + 20];
                    sprintf(mod->line, "IL\t%d\t%s", nroLinea, linea);
                    mod->numLinea = 0;

                    mod->ant = auxMod;
                    mod->sig = NULL;
                    if(auxMod != NULL)
                        auxMod->sig = mod;
                    else
                        actual->modificaciones = mod;

                    return OK;

                }else{
                    strcpy(error, "Nro de linea no es valido");
                    return ERROR;
                }

            }else{
                strcpy(error, "Nro de linea no es valido");
                return ERROR;
            }
        }else{
            strcpy(error, "No existe la version");
            return ERROR;
        }
    }
}

TipoRet BorrarLinea(Archivo &a, char *version, unsigned int nroLinea, char *error){
    if(a == NULL){
        strcpy(error, "El archivo no existe");
        return ERROR;

    }else{
        Version actual = getVersion(a->primerVersion, version);
        if(actual != NULL ){
            if(actual->texto != NULL){
                int largolinea = strlen(actual->texto->line);

                if(actual->subVersion != NULL){
                    strcpy(error, "La version que quiere modificar tiene subversiones");
                    return ERROR;

                }else if(actual->texto->sig == NULL && actual->texto->ant == NULL && actual->texto->numLinea == nroLinea){//Si solo hay una linea para borrar
                    delete[] actual->texto->line;
                    delete actual->texto;
                    actual->texto = NULL;

                    Linea auxMod = actual->modificaciones;
                    while(auxMod != NULL && auxMod->sig != NULL)
                        auxMod = auxMod->sig;

                    Linea mod = new _linea;
                    mod->line = new char[largolinea + 20];
                    sprintf(mod->line, "BL\t%d", nroLinea);
                    mod->numLinea = 0;

                    mod->ant = auxMod;
                    mod->sig = NULL;

                    if(auxMod != NULL)
                        auxMod->sig = mod;
                    else
                        actual->modificaciones = mod;

                    return OK;

                }else{
                    Linea aux = actual->texto;
                    while(aux->sig != NULL && aux->numLinea != nroLinea)//busca la linea a ser borrada
                        aux = aux->sig;

                    if(aux->numLinea == nroLinea){//Si encontro una linea coincidente con el numero de linea especificado
                        if(aux->sig == NULL){//Si es la ultima linea
                            aux->ant->sig = NULL;
                            delete[] aux->line;
                            return OK;

                        }else{
                            Linea tmp = aux;
                            if(aux->ant == NULL){//Si es la primera linea
                                actual->texto = aux->sig;
                                aux->sig->ant = NULL;

                            }else{//Si se encuentra entre la primer y ultima linea
                                aux->ant->sig = aux->sig;
                                aux->ant->sig->ant = aux->ant;

                            }
                            while(aux != NULL){//decremente el numero de linea de las lineas siguientes a la que se borro
                                aux->numLinea--;
                                aux = aux->sig;

                            }
                            delete[] tmp->line;//borrado fisico de la linea

                            Linea auxMod = actual->modificaciones;
                            while(auxMod->sig != NULL)
                                auxMod = auxMod->sig;

                            Linea mod = new _linea;
                            actual->modificaciones = mod;
                            mod->line = new char[largolinea + 20];
                            sprintf(mod->line, "BL\t%d", nroLinea);
                            mod->numLinea = 0;

                            mod->ant = auxMod;
                            mod->sig = NULL;

                            if(auxMod != NULL)
                                auxMod->sig = mod;
                            else
                                actual->modificaciones = mod;

                            return OK;

                        }
                    }else{
                        strcpy(error, "Nro de linea no es valido");
                        return ERROR;

                    }
                }
            }else{
                strcpy(error, "Nro de linea no es valido");
                return ERROR;

            }
        }else{
            strcpy(error, "La version no existe");
            return ERROR;

        }
    }
}

TipoRet MostrarTexto(Archivo a, char *version){
    if(a == NULL)
        return ERROR;

    else if(a->primerVersion == NULL)
        return ERROR;

    else{
        Version actual = getVersion(a->primerVersion, version);
        if(actual != NULL){
            if(actual->texto == NULL){
                cout << a->titulo << " - " << actual->nombre << "\n" <<endl;
                cout << "No contiene lineas" <<endl;

            }else{
                cout << a->titulo << " - " << actual->nombre << "\n" <<endl;
                Linea aux = actual->texto;
                while(aux != NULL){
                    cout << aux->numLinea << "\t" << aux->line <<endl;
                    aux = aux->sig;

                }
            }
            return OK;

        }else
            return ERROR;
    }
}

TipoRet MostrarCambios(Archivo a, char *version){
    if(a == NULL)
        return ERROR;

    else if(a->primerVersion == NULL)
        return ERROR;

    else{
        Version actual = getVersion(a->primerVersion, version);
        if(actual != NULL){
            if(actual->modificaciones == NULL){
                cout << a->titulo << " - " << actual->nombre << "\n" <<endl;
                cout << "No se realizaron modificaciones" <<endl;

            }else{
                cout << a->titulo << " - " << actual->nombre << "\n" <<endl;
                Linea aux = actual->modificaciones;
                while(aux != NULL){
                    cout << aux->line <<endl;
                    aux = aux->sig;

                }
            }
            return OK;

        }else
            return ERROR;
    }
}

TipoRet Iguales(Archivo a, char *version1, char *version2,  bool &iguales){
    if(a != NULL){
        Version v1 = getVersion(a->primerVersion, version1);
        Version v2 = getVersion(a->primerVersion, version2);

        if(v1 != NULL && v2 != NULL){
            Linea l1 = v1->texto;
            Linea l2 = v2->texto;
            iguales = true;

            while(l1 != NULL && l2 != NULL){
                int i = 0;
                while(l1->line[i] != '\0' && l2->line[i] != '\0' && iguales){
                    if(l1->line[i] != l2->line[i])
                        iguales = false;

                    i++;
                }

                if(l1->line[i] != '\0' || l2->line[i] != '\0')
                    iguales = false;


                l1 = l1->sig;
                l2 = l2->sig;
            }

            if(l1 != NULL || l2 != NULL)
                iguales = false;

            return OK;

        }else
            return ERROR;
    }else
        return ERROR;
}

TipoRet VersionIndependiente(Archivo &a, char *version){
    return NO_IMPLEMENTADA;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
