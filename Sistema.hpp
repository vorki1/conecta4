#pragma once
#include <iostream>
#include "GenerarArbol.hpp"
using namespace std;

class Sistema
{
private:
    GenerarArbol* base;
public:
    Sistema(GenerarArbol* base)
    {
        this->base=base;
    }
    void ingresarFicha();
    bool validarJugada();
    void guardarPartida();
    void cargarPartida();
    void puntuaciones();
    void imprimirTablero();
    ~Sistema();
};

Sistema::Sistema(GenerarArbol* base)
{
}

Sistema::~Sistema()
{
}
