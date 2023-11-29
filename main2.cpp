#include <iostream>
#include "Sistema.hpp"
using namespace std;


int** crearTablero();
void comenzarJuego(GenerarArbol*);

int main()
{
    int** tablero = crearTablero();
    NodoArbol* raiz = new NodoArbol(tablero);
    GenerarArbol* arbolPosibilidades = new GenerarArbol(raiz,5);
    

    //Este for sirve para comprobar el funcionamiento de la generacion del arbol de posibilidades
    /*for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            
            cout<<*(*(raiz->getHijos()[0]->getHijos()[6]->getHijos()[0]->getHijos()[0]->getTablero() +i)+j);
        }
        cout<<endl;
    }*/

    int opcion;
    do
    {
        cout<<"     Ingrese la dificultad: "<<endl;
        cout<<"1) Facil"<<endl;
        cout<<"2) Medio"<<endl;
        cout<<"3) Dificil"<<endl;
        cout<<" "<<endl;
        cout<<"4) 2 jugadores"<<endl;
        cout<<"5) Puntuaciones"<<endl;
        cout<<"6) Guardar partida"<<endl;
        cout<<"7) Cargar partida"<<endl;
        cout<<"0) Salir"<<endl;cin>>opcion;
        switch (opcion)
        {
        case 1:
            comenzarJuego(arbolPosibilidades);
            break;
        case 2:
            cout<<"Opcion 2"<<endl;
            break;
        case 3:
            cout<<"Opcion 3"<<endl;
            break;
        case 4:
            break;
        case 5:
            cout<<"Opcion 5"<<endl;
            break;
        case 6:
            cout<<"Opcion 6"<<endl;
            break;
        case 0:
            cout<<"Opcion 0"<<endl;
            break;
        default:
            cout<<"ingrese una opcion valida"<<endl;
            break;
        }
        
    } while (opcion!=0);
    
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

void comenzarJuego(GenerarArbol* ramaPosibilidades)
{

}