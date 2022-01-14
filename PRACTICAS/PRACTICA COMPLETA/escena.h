#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objrevolucion.h"
#include "objply.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "luz.h"
#include "luzPosicional.h"
#include "luzDireccional.h"
#include "material.h"
#include "prisma.h"
#include "semiesfera.h"
#include "antena.h"
#include "satelite.h"
#include "paneles.h"
#include "alien.h"
#include "pataNaveAlien.h"
#include "camara.h"

typedef enum
{
    NADA,
    SELOBJETO,
    SELVISUALIZACION,
    SELDIBUJADO,
    SELILUMINACION,
    MANIPULACION,
    CAMARA
} menu;

typedef enum
{
    TETRAEDRO,
    CUBO,
    NINGUNO
} objetoActivo;


class Escena
{

private:
    // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)

    // variables que definen la posicion de la camara en coordenadas polares
    GLfloat Observer_distance;
    GLfloat Observer_angle_x;
    GLfloat Observer_angle_y;

    // variables que controlan la ventana y la transformacion de perspectiva
    GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
    void change_projection(const float ratio_xy);
    void change_observer();

    void clear_window();

    menu modoMenu = NADA;
    objetoActivo objeto = NINGUNO;
    modoDibujado modo = INMEDIATO;
    std::vector<bool> visu; 
    
    bool modo_solido = false;
    bool modo_puntos = false;
    bool modo_lineas = false;
    bool modo_ajedrez = false;

    bool animacion = true;
    float angulo_giro = 0;
    float angulo_traslacion_satelite = 0;
    bool traslacionSatelite = true;

    bool tapa_sup = true, tapa_inf = true, tapas = true;
    // Objetos de la escena
    Ejes ejes;
    
    LuzPosicional * luz0 = nullptr;
    LuzDireccional * luz1 = nullptr;
    LuzPosicional * luz2 = nullptr;
    Luz * luz3 = nullptr;
    Luz * luz4 = nullptr;
    Luz * luz5 = nullptr;
    Luz * luz6 = nullptr;
    Luz * luz7 = nullptr;
    Esfera *sol = nullptr;
    Cubo *espacio = nullptr;
    
    //Objetos hasta p3
    Cubo *cubo = nullptr;           // es importante inicializarlo a 'nullptr'
    Tetraedro *tetraedro = nullptr; // es importante inicializarlo a 'nullptr'
    ObjRevolucion *lata = nullptr;
    Cilindro *cilindro = nullptr;
    Cono *cono = nullptr;
    Esfera *esfera = nullptr;
    ObjPLY *beethoven= nullptr;    
    
    //modelo jerarquico
    Satelite *satelite = nullptr;

    Panel *panel = nullptr;
    std::vector<bool> luz_activada;
    char angulo;
    char grado_de_libertad;

    bool animacionLuzPuntual = false;

    //vector de camaras
    std::vector<Camara> camaras; // minimo 3, perspectiva y ortogonal 1 de cada.
    int camaraActiva; //nnumero entero para indicar qué camara esta activa.

    int x_ant, y_ant;
    bool ratonPulsado;
    std::vector<Malla3D*> objetos;
public:
    Escena();
    void inicializar(int UI_window_width, int UI_window_height);
    void redimensionar(int newWidth, int newHeight);

    // Dibujar
    void dibujar();
    void dibujaSeleccion();
    void fondo();

    // Interacción con la escena
    bool teclaPulsada(unsigned char Tecla1, int x, int y);
    void teclaEspecial(int Tecla1, int x, int y);

    //funcion de animacion
    void animarModeloJerarquico();

    //raton
    void clickRaton(int boton, int estado, int x, int y);
    void ratonMovido(int x, int y);
    void processPick(int x, int y);

};
#endif
