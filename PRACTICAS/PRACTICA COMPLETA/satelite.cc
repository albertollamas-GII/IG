#include "satelite.h"
#include "material.h"

Satelite::Satelite(){
        Material comun(Tupla4f(0.07, 0.6, 0.07, 1), Tupla4f(0.6, 0.7, 0.6, 1), Tupla4f(0.02, 0.1, 0.02, 1), 1);        
        antena = new Antena(comun);
        panelInferior1 = new Panel(comun);
        panelInferior2 = new Panel(comun);
        panelSuperior1 = new Panel(comun);
        panelSuperior2 = new Panel(comun);

        baseAntena = new Cubo(50);
        baseAntena->setMaterial(comun);

        baseCola = new Cubo(50);
        baseCola->setMaterial(comun);

        conector = new Cilindro(100,100,10,5);
        conector->setMaterial(comun);

        conectaCola = new Cilindro(100,100,10,5);
        conectaCola->setMaterial(comun);
        cola = new SemiEsfera(100,100,5);
        cola->setMaterial(comun);

        manual = 1;
        velocidad_alpha = velocidad_beta = velocidad_altura = velocidad_giro = velocidad_traslacion = 0.01;
        alpha = 0; beta = 0; tita = 0;
        x_nave = 0; giro = 0, traslacion = 0;

}
void Satelite::drawBaseCentral(modoDibujado modo, std::vector<bool> visu, bool tapas){        
        //baseAntena
        glPushMatrix();
            glTranslatef(-35,0,0);
            baseAntena->draw(modo,visu,tapas);
        glPopMatrix();

        //conector
        glPushMatrix();
            // glTranslatef(2,0,0);
            glRotatef(90,0,0,1);
            glScalef(2,2,2);
            conector->draw(modo,visu,tapas);
        glPopMatrix();

        //baseCola
        glPushMatrix();
            glTranslatef(35,0,0);
            baseCola->draw(modo,visu,tapas);
        glPopMatrix();
}
void Satelite::draw(modoDibujado modo, std::vector<bool> visu, bool tapas){
    glPushMatrix();  
        glRotatef(giro, 1,0,0);
        glRotatef(traslacion, 0, 1, 0);
        drawBaseCentral(modo,visu,tapas);
        glPushMatrix();
            glTranslatef(-47,0,0);
            glRotatef(alpha,0,0,1);//orientación en x
            glRotatef(beta, 0,1,0); //orientación en y
            antena->draw(modo,visu,tapas);
        glPopMatrix();

        //Paneles 
        glPushMatrix();
            glScalef(1.3,1,1); //Escalado a todos los paneles

            //Primer panel inferior (mas cercano a base)
            glPushMatrix();
                glTranslatef(0,-55,0);
                panelInferior1->draw(modo,visu,tapas, true, x_nave);
            glPopMatrix();
            //Segunndo Panel inferior (lejano base)
            glPushMatrix();
                glTranslatef(0,-100,0);
                panelInferior2->draw(modo,visu,tapas, false);
            glPopMatrix(); 
            //Panel Superior lejano a base
            glPushMatrix();
                glTranslatef(0,100,0);
                glRotatef(180,1,0,0);
                panelSuperior2->draw(modo,visu,tapas, false);
            glPopMatrix();
            //Panel Superior cercano a base
            glPushMatrix();
                glTranslatef(0,55,0);
                glRotatef(180,1,0,0);
                panelSuperior1->draw(modo,visu,tapas, false);
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(70,0,0);
            glScalef(2,2,2);
            glRotatef(90,0,0,1);
            conectaCola->draw(modo,visu,tapas);
        glPopMatrix();     
        glPushMatrix();
            glTranslatef(80,0,0);
            glScalef(2,2,2);
            glRotatef(-90,0,0,1);
            cola->draw(modo,visu,tapas);
        glPopMatrix();
    glPopMatrix();
}

void Satelite::animacion(){
    if (beta >= 0 && alpha <= 0){
        giroAntena = true;
    }

    if (giroAntena){
        aumentar_alpha();
        aumentar_beta();
    }

    aumentar_x_nave();
    
    if (x_nave == 20 || x_nave < 0)
        reducir_x_nave();
    
    girar();

}

void Satelite::setManual(bool manual){
    if (manual){
        this->manual = 100;
    } else{
        this->manual = 1;
    }
}

void Satelite::aumentar_alpha(){
    if(alpha < 45)
        alpha+=velocidad_alpha*manual;
    
}

void Satelite::aumentar_beta(){
    if(beta < 45)
        beta+=velocidad_beta*manual;
}

void Satelite::reducir_alpha(){
    if(alpha > -45)
        alpha-=velocidad_alpha*manual;
}

void Satelite::reducir_beta(){
    if(beta > -45)
        beta-=velocidad_beta*manual;
}

void Satelite::aumentar_x_nave(){
    if(x_nave < 20)
        x_nave += velocidad_altura*manual;
}
void Satelite::reducir_x_nave(){
    if(x_nave > -20){
        x_nave -= velocidad_altura*manual;
    }
} 

void Satelite::girar(){
    giro += velocidad_giro*manual;
    if((giro - 360)>= 0)
        giro = 0;
}

void Satelite::reducir_giro(){
    giro -= velocidad_giro*manual;
    if(giro < 0)
        giro = 360;
}

void Satelite::aumentar_traslacion(){
    traslacion += velocidad_traslacion*manual;
    if ((traslacion -360) >= 0)
        traslacion = 0;
}

void Satelite::reducir_traslacion(){
    traslacion -= velocidad_traslacion*manual;
    if ((traslacion < 0))
        traslacion = 360;
}