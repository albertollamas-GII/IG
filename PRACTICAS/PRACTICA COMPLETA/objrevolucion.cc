#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"

// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil_original (en un PLY)
//deteccion de tapas tiene que coger tambien 0.000001
//Cambiar lo de las tapas

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string &archivo, int num_instancias, bool tapa_sup, bool tapa_inf, char eje)
{
   // completar ......(práctica 2)
   std::vector<Tupla3f> perfil_original;
   ply::read_vertices(archivo, perfil_original);

   crearMalla(perfil_original, num_instancias, tapa_sup, tapa_inf);

   dividirTriangulosAjedrez();

   for (int i = 0; i < v.size(); i++)
   {
      c_solido.push_back(Tupla3f(1, 0, 0));
      c_lineas.push_back(Tupla3f(0, 0, 1));
      c_puntos.push_back(Tupla3f(0, 1, 0));
      c_ajedrez_impar.push_back(Tupla3f(1, 0, 0));
      c_ajedrez_par.push_back(Tupla3f(0, 0, 0));
   }

   calcular_normales();
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil_original (en un vector de puntos)

ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf, char eje)
{
   crearMalla(archivo, num_instancias, tapa_sup, tapa_inf, eje);

   dividirTriangulosAjedrez();

   for (int i = 0; i < v.size(); i++)
   {
      c_solido.push_back(Tupla3f(1, 0, 0));
      c_lineas.push_back(Tupla3f(0, 0, 1));
      c_puntos.push_back(Tupla3f(0, 1, 0));
      c_ajedrez_impar.push_back(Tupla3f(1, 0, 0));
      c_ajedrez_par.push_back(Tupla3f(0, 0, 0));
   }

   calcular_normales();
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool tapa_sup, bool tapa_inf, char eje)
{
   v.clear();
   f.clear();
   tapa_superior = tapa_inferior = Tupla3f(0, 0, 0);
   Tupla3f aux;

   perfil.clear();
   instancias = num_instancias;
   perfil = perfil_original;

   //completamos la tabla de vertices
   if (eje == 'y')
   {
      if (perfil_original[0][0] <= 0.00001 && perfil_original[0][0] >= 0)
      {
         tapa_inferior = perfil_original[0];
         perfil_original.erase(perfil_original.begin());
      }
      if (perfil_original[perfil_original.size() - 1][0] <= 0.00001 && perfil_original[perfil_original.size() - 1][0] >= 0)
      {
         tapa_superior = perfil_original[perfil_original.size() - 1];
         perfil_original.erase(perfil_original.end() - 1);
      }

      if (perfil_original[0][1] > perfil_original[perfil_original.size() - 1][1])
      {

         aux = tapa_superior;
         tapa_superior = tapa_inferior;
         tapa_inferior = aux;
         abajoarriba = false;
      }
      for (int i = 0; i < num_instancias; i++)
      {
         float angulo = (2 * i * M_PI) / num_instancias;
         for (int j = 0; j < perfil_original.size(); j++)
         {
            Tupla3f vertice;
            vertice[0] = cos(angulo) * perfil_original[j][0] + sin(angulo) * perfil_original[j][2];
            vertice[1] = perfil_original[j][1];
            vertice[2] = -sin(angulo) * perfil_original[j][0] + cos(angulo) * perfil_original[j][2];
            v.push_back(vertice);
         }
      }
   }
   //instancia extra
   for (int i = 0; i < perfil_original.size(); i++)
      v.push_back(v[i]);
   num_instancias++;
   instancias++;
   tam_perfil = perfil_original.size();

   int a, b;

   //tabla de triangulos
   if (abajoarriba)
   {
      for (int i = 0; i < num_instancias; i++)
      {
         for (int j = 0; j < perfil_original.size() - 1; j++)
         {
            a = perfil_original.size() * i + j;
            b = perfil_original.size() * ((i + 1) % num_instancias) + j;
            f.push_back(Tupla3i(a, b, b + 1));
            f.push_back(Tupla3i(a, b + 1, a + 1));
         }
      }
   }
   else
   {
      for (int i = 0; i < num_instancias; i++)
      {
         for (int j = 0; j < perfil_original.size() - 1; j++)
         {
            a = perfil_original.size() * i + j;
            b = perfil_original.size() * ((i + 1) % num_instancias) + j;
            f.push_back(Tupla3i(b + 1, b, a));
            f.push_back(Tupla3i(a + 1, b + 1, a));
         }
      }
   }

   if (tapa_inf)
   {
      inf_creada = true;
      if (eje == 'y')
      {
         if (tapa_inferior[0] == 0 && tapa_inferior[1] == 0 && tapa_inferior[2] == 0)
         {
            if (abajoarriba)
            {
               tapa_inferior = Tupla3f(0, perfil_original[0][1], 0);
            }
            else
            {
               tapa_inferior = Tupla3f(0, perfil_original[perfil_original.size() - 1][1], 0);
            }
         }
      }

      v.push_back(tapa_inferior);

      if (abajoarriba)
      {
         for (int i = 0; i < num_instancias; i++)
         {
            a = perfil_original.size() * i;
            b = perfil_original.size() * ((i + 1) % num_instancias);
            f.push_back(Tupla3i(b, a, v.size() - 1));
         }
      }
      else
      {
         for (int i = 0; i < num_instancias; i++)
         {
            a = (perfil_original.size() * (i + 1)) - 1;
            b = (perfil_original.size() * (i + 2) - 1) % (num_instancias * perfil_original.size());
            f.push_back(Tupla3i(b, a, v.size() - 1));
         }
      }
      num_cara_tapas +=  num_instancias;
   }

   if (tapa_sup)
   {
      sup_creada = true;
      if (eje == 'y')
      {
         if (tapa_superior[0] == 0 && tapa_superior[1] == 0 && tapa_superior[2] == 0)
         {
            if (abajoarriba)
            {
               tapa_superior = Tupla3f(0, perfil_original[perfil_original.size() - 1][1], 0);
            }
            else
            {
               tapa_superior = Tupla3f(0, perfil_original[0][1], 0);
            }
         }
      }
      v.push_back(tapa_superior);

      if (abajoarriba)
      {
         for (int i = 0; i < num_instancias; i++)
         {
            a = (perfil_original.size() * (i + 1)) - 1;
            b = (perfil_original.size() * (i + 2) - 1) % (num_instancias * perfil_original.size());
            f.push_back(Tupla3i(v.size() - 1, a, b));
         }
      }
      else
      {
         for (int i = 0; i < num_instancias; i++)
         {
            a = perfil_original.size() * i;
            b = perfil_original.size() * ((i + 1) % num_instancias);
            f.push_back(Tupla3i(v.size() - 1, a, b));
         }
      }
      num_cara_tapas +=  num_instancias;
   }
   instancias = num_instancias;
}

void ObjRevolucion::calcularCoordTexturas(){
   std::vector<float> perfil_distancias;
   std::vector<Tupla2f> aux;
   float s,t;
   perfil_distancias.resize(tam_perfil);
   perfil_distancias[0] = 0;

   for(int i = 1; i < tam_perfil; i++)
      perfil_distancias[i] = perfil_distancias[i-1] + distanciaPuntos(perfil[i-1], perfil[i]);

   for(int i = 0; i < instancias; i++){
      for(int j = 0; j < tam_perfil; j++){
         s = 1-(float)i/(instancias-1);
         t = (float)perfil_distancias[j]/perfil_distancias[tam_perfil-1];

         aux.push_back(Tupla2f(s,t));
     }
   }

   for(int i = aux.size()-1; i >= 2; i--)
      ct.push_back(aux[i]);

   ct.push_back(Tupla2f(0,1));
   ct.push_back(Tupla2f(0,0));

}

double ObjRevolucion::distanciaPuntos(Tupla3f v1, Tupla3f v2){
   return sqrt(pow(v1[0]-v2[0],2)+pow(v1[1]-v2[1],2)+pow(v1[2]-v2[2],2));
}




