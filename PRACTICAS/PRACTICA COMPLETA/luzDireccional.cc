#include "luzDireccional.h"
#include "aux.h"


LuzDireccional::LuzDireccional(const Tupla2f &direccion, GLenum idLuzOpenGL, Tupla4f colorDifuso, Tupla4f colorEspecular, Tupla4f colorAmbiente){
    this->alpha = direccion[0];
    this->beta = direccion[1];
    this->setID(idLuzOpenGL);
    this->setColorAmbiente(colorAmbiente);
    this->setColorDifuso(colorDifuso);
    this->setColorEspecular(colorEspecular);
}

void LuzDireccional::variarAnguloAlpha(float incremento){
    alpha += incremento;
    if (alpha == 360 || alpha == -360)
        alpha = 0;
    this->calcularPosicion();
}

void LuzDireccional::variarAnguloBeta(float incremento){
    beta += incremento;
    if (beta == 360 || beta == -360)
        beta = 0;
    this->calcularPosicion();
}

void LuzDireccional::calcularPosicion(){
    Tupla4f pos;
    pos = getPosicion();
    
    float alpharot, betarot;

    alpharot = alpha * (M_PI*2)/360;
    betarot = beta * (M_PI*2)/360;
    pos[0] = sin(alpharot)*cos(betarot);
    pos[1] = sin(betarot)*sin(alpharot);
    pos[2] = cos(alpharot);
    pos[3] = 0;
    this->setPosicion(pos);
}
