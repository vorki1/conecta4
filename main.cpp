#include <iostream>
#include <climits>
using namespace std;

const int PROFUNDIDAD_MAX = 5;
void rellenar(string tablero[6][7]);
void imprimirTablero(string tablero[6][7]);
void comenzarJuego(string tablero[6][7]);
void comenzarJuegoCPU(string,string tablero[6][7]);
void ingresarFicha(string tablero[6][7],int,int);
bool juegoTerminado(string tablero[6][7],int,int);
int evaluarMovimiento(string tablero[6][7], int columna, int jugador);
int minimax(string tablero[6][7], int profundidad, bool esMaximizando);
bool columnaValida(string tablero[6][7], int columna);
int evaluarTablero(string tablero[6][7]);
int evaluarLinea(string c1, string c2, string c3, string c4);

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
        cout<<"4) 2 jugadores"<<endl;
        cout<<"5) Puntuaciones"<<endl;
        cout<<"6) Guardar partida"<<endl;
        cout<<"7) Cargar partida"<<endl;
        cout<<"0) Salir"<<endl;cin>>opcion;
        switch (opcion)
        {
        case 1:
            cout<<"Opcion 1"<<endl;
            comenzarJuegoCPU("F",tablero);
            break;
        case 2:
            cout<<"Opcion 2"<<endl;
            break;
        case 3:
            cout<<"Opcion 3"<<endl;
            break;
        case 4:
            comenzarJuego(tablero);
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

void comenzarJuego(string tablero[6][7])
{
    bool bandera = true;
    int columna;
    int jugador = 1;
    do
    {
        imprimirTablero(tablero);
        cout<<"numero del 1 al 7: "<<endl;cin>>columna;
        if(columna < 1 || columna > 7)cout<<"La columna ingresada es invalida."<<endl;
        else
        {
            ingresarFicha(tablero,columna-1,jugador);
            if(juegoTerminado(tablero,columna-1,jugador))bandera=false;
            else
            {
                if(jugador==1)jugador++;
                else if(jugador==2)jugador--;
            }
        }
    } while (bandera);
    cout<<"El juego termino, ganó el jugador: "<<jugador<<endl;
    imprimirTablero(tablero);
    rellenar(tablero);
}

void comenzarJuegoCPU(string dificultad,string tablero[6][7])
{
    bool bandera = true;
    int columna;
    int jugador = 1;
    do
    {
        imprimirTablero(tablero);
        cout<<"numero del 1 al 7: "<<endl;cin>>columna;
        if(columna < 1 || columna > 7)cout<<"La columna ingresada es invalida."<<endl;
        else
        {
            ingresarFicha(tablero,columna-1,jugador);
            if(juegoTerminado(tablero,columna-1,jugador))
            {
                cout<<"El juego termino, le ganaste a la CPU"<<endl;
                break;
            }
            cout<<"Vamos bien"<<endl;
            int mejorJugada = minimax(tablero,0,true);//llamo a la funcion minimax
            ingresarFicha(tablero,mejorJugada,2);
            if(juegoTerminado(tablero,mejorJugada,2))
            {
                cout<<"El juego termino, ganó la CPU"<<endl;
                break;
            }
        }
    } while (bandera);
    
    imprimirTablero(tablero);
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
        else if(tablero[i][columna]==" * " && jugador==2)
        {
            tablero[i][columna]=" O ";
            return;
        }
        if(i==0)
        {
            do
            {
                cout<<"La columna esta llena"<<endl;
                cout<<"numero del 1 al 7: "<<endl;cin>>columna;
                if(columna < 1 || columna > 7)cout<<"La columna ingresada es invalida."<<endl;
            } while (columna < 1 || columna > 7);
            
            

            ingresarFicha(tablero,columna-1,jugador);
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

int minimax(string tablero[6][7], int profundidad, bool esMaximizando) {
    // Definir la lógica del algoritmo minimax
    // Evaluar los posibles movimientos y devolver el mejor movimiento

    // Pseudocódigo básico del algoritmo minimax
    if (profundidad == PROFUNDIDAD_MAX || juegoTerminado(tablero,1,2)) {
        // Devolver el puntaje de la hoja del árbol de juego
        return evaluarTablero(tablero);
    }

    if (esMaximizando) {
        int mejorPuntaje = INT_MIN;
        for (int columna = 0; columna < 7; columna++) {
            // Verificar si la columna es válida para realizar un movimiento
            if (columnaValida(tablero, columna)) {
                // Realizar el movimiento
                // ...
                int puntaje = minimax(tablero, profundidad + 1, false);
                // Deshacer el movimiento
                // ...
                mejorPuntaje = max(mejorPuntaje, puntaje);
            }
        }
        return mejorPuntaje;
    } else {
        int mejorPuntaje = INT_MAX;
        for (int columna = 0; columna < 7; columna++) {
            // Verificar si la columna es válida para realizar un movimiento
            if (columnaValida(tablero, columna)) {
                // Realizar el movimiento
                // ...
                int puntaje = minimax(tablero, profundidad + 1, true);
                // Deshacer el movimiento
                // ...
                mejorPuntaje = min(mejorPuntaje, puntaje);
            }
        }
        return mejorPuntaje;
    }
}
bool columnaValida(string tablero[6][7], int columna)
{
    for (int i = 6; i >=0; i--)
    {
        if (tablero[i][columna]!=" * ")return true;
    }
    return false;
    
}
int evaluarTablero(string tablero[6][7]) {
    int puntaje = 0;

    // Evaluar las filas
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 4; ++j) {
            puntaje += evaluarLinea(tablero[i][j], tablero[i][j + 1], tablero[i][j + 2], tablero[i][j + 3]);
        }
    }

    // Evaluar las columnas
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 3; ++j) {
            puntaje += evaluarLinea(tablero[j][i], tablero[j + 1][i], tablero[j + 2][i], tablero[j + 3][i]);
        }
    }

    // Evaluar las diagonales "/"
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            puntaje += evaluarLinea(tablero[i][j], tablero[i + 1][j + 1], tablero[i + 2][j + 2], tablero[i + 3][j + 3]);
        }
    }

    // Evaluar las diagonales "\"
    for (int i = 0; i < 3; ++i) {
        for (int j = 3; j < 7; ++j) {
            puntaje += evaluarLinea(tablero[i][j], tablero[i + 1][j - 1], tablero[i + 2][j - 2], tablero[i + 3][j - 3]);
        }
    }

    return puntaje;
}

