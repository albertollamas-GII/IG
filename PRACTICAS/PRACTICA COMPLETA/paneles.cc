#include "paneles.h"

Panel::Panel(Material mat){
    panelSolar = new Prisma(30,50,10);
    canal1 = new Prisma (15,5,5);
    canal2 = new Prisma (15,5,5);

    panelSolar->setMaterial(mat);
    canal1->setMaterial(mat); canal2->setMaterial(mat);
    alien = new Alien(mat);
}

void Panel::draw(modoDibujado modo, std::vector<bool> visu, bool tapas, bool balien, float pos_nave){
    glPushMatrix();
        // glScalef(2,2,2);
        //Panel Solar
        glPushMatrix();
            panelSolar->draw(modo,visu,true);
            if (balien){
                glPushMatrix();
                    glTranslatef(pos_nave,0,13);
                    glScalef(0.2,0.2,0.2);
                    glRotatef(90,1,0,0);
                    alien->draw(modo, visu, tapas);
                glPopMatrix();
            }
        glPopMatrix();

        //canal que conecta con otro panel/cuerpo (izquierda)
        glPushMatrix();
            glTranslatef(-20,23,0);
            canal1->draw(modo,visu,true);
        glPopMatrix();

        //canal que conecta con otro panel/cuerpo (derecha)
        glPushMatrix();
            glTranslatef(20,23,0);
            canal1->draw(modo,visu,true);
        glPopMatrix();
    glPopMatrix();
}

void Panel::aumentar_x_nave(float x){
    this->x_alien = x;
}
void Panel::reducir_x_nave(float x){
    this->x_alien = x;
} 