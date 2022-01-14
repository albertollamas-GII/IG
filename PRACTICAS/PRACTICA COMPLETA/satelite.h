#ifndef SATELITE_H_INCLUDED
#define SATELITE_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"
#include "objply.h"
#include "esfera.h"
#include "cubo.h"
#include "cono.h"
#include "cilindro.h"
#include "prisma.h"
#include "antena.h"
#include "paneles.h"
#include "material.h"
#include "semiesfera.h"

class Satelite{
    public:
        Satelite();
        void draw(modoDibujado modo, std::vector<bool> visu, bool tapas);
        void drawBaseCentral(modoDibujado modo, std::vector<bool> visu, bool tapas);
        
        void animacion();
        void setManual(bool manual);
        void aumentar_beta();
        void reducir_beta();
        void aumentar_alpha();
        void reducir_alpha();
        void aumentar_x_nave();
        void reducir_x_nave();
        void aumentar_tita();
        void girar();
        void reducir_giro();
        void aumentar_traslacion();
        void reducir_traslacion();
    private:
        //Elementos Satelite
        Antena *antena = nullptr;

        Panel *panelInferior1 = nullptr;
        Panel *panelInferior2 = nullptr;
        Panel *panelSuperior1 = nullptr;
        Panel *panelSuperior2 = nullptr;

        Cubo *baseAntena = nullptr;
        Cubo *baseCola = nullptr;
        Cilindro *conector = nullptr;

        SemiEsfera *cola = nullptr;
        Cilindro *conectaCola = nullptr;

        //Elementos animacion
        int manual;
        float alpha, beta, tita;
        float velocidad_alpha,velocidad_beta, velocidad_giro, velocidad_traslacion;
        bool giroAntena;

        float x_nave, velocidad_altura, giro, traslacion;


};


#endif