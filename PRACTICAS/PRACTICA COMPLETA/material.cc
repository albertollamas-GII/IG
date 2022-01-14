#include "material.h"

Material::Material(Tupla4f mdifuso, Tupla4f mespecular, Tupla4f mambiente, float brillo){
    this->difuso = mdifuso;
    this->especular = mespecular;
    this->ambiente = mambiente;
    this->brillo = brillo;
}

void Material::aplicar(){
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, difuso);
    glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
    glMaterialf(GL_FRONT, GL_SHININESS, brillo);

    glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glColorMaterial(GL_FRONT, GL_SPECULAR);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

Tupla4f Material::getAmbiente(){ return this->ambiente;}
Tupla4f Material::getDifuso() {return this->difuso;}
Tupla4f Material::getEspecular() {return this->especular;}
float Material::getBrillo() {return this->brillo;}
