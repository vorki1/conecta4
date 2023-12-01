#pragma once
#include <iostream>
#include <climits>
#include <fstream>
#include "GenerarArbol.hpp"

using namespace std;

void imprimirTablero(int** m)
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if(*(*(m + i) + j)==1)cout<<"|X|";
            else if(*(*(m + i) + j)==2) cout<<"|O|";
            else cout<<"|_|";
            
        }
        cout<<endl;
    }
}
int** crearTablero()
{
    int** m = new int*[6];
    for (int i = 0; i < 6; i++)
    {
        m[i] = new int[7];
    }
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            *(*(m + i) + j) = 0;
        }
    }
    return m;
}
int evaluarLinea(int s1, int s2, int s3, int s4);
void escribirMatrizEnArchivo(const char* nombreArchivo,int**);
void ingresarPuntuaciones(int ,int);

class Sistema
{
private:
    GenerarArbol* base;
    int** tablero;
    int columnaCPU;
    int ganaJugador=0;
    int ganaCPU=0;

    int minimax(NodoArbol* nodo, int profundidad, int alfa, int beta, bool esMaximizando);
    int evaluarTablero();
    int ingresarFichaCPU();

public:
    Sistema(GenerarArbol* base)
    {
        this->base = base;
        this->tablero = crearTablero();
        cargarPuntuaciones();
    }
    void setTablero()
    {
        this->tablero = crearTablero();
    }
    void ganador(int jugador)
    {
        if(jugador==1)ganaJugador++;
        else if(jugador==2)ganaCPU++;
    }
    int getVictoriasJugador()
    {
        return ganaJugador;
    }
    int getVictoriasCPU()
    {
        return ganaCPU;
    }
    void cargarPuntuaciones();
    bool ingresarFicha(int columna);//Listo
    bool fichaCPU(string dificultad);//Listo
    void fichaRandomCPU(int);
    bool validarJugada(int,int);//Listo
    void guardarPartida();
    void cargarPartida();
    void puntuaciones();
    ~Sistema();
};

bool Sistema::ingresarFicha(int columna)
{
    for (int i = 5; i >= 0; i--)
    {
        if (*(*(tablero + i) + columna) == 0)
        {
            *(*(tablero + i) + columna) = 1;
            break;
        }
        if (i == 0) return false;
    }
    imprimirTablero(tablero);
    return true;
}
bool Sistema::fichaCPU(string dificultad)
{
    if(dificultad=="F")
    {
        int columna = rand() % 7;
        fichaRandomCPU(columna);
        cout<<"Movimiento de la computadora: "<<endl;
        imprimirTablero(tablero);
        return validarJugada(columna,2);
    }
    else if(dificultad=="M")
    {
        if (rand() % 100 < 20) 
        {  // Aproximadamente un 20% de las veces toma una decisión aleatoria
            int columna = rand() % 7;
            fichaRandomCPU(columna);
            cout<<"Movimiento de la computadora: "<<endl;
            imprimirTablero(tablero);
            return validarJugada(columna,2);
        } 
        else 
        {
            columnaCPU = ingresarFichaCPU();
            cout<<"Movimiento de la computadora: "<<endl;
            imprimirTablero(tablero);
            return validarJugada(columnaCPU,2);
        }

    }
    if(dificultad=="D")
    {
        columnaCPU = ingresarFichaCPU();
        cout<<"Movimiento de la computadora: "<<endl;
        imprimirTablero(tablero);
        return validarJugada(columnaCPU,2);
    }
    return false;
}
void Sistema::fichaRandomCPU(int columna)
{
    for (int i = 5; i >= 0; i--)
    {
        if (*(*(tablero + i) + columna) == 0)
        {
            *(*(tablero + i) + columna) = 2;
            return;
        }
        if (i == 0) fichaRandomCPU(columna);
    }
}

int Sistema::minimax(NodoArbol* nodo, int profundidad, int alfa, int beta, bool esMaximizando)
{
    if (profundidad == 0 || nodo->esUnaHoja())
    {
        return evaluarTablero();
    }

    if (esMaximizando)
    {
        int mejorValor = INT_MIN;
        for (NodoArbol* hijo : nodo->getHijos())
        {
            int valor = minimax(hijo, profundidad - 1, alfa, beta, false);
            mejorValor = max(mejorValor, valor);
            alfa = max(alfa, mejorValor);

            if (beta <= alfa)
                break; // Poda alfa-beta

        }
        return mejorValor;
    }
    else
    {
        int mejorValor = INT_MAX;
        for (NodoArbol* hijo : nodo->getHijos())
        {
            int valor = minimax(hijo, profundidad - 1, alfa, beta, true);
            mejorValor = min(mejorValor, valor);
            beta = min(beta, mejorValor);

            if (beta <= alfa)
                break; // Poda alfa-beta
        }
        return mejorValor;
    }
}


