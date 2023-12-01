#include <iostream>
#include "Sistema.hpp"
using namespace std;


int** crearTablero();
void comenzarJuego(Sistema*,string);

int main()
{
    int** tablero = crearTablero();
    NodoArbol* raiz = new NodoArbol(tablero);
    GenerarArbol* arbolPosibilidades = new GenerarArbol(raiz,6);
    Sistema* sistema = new Sistema(arbolPosibilidades);

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
        cout<<"6) Cargar partida"<<endl;
        cout<<"0) Salir"<<endl;cin>>opcion;
        switch (opcion)
        {
        case 1:
            comenzarJuego(sistema,"F");
            break;
        case 2:
            comenzarJuego(sistema,"M");
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
            sistema->cargarPartida();
            cout<<"Partida cargada"<<endl;
            comenzarJuego(sistema,"F");
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

void comenzarJuego(Sistema* sistema,string dificultad)
{
    int columna;
    bool bandera = true;
    do
    {
        cout<<"numero del 0 al 6: "<<endl;
        cout<<"Ingrese el numero 9 para guardar la partida: "<<endl;cin>>columna;
        if(columna==9)
        {
            sistema->guardarPartida();
            break;
        }
        if(columna < 0 || columna > 6)cout<<"La columna ingresada es invalida."<<endl;
        else
        {
            if(!sistema->ingresarFicha(columna))cout<<"La columna esta llena!!"<<endl;
            else
            {
                if(sistema->validarJugada(columna,1))
                {
                    cout<<"Has ganado!!"<<endl;
                    break;
                }
                if(sistema->fichaCPU(dificultad))
                {
                    cout<<"La CPU ha ganado!!"<<endl;
                    break;
                }
            }
            
            if(columna==5)bandera = false;
        }
    } while (bandera);
    sistema->setTablero();
}