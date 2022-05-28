## <div style="text-align:center"> Resolucion de problemas con logica difusa
###### <div style="text-align:center"> Martín Fuschetto, Gabriel Rotondo, Hernán Trinidad

En este trabajo se resuelve un problema de planificación de movimiento utilizando la técnica de control difuso para un móvil con tres sensores de distancia y libertad de movimiento. Tanto la simulación del problema como la resolución de la lógica difusa se encuentran implementados en matlab.

### Introduccion 

Los sistemas de control difuso se utilizan en una amplia variedad de aplicaciones, que van desde el control de electrodomésticos, por ejemplo los lavarropas, hasta aplicaciones críticas como es el control de trenes y subterráneos. A diferencia de los sistemas de control clásico, en los sistemas de control difuso el comportamiento se basa en reglas definidas en lenguaje natural. Además permite agregar múltiples variables de entrada y salida sin complejizar demasiado su resolución. Otra ventaja del control difuso es la suavidad de las variaciones en las salidas frente a cambios bruscos en las entradas. El problema resuelto mediante esta técnica es la planificación de movimiento de un móvil que tiene como entradas las distancias medidas por tres sensores y el sistema debe resolver los movimientos a realizar para llegar a su destino evadiendo los obstáculos. El control difuso nos permite trabajar de manera sencilla con la combinación de las entradas para definir las decisiones del móvil.

### Antecedentes

