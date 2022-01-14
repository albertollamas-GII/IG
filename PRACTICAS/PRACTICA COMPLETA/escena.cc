

#include "aux.h" // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....
#include "objrevolucion.h"

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************
Escena::Escena()
{
   Front_plane = 50.0;
   Back_plane = 2000.0;
   Observer_distance = 4 * Front_plane;
   Observer_angle_x = 0.0;
   Observer_angle_y = 0.0;

   ejes.changeAxisSize(5000);

   // crear los objetos de la escena....
   // .......completar: ...
   // .....
   visu.resize(5);
   for (int i = 0; i < visu.size(); i++)
      visu[i] = false;
   visu[4] = true;

   luz_activada.resize(8);
   for (int i = 0; i < luz_activada.size(); i++)
      luz_activada[i] = false;
   luz_activada[0] = true;

   luz0 = new LuzPosicional(Tupla3f(0, 100, 250), GL_LIGHT0, Tupla4f(1, 1, 1, 1), Tupla4f(1, 1, 1, 0.5), Tupla4f(1, 1, 1, 1));
   luz1 = new LuzDireccional(Tupla2f(0, 0), GL_LIGHT1, Tupla4f(1, 1, 1, 1), Tupla4f(1, 1, 1, 1), Tupla4f(1, 1, 1, 1));
   luz2 = new LuzPosicional(Tupla3f(-100, 100, 0), GL_LIGHT2, Tupla4f(1, 1, 1, 1), Tupla4f(1, 1, 1, 0.5), Tupla4f(1, 1, 1, 1));

   cubo = new Cubo(20);
   tetraedro = new Tetraedro(20);
   lata = new ObjRevolucion("plys/lata-pcue.ply", 10, tapa_sup, tapa_inf, 'y');
   cono = new Cono(10, 10, 70, 30, tapa_sup, tapa_inf);
   cilindro = new Cilindro(100, 100, 70, 30, tapa_sup, tapa_inf);
   esfera = new Esfera(100, 100, 30, tapa_sup, tapa_inf);
   beethoven = new ObjPLY("plys/beethoven.ply");
   sol = new Esfera(100,100,10);


   Material comun(Tupla4f(0.07, 0.6, 0.07, 1), Tupla4f(0.6, 0.7, 0.6, 1), Tupla4f(0.02, 0.1, 0.02, 1), 1);
   Material grey(Tupla4f(0.01,0.01,0.01,0.2),Tupla4f(0.5,0.5,0.5,1),Tupla4f(0,0,0,1),1);
   Material white(Tupla4f(0.55, 0.55, 0.55, 1), Tupla4f(0, 0, 0, 0), Tupla4f(1, 1, 1, 1), 1);
   Material azul(Tupla4f(0.1, 0.2, 0.4, 1), Tupla4f(0.2, 0.3, 0.6, 1), Tupla4f(0.6, 0.2, 0.6, 1), 1);

   cubo->setMaterial(white);
   cubo->setTextura("text-madera.jpg");
   tetraedro->setMaterial(grey);
   lata->setMaterial(white);
   lata->setTextura("text-lata-1.jpg");
   lata->calcularCoordTexturas();

   cono->setMaterial(comun);
   cilindro->setMaterial(azul);
   esfera->setMaterial(white);
   esfera->setTextura("textura-Tierra.jpg");
   esfera->calcularCoordTexturas();
   beethoven->setMaterial(grey);
   sol->setMaterial(comun);
   
   satelite = new Satelite();
   angulo_giro = 0;

   Camara *camara1 = new Camara(Tupla3f(0,0,300), Tupla3f(0,0,0), Tupla3f(0,1,0), 0, 50, 50, Front_plane, Back_plane, 25, 25);
   Camara *camara2 = new Camara(Tupla3f(0,0,350), Tupla3f(0,0,0), Tupla3f(0,1,0), 1, 50, 50, Front_plane, Back_plane, 25, 25);
   Camara *camara3 = new Camara(Tupla3f(0,0,200), Tupla3f(0,0,0), Tupla3f(0,1,0), 0, 50, 50, Front_plane, Back_plane, 25, 25);

   camaraActiva = 0;

   camaras.push_back(*camara1);
   camaras.push_back(*camara2);
   camaras.push_back(*camara3);

   objetos.push_back((Malla3D*) satelite);
   objetos.push_back((Malla3D*) sol);
   objetos.push_back((Malla3D*) cubo);
   objetos.push_back((Malla3D*) tetraedro);
   objetos.push_back((Malla3D*) lata);
   objetos.push_back((Malla3D*) cono);
   objetos.push_back((Malla3D*) cilindro);
   objetos.push_back((Malla3D*) esfera);
   objetos.push_back((Malla3D*) beethoven);
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar(int UI_window_width, int UI_window_height)
{
   glClearColor(1.0, 1.0, 1.0, 1.0); // se indica cual sera el color para limpiar la ventana	(r,v,a,al)

   glEnable(GL_DEPTH_TEST); // se habilita el z-bufer

   Width = UI_window_width / 10;
   Height = UI_window_height / 10;

   for (int i = 0; i < camaras.size(); i++)
      camaras[i].setProporciones(-Width, Width, -Height, Height);

   change_projection(float(UI_window_width) / float(UI_window_height));
   glViewport(0, 0, UI_window_width, UI_window_height);
}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************
//colocar cada objeto en un sitio distinto
void Escena::dibujar()
{

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar la pantalla
   change_observer();

   glDisable(GL_LIGHTING);

   ejes.draw();

   if (visu[4])
   {
      glEnable(GL_LIGHTING);
   }
   else
   {
      glDisable(GL_LIGHTING);
   }

   glPushMatrix();
         glRotatef(angulo_giro,0,1,0);
         Tupla4f pos = luz0->getPosicion();
         glTranslatef(pos(0), pos(1), pos(2));
         if(luz_activada[0]){
            luz0->activar();
         } else{
            luz0->desactivar();
         }
   glPopMatrix();

   glPushMatrix();
      if (luz_activada[1])
         luz1->activar();
      else
         luz1->desactivar();
   glPopMatrix();

   glPushMatrix();
      if (luz_activada[2])
         luz2->activar();
      else
         luz2->desactivar();
   glPopMatrix();

   glPushMatrix();
      glRotatef(angulo_traslacion_satelite,0,1,0);
      glScalef(0.25,0.25,0.25);
      glTranslatef(0,100,400);
      satelite->draw(modo,visu,tapas);
   glPopMatrix();

   glPushMatrix();
      esfera->draw(modo,visu,tapas);
   glPopMatrix();
   
   int j = 1;

   // for (int i = 1; i < objetos.size(); i++){
   //    if ( i != 6){
   //       glPushMatrix();
   //          if (i % 2 == 0)
   //             glTranslatef(50,0,-j*30);
   //          else
   //             glTranslatef(-50,0,j*30);
   //          if (i == 3)
   //             glScalef(30,30,30);
   //          if (i == 7)
   //             glScalef(10,10,10);
   //          objetos[i]->draw(modo, visu, tapas);
   //       glPopMatrix();
   //    }
   //    j++;
   // }
   
   glPushMatrix();
      glTranslatef(0, 0, -100);
      cubo->draw(modo, visu, true);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(100, 0, 0);
      tetraedro->draw(modo, visu,true);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(-100, 0, 0);
      glScalef(30, 30, 30);
      lata->draw(modo, visu, tapas);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(-100, 0, -50);
      cilindro->draw(modo, visu, tapas);
   glPopMatrix();

}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada(unsigned char tecla, int x, int y)
{
   using namespace std;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir = false;
   switch (toupper(tecla))
   {
   case 'Q':
      if (modoMenu != NADA)
         modoMenu = NADA;
      else
      {
         salir = true;
      }
      break;
   case 'H':
         if (tapas)
         {
            cout << "\nQuitando Tapas" << endl;
            tapas = false;
         }
         else
         {
            cout << "\nPoniendo Tapas" << endl;
            tapas = true;
         }
      break;

   case 'V':
      // ENTRAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
      if (modoMenu == NADA)
      {
         cout << "Menu seleccion de modo de visualizacion" << endl;
         cout << "Activar/desactivar visualización en modo puntos: P" << endl;
         cout << "Activar/desactivar visualización en modo lineas: L" << endl;
         cout << "Activar/desactivar visualización en modo solido: S" << endl;
         cout << "Activar/desactivar visualización en modo ajedrez: A" << endl;
         cout << "Activar/desactivar visualización en modo iluminacion: I" << endl;

         modoMenu = SELVISUALIZACION;
      }
      else
      {
         cout << "Opcion no valida!\n";
      }

   case 'D':
      // ENTRAMOS EN MODO SELECCION DE DIBUJADO
      if (modoMenu == NADA)
      {
         cout << "Menu seleccion de modo de dibujado" << endl;
         cout << "1: Activar dibujado con glDrawElements" << endl;
         cout << "2: Activar dibujado con Vertex Buffer Objects" << endl;
         modoMenu = SELDIBUJADO;
      }
      else
      {
         cout << "Opcion no valida!\n";
      }
      break;

   //MODO SELECCION OBJETO

   //MODO SELECCION MODO DE VISUALIZACION
   case 'P':
      if (modoMenu == SELVISUALIZACION)
      {
         if (visu[0])
         {
            visu[0] = false;
         }
         else
         {
            cout << "Modo Puntos elegido\n";
            visu[4] = false;
            visu[0] = true;
         }
      } else if (modoMenu == SELILUMINACION){
         if (animacionLuzPuntual){
            animacionLuzPuntual = false;
            cout << "Desactivada animacion automatica de la Luz puntual.\n";
         }else{
            animacionLuzPuntual = true;
            cout << "Activada animacion automatica de la Luz puntual.\n";         
         }
      }
      else
         cout << "Opcion no valida!\n";
      break;

   case 'L':
      if (modoMenu == SELVISUALIZACION)
      {
         if (visu[1])
            visu[1] = false;
         else
         {
            cout << "Modo Lineas elegido\n";
            visu[4] = false;
            visu[1] = true;
         }
      }
      else
         cout << "Opcion no valida!\n";
      break;

   case 'S':
      if (modoMenu == SELVISUALIZACION)
      {
         if (visu[2])
            visu[2] = false;
         else
         {
            cout << "Modo Solido elegido\n";
            visu[4] = false;
            visu[2] = true;
         }
      }
      else
         cout << "Opcion no valida!\n";

      break;

   case 'A':
      if (modoMenu == SELVISUALIZACION)
      {
         if (visu[3])
            visu[3] = false;
         else
         {
            cout << "Modo Ajedrez elegido\n";
            visu[4] = false;
            visu[3] = true;
         }
      }
      else if (modoMenu == SELILUMINACION)
      {
         if (luz_activada[1])
         {
            angulo = 'a';
            cout << "Ángulo alfa elegido.\n";
         }
      } 
      else
         cout << "Opcion no valida!\n";
      
      if (animacion){
         cout << "Desactivando animacion automatica.\n";
         animacion = false;
         animacionLuzPuntual = false;
      } else{
         cout << "Activando animacion automatica.\n";
         animacion = true;
         animacionLuzPuntual = true;
      }
      break;
   case 'I':
      if (modoMenu == SELVISUALIZACION)
      {
         if (!visu[4])
         {
            cout << "Modo Iluminacion elegido\n";
            cout << "Usa las teclas 0 a 7 para activar las diferentes luces de la escena.\n";
            cout << "Las teclas 0 y 1 son para la luz posicional y direccional respectivamente.\n";
            cout << "A: activar modo variación ángulo alfa.\n";
            cout << "B: activar modo variacion ángulo beta.\n";
            cout << "Usa > y < para incrementar y decrementar respectivamente el ángulo elegido anteriormente.\n";
            cout << "Usa P para animar automaticamente la luz puntual.\n";
            visu[4] = true;
            for (int i = 0; i < 4; i++)
               visu[i] = false;

            modoMenu = SELILUMINACION;
         } 
      }
      else
         cout << "Opcion no valida!\n";
      break;
      //MODO SELECCION DE DIBUJADO
   case '0':
      if (modoMenu == MANIPULACION)
         grado_de_libertad = '0';
      else if (modoMenu == SELILUMINACION)
      {
         if (!luz_activada[0] && luz0 != nullptr)
         {
            cout << "Luz Posicional activada\n";
            luz_activada[0] = true;
         }
         else
         {
            luz_activada[0] = false;
            cout << "Luz Posicional desactivada.\n";
         }
      } else if (modoMenu == CAMARA){
         camaraActiva = 0;
         change_projection(1.0);
         cout << "Se ha activado la cámara 0.\n";
      } else {
         cout << "Opción no valida.\n";
      }
      break;

   case '1':
      if (modoMenu == MANIPULACION)
         grado_de_libertad = '1';
      else if (modoMenu == SELDIBUJADO)
      {
         cout << "Modo Inmediato elegido\n";
         modo = INMEDIATO;
      }
      else if (modoMenu == SELILUMINACION)
      {
         if (!luz_activada[1] && luz1 != nullptr)
         {
            cout << "Luz Direccional activada\n";
            luz_activada[1] = true;
         }
         else
         {
            luz_activada[1] = false;
            cout << "Luz Direccional desactivada.\n";
         }
      } else if (modoMenu == CAMARA){
         camaraActiva = 1;
         change_projection(1.0);
         cout << "Se ha activado la cámara 1.\n";
      }
      else
         cout << "Opcion no valida!\n";
      break;

   case '2':
      if (modoMenu == MANIPULACION)
         grado_de_libertad = '2';
      else if (modoMenu == SELDIBUJADO)
      {
         cout << "Modo Diferido elegido\n";
         modo = DIFERIDO;
      }
      else if (modoMenu == SELILUMINACION)
      {
         if (!luz_activada[2] && luz2 != nullptr)
         {
            cout << "Luz 2 activada\n";
            luz_activada[2] = true;
         }
         else
         {
            luz_activada[2] = false;
            cout << "Luz 2 desactivada.\n";
         }
      }else if (modoMenu == CAMARA){
         camaraActiva = 2;
         change_projection(1.0);
         cout << "Se ha activado la cámara 2.\n";
      }
      else
         cout << "Opcion no valida!\n";
      break;

   //MODO SELECCION DE ILUMINACION
   case '3':
      if (modoMenu == MANIPULACION)
         grado_de_libertad = '3';
      else if (modoMenu == SELILUMINACION)
      {
         if (!luz_activada[3] && luz3 != nullptr)
         {
            cout << "Luz 3 activada\n";
            luz_activada[3] = true;
         }
         else
         {
            luz_activada[3] = false;
            cout << "Luz 3 desactivada.\n";
         }
      }
      else
         cout << "Opcion no valida!\n";
      break;
   case '4':
      if (modoMenu == MANIPULACION)
         grado_de_libertad = '4';
      else if (modoMenu == SELILUMINACION)
      {
         if (!luz_activada[4] && luz4 != nullptr)
         {
            cout << "Luz 4 activada\n";
            luz_activada[4] = true;
         }
         else
         {
            luz_activada[4] = false;
            cout << "Luz 4 desactivada.\n";
         }
      }
      else
         cout << "Opcion no valida!\n";
      break;
   case '5':
      if (modoMenu == SELILUMINACION)
      {
         if (!luz_activada[5] && luz5 != nullptr)
         {
            cout << "Luz 5 activada\n";
            luz_activada[5] = true;
         }
         else
         {
            luz_activada[5] = false;
            cout << "Luz 5 desactivada.\n";
         }
      }
      else
         cout << "Opcion no valida!\n";
      break;
   case '6':
      if (modoMenu == SELILUMINACION)
      {
         if (!luz_activada[6] && luz6 != nullptr)
         {
            cout << "Luz 6 activada\n";
            luz_activada[6] = true;
         }
         else
         {
            luz_activada[6] = false;
            cout << "Luz 6 desactivada.\n";
         }
      }
      else
         cout << "Opcion no valida!\n";
      break;
   case '7':
      if (modoMenu == SELILUMINACION)
      {
         if (!luz_activada[7] && luz7 != nullptr)
         {
            cout << "Luz 7 activada\n";
            luz_activada[7] = true;
         }
         else
         {
            luz_activada[7] = false;
            cout << "Luz 7 desactivada.\n";
         }
      }
      else
         cout << "Opcion no valida!\n";
      break;
   case 'B':
      if (modoMenu == SELILUMINACION)
      {
         if (luz_activada[1])
         {
            angulo = 'b';
            cout << "Ángulo beta elegido.\n";
         }
      }
      else
      {
         cout << "Opción no valida.\n";
      }
      break;
   case '<':
      if (modoMenu == SELILUMINACION)
      {
         if (angulo == 'a')
         {
            luz1->variarAnguloAlpha(-10);
            cout << "Variado ángulo alfa.\n";
         }

         else if (angulo == 'b')
         {
            luz1->variarAnguloBeta(-10);
            cout << "Variado ángulo beta.\n";
         }

         else
            cout << "No has elegido un ángulo para variar" << endl;
      }
      break;
   case '>':
      if (modoMenu == SELILUMINACION)
      {
         if (angulo == 'a')
         {
            luz1->variarAnguloAlpha(10);
            cout << "Variado ángulo alfa.\n";
         }

         else if (angulo == 'b')
         {
            luz1->variarAnguloBeta(10);
            cout << "Variado ángulo beta.\n";
         }

         else
            cout << "No has elegido un ángulo para variar" << endl;
      }
      break;

      //MODO MANIPULACION
      case 'M':
         if (modoMenu == NADA){
            modoMenu = MANIPULACION;
            animacion = false;
            satelite->setManual(true);
            cout << "Menu selección grado de libertad a modificar\n";
            cout << "Tecla 0: giro alpha de la antena\n";
            cout << "Tecla 1: giro beta de la antena\n";
            cout << "Tecla 2: Translacion de la nave alienigena sobre el panel\n";
            cout << "Tecla 3: Rotacion Satelite sobre eje X\n";
            cout << "Tecla 4: Rotacion Satélite sobre eje Y (decidir si captura datos de tierra o sol)\n";

         } else{
            cout << "Opcion no valida!\n";
         }
      break;

      case '+':
         if (modoMenu == MANIPULACION){
            switch(grado_de_libertad){
               case '0':
                  satelite->aumentar_alpha();
               break;

               case '1':
                  satelite->aumentar_beta();
               break;

               case '2':
                  satelite->aumentar_x_nave();
               break;
               case '3':
                  satelite->girar();
               break;
               case '4':
                  satelite->aumentar_traslacion();
               break;
               default:
               break;
            }
         }
      break;

      case '-':
         if (modoMenu == MANIPULACION){
            switch(grado_de_libertad){
               case '0':
                  satelite->reducir_alpha();
               break;

               case '1':
                  satelite->reducir_beta();
               break;

               case '2':
                  satelite->reducir_x_nave();
               break;
               case '3':
                  satelite->reducir_giro();
               break;

               case '4':
                  satelite->reducir_traslacion();
                  break;
               default:
               break;
            }
         }
      break;

      //MODO SELECCION CAMARAS
      case 'C':
         if (modoMenu == NADA){
            modoMenu = CAMARA;
            cout << "Menu selección de cámaras:\n";
            cout << "Tecla 0: Cámara perspectiva\n";
            cout << "Tecla 1: Cámara ortogonal\n";
            cout << "Tecla 2: Cámara perspectiva\n";
         } else {
            cout << "Opcion no válida.\n";
         }
      break;

      case 'U':
         if (traslacionSatelite)
            traslacionSatelite = false;
         else
            traslacionSatelite = true;
         break;
      
   }
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial(int Tecla1, int x, int y)
{
   switch (Tecla1)
   {
   case GLUT_KEY_LEFT:
      camaras[camaraActiva].rotarYExaminar(-2.5*M_PI / 180.0);
      break;
   case GLUT_KEY_RIGHT:
      camaras[camaraActiva].rotarYExaminar(2.5*M_PI / 180.0);
      break;
   case GLUT_KEY_UP:
      camaras[camaraActiva].rotarXExaminar(2.5*M_PI / 180.0);
      break;
   case GLUT_KEY_DOWN:
      camaras[camaraActiva].rotarXExaminar(-2.5*M_PI / 180.0);
      break;
   case GLUT_KEY_F1: //He cambiado las teclas porque no las tengo en mi teclado
      camaras[camaraActiva].zoom(1.2);
      break;
   case GLUT_KEY_F2: // He cambiado las teclas porque no las tengo en mi teclado
      camaras[camaraActiva].zoom(0.75);
      break;
   }
   change_projection(1.0);

   //std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection(const float ratio_xy)
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   // const float wx = float(Height) * ratio_xy;
   // glFrustum(-wx, wx, -Height, Height, Front_plane, Back_plane);
   camaras[camaraActiva].setProyeccion();
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar(int newWidth, int newHeight)
{
   Width = newWidth / 10;
   Height = newHeight / 10;
   //change_projection(float(newHeight) / float(newWidth));
   glViewport(0, 0, newWidth, newHeight);

   for (int i = 0; i < camaras.size(); i++)
      camaras[i].setProporciones(-Width, Width, -Height, Height);
   
   change_projection(Width/Height);

}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   // glTranslatef(0.0, 0.0, -Observer_distance);
   // glRotatef(Observer_angle_y, 0.0, 1.0, 0.0);
   // glRotatef(Observer_angle_x, 1.0, 0.0, 0.0);

   camaras[camaraActiva].setObserver();
}

void Escena::animarModeloJerarquico(){
   if(animacion)
      satelite->animacion();
   if (animacionLuzPuntual)
      angulo_giro+=1;
   if (traslacionSatelite)
      angulo_traslacion_satelite += 0.05;
}

void Escena::clickRaton(int boton, int estado, int x, int y){
   ratonPulsado = (boton == GLUT_LEFT_BUTTON) && (estado == GLUT_DOWN);
   if (ratonPulsado){
      dibujaSeleccion();
      processPick(x, y);
      x_ant = x;
      y_ant = y;
      change_observer();
      change_projection(1.0);
   }
   if (boton == 3)
   {
      camaras[camaraActiva].zoom(1.2);
      change_projection(1.0);
   }

   if (boton == 4)
   {
      camaras[camaraActiva].zoom(0.75);
      change_projection(1.0);
   }
}

void Escena::ratonMovido(int x, int y){
   if(ratonPulsado){
      camaras[camaraActiva].girar1aPersona(x-x_ant,y-y_ant) ;
      x_ant=x ; y_ant=y ;
   }
}

void Escena::dibujaSeleccion(){
   glDrawBuffer(GL_BACK) ;
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
   glDisable (GL_DITHER) ;
   glDisable(GL_LIGHTING) ;
   glDisable (GL_TEXTURE_2D) ;


   glPushMatrix();
      esfera->setColorSeleccion(Tupla3f(0,0,1));
      esfera->drawSeleccion();
   glPopMatrix();

   glEnable(GL_DITHER);
}

void Escena::processPick(int x, int y){
      GLint viewport[4];
      GLubyte pixel[3];
      glGetIntegerv(GL_VIEWPORT,viewport);
      glReadBuffer(GL_BACK);
      glReadPixels(x,viewport[3]-y,1,1, GL_RGB,GL_FLOAT,(void *)pixel);
      printf("%d %d %d\n",pixel[0],pixel[1],pixel[2]);

      if (pixel[0] == 1.0 || pixel[1] == 1.0 || pixel[2] == 1.0)
         std::cout << "Planeta Tierra\n";
}