int Sistema::evaluarTablero()
{
    int puntaje = 0;

    // Evaluar las filas
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 4; ++j) {
            puntaje += evaluarLinea(*(*(tablero + i) + j), *(*(tablero + i) + j+1), *(*(tablero + i) + j+2), *(*(tablero + i) + j+3));
        }
    }

    // Evaluar las columnas
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 3; ++j) {
            puntaje += evaluarLinea(*(*(tablero + j) + i), *(*(tablero + j + 1) + i), *(*(tablero + j + 2) + i), *(*(tablero + j + 3) + i));
        }
    }

    // Evaluar las diagonales "/"
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            puntaje += evaluarLinea(*(*(tablero + i) + j), *(*(tablero + i + 1) + j + 1), *(*(tablero + i + 2) + j + 2), *(*(tablero + i + 3) + j + 3));
        }
    }

    // Evaluar las diagonales "\"
    for (int i = 0; i < 3; ++i) {
        for (int j = 3; j < 7; ++j) {
            puntaje += evaluarLinea(*(*(tablero + i) + j), *(*(tablero + i + 1) + j - 1), *(*(tablero + i + 2) + j - 2), *(*(tablero + i + 3) + j - 3));
        }
    }

    return puntaje;
}

int evaluarLinea(int s1, int s2, int s3, int s4) {
    int puntaje = 0;

    // Contar las fichas del jugador en la línea
    int fichasJugador = 0;
    int fichasOponente = 0;

    if (s1 == 1) fichasJugador++;
    else if (s1 == 2) fichasOponente++;

    if (s2 == 1) fichasJugador++;
    else if (s2 == 2) fichasOponente++;

    if (s3 == 1) fichasJugador++;
    else if (s3 == 2) fichasOponente++;

    if (s4 == 1) fichasJugador++;
    else if (s4 == 2) fichasOponente++;

    // Asignar puntajes según la cantidad de fichas en la línea
    if (fichasJugador == 4) puntaje += 100; // Ganador
    else if (fichasJugador == 3 && fichasOponente == 0) puntaje += 5; // Tres fichas del jugador
    else if (fichasJugador == 2 && fichasOponente == 0) puntaje += 2; // Dos fichas del jugador

    if (fichasOponente == 4) puntaje -= 100; // Oponente gana
    else if (fichasOponente == 3 && fichasJugador == 0) puntaje -= 5; // Tres fichas del oponente
    else if (fichasOponente == 2 && fichasJugador == 0) puntaje -= 2; // Dos fichas del oponente

    return puntaje;
}

int Sistema::ingresarFichaCPU()
{
    int mejorJugada = -1;
    int mejorValor = INT_MIN;

    for (int columna = 0; columna < 7; ++columna)
    {
        int fila = 5;  // Comenzar desde la parte inferior de la columna

        while (fila >= 0 && *(*(tablero + fila) + columna) != 0)
        {
            --fila;
        }

        if (fila >= 0)
        {
            *(*(tablero + fila) + columna) = 2;  // Colocar la ficha en la posición válida
            int valor = minimax(base->getRaiz(), 7, INT_MIN, INT_MAX, false);  // Evaluar el tablero después de colocar la ficha
            cout << "Valor de la jugada " << columna << ": " << valor << endl;

            if (valor > mejorValor)
            {
                mejorValor = valor;
                mejorJugada = columna;
            }

            *(*(tablero + fila) + columna) = 0;  // Deshacer la jugada para probar con la siguiente columna
        }
    }

    cout << "Mejor jugada: " << mejorJugada << " con valor: " << mejorValor << endl;

    for (int i = 5; i >= 0; i--)
    {
        if (*(*(tablero + i) + mejorJugada) == 0)
        {
            *(*(tablero + i) + mejorJugada) = 2;
            return mejorJugada;
        }
        //if(i=0)return 0;
    }
    return 0;
}

