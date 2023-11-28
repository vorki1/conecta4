#pragma once
#include <iostream>
#include <stdlib.h>
#include "NodoArbol.h"
using namespace std;

const int fil = 6;
const int col = 7;

void crearProfundidades(NodoArbol*);
void ingresarFicha(NodoArbol*,int);
class GenerarArbol
{
private:
    NodoArbol* raiz;
    int profundidad;
public:
    GenerarArbol(NodoArbol* raiz,int profundidad)
    {
        this->raiz=raiz;
        this->profundidad=profundidad;
        crearProfundidades(raiz);
    }
    void crearRamas();
    ~GenerarArbol();
};


void crearProfundidades(NodoArbol* raiz)
{
    NodoArbol* hijo;
    for (int i = 0; i < 7; i++)
    {
        raiz->getHijos().push_back(hijo);
    }
    for (int i = 0; i < 7; i++)
    {
        raiz->getHijos()[0];
    }
    
}

void ingresarFicha(NodoArbol* raiz,int columna)
{
    for (int i = 6; i >= 0; i--)
    {
        if(*(*(raiz->getTablero()+i)+columna)==0)
        {
            *(*(raiz->getTablero()+i)+columna)=1;
            return;
        }
        else if(*(*(raiz->getTablero()+i)+columna)==0)
        {
            *(*(raiz->getTablero()+i)+columna)=2;
            return;
        }
        
    }
}

GenerarArbol::~GenerarArbol()
{
   
}
