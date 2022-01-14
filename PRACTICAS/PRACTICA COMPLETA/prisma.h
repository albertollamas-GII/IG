// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: prisma.h

//
// #############################################################################

#ifndef PRISMA_H_INCLUDED
#define PRISMA_H_INCLUDED

#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************


class Prisma : public Malla3D
{
   public:
   Prisma(float altura=1, float anchura=1, float profundidad=1);

} ;



#endif