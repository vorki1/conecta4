#include <iostream>
using namespace std;

int main()
{
    int opcion;
    //Tablero de 6x7
    string casilla = "O";
    cout<<casilla+" "+casilla+" "+casilla+" "+casilla+" "+casilla+" "+casilla+" "+casilla<<endl;
    cout<<casilla+" "+casilla+" "+casilla+" "+casilla+" "+casilla+" "+casilla+" "+casilla<<endl;
    cout<<casilla+" "+casilla+" "+casilla+" "+casilla+" "+casilla+" "+casilla+" "+casilla<<endl;
    cout<<casilla+" "+casilla+" "+casilla+" "+casilla+" "+casilla+" "+casilla+" "+casilla<<endl;
    cout<<casilla+" "+casilla+" "+casilla+" "+casilla+" "+casilla+" "+casilla+" "+casilla<<endl;
    cout<<casilla+" "+casilla+" "+casilla+" "+casilla+" "+casilla+" "+casilla+" "+casilla<<endl;
    do
    {
        cout<<"     Ingrese la dificultad: "<<endl;
        cout<<"1) Facil"<<endl;
        cout<<"2) Medio"<<endl;
        cout<<"3) Dificil"<<endl;
        cout<<" "<<endl;
        cout<<"4) Puntuaciones"<<endl;
        cout<<"5) Guardar partida"<<endl;
        cout<<"6) Cargar partida"<<endl;
        cout<<"0) Salir"<<endl;cin>>opcion;
        switch (opcion)
        {
        case 1:
            cout<<"Opcion 1"<<endl;
            break;
        case 2:
            cout<<"Opcion 2"<<endl;
            break;
        case 3:
            cout<<"Opcion 3"<<endl;
            break;
        case 4:
            cout<<"Opcion 4"<<endl;
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