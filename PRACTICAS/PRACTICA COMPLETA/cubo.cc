#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float l)
{

   // inicializar la tabla de vértices
   v.push_back(Tupla3f(-0.5 * l, -0.5 * l, -0.5 * l)); // 0
   v.push_back(Tupla3f(-0.5 * l, -0.5 * l, +0.5 * l)); // 1
   v.push_back(Tupla3f(-0.5 * l, +0.5 * l, -0.5 * l)); // 2
   v.push_back(Tupla3f(-0.5 * l, +0.5 * l, +0.5 * l)); // 3
   v.push_back(Tupla3f(+0.5 * l, -0.5 * l, -0.5 * l)); // 4
   v.push_back(Tupla3f(+0.5 * l, -0.5 * l, +0.5 * l)); // 5
   v.push_back(Tupla3f(+0.5 * l, +0.5 * l, -0.5 * l)); // 6
   v.push_back(Tupla3f(+0.5 * l, +0.5 * l, +0.5 * l)); // 7

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   
   f.push_back(Tupla3i(0, 2, 4));
   f.push_back(Tupla3i(4, 2, 6));
   f.push_back(Tupla3i(1, 5, 3));
   f.push_back(Tupla3i(3, 5, 7));
   f.push_back(Tupla3i(1, 3, 0));
   f.push_back(Tupla3i(0, 3, 2));
   f.push_back(Tupla3i(5, 4, 7));
   f.push_back(Tupla3i(7, 4, 6));
   f.push_back(Tupla3i(1, 0, 5));
   f.push_back(Tupla3i(5, 0, 4));
   f.push_back(Tupla3i(3, 7, 2));
   f.push_back(Tupla3i(2, 7, 6));

   dividirTriangulosAjedrez();
   
   for (int i = 0; i < v.size(); i++){
      c_solido.push_back(Tupla3f(1,0,0));
      c_lineas.push_back(Tupla3f(0,0,1));
      c_puntos.push_back(Tupla3f(0,1,0));
      c_ajedrez_impar.push_back(Tupla3f(1,0,0));
      c_ajedrez_par.push_back(Tupla3f(0,0,0));
   }

   ct.push_back(Tupla2f(0.0,0.0));
   ct.push_back(Tupla2f(0.25,0.0));
   ct.push_back(Tupla2f(0.0,0.25));
   ct.push_back(Tupla2f(0.25,0.25));
   ct.push_back(Tupla2f(0.5, 0.5));
   ct.push_back(Tupla2f(0.75, 0.5));
   ct.push_back(Tupla2f(0.5, 0.75));
   ct.push_back(Tupla2f(0.75, 0.75));
   
   calcular_normales();
}
