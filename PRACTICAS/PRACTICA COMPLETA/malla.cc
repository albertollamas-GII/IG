#include "aux.h"
#include "malla.h"

// Funciones de OpenGL solo en funciones draw NO en constructores
//  *****************************************************************************
//
//  Clase Malla3D
//
//  *****************************************************************************
/**
 *
 * */

// -----------------------------------------------------------------------------
GLuint Malla3D::CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid *puntero_ram)
{
   GLuint id_vbo;
   glGenBuffers(1, &id_vbo);
   glBindBuffer(tipo_vbo, id_vbo);
   glBufferData(tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW);
   glBindBuffer(tipo_vbo, 0);
   return id_vbo;
}
// -----------------------------------------------------------------------------
// Visualización en modo inmediato con 'glDrawElements'
void Malla3D::draw_ModoInmediato(std::vector<bool> visu)
{
   // visualizar la malla usando glDrawElements,
   // completar (práctica 1)

   // habilitar uso de un array de vértices
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);

   // indicar el formato y la dirección de memoria del array de vértices
   // (son tuplas de 3 valores float, sin espacio entre ellas)
   glVertexPointer(3, GL_FLOAT, 0, v.data());

   glEnable(GL_CULL_FACE);

   if (textura != nullptr && (visu[4] || visu[2]) && ct.size() > 0){
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glTexCoordPointer(2,GL_FLOAT,0,ct.data());
      textura->activar();
   }
   if (visu[0])
   {
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); //Usamos GL_POINT para pintar los puntos
      glPointSize(3);                             //Indicar tamaño de los puntos
      if (c_puntos.size() != 0)
         glColorPointer(3, GL_FLOAT, 0, c_puntos.data());
      else
         glDisableClientState(GL_COLOR_ARRAY);
      //visualizar, indicando: tipo de primitiva, número de indices
      //tipo de los indices, y direccion de la tabla de vertices.
      if (tapas)
         glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, f.data()); //para el modo sintapas restar la variable num_cara_tapas
      else
         glDrawElements(GL_TRIANGLES, f.size() * 3 - num_cara_tapas * 3, GL_UNSIGNED_INT, f.data());
   }

   if (visu[1])
   {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //usamos GL_LINE para pintar las lineas
      glLineWidth(1);                            //Indicar tamaño de linea
      if (c_lineas.size() != 0)
         glColorPointer(3, GL_FLOAT, 0, c_lineas.data());
      else
         glDisableClientState(GL_COLOR_ARRAY);
      if (tapas)
         glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, f.data()); //para el modo sintapas restar la variable num_cara_tapas
      else
         glDrawElements(GL_TRIANGLES, f.size() * 3 - num_cara_tapas * 3, GL_UNSIGNED_INT, f.data());
   }

   if (visu[2])
   {
      glPolygonMode(GL_FRONT, GL_FILL);
      //dependiendo del array de colores, habilitamos o deshabilitamos el array
      if (c_solido.size() != 0 && textura == nullptr)
         glColorPointer(3, GL_FLOAT, 0, c_solido.data());
      else
         glDisableClientState(GL_COLOR_ARRAY);
      if (tapas)
         glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, f.data()); //para el modo sintapas restar la variable num_cara_tapas
      else
         glDrawElements(GL_TRIANGLES, f.size() * 3 - num_cara_tapas * 3, GL_UNSIGNED_INT, f.data());
   }
   else if (visu[3])
   {
      drawAjedrez(INMEDIATO);
      ajedrez = true;
   }

   if (visu[4])
   {
      m->aplicar();
      glShadeModel(GL_SMOOTH);
      glEnable(GL_NORMALIZE);
      glEnableClientState(GL_NORMAL_ARRAY);

      glNormalPointer(GL_FLOAT, 0, nv.data());
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      if (tapas)
         glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, f.data()); //para el modo sintapas restar la variable num_cara_tapas
      else
         glDrawElements(GL_TRIANGLES, f.size() * 3 - num_cara_tapas * 3, GL_UNSIGNED_INT, f.data());
   }

   if (textura != nullptr && ct.size() > 0){
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);
      textura->desactivar();
   }
   //deshabilitar array de vertices
   glDisableClientState(GL_NORMAL_ARRAY);
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
}

// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)
void Malla3D::draw_ModoDiferido(std::vector<bool> visu)
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)

   // // Comprobamos si estan creados los VBO's
   if (id_vbo_ver == 0)
      id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, v.size() * 3 * sizeof(float), v.data());
   if (id_vbo_tri == 0)
      id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size() * 3 * sizeof(float), f.data());
   if (id_vbo_texturas == 0 && textura != nullptr && ct.size() > 0)
      id_vbo_texturas = CrearVBO(GL_ARRAY_BUFFER, 2*ct.size()*sizeof(float), ct.data());

   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver); // activar VBO de vértices
   glVertexPointer(3, GL_FLOAT, 0, 0);        // especifica formato y offset(=0)
   glBindBuffer(GL_ARRAY_BUFFER, 0);          // desactivar VBO de vértices
   glEnableClientState(GL_VERTEX_ARRAY);      // habilitar tabla de vertices
   
   // visualizar triángulos con glDrawElements (puntero a tabla == 0)

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri); // activar VBO de triángulos
   glEnable(GL_CULL_FACE);

   if (visu[1])
   {
      cargarColorDiferido(id_vbo_col_lin, c_lineas);
      glLineWidth(1);
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      if (tapas)
         glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, 0); //para el modo sintapas restar la variable num_cara_tapas
      else
         glDrawElements(GL_TRIANGLES, f.size() * 3 - num_cara_tapas * 3, GL_UNSIGNED_INT, 0);
   }

   if (visu[0])
   {
      cargarColorDiferido(id_vbo_col_pun, c_puntos);
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
      glPointSize(3);
      if (tapas)
         glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, 0); //para el modo sintapas restar la variable num_cara_tapas
      else
         glDrawElements(GL_TRIANGLES, f.size() * 3 - num_cara_tapas * 3, GL_UNSIGNED_INT, 0);
   }

   if (textura != nullptr){
      textura->activar();
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_texturas);
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glTexCoordPointer(2,GL_FLOAT, 0, 0);
   }
   
   if (visu[2])
   {
      if (textura == nullptr)
         cargarColorDiferido(id_vbo_col_sol, c_solido);
      
      glPolygonMode(GL_FRONT, GL_FILL);
      if (tapas)
         glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, 0); //para el modo sintapas restar la variable num_cara_tapas
      else
         glDrawElements(GL_TRIANGLES, f.size() * 3 - num_cara_tapas * 3, GL_UNSIGNED_INT, 0);
   }
   else if (visu[3])
   {
      if (id_vbo_ajedrez_par == 0)
         id_vbo_ajedrez_par = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f_ajedrez_par.size() * 3 * sizeof(float), f_ajedrez_par.data());
      if (id_vbo_ajedrez_impar == 0)
         id_vbo_ajedrez_impar = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f_ajedrez_impar.size() * 3 * sizeof(float), f_ajedrez_impar.data());
      drawAjedrez(DIFERIDO);
      ajedrez = true;
   }

   //Modo luces
   if (visu[4])
   {
      if (id_vbo_normales == 0)
         id_vbo_normales = CrearVBO(GL_ARRAY_BUFFER, 3 * nv.size() * sizeof(float), nv.data());

      m->aplicar();
      glShadeModel(GL_SMOOTH);

      glEnableClientState(GL_COLOR_ARRAY);
      glEnable(GL_NORMALIZE);
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_normales); //activar VBO de colores
      glNormalPointer(GL_FLOAT, 0, 0);                //activar formato y offset(=0)
      glBindBuffer(GL_ARRAY_BUFFER, 0);               //desactivar VBO de colores
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glEnableClientState(GL_NORMAL_ARRAY); //habilitar tabla de normales
      if (tapas)
         glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, 0); //para el modo sintapas restar la variable num_cara_tapas
      else
         glDrawElements(GL_TRIANGLES, f.size() * 3 - num_cara_tapas * 3, GL_UNSIGNED_INT, 0);
   }
   
   
   if (textura != nullptr){
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);
      textura->desactivar();
   }

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //desactivar VBO de triangulos
   glDisableClientState(GL_VERTEX_ARRAY);    // desactivar uso de array de vertices
   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_NORMAL_ARRAY);
}

// -----------------------------------------------------------------------------
//metodo que crea los colores para el modo diferido
void Malla3D::cargarColorDiferido(GLuint &id_vbo_col, std::vector<Tupla3f> c)
{
   if (c.size() != 0 || id_vbo_col == 0)
   {
      id_vbo_col = CrearVBO(GL_ARRAY_BUFFER, c.size() * 3 * sizeof(float), c.data());
   }
   // Cargamos los colores
   glEnableClientState(GL_COLOR_ARRAY);       // habilitar tabla de colores
   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_col); // activar VBO de colores
   glColorPointer(3, GL_FLOAT, 0, 0);         // formato y offset (=0)
   glBindBuffer(GL_ARRAY_BUFFER, 0);          // desactivar VBO de colores
}

// -----------------------------------------------------------------------------
//Metodo para dividir las caras del modo ajedrez
void Malla3D::dividirTriangulosAjedrez()
{
   for (int i = 0; i < f.size(); i += 2)
   {
      f_ajedrez_par.push_back(f[i]);
   }

   for (int i = 1; i < f.size(); i += 2)
   {
      f_ajedrez_impar.push_back(f[i]);
   }
}

