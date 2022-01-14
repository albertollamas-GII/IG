#ifndef ALIEN_H_INCLUDED
#define ALIEN_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"
#include "objply.h"
#include "esfera.h"
#include "cilindro.h"
#include "semiesfera.h"
#include "material.h"
#include "pataNaveAlien.h"

class Alien{
    private:
        SemiEsfera *cristal = nullptr;
        Cilindro *baseNave = nullptr;
        pataNaveAlien *pata1 = nullptr;
        pataNaveAlien *pata2 = nullptr;
        pataNaveAlien *pata3 = nullptr;


    public:
        Alien(Material material);
        void draw(modoDibujado modo, std::vector<bool> visu, bool tapas);
};

#endif