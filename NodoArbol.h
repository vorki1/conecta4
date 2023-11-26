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
public:
    NodoArbol(int**tablero)
    {   
        this->tablero=tablero;
        /*
        tablero = new int*[6];
        for (int i = 0; i < 6; i++)
        {
            tablero[i]= new int[7];
        }*/
        //Para poner elementos en una matriz: cin>>*(*(tablero+i)+j)
    }
    int getPuntaje()
    {
        return puntaje;
    }
    void setPuntaje(int puntaje)
    {
        this->puntaje=puntaje;
    }
    int** getTablero()
    {
        return tablero;
    }
    vector<NodoArbol*> getHijos()
    {
        return hijos;
    }
    ~NodoArbol();
};