bool::Sistema::validarJugada(int columna,int jugador)
{
    int cant = 0;
    int fila=5;
    for (int i = 0; i < 5; i++)
    {
        if (*(*(tablero + i) + columna)!=0)
        {
            fila=i;
            break;
        }
    }
    int inicioCol= columna;
    //Horizontal
    for (int i = columna; i >= 0; i--)
    {

        if(*(*(tablero + fila) + i)==jugador)
        {
            inicioCol=i;
        }
        else if(*(*(tablero + fila) + i)==0)break;
    }
    for (int i = 0; i < 4; i++)
    {
        if(*(*(tablero + fila) + inicioCol)==jugador)
        {
            cant++;
            inicioCol++;
        }
    }
    if(cant==4)
    {
    cout<<"Gano en la horizontal de: "<<fila<<endl;
    return true;
    }


    cant=0;
    int inicioFil = fila;
    //Vertical
    for (int i = fila; i >0; i--)
    {
        if(*(*(tablero + i) + columna)==jugador)
        {
            inicioFil=i;
        }
        else if(*(*(tablero + i) + columna)==0)break;
    }
    for (int i = 0; i < 4; i++)
    {
        if(*(*(tablero + inicioFil) + columna)==jugador)
        {
            cant++;
            inicioFil++;
        }
    }
    if(cant==4)
    {
    cout<<"Gano en la vertical de: "<<columna<<endl;
    return true;
    }

    //Diagonal "/"
    cant=0;
    inicioFil=fila;
    inicioCol=columna;

    for (int i = columna; i >= 0; i--)
    {
        if(tablero[inicioFil+1][inicioCol-1]==jugador && inicioFil!=0)
        {
            inicioFil++;
            inicioCol--; 
        }
        else if(tablero[inicioFil][inicioCol]==jugador || inicioFil!= -1)break;
    }

    for (int i = 0; i < 4; i++)
    {
        if(tablero[inicioFil][inicioCol]==jugador)
        {
            cant++;
            inicioFil--;
            inicioCol++;
        }
    }
    if(cant==4) 
    {
    cout<<"Gano en la diagonal que parte de: "<<inicioFil<<" "<<inicioCol<<endl;
    return true;
    }


    //Diagonal "\"
    cant=0;
    inicioFil=fila;
    inicioCol=columna;

    for (int i = columna; i >= 0; i--)
    {
        if(fila==0)break;
        else if(*(*(tablero + inicioFil-1) + inicioCol-1)==0)break;
        else if(*(*(tablero + inicioFil-1) + inicioCol-1)==1)
        {
            inicioFil--;
            inicioCol--; 
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if(*(*(tablero + inicioFil) + inicioCol)==1)
        {
            cant++;
            inicioFil++;
            inicioCol++;
        }
    }
    if(cant==4)
    {
    cout<<"Gano en la diagonal que parte de: "<<inicioFil<<" "<<inicioCol<<endl;
    return true;
    }
    return false;
}

void Sistema::guardarPartida()
{
    const char* nombreArchivo = "partida_guardada.txt";
    escribirMatrizEnArchivo(nombreArchivo,tablero);
}
void escribirMatrizEnArchivo(const char* nombreArchivo,int** tablero)
{
    ofstream archivo(nombreArchivo);

    if (archivo.is_open())
    {
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                archivo << *(*(tablero + i) + j) << " ";
            }
            archivo << endl;
        }

        archivo.close();
        cout << "Matriz guardada en el archivo " << nombreArchivo << endl;
    }
    else
    {
        cout << "No se pudo abrir el archivo " << nombreArchivo << " para guardar la matriz." << endl;
    }
}
void Sistema::cargarPartida()
{
    const char* nombreArchivo = "partida_guardada.txt";
    ifstream archivo(nombreArchivo);

    if (archivo.is_open())
    {
        // Limpiar el tablero actual
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                *(*(tablero + i) + j) = 0;
            }
        }

        // Leer los valores desde el archivo y actualizar el tablero
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                archivo >> *(*(tablero + i) + j);
            }
        }

        archivo.close();
        cout << "Matriz cargada desde el archivo " << nombreArchivo << endl;
    }
    else
    {
        cout << "No se pudo abrir el archivo " << nombreArchivo << " para cargar la matriz." << endl;
    }
}
void Sistema::puntuaciones()
{

    const char* nombreArchivo = "estadisticas.txt";
    ofstream archivo(nombreArchivo);

    if (archivo.is_open())
    {
        archivo <<getVictoriasJugador() << endl;
        archivo <<getVictoriasCPU() << endl;

        archivo.close();
        cout << "Estadísticas guardadas en el archivo " << nombreArchivo << endl;
    }
    else
    {
        cout << "No se pudo abrir el archivo " << nombreArchivo << " para guardar las estadísticas." << endl;
    }
}
void Sistema::cargarPuntuaciones() 
{
        const char* nombreArchivo = "estadisticas.txt";
        ifstream archivo(nombreArchivo);

        if (archivo.is_open()) {
            archivo >> ganaJugador >> ganaCPU;
            cout<<" Este puntaje tiene el jugador: "<<ganaJugador<<endl;
            cout<<" Este puntaje tiene la CPU: "<<ganaCPU<<endl;
            archivo.close();
            cout << "Estadísticas cargadas desde el archivo " << nombreArchivo << endl;
        } else {
            // Si no se pudo abrir el archivo, asignamos 0 a ambas variables
            ganaJugador = 0;
            ganaCPU = 0;
            cout << "No se pudo abrir el archivo " << nombreArchivo << ". Se asignaron 0 a las estadísticas." << endl;
        }
    }