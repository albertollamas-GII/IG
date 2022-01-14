#include "aux.h"
#include "luz.h"

void Luz::activar(){
    glEnable(id);
    glLightfv(id, GL_AMBIENT, colorAmbiente);
    glLightfv(id, GL_DIFFUSE, colorDifuso);
    glLightfv(id, GL_SPECULAR, colorEspecular);
    glLightfv(id, GL_POSITION, posicion);
}

void Luz::desactivar(){
    glDisable(id);
}

void Luz::setPosicion(Tupla4f posicion){
    this->posicion = posicion;
}

void Luz::setID(GLenum id){
    this->id = id;
}

void Luz::setColorAmbiente(Tupla4f colorAmbiente){
    this->colorAmbiente = colorAmbiente;
}

void Luz::setColorDifuso(Tupla4f colorDifuso){
    this->colorDifuso = colorDifuso;
}

void Luz::setColorEspecular(Tupla4f colorEspecular){
    this->colorEspecular = colorEspecular;
}

Tupla4f Luz::getPosicion(){
    return this->posicion;
}