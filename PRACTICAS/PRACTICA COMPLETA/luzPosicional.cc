#include "luzPosicional.h"

LuzPosicional::LuzPosicional(const Tupla3f & posicion, GLenum idLuzOpenGL, Tupla4f colorDifuso, Tupla4f colorEspecular, Tupla4f colorAmbiente){
    Tupla4f pos;
    pos(0) = posicion(0);
    pos(1) = posicion(1);
    pos(2) = posicion(2);
    pos(3) = 1.0;
    this->setPosicion(pos);
    this->setID(idLuzOpenGL);
    this->setColorAmbiente(colorAmbiente);
    this->setColorDifuso(colorDifuso);
    this->setColorEspecular(colorEspecular);
}