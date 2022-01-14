#include "antena.h"

Antena::Antena(Material material){
    antena = new ObjPLY("plys/Satellite.ply") ;
    tubo1 = new Cilindro(100,100,10,5);
    antena->setMaterial(material);
    tubo1->setMaterial(material);

}

void Antena::draw(modoDibujado modo, std::vector<bool> visu, bool tapas){
    glPushMatrix();
        //parabola
        glPushMatrix();
            glScalef(20,20,20);
            antena->draw(modo,visu,true);
        glPopMatrix();
        
        //base que conecta con cuerpo del satélite
        glPushMatrix();
            glScalef(2,2,2);
            glTranslatef(-10,0,1);
            glRotatef(90,0,0,1);
            tubo1->draw(modo,visu,tapas);
        glPopMatrix();

    glPopMatrix();

}