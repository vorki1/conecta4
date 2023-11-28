#include <iostream>
#include "GenerarArbol.hpp"
using namespace std;


int** crearTablero();

int main()
{
    int** tablero = crearTablero();
    NodoArbol* raiz = new NodoArbol(tablero);
    GenerarArbol* arbolPosibilidades = new GenerarArbol(raiz,5);
    

    //Este for sirve para comprobar el funcionamiento de la generacion del arbol
    /*for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            
            cout<<*(*(raiz->getHijos()[0]->getHijos()[6]->getHijos()[0]->getHijos()[0]->getTablero() +i)+j);
        }
        cout<<endl;
    }*/

    return 0;
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
            
            *(*(m+i)+j) = 0;
        }
    }
    
    return m;
}