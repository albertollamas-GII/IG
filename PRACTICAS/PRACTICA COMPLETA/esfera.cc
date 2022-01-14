#include "aux.h"
#include "malla.h"
#include "esfera.h"

Esfera::Esfera(const int num_vert_perfil, const int num_instancias_perf, const float r, bool tapa_sup, bool tapa_inf){
    perfil.clear();
    instancias = num_instancias_perf;
    float alpha = M_PI/(num_vert_perfil-1);
   
    Tupla3f vertice(0,-r,0);
    
    for(int i = 0; i < (num_vert_perfil-1); i++){
      
        perfil.push_back(Tupla3f(cos(i*alpha)*vertice[0]-sin(i*alpha)*vertice[1],sin(i*alpha)*vertice[0]+cos(i*alpha)*vertice[1],0));
    }

    perfil.push_back(Tupla3f(0,r,0));

    crearMalla(perfil, num_instancias_perf, tapa_sup, tapa_inf, 'y');

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
