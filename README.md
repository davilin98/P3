PAV - P3: detección de pitch
============================

Esta práctica se distribuye a través del repositorio GitHub [Práctica 3](https://github.com/albino-pav/P3).
Siga las instrucciones de la [Práctica 2](https://github.com/albino-pav/P2) para realizar un `fork` de la
misma y distribuir copias locales (*clones*) del mismo a los distintos integrantes del grupo de prácticas.

Recuerde realizar el *pull request* al repositorio original una vez completada la práctica.

Ejercicios básicos
------------------

- Complete el código de los ficheros necesarios para realizar la detección de pitch usando el programa
  `get_pitch`.

   * Complete el cálculo de la autocorrelación e inserte a continuación el código correspondiente.
   ![](https://github.com/davilin98/P3/blob/Guardia-Linde/codiauto.PNG)

   * Inserte una gŕafica donde, en un *subplot*, se vea con claridad la señal temporal de un sonido sonoro
     y su periodo de pitch; y, en otro *subplot*, se vea con claridad la autocorrelación de la señal y la
	 posición del primer máximo secundario.
	 
	 ![](https://github.com/davilin98/P3/blob/Guardia-Linde/auto.png)
	 
	> Se puede observar que el pico del segundo máximo secundario está situado en 120. Por lo tanto, para calcular el pitch, haríamos fm/r[k] y en este caso es 16000/120 = 133 Hz. 
	>Para hacer la autocorrelación de la señal, hemos usado una señal de 40ms para evitar estacionariedades, esta señal la hemos obtenido de recortar un audio nuestro en el cual hemos buscado un audio sonoro.
	> En la señal, se puede observar el periodo de pitch ya que al ser sonora, hay una gran periodicidad.  

	 NOTA: es más que probable que tenga que usar Python, Octave/MATLAB u otro programa semejante para
	 hacerlo. Se valorará la utilización de la librería matplotlib de Python.

   * Determine el mejor candidato para el periodo de pitch localizando el primer máximo secundario de la
     autocorrelación. Inserte a continuación el código correspondiente.
     
![](https://github.com/davilin98/P3/blob/Guardia-Linde/pitch.PNG)

> Lo que realizamos en este código es bucar el máximo del primer máximo secundario de la autocorrelación y como tenemos un intervalo en el que buscar, (npitch_min, npitch_max) hemos ido iterando hasta encontrar el máximo absoluto. 

   * Implemente la regla de decisión sonoro o sordo e inserte el código correspondiente.
   
 > Primeramente habíamos decidido unas reglas muy a ojo que nos proporcionaban una detección del 15%. Al observarlo más detalladamente hemos ido cambiando estos valores y hemos finalmente decidido los siguientes valores, bteniendo asi un 90% de detección.
   
   ![](https://github.com/davilin98/P3/blob/Guardia-Linde/unvoiced.JPG)
   
- Una vez completados los puntos anteriores, dispondrá de una primera versión del detector de pitch. El 
  resto del trabajo consiste, básicamente, en obtener las mejores prestaciones posibles con él.

  * Utilice el programa `wavesurfer` para analizar las condiciones apropiadas para determinar si un
    segmento es sonoro o sordo. 
	
	  - Inserte una gráfica con la detección de pitch incorporada a `wavesurfer` y, junto a ella, los 
	    principales candidatos para determinar la sonoridad de la voz: el nivel de potencia de la señal
		(r[0]), la autocorrelación normalizada de uno (r1norm = r[1] / r[0]) y el valor de la
		autocorrelación en su máximo secundario (rmaxnorm = r[lag] / r[0]).

		Puede considerar, también, la conveniencia de usar la tasa de cruces por cero.

	    Recuerde configurar los paneles de datos para que el desplazamiento de ventana sea el adecuado, que
		en esta práctica es de 15 ms.

      - Use el detector de pitch implementado en el programa `wavesurfer` en una señal de prueba y compare
	    su resultado con el obtenido por la mejor versión de su propio sistema.  Inserte una gráfica
		ilustrativa del resultado de ambos detectores.
  
  * Optimice los parámetros de su sistema de detección de pitch e inserte una tabla con las tasas de error
    y el *score* TOTAL proporcionados por `pitch_evaluate` en la evaluación de la base de datos 
	`pitch_db/train`..

   * Inserte una gráfica en la que se vea con claridad el resultado de su detector de pitch junto al del
     detector de Wavesurfer. Aunque puede usarse Wavesurfer para obtener la representación, se valorará
	 el uso de alternativas de mayor calidad (particularmente Python).
   

Ejercicios de ampliación
------------------------

- Usando la librería `docopt_cpp`, modifique el fichero `get_pitch.cpp` para incorporar los parámetros del
  detector a los argumentos de la línea de comandos.
  
  Esta técnica le resultará especialmente útil para optimizar los parámetros del detector. Recuerde que
  una parte importante de la evaluación recaerá en el resultado obtenido en la detección de pitch en la
  base de datos.

  * Inserte un *pantallazo* en el que se vea el mensaje de ayuda del programa y un ejemplo de utilización
    con los argumentos añadidos.

- Implemente las técnicas que considere oportunas para optimizar las prestaciones del sistema de detección
  de pitch.

  Entre las posibles mejoras, puede escoger una o más de las siguientes:

  * Técnicas de preprocesado: filtrado paso bajo, *center clipping*, etc.
  * Técnicas de postprocesado: filtro de mediana, *dynamic time warping*, etc.
  * Métodos alternativos a la autocorrelación: procesado cepstral, *average magnitude difference function*
    (AMDF), etc.
  * Optimización **demostrable** de los parámetros que gobiernan el detector, en concreto, de los que
    gobiernan la decisión sonoro/sordo.
  * Cualquier otra técnica que se le pueda ocurrir o encuentre en la literatura.
  
  
  > Hemos implementado las dos tecnicas siguientes; filtrado de center-clipping para el preprocesado y filtrado de mediana para el postprocesado. Estan implementados de la siguiente manera. Nos gustaria comentar primeramente del center clipping que hemos decidido usarlo con offset, siendo xth 0.0005, valor que hemos creido oportuno al realizar una visualización previa de los valores que obteniamos sin ella. A parte también creemos oportuno comentar el hecho de que hemos decidido normalizar las muestras de x ya que estas nos daban un valor muy pequeño, y de este caso obteniamos valores más cercanos a 1 y -1.
  
  
  > Por otro lado, para la realización del filtro de mediana, comparamos 3 muestras (la que nos encontramos, la siguiente y la anterior) y nos quedamos con el valor del medio. Para hacerlo principalmente lo que hacemos es calcularnos el máximo y el mínimo de los tres, y seguidamente los sumamos todos y restamos este máximo y mínimo, obteniendo así la muestra de valor central y decidimos que la muestra del filtro en esa posición será este valor.
 
 ![](https://github.com/davilin98/P3/blob/Guardia-Linde/centralclipping.JPG)
 
 ![](https://github.com/davilin98/P3/blob/Guardia-Linde/filtromediana.JPG)
  

  Encontrará más información acerca de estas técnicas en las [Transparencias del Curso](https://atenea.upc.edu/pluginfile.php/2908770/mod_resource/content/3/2b_PS Techniques.pdf)
  y en [Spoken Language Processing](https://discovery.upc.edu/iii/encore/record/C__Rb1233593?lang=cat).
  También encontrará más información en los anexos del enunciado de esta práctica.

  Incluya, a continuación, una explicación de las técnicas incorporadas al detector. Se valorará la
  inclusión de gráficas, tablas, código o cualquier otra cosa que ayude a comprender el trabajo realizado.

  También se valorará la realización de un estudio de los parámetros involucrados. Por ejemplo, si se opta
  por implementar el filtro de mediana, se valorará el análisis de los resultados obtenidos en función de
  la longitud del filtro.
   

Evaluación *ciega* del detector
-------------------------------

Antes de realizar el *pull request* debe asegurarse de que su repositorio contiene los ficheros necesarios
para compilar los programas correctamente ejecutando `make release`.

Con los ejecutables construidos de esta manera, los profesores de la asignatura procederán a evaluar el
detector con la parte de test de la base de datos (desconocida para los alumnos). Una parte importante de
la nota de la práctica recaerá en el resultado de esta evaluación.
