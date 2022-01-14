#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

#include <cmath>

Tetraedro::Tetraedro(float l)
{

   // inicializar la tabla de vértices
   float mediana = sqrt(pow(l,2) - pow(l/2,2));
   float altura = sqrt(pow(mediana,2) - pow(mediana/3,2));
   
   v.push_back(Tupla3f(-l/2,-altura/2,-(mediana)/3)); //2
   v.push_back(Tupla3f(0,-altura/2,(2*mediana)/3)); //1
   v.push_back(Tupla3f(l/2,-altura/2,-(mediana)/3)); //3
   v.push_back(Tupla3f(0,altura/2,0)); //0

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   f.push_back(Tupla3i(0,1,3));
   f.push_back(Tupla3i(1,2,3));
   f.push_back(Tupla3i(2,0,3));
   f.push_back(Tupla3i(0,2,1));

   dividirTriangulosAjedrez();

   for (int i = 0; i < v.size(); i++){
      c_solido.push_back(Tupla3f(1,0,0));
      c_lineas.push_back(Tupla3f(0,0,1));
      c_puntos.push_back(Tupla3f(0,1,0));
      c_ajedrez_impar.push_back(Tupla3f(1,0,0));
      c_ajedrez_par.push_back(Tupla3f(0,0,0));
   }
 
   calcular_normales();

}