// -----------------------------------------------------------------------------
//metodo para dibujar en modo ajedrez dependiendo del modo utilizado
void Malla3D::drawAjedrez(modoDibujado modo)
{

   if (modo == DIFERIDO)
   {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_ajedrez_par); // activar VBO de cada grupo de triangulos
      cargarColorDiferido(id_vbo_col_ajedrez_par, c_ajedrez_par);
      glPolygonMode(GL_FRONT, GL_FILL);
      if (tapas)
         glDrawElements(GL_TRIANGLES, f_ajedrez_par.size() * 3, GL_UNSIGNED_INT, 0); //para el modo sintapas restar la variable num_cara_tapas
      else
         glDrawElements(GL_TRIANGLES, f_ajedrez_par.size() * 3 - (num_cara_tapas * 3) / 2, GL_UNSIGNED_INT, 0);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_ajedrez_impar); // activar VBO de cada grupo de triangulos
      cargarColorDiferido(id_vbo_col_ajedrez_impar, c_ajedrez_impar);
      glPolygonMode(GL_FRONT, GL_FILL);
      if (tapas)
         glDrawElements(GL_TRIANGLES, f_ajedrez_impar.size() * 3, GL_UNSIGNED_INT, 0); //para el modo sintapas restar la variable num_cara_tapas
      else
         glDrawElements(GL_TRIANGLES, f_ajedrez_impar.size() * 3 - (num_cara_tapas * 3) / 2, GL_UNSIGNED_INT, 0);
   }
   else if (modo == INMEDIATO)
   {
      glPolygonMode(GL_FRONT, GL_FILL);
      // Pintamos triangulos pares
      if (c_ajedrez_par.size() != 0)
         glColorPointer(3, GL_FLOAT, 0, c_ajedrez_par.data());

      if (tapas)
         glDrawElements(GL_TRIANGLES, f_ajedrez_par.size() * 3, GL_UNSIGNED_INT, f_ajedrez_par.data()); //para el modo sintapas restar la variable num_cara_tapas
      else
         glDrawElements(GL_TRIANGLES, f_ajedrez_par.size() * 3 - (num_cara_tapas * 3) / 2, GL_UNSIGNED_INT, f_ajedrez_par.data());
      // Pintamos triangulos impares
      if (c_ajedrez_impar.size() != 0)
         glColorPointer(3, GL_FLOAT, 0, c_ajedrez_impar.data());

      if (tapas)
         glDrawElements(GL_TRIANGLES, f_ajedrez_impar.size() * 3, GL_UNSIGNED_INT, f_ajedrez_impar.data()); //para el modo sintapas restar la variable num_cara_tapas
      else
         glDrawElements(GL_TRIANGLES, f_ajedrez_impar.size() * 3 - (num_cara_tapas * 3) / 2, GL_UNSIGNED_INT, f_ajedrez_impar.data());
   }
}

// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido
void Malla3D::draw(modoDibujado modo, std::vector<bool> visu, bool tapas)
{
   this->tapas = tapas;
   if (modo == INMEDIATO)
      draw_ModoInmediato(visu);
   else if (modo == DIFERIDO)
      draw_ModoDiferido(visu);
   else if (visu[3])
      drawAjedrez(modo);
}
// -----------------------------------------------------------------------------
//Calcular Normales de las caras
void Malla3D::calcular_normales()
{

   nv.clear();
   nv.resize(v.size(), Tupla3f(0, 0, 0));
   nc.clear();

   for (int i = 0; i < f.size(); i++)
   {
      Tupla3f p, q, r, a, b;
      //normales de las caras
      p = v[f[i][0]];
      q = v[f[i][1]];
      r = v[f[i][2]];

      a = p - q;
      b = r - p;

      Tupla3f mc = a.cross(b);
      Tupla3f normal;
      
      if (mc.lengthSq() > 0)
         normal = mc.normalized();

      nc.push_back(normal);

      //normales de los vertices
      nv[f[i][0]] = nv[f[i][0]] + normal;
      nv[f[i][1]] = nv[f[i][1]] + normal;
      nv[f[i][2]] = nv[f[i][2]] + normal;
   }

   //normalizamos vectores de los vertices
   for (int i = 0; i < nv.size(); i++)
   {
      if (nv[i].lengthSq() > 0)
         nv[i] = nv[i].normalized();
   }
}

void Malla3D::setMaterial(Material mat)
{
   m = new Material(mat.getDifuso(), mat.getEspecular(), mat.getAmbiente(), mat.getBrillo());
}

void Malla3D::setTextura(std::string archivo){
   textura = new Textura(archivo);
}

void Malla3D::setColorSeleccion(Tupla3f color){
   c_sel.clear();
   for (int i = 0; i < v.size(); i++)
      c_sel.push_back(color);
}

void Malla3D::drawSeleccion(){
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0 , v.data());

   glEnableClientState(GL_COLOR_ARRAY);
   glColorPointer(3, GL_FLOAT, 0, c_sel.data());

   glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());

   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
}
