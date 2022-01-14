// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cilindro.h

//
// #############################################################################

#ifndef CILINDRO_H_INCLUDED
#define CILINDRO_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clases derivadas de ObjRevolucion (definen constructores específicos)
//
// *****************************************************************************

class Cilindro : public ObjRevolucion{
    
    public:
        Cilindro(const int num_vert_perfil = 2, const int num_instancias_perf = 20, const float altura = 1.0, const float radio = 1.0, bool tapa_sup = true, bool tapa_inf = true);
};

#endif