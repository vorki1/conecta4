#pragma once
#include <iostream>
#include <vector>
using namespace std;

class NodoArbol
{
private:
    int **tablero;
    int puntaje;
    vector<NodoArbol*> hijos;
    int movimiento;
    bool esHoja;
public:
    NodoArbol(int**tablero)
    {   
        this->tablero=tablero;
        esHoja=true;
    }
    int getPuntaje()
    {
        return puntaje;
    }
    void setPuntaje(int puntaje)
    {
        this->puntaje=puntaje;
    }
    int getMovimiento()
    {
        return movimiento;
    }
    void setMovimiento(int columna)
    {
        this->movimiento=columna;
    }
    int** getTablero()
    {
        int** aux = new int*[6];
    
        for (int i = 0; i < 6; ++i) {
            aux[i] = new int[7];
            for (int j = 0; j < 7; ++j) {
                *(*(aux+i)+j) = *(*(tablero+i)+j);
            }
    }
        return aux;
    }
    void setTablero(int** tablero)
    {
        this->tablero=tablero;
    }
    vector<NodoArbol*> getHijos()
    {
        return hijos;
    }
    bool esUnaHoja()
    {
        return esHoja;
    }
    void generarHijos(int** tablero)
    {
        for (int i = 0; i < 7; i++)
        {
            NodoArbol* hijo = new NodoArbol(tablero);
            hijos.push_back(hijo);
        }
        esHoja=false;
    }
    ~NodoArbol();
};

