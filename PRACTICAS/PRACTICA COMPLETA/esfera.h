// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Esfera.h

//
// #############################################################################

#ifndef ESFERA_H_INCLUDED
#define ESFERA_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clases derivadas de ObjRevolucion (definen constructores específicos)
//
// *****************************************************************************

class Esfera : public ObjRevolucion{

    public:
        Esfera(const int num_vert_perfil = 10, const int num_instancias_perf = 20, const float r = 1.0, bool tapa_sup=true, bool tapa_inf=true);

};

#endif