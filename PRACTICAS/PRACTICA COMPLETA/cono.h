// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cono.h

//
// #############################################################################

#ifndef CONO_H_INCLUDED
#define CONO_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clases derivadas de ObjRevolucion (definen constructores específicos)
//
// *****************************************************************************

class Cono : public ObjRevolucion{
    public:
        Cono(const int num_vert_perfil = 2, const int num_instancias_perf = 20, const float h = 1.0, const float r = 1.0, bool tapa_sup = true, bool tapa_inf = true);
};

#endif