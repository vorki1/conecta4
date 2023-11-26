#pragma once
#include <iostream>
#include <stdlib.h>
#include "NodoArbol.h"
using namespace std;

const int fil = 6;
const int col = 7;

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
        /*for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                //*(*(raiz->getTablero()+i)+j)=2;
            }
        }*/
    }
    void crearRamas();
    ~GenerarArbol();
};



GenerarArbol::~GenerarArbol()
{
}
