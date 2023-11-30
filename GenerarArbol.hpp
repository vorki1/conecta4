#pragma once
#include <iostream>
#include <stdlib.h>
#include "NodoArbol.h"
using namespace std;


void crearProfundidades(NodoArbol*,int profundidad,int jugador);
void ingresarFicha(NodoArbol*,int**,int,int);
class GenerarArbol
{
private:
    NodoArbol* raiz;
    int profundidad;
    int jugador=1;
public:
    GenerarArbol(NodoArbol* raiz,int profundidad)
    {
        this->raiz=raiz;
        this->profundidad=profundidad;
        crearProfundidades(raiz,profundidad,1);
    }
    void setearProfundidades(int** tablero,int prof)
    {
        raiz->setTablero(tablero);
        crearProfundidades(raiz,prof,1);
    }
    NodoArbol* getRaiz()
    {
        return raiz;
    }
    ~GenerarArbol();
};


void crearProfundidades(NodoArbol* raiz,int profundidad,int jugador)
{
    if (profundidad==0)return;//Caso base

    jugador++;
    if(jugador!=2)jugador=1;
    raiz->generarHijos(raiz->getTablero());//Se generan los 7 hijos de la raiz
    for (int i = 0; i < raiz->getHijos().size(); i++)
    {
        ingresarFicha(raiz->getHijos()[i],raiz->getTablero(),i,jugador);
        raiz->getHijos()[i]->setMovimiento(i);
    }
    
    for (int i = 0; i < raiz->getHijos().size(); i++)
    {
        crearProfundidades(raiz->getHijos()[i],profundidad-1,jugador);
    }
    
}

void ingresarFicha(NodoArbol* raiz,int** tablero,int columna,int jugador)
{
    for (int i  =5; i >= 0; i--)
    {
        if(*(*(tablero+i)+columna)==0 && jugador==1)
        {
            *(*(tablero+i)+columna)=1;
            raiz->setTablero(tablero);
            return;
        }
        else if(*(*(tablero+i)+columna)==0 && jugador==2)
        {
            *(*(tablero+i)+columna)=2;
            raiz->setTablero(tablero);
            return;
        }
    }
}

GenerarArbol::~GenerarArbol()
{
   
}
