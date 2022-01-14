#include "camara.h"

Camara::Camara(Tupla3f eye, Tupla3f at, Tupla3f up, int tipo, float left, float right, float near, float far, float top, float bottom){
    this->eye = eye;
    this->at = at;
    this->up = up;
    this->tipo = tipo;
    this->left = left;
    this->right = right;
    this->near = near;
    this->far = far;
    this->top = top;
    this->bottom = bottom;
}

void Camara::rotarXExaminar(float angle){
    Tupla3f vd = eye - at; //eye centro
    float modulo = sqrt(vd(0) * vd(0) + vd(1) * vd(1) + vd(2) * vd(2));

    vd(1) = cos(angle) * vd(1) - sin(angle) * vd(2);
    vd(2) = sin(angle) * vd(1) + cos(angle) *vd(2);

    eye = vd.normalized() * modulo + at;
}

void Camara::rotarYExaminar(float angle){
    Tupla3f vd = eye - at; //eye centro
    float modulo = sqrt(vd(0) * vd(0) + vd(1) * vd(1) + vd(2) * vd(2));

    vd(0) = cos(angle) * vd(0) + sin(angle) * vd(2);
    vd(2) = -sin(angle) * vd(0) + cos(angle) *vd(2);

    eye = vd.normalized() * modulo + at;
}

void Camara::rotarZExaminar(float angle){
    Tupla3f vd = eye - at; //eye centro
    float modulo = sqrt(vd(0) * vd(0) + vd(1) * vd(1) + vd(2) * vd(2));

    vd(0) = cos(angle) * vd(0) - sin(angle) * vd(1);
    vd(1) = sin(angle) * vd(0) + cos(angle) *vd(1);

    eye = vd.normalized() * modulo + at;
}

void Camara::rotarXFirstPerson(float angle){
    Tupla3f vd = at-eye; //at centro
    float modulo = sqrt(vd(0) * vd(0) + vd(1) * vd(1) + vd(2) * vd(2));

    vd(1) = cos(angle) * vd(1) - sin(angle) * vd(2);
    vd(2) = sin(angle) * vd(1) + cos(angle) *vd(2);

    eye = vd.normalized() * modulo + eye;
}

void Camara::rotarYFirstPerson(float angle){
    Tupla3f vd = at-eye; //at centro
    float modulo = sqrt(vd(0) * vd(0) + vd(1) * vd(1) + vd(2) * vd(2));

    vd(0) = cos(angle) * vd(0) + sin(angle) * vd(2);
    vd(2) = -sin(angle) * vd(0) + cos(angle) *vd(2);

    eye = vd.normalized() * modulo + eye;
}

void Camara::rotarZFirstPerson(float angle){
    Tupla3f vd = at-eye; //at centro
    float modulo = sqrt(vd(0) * vd(0) + vd(1) * vd(1) + vd(2) * vd(2));

    vd(0) = cos(angle) * vd(0) - sin(angle) * vd(1);
    vd(1) = sin(angle) * vd(0) + cos(angle) *vd(1);

    eye = vd.normalized() * modulo + eye;
}

void Camara::setObserver(){
    gluLookAt(eye(0),eye(1),eye(2),at(0),at(1),at(2),up(0),up(1),up(2));
}

void Camara::setProyeccion(){
    if(tipo == 0) //Perspectiva
        glFrustum(left, right, bottom, top, near, far);
    if(tipo == 1) //Ortogonal
        glOrtho(left, right, bottom, top, near, far);
}

void Camara::mover(float x, float y, float z){
        this->at(0) += x;
        this->eye(0) += x;

        this->at(1) += y;
        this->eye(1) += y;

        this->at(2) += z;
        this->eye(2) += z;
}

void Camara::zoom(float factor){
    top *= factor;
    bottom *= factor;
    left *= factor;
    right *= factor;
}

void Camara::setProporciones(float left, float right, float bottom, float top){
    this->left = left;
    this->right = right;
    this->bottom = bottom;
    this->top = top;
}

void Camara::girar1aPersona(float x, float y){
   rotarXFirstPerson(-y*M_PI/180.0);
   rotarYFirstPerson(-x*M_PI/180.0);
}

modoRaton Camara::getEstadoRaton(){
    return estadoRaton;
}

void Camara::setEstadoRaton(modoRaton modo){
    this->estadoRaton = modo;
}

void Camara::girarExaminar (float x, float y)
{
	rotarXExaminar(abs(y)*M_PI/180.0);
	rotarYExaminar(x*M_PI/180.0);
}


