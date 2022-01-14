#include "pataNaveAlien.h"

pataNaveAlien::pataNaveAlien(Material material){
        basePata = new Cilindro(100,100,10,5);
        basePata->setMaterial(material);
        
        pata = new Cilindro(100,100,10,3);
        pata->setMaterial(material);

        apoyo = new Esfera(100, 100, 3);
        apoyo->setMaterial(material);
}

void pataNaveAlien::draw(modoDibujado modo, std::vector<bool> visu, bool tapas){
    glPushMatrix();
        basePata->draw(modo,visu,tapas);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,-10,0);
        glScalef(1,2,1);
        pata->draw(modo,visu,tapas);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,-20,0);
        apoyo->draw(modo,visu,tapas);
    glPopMatrix();
}
