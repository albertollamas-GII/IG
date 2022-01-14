#ifndef PATANAVEALIEN_H_INCLUDED
#define PATANAVEALIEN_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"
#include "objply.h"
#include "esfera.h"
#include "cilindro.h"
#include "material.h"

class pataNaveAlien{
    private:
        Cilindro *basePata = nullptr;
        Cilindro *pata = nullptr;
        Esfera *apoyo = nullptr;
        
    public:
        pataNaveAlien(Material material);
        void draw(modoDibujado modo, std::vector<bool> visu, bool tapas);
};

#endif