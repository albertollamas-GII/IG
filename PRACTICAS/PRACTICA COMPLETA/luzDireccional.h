// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luzDireccional.h

//
// #############################################################################

#ifndef LUZDIRECCIONAL_H_INCLUDED
#define LUZDIRECCIONAL_H_INCLUDED

#include "aux.h"
#include "luz.h"

// *****************************************************************************
//
//
// *****************************************************************************

// *****************************************************************************

class LuzDireccional : public Luz
{
protected:
    float alpha;
    float beta;

public:
    // inicializar la fuente de luz
    LuzDireccional(const Tupla2f &direccion, GLenum idLuzOpenGL, Tupla4f colorDifuso, Tupla4f colorEspecular, Tupla4f colorAmbiente);
    // Cambiar ángulo:
    void variarAnguloAlpha(float incremento);
    void variarAnguloBeta(float incremento);
    void calcularPosicion();
};

#endif