int evaluarLinea(string c1, string c2, string c3, string c4) {
    int puntaje = 0;

    // Contar las fichas del jugador en la línea
    int fichasJugador = 0;
    int fichasOponente = 0;

    if (c1 == " X ") fichasJugador++;
    else if (c1 == " O ") fichasOponente++;

    if (c2 == " X ") fichasJugador++;
    else if (c2 == " O ") fichasOponente++;

    if (c3 == " X ") fichasJugador++;
    else if (c3 == " O ") fichasOponente++;

    if (c4 == " X ") fichasJugador++;
    else if (c4 == " O ") fichasOponente++;

    // Asignar puntajes según la cantidad de fichas en la línea
    if (fichasJugador == 4) puntaje += 100; // Ganador
    else if (fichasJugador == 3 && fichasOponente == 0) puntaje += 5; // Tres fichas del jugador
    else if (fichasJugador == 2 && fichasOponente == 0) puntaje += 2; // Dos fichas del jugador

    if (fichasOponente == 4) puntaje -= 100; // Oponente gana
    else if (fichasOponente == 3 && fichasJugador == 0) puntaje -= 5; // Tres fichas del oponente
    else if (fichasOponente == 2 && fichasJugador == 0) puntaje -= 2; // Dos fichas del oponente

    return puntaje;
}