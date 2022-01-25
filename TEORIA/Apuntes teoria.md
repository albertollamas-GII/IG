# Informática Gráfica

Javier Melero

Importancia del grupo de Telegram.

Evaluación
10% trabajo teórico que se suma a la asignatura si está aprobada la asignatura.
30% exámen teórico
70% prácticas
- 20% de prácticas
- 80% de prácticas

Si se entrega dentro del plazo y funciona hasta un 20% de la práctica, el 80% de la práctica el examen de cada práctica.
Las prácticas empiezan la semana que viene

Bibliografía mirarla, parece importante.
SIGGRAPH desde la red de la universidad.
Atalaya3D

Al principio de cada clase hay un Kahoot sobre lo que se va a ver en la clase (LEER ANTES DE CLASE LA GUÍA)
Importancia de la teoría para las prácticas.

Prácticas en C++ y linux :)

## Tema 1

Dos definiciones de informática gráfica
T1P4.
Son dos definiciones complementarias.

Síntesis de imágenes != análisis de imágenes.
La parte de análisis de imágenes es de visión por computador, en IG se hace síntesis de imágenes (generarlas) T1P3
Videos de youtube 
1963 https://www.youtube.com/watch?v=hB3jQKGrJo0 Primer ejemplo de interacción gráfica con un ordenador.
1968 https://www.youtube.com/watch?v=yJDv-zdhzMY Primera demo del ratón.

Historia una poquita.
El mundo de los gráficos se ha desarrollado muy rápidamente porque hay una industria (automovilística) que pide estos avances. A partir de los 80 la industria de videojuego. En esta época es la industria del cine. Los militares siempre han estado de fondo. Hay un sector que falta por desarrollar (la medicina) pero no hay tanta inversión como en las otras industrias.

Muchas áreas de la Informática gráfica.
- Modelado
- Rendering (síntesis de imágenes) (ARNOL?)
- Animación
- Realidad Virtual
- Interacción
- Visualización
- Digitalización 3D

Al finalizar la asignatura tenemo la base y el nivel de los años 80. Los gráficos se juntan con muchas otras disciplinas.
GRAFEX empresa granadina de visualización de datos.

Corto (dice que cuando terminemos seríamos capaces de hacer esto)  https://www.youtube.com/watch?v=9qha0kEeVl0
Este otro todo está generado por ordenador https://www.youtube.com/watch?v=G1D5hbxa8CM

Proceso de generación de imágenes. Igual que para tomar una fotografía. A lo largo de los temas se irán viendo los distintos pasos necesarios.
Primero necesitaremos las coordenadas 3d del objeto. Una vez tenemos la definición del modelo montamos una escena y le aplicamos transformaciones. Tenemos también que colocar la cámara (posición y orientación). Se aplica una transformación de perspectiva para obtener una imagen 2D del mundo 3D con el que estábamos trabajando.

Formas de pasar del 3D al 2D
Rasterización y raytracing.

## Tema 2: Modelado de objetos
Hay dos tipos de modelos, los basados en enumeración espacial y los basados en fronteras.
Los primeros vienen de datos médicos o atmosféricos. Si dividimos el cuerpo en dados pequeños y cada dado tiene un valor de una propiedad (color, densidad, temperatura). Esto es un modelo volumétrico.
Los modelos basados en fronteras. Si represento un huevo me quedo solo con la cáscara. Estos ocupan mucho menos. Además como la mayoría de las aplicaciones no entran al interior de los objetos pa que guardar el interior. Hay que distinguir entre geometría y topología.
Los modelos podría usar solo la geometría, pero por si sola no dice nada, hace falta la topología. Geometría: localización de los puntos. Topología: Conexión entre los puntos
- Geometría: Lo único que es cierto del modelo.
- Topología: 
Está poniendo el ejemplo de que un escaneo 3D te puede dar los puntos con unas coordenadas XYZ perfectas, pero el algoritmo de recostrucción no sea capaz de generar la topología correcta (de unir los puntos para generar el modelo de forma precisa y correcta).

