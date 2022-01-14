#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED
#include "aux.h"

class Camara{
    private:
        Tupla3f eye;
        Tupla3f at;
        Tupla3f up;

        int tipo; // 0 perspectiva 1 ortogonal
        float left, right, near, far, top, bottom;

        modoRaton estadoRaton;

    public:
        Camara(Tupla3f eye, Tupla3f at, Tupla3f up, int tipo, float left, float right, float near, float far, float top, float bottom);
        void rotarXExaminar(float angle);
        void rotarYExaminar(float angle);
        void rotarZExaminar(float angle);
        void rotarXFirstPerson(float angle);
        void rotarYFirstPerson(float angle);
        void rotarZFirstPerson(float angle);
        void mover(float x, float y, float z);
        void zoom(float factor);

        void setObserver();
        void setProyeccion(); // 0 perspectiva 1 ortogonal

        void setProporciones(float left, float right, float bottom, float top);

        void girar1aPersona(float x, float y);
        modoRaton getEstadoRaton();
        void setEstadoRaton(modoRaton modo);
        void girarExaminar(float x, float y);

};


#endif