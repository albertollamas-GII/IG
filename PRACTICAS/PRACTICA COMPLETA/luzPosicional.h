// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luzPosicional.h

//
// #############################################################################

#ifndef LUZPOSICIONAL_H_INCLUDED
#define LUZPOSICIONAL_H_INCLUDED

#include "aux.h"
#include "luz.h"

// *****************************************************************************
//
//
// *****************************************************************************

// *****************************************************************************

class LuzPosicional : public Luz { 
    public:
        LuzPosicional( const Tupla3f & posicion, GLenum idLuzOpenGL, Tupla4f colorDifuso, Tupla4f colorEspecular, Tupla4f colorAmbiente) ;
};
#endif