- Vértice: punto de una superficie
- Arista: conexión entre dos vértices
- Cara: secuencia de arista. Normalmente las caras son triangulares, ya que garantiza que las caras sean planas.

Al final todos los modelos se guardan de la misma forma en memoria, sean de la complejidad que sean. Una forma de representar los modelos es guardando la posición de cada vértice de cada cara triangular. Es ineficiente y rendundante ya que un cambio en un punto tiene que reflejarse en el resto caras con ese punto en común. STL guarda los modelos así.
Otra forma de guardar los modelos es separar geometría de topología haciendo una tabla de puntos y una tabla de caras. Los archivos PLY usan esta forma de guardar.

Para la práctica 1 tendremos que rellenar la tabla de vértices y caras de distintas figuras geométricas. La tabla de vértices tienen x,y,z y la de caras v1,v2,v3. En OpenGL los vértices se dan en sentido antihorario sin importar (al parecer) por donde empiezas, pero siempre en sentido antihorario.


### 24-09-2018

## Continuación Tema 1 (T1P15)

Antes solo se procesaban gráficos en la CPU. Ahora mismo OpenGL se ejecuta sobre las GPU. Tenemos openGL y sus versiones (OpenGL ES, WebGL, OpenCL...). OpenGL es un estándar, no una librería. Por eso es multiplatafomra, porque hay muchas implementaciones de dicho estándar. OpenGL no gestiona eventos ni ventanas. Simplemente se encarga de pintar. Además tiene una arquitectura cliente/servidor. Además funciona como una máquina de estados.

Cauce gráfico. Vamos a usar en prácticas uno cauce obsoleto, el cauce fijo.
Además, como el estándar estaba pensado para C hay una convecnión de nombres de las funciones.
Poner nuestro nombre en el título de las prácticas.

Glut funcioa mediante una cola de eventos. Hay un evneto idle que glut manda si no hay ningún evento que gestionar.

Los elementos de OpenGL están formados por primitivas, que suelen ser triángulos.
Modo inmediato y modo por vertex arrays y vertex buffers.

glDrawElements. transparencia perdida. Es el que se va a usar en la función de dibujado. Tiene un último parámetro que es el puntero a los índices. Hace que no se repiten vértices y permite reutilizar la información.

No es lo mismo pintar puntos que pintar triángulos en modo puntos. Se definen mediante glPolygonMode.


## Volvemos al tema 2.

Da igual lo que tengamos que lo único que le tenemos que programar es el constructor: como se produce el vector de caras y como el de vértices. Conceptualmente son todos objetos 3D. La práctica 1 queda en eso. El modo ajedrez cambiar otro parámetro de la máquina de estados según sean caras pares y caras impares.

Para prevenir los problemas con la sopa de triángulos se crearon la estructuras de aristas aladas y su evolución, las semiaristas aladas.

Ahora tenemos la tabla de vértices (x,y,z y una semiarista) la tabla de caras, que guarda una única semiarista y una tabla de semiaristas, que guarda el índice del vértice, el índice de una cara, la semiarista anterior y siguiente y la semiarista opuesta.
Esto simplifica las operaciones de análisis. Por ejemplo como saber que en una malla hay un agujero. Con una lista de caras y vértices para hacer eso hay que marcarse una matriz bidimiensional donde se comprueben que todas las parejas de vértices adyacentes se han hecho en lo dos sentidos (lo correspondiente a las dos semiaristas). Cuando se usa una estructura de semiaristas simplemente se buscan semiraristas que no tengan opuesto.

Ver cuantas caras comparten un mismo vértice también se simplifica mucho. Llegadno a hacerse en tiempo constante.

Video del día: https://www.youtube.com/watch?v=D4NPQ8mfKU0 Corto de las lámparitas de pixar.

##01-10-18 Seminario de geometría

Está contando por qué hacen falta las mates para la IG. Contando que se usan BSDF y SS-BSDT (Subsurface) junto con la ecuación del render.

