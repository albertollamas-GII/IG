#include "prisma.h"

Prisma::Prisma(float altura, float anchura, float profundidad){
    // inicializar la tabla de vértices

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   v.resize(8);
   v[0] = Tupla3f(-anchura/2,altura/2,-profundidad/2);
   v[1] = Tupla3f(anchura/2,altura/2,-profundidad/2);
   v[2] = Tupla3f(anchura/2,altura/2,profundidad/2);
   v[3] = Tupla3f(-anchura/2,altura/2,profundidad/2);
   v[4] = Tupla3f(-anchura/2,-altura/2,-profundidad/2);
   v[5] = Tupla3f(anchura/2,-altura/2,-profundidad/2);
   v[6] = Tupla3f(anchura/2,-altura/2,profundidad/2);
   v[7] = Tupla3f(-anchura/2,-altura/2,profundidad/2);

   v.push_back(Tupla3f(-anchura/2,altura/2,-profundidad/2));
   v.push_back(Tupla3f(-anchura/2,altura/2,-profundidad/2));

   v.push_back(Tupla3f(anchura/2,altura/2,-profundidad/2));
   v.push_back(Tupla3f(anchura/2,altura/2,-profundidad/2));

   v.push_back(Tupla3f(-anchura/2,-altura/2,-profundidad/2));
   v.push_back(Tupla3f(anchura/2,-altura/2,-profundidad/2));   
   
   f.resize(12); 
   
   f[0] = Tupla3i(0,3,1);//cara1
   f[1] = Tupla3i(2,1,3);
   f[2] = Tupla3i(3,7,2);//cara2
   f[3] = Tupla3i(2,7,6);
   f[4] = Tupla3i(13,6,7);//f[4] = Tupla3i(5,6,7);//cara3
   f[5] = Tupla3i(13,7,12);//f[5] = Tupla3i(5,7,4);
   f[6] = Tupla3i(11,13,9);//f[6] = Tupla3i(1,5,0);//cara4
   f[7] = Tupla3i(13,12,9);//f[7] = Tupla3i(5,4,0);
   f[8] = Tupla3i(8,4,3);//f[8] = Tupla3i(0,4,3);//cara5
   f[9] = Tupla3i(3,4,7);
   f[10] = Tupla3i(10,2,6);//f[10] = Tupla3i(1,2,6);//cara6
   f[11] = Tupla3i(6,5,10); //f[11] = Tupla3i(6,5,1); 
   
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