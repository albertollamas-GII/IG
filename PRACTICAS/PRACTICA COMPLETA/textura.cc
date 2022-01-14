#include "textura.h"
#include "jpg_imagen.hpp"
#include "jpg_jinclude.h"


Textura::Textura(std::string archivo){
    jpg::Imagen *pimg = nullptr;
    //cargar al imagen 
    pimg = new jpg::Imagen(archivo);
    
    //usar con:
    width = pimg->tamX();
    height = pimg->tamY();
    texels = pimg->leerPixels();

    for (int i = 0; i < 3*this->getWidth()*this->getHeight();i++)
        data.push_back(texels[i]);
}

void Textura::activar(){
    glEnable(GL_TEXTURE_2D);//activar texturas
    //habilitar identificador de textura
    if(textura_id == 0){
        glGenTextures(1,&textura_id);
        glBindTexture(GL_TEXTURE_2D, textura_id);
        std::cout << "codigo: " << textura_id << std::endl;
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, texels);
        
    }
    
    glBindTexture(GL_TEXTURE_2D, textura_id);
   
}

void Textura::desactivar(){
    glDisable(GL_TEXTURE_2D);//activar texturas
}


int Textura::getHeight(){
    return height;
}

int Textura::getWidth(){
    return width;
}

GLuint Textura::getIdentificador(){
    return textura_id;
}