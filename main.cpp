#include <iostream>
using namespace std;

void rellenar(string tablero[6][7]);
void imprimirTablero(string tablero[6][7]);
void comenzarJuego(string,string tablero[6][7]);
void ingresarFicha(string tablero[6][7],int,int);
bool juegoTerminado(string tablero[6][7],int,int);
bool evaluarTablero(string tablero[6][7], int);

int main()
{
    string tablero[6][7];
    rellenar(tablero);
    int opcion;
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
            comenzarJuego("F",tablero);
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

void rellenar(string tablero[6][7])
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            tablero[i][j]=" * ";
        }
    }
}

void imprimirTablero(string tablero[6][7])
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            
                cout<<tablero[i][j];
        }
        cout<<endl;
    }
    
}

void comenzarJuego(string dificultad,string tablero[6][7])
{
    bool bandera = true;
    int columna;
    int jugador = 1;

    do
    {
        imprimirTablero(tablero);
        //cout<<"Ingresa una columna (solo ingresar un numero del 1 al 7): "<<endl;cin>>columna;
        cout<<"numero del 1 al 7: "<<endl;cin>>columna;
        if(columna < 1 || columna > 7)cout<<"La columna ingresada es invalida."<<endl;
        else
        {
            ingresarFicha(tablero,columna-1,jugador);
            if(juegoTerminado(tablero,columna-1,jugador)) 
            {
                bandera=false;
                cout<<"Ganó el jugador "<<jugador<<endl;
            }
            if(jugador==1)jugador++;
            else if(jugador==2)jugador--;
        }
    } while (bandera);
    cout<<"El juego termino:"<<endl;
    rellenar(tablero);
}

void ingresarFicha(string tablero[6][7],int columna,int jugador)
{
    for (int i = 6; i >= 0; i--)
    {
        if(tablero[i][columna]==" * " && jugador==1)
        {
            tablero[i][columna]=" X ";
            return;
        }
        if(tablero[i][columna]==" * " && jugador==2)
        {
            tablero[i][columna]=" O ";
            return;
        }
        if(i==0) cout<<"La columna esta llena "<<endl;
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
    cout<<"La ficha se inserto en la fila "<<fila<<" de la columna "<<columna<<endl;
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
    if(cant==4)return true;
    


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
    if(cant==4)return true;

    //Diagonal "/"
    cant=0;
    inicioFil=fila;
    inicioCol=columna;

    for (int i = columna; i >= 0; i--)
    {
        if(tablero[inicioFil+1][inicioCol-1]==player)
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
    if(cant==4) return true;


    //Diagonal "\"
    cant=0;
    inicioFil=fila;
    inicioCol=columna;

    for (int i = columna; i >= 0; i--)
    {
        if(tablero[inicioFil][inicioCol]==" * " || inicioCol == 0)break;
        else if(tablero[inicioFil-1][inicioCol-1]==" X ")
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
    if(cant==4) return true;

    if(columna == 6)return true;
    


    return false;

}

bool evaluarTablero(string tablero[6][7],int columna)
{
    for (int i = 0; i < 7; i++)
    {
        if(tablero[i][columna]=="")
        {
            tablero[i][columna]="X";
            return true;
        }
    }
    return false;
}