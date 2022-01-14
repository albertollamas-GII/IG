// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luz.h

//
// #############################################################################

#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

// *****************************************************************************
//
//
// *****************************************************************************

// *****************************************************************************

class Luz {
    private:
        Tupla4f posicion;
        GLenum id;
        Tupla4f colorAmbiente;
        Tupla4f colorDifuso;
        Tupla4f colorEspecular;
    public:
        void activar();
        void desactivar();
        Tupla4f getPosicion();

    protected:
        void setPosicion(Tupla4f posicion);
        void setID(GLenum id);
        void setColorAmbiente(Tupla4f colorAmbiente);
        void setColorDifuso(Tupla4f colorDifuso);
        void setColorEspecular(Tupla4f colorEspecular);

};

#endif