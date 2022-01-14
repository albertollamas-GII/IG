#ifndef PANEL_H_INCLUDED
#define PANEL_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"
#include "objply.h"
#include "esfera.h"
#include "cilindro.h"
#include "prisma.h"
#include "alien.h"

class Panel{

    public:
        Panel (Material mat);
        void draw(modoDibujado modo, std::vector<bool> visu, bool tapas, bool balien = false, float pos_nave = 0.0);
        void aumentar_x_nave(float x);
        void reducir_x_nave(float x);
    private:
        Alien *alien = nullptr;
        Prisma *panelSolar = nullptr;
        Prisma *canal1 = nullptr;
        Prisma *canal2 = nullptr;

        float x_alien;
};


#endif