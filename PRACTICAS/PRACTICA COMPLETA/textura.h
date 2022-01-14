#ifndef _TEXTURA_H
#define _TEXTURA_H
#include "aux.h"

class Textura{
    
    private: 
        GLuint textura_id = 0;
        int width, height;
        std::vector<unsigned char> data;
        unsigned char *texels;

    public:
        Textura(std::string archivo);
        void activar();
        void desactivar();
        int getWidth();
        int getHeight();
        GLuint getIdentificador();
};
#endif