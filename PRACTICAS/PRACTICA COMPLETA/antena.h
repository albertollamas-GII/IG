#ifndef ANTENA_H_INCLUDED
#define ANTENA_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"
#include "objply.h"
#include "esfera.h"
#include "cilindro.h"
#include "semiesfera.h"

class Antena{
    private:
        ObjPLY *antena= nullptr;
        Cilindro *tubo1 = nullptr;
    public:
        Antena(Material material);
        void draw(modoDibujado modo, std::vector<bool> visu, bool tapas);
};

#endif