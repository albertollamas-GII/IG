#include "alien.h"

Alien::Alien(Material material){
    cristal = new SemiEsfera(100,100,10);
    cristal->setMaterial(material); // poner material blanco

    baseNave = new Cilindro(100,100,10,15);
    baseNave->setMaterial(material);

    pata1 = new pataNaveAlien(material);
    pata2 = new pataNaveAlien(material);
    pata3 = new pataNaveAlien(material);

}

void Alien::draw(modoDibujado modo, std::vector<bool> visu, bool tapas){
    glPushMatrix();
        glScalef(2,2,2);
        baseNave->draw(modo, visu, tapas);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,-15,15);
        glRotatef(-10,1,0,0);
        pata1->draw(modo,visu,tapas);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(18,-15,-13);
        glRotatef(10,0,0,1);
        pata2->draw(modo,visu,tapas);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-18,-15,-13);
        glRotatef(-10,0,0,1);
        pata3->draw(modo,visu,tapas);
    glPopMatrix();

    glPushMatrix();
        glScalef(2,2,2);
        glTranslatef(0,5,0);
        cristal->draw(modo,visu,tapas);
    glPopMatrix();
}