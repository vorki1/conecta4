#include <iostream>
#include "GenerarArbol.hpp"
using namespace std;


void tableroVacio(int**);
int** crearTablero();

int main()
{
    int** tablero = crearTablero();
    
    cout<<"Hola";
    tableroVacio(tablero);
    NodoArbol* raiz= new NodoArbol(tablero);
    return 0;
}

int** crearTablero()
{
    int** m = new int*[6];
    for (int i = 0; i < 6; i++)
    {
        m[0] = new int[7];
    }
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            cout<<"Hola"<<endl;
            *(*(m+i)+j) = 0;
        }
    }
    
    return m;
}

void tableroVacio(int** tablero)
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            cout<<"Hola"<<i<<" ";
            *(*(tablero+i)+j)=0;
        }
        
    }
    cout<<"Hola";
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            cout<<*(*(tablero+i)+j);
        }
        cout<<endl;
        
    }
    
}