Tradicionalmente la robótica estuvo centrada en sectores industriales manufactureros orientados a la producción masiva. A mediados de la década del 60 se introducen robots manipuladores en la industria debido a las posibilidades que estos ofrecían [1]. 
Normalmente los robots desarrollaban tareas repetitivas. Estas tareas exigían tomar algunas piezas y reubicarlas en otra área a la cual el robot manipulador sea capaz de llegar con la máxima extensión de su articulación, es decir su área de acción estaba limitado al largo de su articulación.
Una mejora frente a esta limitación se dió al desarrollar un vehículo móvil sobre rieles para que el robot tenga mayor alcance. Así es como a mediados de la década del 80 aparecieron los primeros vehículos guiados automáticamente (AGV's) en la industria.
Fuera del entorno industrial, en donde se imposibilita estructurar el entorno, se les dotó a los robots un mayor grado de inteligencia y capacidad para poder
desenvolverse.
Uno de los desafíos más grandes en la aplicación de robots es la navegación en entornos desconocidos abarrotados de obstáculos. La navegación se vuelve aún más compleja cuando no se conoce la ubicación de estos a priori.
Para mover un robot en un entorno definido con cierto grado de autonomía es necesario que este sea capaz de la detección y evitación autónoma de obstáculos y/o del reconocimiento de estos para poder actuar.
La lógica difusa fue investigada a mediados de los años sesenta en la Universidad de Berkeley (California) y trae una solución a este problema.

### Bases Teoricas

Los sistemas de control en general se encargan de evaluar las variables de entrada, realizar un proceso en base a un comportamiento deseado para poder modificar las salidas y en definitiva actuar sobre la planta. En el caso del control difuso las variables se evalúan utilizando lógica difusa y el proceso se realiza en base a un conjunto de reglas.


#### Logica difusa

Las variables que intervienen en las reglas no son verdaderas o falsas, sino que el grado de pertenencia a un conjunto está dado por una función que varía entre 0 y 1 en todo el rango de la variable también llamado universo de discurso [2].

#### Sistemas Basados en Reglas

El conjunto de reglas se definen en lenguaje natural, según el grado de pertenencia de sus variables será el grado de verdad de la regla. El comportamiento de la salida dependerá de las reglas con mayor grado de verdad.

SI antecedente ENTONCES consecuente
SI condición ENTONCES acción

#### Control Difuso
Se puede descomponer el proceso de control difuso en tres etapas principales.

##### <div style="text-align:center"> 1) Fuzzificación 

Dados los valores de entrada se calcula el grado de pertenencia a cada uno de los conjuntos difusos considerados, mediante las funciones características asociadas a estos conjuntos difusos.

<p align="center">
  <img src=./imagenes/fpertenencia.png alt="Hardware" /> 
  <p align="center"> Fig. 1 Función de pertenencia de una variable x <p align="center">
</p>


##### <div style="text-align:center"> 2) Evaluación de reglas

Relaciona los conjuntos de entrada (las cuales son conjuntos difusos, grados de pertenencia) mediante mecanismos de inferencia (reglas) con las salidas (las cuales también son conjuntos difusos, asociados a una o varias variables de salida).

##### <div style="text-align:center"> 3) Defuzzificación

A partir del conjunto difuso obtenido en el mecanismo de inferencia y mediante métodos matemáticos de desdifusión, se obtiene un valor concreto de la/s variable/s de salida.

<p align="center">
<img src=./imagenes/etapas.png alt="Hardware" />
  <p align="center"> Fig. 2 Etapas del control difuso. <p align="center">
</p>

#### Estado del arte

En 2006 se desarrolló un sistema difuso para la navegación en entornos densamente abarrotados de obstáculos. En donde utilizaron lógica de preferencias para poder arbitrar o fusionar las reacción de los comportamientos individuales difusos.
“El problema más difícil al aplicar sistemas de control de navegación basados en el comportamiento reactivo difuso es el de arbitrar o fusionar las reacciones de los comportamientos individuales, que se aborda aquí mediante el uso de la lógica de preferencias.” [3]

<p align="center">
<img src=./imagenes/state1.png alt="Hardware" />
  <p align="center"> Fig. 3 Esquema de preferencia de comportamiento. <p align="center">
</p>


Danial y Babak [4] dividieron la navegación en dos partes. La primera compuesta en comportamientos básicos: lograr metas, evitación de obstáculos y seguimiento de muros. La segunda, una capa de supervisión responsable de la selección de las acciones (elección de comportamientos según el contexto) en donde seleccionan un comportamiento de la lista de estos en función de su prioridad.

<p align="center">
<img src=./imagenes/state2.png alt="Hardware" />
  <p align="center"> Fig. 4 Diferentes tareas de navegación. <p align="center">
</p>

En 2016 se desarrolló un sistema de control difuso con la ventaja de que solo necesitaba un único controlador difuso para la navegación y la evasión de obstáculos para un robot [5].

<p align="center">
<img src=./imagenes/state3.png />
  <p align="center"> Fig. 5 Esquema de control difuso con 35 reglas. <p align="center">
</p>

<p align="center">
<img src=./imagenes/state4.png  />
  <p align="center"> Fig. 6 Diagrama en bloques del sistema de control. <p align="center">
</p>


#### Planteo del problema

Como se mencionó anteriormente el problema se puede clasificar dentro de los de planificación de movimiento (motion planning), se debe mover un objeto (robot) desde un punto inicial a un punto final evitando colisionar con los posibles obstáculos del entorno. El robot conoce su pose (el ángulo hacia dónde se orienta respecto al eje de coordenadas) en todo momento y el ángulo hacia el target, además no presenta limitaciones en cuanto al ángulo de giro. La detección de obstáculos se realiza mediante tres sensores de distancia.


Algunas consideraciones que se tuvieron en cuenta para el armado de reglas y funciones de pertenencia [6].

* Cubrir adecuadamente el espacio de estado del problema.
* El conjunto de reglas debe ser completo y correcto.
* Las reglas no deben ser contradictorias.
* Para todos los valores de entrada la suma del grado de pertenencia de los distintos conjuntos debe ser 1.

#### Desarrollo 

El desarrollo de la solución se puede dividir en versiones que van desde menor a mayor complejidad.

##### 1) MySimAvoidObs2

<p align="center">
<img src=./imagenes/des1.png  />
  <p align="center"> Fig. 7 Captura de la simulación de MySimAvoidObs2. <p align="center">
</p>


En un principio partimos de un ejemplo de simulación y control difuso implementado en matlab (MySimAvoidObs1[7]). Nuestra idea base, fue controlar con el sistema difuso la variación del ángulo actual del robot para evadir un obstáculo. En este planteo el robot no tiene información sobre el destino, solo se encarga de evadir obstáculos. De este modo se representa el control con el siguiente esquema.

<p align="center">
<img src=./imagenes/esquema1.png  />
  <p align="center"> Fig. 8 Esquema de entradas y salidas MySimAvoidObs2. <p align="center">
</p>


En donde Sleft, Sfront, y Sright representa las distancias al obstáculo y Theta el ángulo que deberá girar el robot para evadirlo.

Ecuación a controlar con el sistema difuso:

nav.robot(3) = nav.robot(3) - Theta;

Tal que:
* nav.robot(3) representa la dirección de avance actual del robot. 
* Theta la salida del sistema difuso, evasión del obstáculo.


##### 2) MySimReachTarget

En esta versión la tarea de navegación se trata de combinar dos vectores, la variación del ángulo actual (ángulo que proporciona una dirección libre de colisión para el robot) y el ángulo al target. La salida w varía entre 0 y 1 e indica el peso que tendrá cada ángulo en el ángulo resultado tal como se muestra en la ecuación de control.

<p align="center">
<img src=./imagenes/esquema2.png  />
  <p align="center"> Fig. 9 Esquema de entradas y salidas MySimReachTarget. <p align="center">
</p>


Ecuación a controlar con el sistema difuso:

nav.robot(3)=(1-w)*(nav.robot(3)-Theta) + w*(ang);

Tal que:

* nav.robot(3) representa la dirección de avance actual del robot. 
* Theta la salida del sistema difuso, evasión del obstáculo. 
* w: Parámetro [0-1]. 
* ang: ángulo al target con respecto a la horizontal en cada ubicación del robot.


##### 3) MySimReachTargetVelControl

En la tercera versión la ecuación de control se mantiene igual, pero se agrega a la como salida del control difuso el control de la velocidad del robot.

<p align="center">
<img src=./imagenes/esquema3.png  />
  <p align="center"> Fig. 10 Captura de la simulación de MySimReachTarget. <p align="center">
</p>

La salida Vel afecta al desplazamiento del robot en la dirección definida por el ángulo. Esta salida varía entre 1 y -1, permitiéndole al robot avanzar y retroceder.

<p align="center">
<img src=./imagenes/esquema4.png  />
  <p align="center"> Fig. 11 Esquema de entradas y salidas de MySimReachTarget. <p align="center">
</p>

#### Variables Fuzzy

A continuación se muestra el detalle de las funciones de pertenencia de las variables intervinientes en el control difuso. Consideramos como entradas la distancia al obstáculo obtenida mediante tres sensores con ángulo ajustable. En los tres sensores se repiten las funciones “cerca” y “lejos”.

<p align="center">
<img src=./imagenes/varfuzzy1.png  />
  <p align="center"> Fig. 12 Detalle de funciones de pertenencia de entrada Sright, sensor derecho de distancia. <p align="center">
</p>

Para la salida Theta definimos las funciones “izquierda” “centro” y  “derecha”.

<p align="center">
<img src=./imagenes/varfuzzy2.png  />
  <p align="center"> Fig. 13 Detalle de funciones de pertenencia de salida Theta. <p align="center">
</p>

Para la salida w se definieron los conjuntos “bajo” y “alto” según el peso que tendrá el ángulo hacia el target.

<p align="center">
<img src=./imagenes/varfuzzy3.png  />
  <p align="center"> Fig. 14 Detalle de funciones de pertenencia de salida w. <p align="center">
</p>

Finalmente la variable de salida Vel permite que el robot avance y retroceda según la ubicación de los obstáculos. Se definieron las funciones “retroceder”, “avanzar” y “avanzarMucho”. Debido a que el robot no cuenta con sensores traseros se limita la velocidad de retroceso disminuyendo el rango negativo de la variable Vel.

<p align="center">
<img src=./imagenes/varfuzzy3.1.png  />
  <p align="center"> Fig. 15 Detalle de funciones de pertenencia de salida Vel. <p align="center">
</p>

El esquema del control difuso de la última versión con estas entradas y salidas se muestra en la siguiente figura.

<p align="center">
<img src=./imagenes/varfuzzy4.png  />
  <p align="center"> Fig. 16 Esquema del control difuso con tres entradas y tres salidas. <p align="center">
</p>

#### Reglas

Para las tres versiones se definieron 8 reglas a las que se le fueron incorporando las nuevas variables de cada versión. Se muestra el detalle de cada una.

<p align="center">
<img src=./imagenes/reglas.png  />
  <p align="center"> Fig. 17 Conjunto de reglas de MySimAvoidObs2. <p align="center">
</p>

<p align="center">
<img src=./imagenes/reglas2.png  />
  <p align="center"> Fig. 18 Conjunto de reglas de MySimReachTarget. <p align="center">
</p>

<p align="center">
<img src=./imagenes/reglas3.png  />
  <p align="center"> Fig. 19 Conjunto de reglas de MySimReachTargetVelControl. <p align="center">
</p>

#### Resultados
A continuación se pueden ver la trayectorias realizadas por el robot según la versión del sistema difuso:

<p align="center">
<img src=./imagenes/res_1.png  />
  <p align="center"> Fig. 20 Camino recorrido en un laberinto sin target MySymAvoidObs2. <p align="center">
</p>

En esta versión la dirección del robot está determinada solamente por los obstáculos que se presentan. Se puede apreciar que hay una pequeña desviación en la trayectoria debida a que la salida del sistema es difusa y que no hay cambio en su velocidad.

<p align="center">
<img src=./imagenes/res_2.png  />
  <p align="center"> Fig. 21 Camino recorrido en un laberinto MySimReachTargetVelControl. <p align="center">
</p>


<p align="center">
<img src=./imagenes/res_3.png  />
  <p align="center"> Fig. 22 Camino recorrido con obstáculos aleatorios
MySimReachTargetVelControl. <p align="center">
</p>


En Fig. [21] y Fig. [22] se puede observar el cambio de la velocidad del robot por la densidad de los marcadores violetas (cuanto más espaciados mayor es el desplazamiento en cada paso de la simulación).


#### Conclusiones

Trabajar con control difuso simplifica el modelo de comportamiento del móvil. Definir reglas en lenguaje natural se asemeja a darle indicaciones al móvil sobre cómo reaccionar frente a determinadas circunstancias.

Además, plantear la solución del problema utilizando un controlador difuso nos permite:

● Evaluar múltiples entradas de manera sencilla.
● Independizarnos de posibles alinealidades en los sensores.
● Que el robot realice movimientos suaves.

Complejizar el comportamiento agregando nuevas variables se traduce en agregar nuevas funciones de pertenencia y nuevas reglas, esto hace que el modelo sea
flexible.
En el caso de una implementación en hardware con sensores que presenten alinealidades se puede realizar una compensación definiendo convenientemente la función de pertenencia de dicha variable.


REFERENCIAS
* [1] Ing. Morris William Diaz Saravia. Tesis. Diseño de prototipo de vehículo autónomo utilizando redes neuronales.
* [2] Prof. Lotfi A. Zadeh (1965). Fuzzy Sets-Information and Control.
* [3] Majura F. Selekwaa Damion D. Dunlapb Dongqing Shib Emmanuel G. Collins Jr. «“Robot navigation in very cluttered environments by preference-based fuzzy behaviors ». En:Elsevier B.V.(2007)..
* [4] Babak Karasfi Danial Nakhaeinia. “Application of Fuzzy Logic in Mobile Robot Navigation”.Año: 2012.
* [3] Mohamed Slim Masmoudi Hajer Omrane y col. «“Fuzzy Logic Based Control for Autonomous Mobile Robot Navigation”». En:-(2016)
* [6] Apunte de cátedra Introducción a la Inteligencia Artificial “Fuzzy Control” (2021), Juan Carlos Gómez Claudio Abel Verrastro. Universidad Tecnológica Nacional.
 *[7] Tune Fuzzy Robot Obstacle Avoidance System Using Custom CostFunction. https://www.mathworks.com/help/fuzzy/tune-fuzzy-systems-usingcustom-cost-function.html

