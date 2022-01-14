#ifndef SEMIESFERA_H_INCLUDED
#define SEMIESFERA_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

class SemiEsfera : public ObjRevolucion{
    
    public:
        SemiEsfera(const int num_vert_perfil, const int num_instancias_perf, const float r, bool tapa_sup=true, bool tapa_inf=true);
};

#endif