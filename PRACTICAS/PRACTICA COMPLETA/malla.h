// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "material.h"
#include "textura.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************
typedef enum{INMEDIATO, DIFERIDO} modoDibujado;
typedef enum{PUNTOS,LINEAS,SOLIDO,AJEDREZ,ILUMINACION} visualizacion;

class Malla3D
{
   public:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato(std::vector<bool> visu);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido(std::vector<bool> visu);

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(modoDibujado modo, std::vector<bool> visu, bool tapas) ;
   
   GLuint CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid *puntero_ram);

   void drawAjedrez(modoDibujado modo);
   void setMaterial(Material mat);
   void setTextura(std::string archivo);
   void setColorSeleccion(Tupla3f color);
   void drawSeleccion();
   protected:
   bool tapas = true;
   bool ajedrez = false;
   int num_cara_tapas = 0;
   
   void dividirTriangulosAjedrez();
   void cargarColorDiferido(GLuint &id_vbo_col, std::vector<Tupla3f> c);
   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)
   
   std::vector<bool> visu;
   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3f> c_solido ; //terna para colores
   std::vector<Tupla3f> c_lineas;  //terna para lineas
   std::vector<Tupla3f> c_puntos;  //terna para puntos
   std::vector<Tupla3f> c_sel; //terna para seleccion
   
   std::vector<Tupla3f> c_ajedrez_par;
   std::vector<Tupla3f> c_ajedrez_impar;
   
   std::vector<Tupla3i> f_ajedrez_par;
   std::vector<Tupla3i> f_ajedrez_impar;

   GLuint id_vbo_col_ajedrez_par = 0, id_vbo_col_ajedrez_impar = 0, id_vbo_ajedrez_par = 0, id_vbo_ajedrez_impar = 0;
   GLuint id_vbo_ver = 0, id_vbo_tri= 0, id_vbo_col_sol = 0, id_vbo_col_lin = 0, id_vbo_col_pun = 0;
   GLuint id_vbo_normales = 0, id_vbo_texturas = 0;
   // completar: tabla de colores, tabla de normales de vértices
   std::vector<Tupla3f> nv, nc; //normales de los vertices y normales de las caras
   
   //Texturas
   std::vector <Tupla2f> ct;

private:
   Material *m = nullptr;
   Textura *textura = nullptr;
   
} ;


#endif
