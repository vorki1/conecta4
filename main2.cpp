#include <iostream>
#include "Nodo.hpp"
using namespace std;

void generarArbol(Nodo* raiz, int profundidad);
bool juegoTerminado(string tablero[6][7],int columna,int jugador);
int main()
{
    Nodo* raiz = new Nodo();
    return 0;
}

void generarArbol(Nodo* nodo, int profundidad) {
    if (profundidad == 0 || nodo->juegoTerminado()) {
        //nodo->setPuntaje(evaluarTablero(nodo->tablero));
        return;
    }

    // Generar nodos hijos para todas las posibles jugadas
    for (int columna = 0; columna < 7; columna++) {
        if (true/*columnaValida(nodo->tablero, columna)*/) {
            Nodo* hijo = new Nodo();
            // Realizar la jugada en el nuevo nodo
            // ...
            //nodo->hijos.push_back(hijo);
            generarArbol(hijo, profundidad - 1);
        }
    }
}

bool juegoTerminado(string tablero[6][7],int columna,int jugador)
{
    int cant = 0;
    int fila=5;
    string player=""; 
    if(jugador==1)
    {
        player = " X ";
    }
    else
    {
        player= " O ";
    }
    for (int i = 0; i < 5; i++)
    {
        if (tablero[i][columna]!=" * ")
        {
            fila=i;
            break;
        }
    }
    int inicioCol= columna;
    //Horizontal
    for (int i = columna; i >= 0; i--)
    {

        if(tablero[fila][i]==player)
        {
            inicioCol=i;
        }
        else if(tablero[fila][i]==" * ")break;
    }
    for (int i = 0; i < 4; i++)
    {
        if(tablero[fila][inicioCol]==player)
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
        if(tablero[i][columna]==player)
        {
            inicioFil=i;
        }
        else if(tablero[i][columna]==" * ")break;
    }
    for (int i = 0; i < 4; i++)
    {
        if(tablero[inicioFil][columna]==player)
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
        if(tablero[inicioFil+1][inicioCol-1]==player && inicioFil!=0)
        {
            inicioFil++;
            inicioCol--; 
        }
        else if(tablero[inicioFil][inicioCol]==player || inicioFil!= -1)break;
    }

    for (int i = 0; i < 4; i++)
    {
        if(tablero[inicioFil][inicioCol]==player)
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
        else if(tablero[inicioFil-1][inicioCol-1]==" * ")break;
        else if(tablero[inicioFil-1][inicioCol-1]==" X " )
        {
            inicioFil--;
            inicioCol--; 
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if(tablero[inicioFil][inicioCol]==" X ")
        {
            cant++;
            inicioFil++;
            inicioCol++;
        }
    }
    cout<<fila<<endl;
    if(cant==4)
    {
    cout<<"Gano en la diagonal que parte de: "<<inicioFil<<" "<<inicioCol<<endl;
    return true;
    }
    return false;

}