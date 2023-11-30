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

class Sistema
{
private:
    GenerarArbol* base;
    int** tablero;

    int minimax(NodoArbol* nodo, int profundidad, bool esMaximizando);
    int evaluarTablero();

    void ingresarFichaCPU();

public:
    Sistema(GenerarArbol* base)
    {
        this->base = base;
        this->tablero = crearTablero();
    }

    bool ingresarFicha(int columna);
    bool validarJugada();
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
    ingresarFichaCPU();
    cout<<"Hola"<<endl;
    imprimirTablero(tablero);
    cout<<"Como estas"<<endl;
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
    // Evaluar horizontalmente
    for (int fila = 0; fila < 6; fila++)
    {
        for (int columna = 0; columna < 5; columna++)
        {
            int suma = 0;
            for (int i = 0; i < 3; i++)
            {
                if (*(*(tablero + fila) + columna + i) == 1) suma++;
                else if (*(*(tablero + fila) + columna + i) == 2) suma--;
            }
            if (suma == 3)
                return 100; // Ganó el jugador 1
            else if (suma == -3)
                return -100; // Ganó el jugador 2
        }
    }

    // Evaluar verticalmente
    for (int columna = 0; columna < 7; columna++)
    {
        for (int fila = 0; fila < 4; fila++)
        {
            int suma = 0;
            for (int i = 0; i < 3; i++)
            {
                if (*(*(tablero + fila + i) + columna) == 1) suma++;
                else if (*(*(tablero + fila + i) + columna) == 2) suma--;
            }
            if (suma == 3)
                return 100; // Ganó el jugador 1
            else if (suma == -3)
                return -100; // Ganó el jugador 2
        }
    }

    // Evaluar diagonalmente (hacia abajo a la derecha)
    for (int fila = 0; fila < 4; fila++)
    {
        for (int columna = 0; columna < 5; columna++)
        {
            int suma = 0;
            for (int i = 0; i < 3; i++)
            {
                if (*(*(tablero + fila + i) + columna + i) == 1) suma++;
                else if (*(*(tablero + fila + i) + columna + i) == 2) suma--;
            }
            if (suma == 3)
                return 100; // Ganó el jugador 1
            else if (suma == -3)
                return -100; // Ganó el jugador 2
        }
    }

    // Evaluar diagonalmente (hacia arriba a la derecha)
    for (int fila = 2; fila < 6; fila++)
    {
        for (int columna = 0; columna < 5; columna++)
        {
            int suma = 0;
            for (int i = 0; i < 3; i++)
            {
                if (*(*(tablero + fila - i) + columna + i) == 1) suma++;
                else if (*(*(tablero + fila - i) + columna + i) == 2) suma--;
            }
            if (suma == 3)
                return 100; // Ganó el jugador 1
            else if (suma == -3)
                return -100; // Ganó el jugador 2
        }
    }

    // Si no hay ganador, devuelve 0
    return 1;
}



void Sistema::ingresarFichaCPU()
{
    int mejorJugada = -1;
    int mejorValor = INT_MIN;

    for (NodoArbol* hijo : base->getRaiz()->getHijos())
    {
        int valor = minimax(hijo, 5, false); // Ajusta la profundidad según tus necesidades
        cout << "Valor de la jugada " << hijo->getMovimiento() << ": " << valor << endl;
        cout<<mejorJugada<<endl;
        if (valor >= mejorValor)//Aqui esta en el error, en el >=, la variable valor nunca cambia de valor, porque falta evaluar mejor el tablero.
        {
            mejorValor = valor;
            mejorJugada = hijo->getMovimiento();
            cout<<mejorJugada<<endl;
        }
    }

    cout << "Mejor jugada: " << mejorJugada << " con valor: " << mejorValor << endl;

    for (int i = 5; i >= 0; i--)
    {
        if (*(*(tablero + i) + mejorJugada) == 0)
        {
            *(*(tablero + i) + mejorJugada) = 2;
            return;
        }
    }
}


// Resto de la implementación de la clase Sistema...
