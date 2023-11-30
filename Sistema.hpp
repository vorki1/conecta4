#pragma once
#include <iostream>
#include <climits>
#include "GenerarArbol.hpp"

using namespace std;

void imprimirTablero(int** m)
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            cout<<*(*(m + i) + j);
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

class Sistema
{
private:
    GenerarArbol* base;
    int** tablero;
    int columnaCPU;

    int minimax(NodoArbol* nodo, int profundidad, bool esMaximizando);
    int evaluarTablero();
    int ingresarFichaCPU();

public:
    Sistema(GenerarArbol* base)
    {
        this->base = base;
        this->tablero = crearTablero();
    }

    bool ingresarFicha(int columna);
    bool validarJugada(int,int);
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
        if (i == 0)
            return false;
    }
    columnaCPU = ingresarFichaCPU();
    imprimirTablero(tablero);
    return true;
}

int Sistema::minimax(NodoArbol* nodo, int profundidad, bool esMaximizando)
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
            int valor = minimax(hijo, profundidad - 1, false);
            mejorValor = max(mejorValor, valor);
        }
        return mejorValor;
    }
    else
    {
        int mejorValor = INT_MAX;
        for (NodoArbol* hijo : nodo->getHijos())
        {
            int valor = minimax(hijo, profundidad - 1, true);
            mejorValor = min(mejorValor, valor);
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
            int valor = minimax(base->getRaiz(), 5, false);  // Evaluar el tablero después de colocar la ficha
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
    }
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