Circunferencia goniométrica

Importancia del producto escalar
Si quiero solo siluetas me invento una normal de una arista y si esa normal es perpendicular al vector de cámara sería una arista de la silueta. Posible ejercicio de examen. ¿Si tengo un vector director de vista como pintarías solo las siluetas? Pues así. La "normal" de la arista es la suma de las normales de las caras de la arista.

Para calcular las normales de los vértices hay una cosa parecida. Una cosa es la definición formal. Si se pasa a código sale en O(n^2). Eso es caca. Hay que darle una vuelta de tuerca (hacer un vector de normales de vértices e ir sumando para cada cara O(n) su normal, al final normalizados y chimpum).

## Fin del seminario de geometría
## Vamos a por el tema 2.
 Vídeo de hoy: Il sogno di red pixar 1987

 ## Día 08-10-18

 Cuidado con los escalados negativos. Invierte los triángulos y las normales. Intentar no hacerlo. Habría que invertir el orden de caras.

 Rotaciones: Siempre se hacen con respecto al eje de origen. En el espacio 2D se rota con respecto al eje de coordenadas. En el mundo 3D hay que tener en cuenta el eje respecto al cual se rota. Las rotaciones son siempre en el sentido antihorario.

 OpenGL hace las transformaciones al revés de como están escritas en el código.

 ## 15-10-18 Modelos jerárquicos

 Un objeto jerarquico son objetos que dependen unos de otros. El movimiento de una cosa me afecta a otra. Podemos crear una escena a trozos sin crear dependencia entre objetos. Esto a la larga da dolores de cabeza. Hay que hacer un análisis descendente de la construcción del modelo (ver las partes) y luego hacer un proceso ascendente de construcción a raiz de las primitivas.

 Si vamos a hacer una hormigonera: si lo hacemos no jerárquico ponemos cada cosa en su sitio. A la hora de jerarquizarlo empezamos dividiendo. Primero tenemos una cuba con el brazo y por otro lado el camión con las ruedas. La cuba es por un lado la cuba y por otro el brazo. En la parte del camión tenemos el chásis y luego las ruedas (que a su vez son dos ejes de dos ruedas. Sale un diagrama como el del tema.

 El truco de donde cortar es donde haya una translación o una rotación.
 La esencia es que si aplicamos una transformación
 Cuando dividimos nos tenemos que asegurar que cada parte esté en el origen y que esté bien enganchado con todo lo que dependa de él.
 Los modelos jerarquicos se construyen creando un grafo de escena. Nodos azules S(primitivas, objetos simples). Verdes T(transformaciones) morados C(clarificar, grupos).

 Ahora está explicando el ejemplo de la casa que aparece en T2P25. Dice que el escalado que aparece como E[-1,1] sería mejor rotarlo (por eso de que un escalado negativo te invierte las normales).

 Corto del día: https://www.youtube.com/watch?v=ffIZSAZRzDA



## Tema 3: Visualización

### 29-10-18

En las siguientes semanas no puede venir Melero. 

Empezamos con la visualización. Vamos a cambiar el orden del tema. Primero veremos iluminación, luego texturas y por último la cámara.

El tema lo representa la ilustración 78. Dice que en dos semanas se acaba lo gordo de la asignatura. 

Reexplicando el pipeline fijo. Vamos a ver como funcionan las geometrías texturizadas. Va a intentar que en la semana del 16 hagamos ejercicios de texturas, que parecen ser los que mas se traban



Empezamos con la parte de iluminación. (T3P12)

Radiancia en un punto es una función que determina el color y el brillo con el que se ve un punto desde otro. Esto se debe a la simulación de los fotones que se realiza junto con las interacciones entre estos y las texturas de los materiales.

Explica el espacio aditivo de color RGB. Propiedades de los materiales. Si tengo una pizarra verde pura y la ilumino con una luz roja pura la pizarra se ve negra, porque no se mandan fotones que reboten, solo se absorben.

Como OpenGl no hace raytracing utiliza un modelo simplificado de iluminación. Hace una serie de suposiciones:

- Las fuentes de luz son puntuales o unidireccionales
- Solo pueden haber 8 luces activas al mismo tiempo
- No considero los rebotes de luz. OpenGL usa una mínima luz ambiente para iluminar las zonas en las que no incide ninguna luz. La radiancia ambiente constante.

> El negro puro no existe (clases de pintura)

- Los objetos son opacos
- No se consideran sombras alojadas
- Da iugal lo lejos que esté un objeto que la luz siempre llega a tope
- En vez de usar el espectro completo usamos los colores RGB.

Reflexión especular: si un rayo viene contra una superficie con un ángulo a sale reflejado con un ángulo a. Como un espejo

Reflexión difusa: Los fotones se reparten uniformemente en todas las direcciones al rebotar.

Las dos fuentes de luz de OpenGL:

- Fuentes posicionales o puntuales: Una bombilla. Tengo un punto de luz que emite en todas las direcciones.
- Fuentes direccionales. Emiten a lo largo de una trayectoria dada. Esto hace que todos los objetos sean iluminados desde el mismo punto en el infinito.

Valor de la normal. 

La normal es el vector perpendicular a una superficie. Es el que utiliza OpenGL para calcular la orientación de un polígono y ver como iluminarlos. De ahí la importancia de calcular bien las normales de los objetos.

Como funciona la iluminación en OpenGL.

Por defecto las luces están desactivadas. El color de los objetos por defecto se basa en los colores RGB de los vértices. Para habilitarla hay que activarla con `glEnable(GL_LIGHTING)`. Si se activa ahora mismo sin poner luces, ni definir normales, ni definir materiales se verá todo negro. Con las luces activadas `glColor` no sirve para nada.

Cuando tenemos luces hacen falta materiales. El material es una evolución del color que surgió para representar un poco más realista los materiales. Los materiales tienen propiedades que definen como se comportan con los distintos componentes de la luz. 

- El color difuso indica que longitudes de onda refleja de forma difusa (color base).
- El color especular define que componentes de la luz se reflejan como brillos
- El color ambiente es el color del material cuando no hay ninguna luz incidiendo sobre él. Suele ser el color difuso un poco más oscuro.
- El color de emisión es como las estrellas fluorescentes de las habitaciones de chico.
- El brillo: cuanto de brillante es mi material. En un metal el brillo sería alto y en el yeso sería nulo.

El color final de un pixel depende de las propiedades del material y de las propiedades de la esfera.

Las luces en OpenGL se activan con constantes. La luz 0 tiene valores por defecto. 

La luz ambiente global se puede modificar glLightModel (T3P18)

La cuarta componente de la luz se usa para mantener las cuaternas. Es un factor de multiplicación de las componentes de color. Se suele poner 1.0

Las luces también tienen componentes ambientales, difusa y especular.

Para definir la posición y el tipo (puntual o direccional) de una luz. Con la misma función `glLightfv` se pasa un vector con la posición de una luz. Si la cuarta componente es 0.0 la luz es direccional (posición/0=$\infty$) Con vector dirección.

Ahora los objetos tienen un materil. Hay que definir las 4 componentes del material y aplicarselas al objeto.

Sistema de coordenadas de las luces. Las luces pueden moverse según los objetos, la cámara o con el mundo. ¿Cómo se posicionan las luces? Depende de donde se llame al parámetro GL_POSITION. Recomienda que nos creemos una clase Luz con una función draw con la linea de setear la posición (equivalente a dibujar la luz).

Podemos tener luces y materiales, pero si no tenemos normales no nos sirven para nada.

Cálculo de la normal en un vertice. Suma normalizada de las normales de los triángulos que comparter ese vértice. Nos va a exigir que el calculo de las normales sea O(n).

La práctica 4 consitirá en montar una escena con nuestros objetos u otros en los que haya una o varias luces, uno o varios materiales y alguna textura.

### 09-11-18 Texturas

Las texturas son un paso más en la consecución del realismo en la generación de imágenes. Con las texturas ya seríamos capaces casi de hacer el primer curso. Una textura es "pegatina" que se le pega a un polígono. Nos permiten convertir una esfera de 40 poligonos en un globo terráqueo.

Distintas aproximaciones. Crear pequeñas piezas geométricas y repetirlas.

Otra es hacer bump maping. En esta asignatura no podemos usar esta técnica ya que requiere programar los shaders. En la silueta es donde se nota que se está usando bump maping, ya que la geometría es muy simple. Enseña mapas de normales de una pared de ladrillo.

La textura es una imagen que representa las modificaciones de los parametros del color de una superficie. Al igual que en una imagen hablamos de pixel, en las texturas hablamos de texels.

Asignación de coordenadas de texturas a un objeto:

- Tengo mi imagen de un tamaño dado. Tengo un triángulo donde cada vértice tiene coordenadas de textura normalizadas (de 0 a 1 para ser independientes del tamaño de la imagen). 
- Cuando renderizo la parte de la imagen de textura que corresponde a la superficie entre las coordenadas de textura se "pega" a la geometría.

Para las coordenadas de textura el origen están donde nos esperamos. Pero cuando se cargan imágenes el (0,0) es el de arriba izquierda (primera fila de píxeles).

El uso de texturas no excluye el uso de luces. Si combino un material base con una textura, la textura se ve modificada por las propiedades del material. 

Las coordenadas de textura son (s, t) en OpenGL. Formas de asignar coordenadas de texturas:

- Asignación explícita a todos los vértices. Tenemos total libertad a la hora de asignar las texturas (puedes poner cosas al revés, que ya OpenGL se encarga)

> Ejercicio 62:

>- Dada la geometría de la imagen (que está en 4:3).  Para asignar las coordenadas de texturas empiezo a asignar a vértices las coordenadas s y t: (0,1/3); (0.25,1/3)
>   El problema viene cuando un vértice tiene que tomar más de una coordenada de textura. En ese caso se hacen dos vértices. No se crean caras nuevas. Las caras que antes compartían vértices ahora ya no los comparten

- Otra forma es hacer una asignación procedural paramétrica. Cojo el modelo y lo aplasto. Y esa imagen pues la pintas. El problema es que está distorsionada.

Omisión parcial. La textura solo va de 0 a 1 pero un objeto puede tener coodenadas de texturas que se pasen del 1 en cualquiera de los sentidos. OpenGL puede:

- Poner la imagen como una continuación (1,5 sería igual que 0.5)
- Mantenerse en el color del último pixel
- Volver para atrás como si fuese un espejo.

Asignaciones procedurales hay de 2 tipos: proyecciones cilíndricas o proyecciones esféricas.

En proyecciones cilíndricas todos los vértices que tengn la misma altura y el mismo ángulo de giro tendrán la misma coordenada de textura.

En coordenadas esféricas (de forma intuitiva) es como si englobáramos en lbjeto en color. La altura (s) se calcula igual que en las coordenadas cilíndricas. La t se calcula midiendo el ángulo de giro en altura (con respecto al eje XZ)

Para utilizar texturas en OpenGL hay que habilitarlas (igual que las luces). Si nuestro objeto tiene texturas y no tenemos luces prima la textura ante el color. Si la iluminación está activada

Ahora hay que generar una textura. Una vez que tenemos una textura generada y bindeada glTexImage2D genera una textura a partir de una matriz de téxeles (píxeles cargados de una imagen o matriz generada proceduralmente) y una serie de parámetros.

MipMap generación de glut automática de los niveles de detalle.

Opciones de las texturas

Generación automática procedural de las coordenadas de texturas de un objeto.

Las texturas se usan de forma muy similar a los otros arrays. Se parecen a un VBO en el sentido de que hay que generarlas y si no están generadas hay que cargarlas en memoria. OpenGL usará la última textura que se haya activado.