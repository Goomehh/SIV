# SIV

Sistema de identificacion vehicular

# Info

Video presentacion del proyecto: https://youtu.be/XcQt5sAtSic (Principal)

El modelado de la caja y la placa de las conexiones usadas se encuentran en el apartado "Fotos" y "Videos"

# Poster Ingenia Futuro

Poster enfocado a la problematica junto a la propuesta de solucion presentada

![Poster](https://github.com/Goomehh/SIV/assets/133666827/ec5315f4-2898-4402-9702-ef28de077d79)

# Idea principal del funcionamiento del sistema (flow-chart)

Dos diagramas independientes pero que hacen parte del mismo objetivo.
Como se puede ver en la primera parte del diagrama, el proyecto esta principalemtne orientado a las motos, esto debido a su inidice de hurto en la capital y la accesibilidad que se tiene a sus componentes internos.

![image](https://github.com/Goomehh/SIV/assets/133666827/40a292cd-8201-4537-b9b8-ec569c7c0965)

Por otro lado esta el sistema de la aplicacion movil, este cuanto mas es parte escencial del proyecto, pues es la que permite el ingreso de nuevos usuarios al sistema y ubica la moto en tiempo real para transmitirlo graficamente

# Boceto superficial del funcionamiento del sistema

Se hace una idea de como puede quedar instalado el circuito en la moto.
De la misma forma se grafica como iria linealmente la secuencia de pasos necesaria para que el motor de la moto sea prendido.

![image](https://github.com/Goomehh/SIV/assets/133666827/bb95a9e8-ac62-417c-8e5b-23b1a3ffeda5)

# Diagrama de caja negra

Se plantea lo que viene siendo la alimentacion del circuito y de la misma forma la secuencia adecuada para el procesamiento de los datos, esto teniendo en cuenta el diagrama de flujo que nos explica como debe funcionar el circuito, es necesario tener en cuenta los componenetes principales de cada sector, es decir, los puntos vitales que requiere el circuito, como la alimentacion, el "cerebro", los actuadores, sensores, entre otros.

![image](https://github.com/Goomehh/SIV/assets/133666827/4f9223af-d3ee-42a9-8b0c-bbfc7adafeba)

# Diagrama de caja negra con tecnologia definida

Una vez definida la dinamica y funcionamiento del circuito se empiezan a buscar componentes aptos para facilitar el ensamble, programacion y adaptacion, en nuestro caso usaremos componentes especificos como lo son el Esp32, un sensor de huellas fpm10a, un modulo sim para la tarjeta SD, entre otros (Lista completa en la seccion "Materiales").

![image](https://github.com/Goomehh/SIV/assets/133666827/2f8c2ea7-a974-48cc-8fa4-8a95fc53769e)

# Esquematico del circuito 

En esta seccion se pretende diseñar de forma clara y organizada la conexion de los diferentes componentes que se van a implementar de forma que en caso de requerir fabricar una PCB, no haya mayor complicacion, el circuito fue hecho mediante la aplicacion Kicad.

![image](https://github.com/Goomehh/SIV/assets/133666827/52da2a77-c38f-4f12-aae1-b41fa6d9ed6a)

# Esquematico de la placa PCB

En este esqumatico se puede apreciar la ubicacion de cada uno de los compenetes presentados anteriormente, a excepcion de los pulsadores que simulan al teclado, para este se ponen los puertos para soldar, por otro lado tambien se aprecian las conexiones que se realizan de forma que se ahorra bastante espacio, este tipo de conexiones se manejaron por ambos lados con ese mismo objetivo en mente.

![image](https://github.com/Goomehh/SIV/assets/133666827/1a84122d-c368-4c1f-addb-f30294e7e384)

# Vista 3D del a PCB

![image](https://github.com/Goomehh/SIV/assets/133666827/9f9d901e-151e-42fe-8aa8-322061450e03)


# Pruebas

A continuacion se anexan algunas fotos sobre los montajes del circuito al vehiculo, sin embargo la mayoria de este archivo multimedia lo puede encontrar en las carpetas designadas.

![image](https://github.com/Goomehh/SIV/assets/133666827/bfd6745d-a2c4-4aa6-9993-9beb741e0051)

![image](https://github.com/Goomehh/SIV/assets/133666827/b74f8399-f396-4af8-b72d-c09fa02bc266)

![image](https://github.com/Goomehh/SIV/assets/133666827/d765011c-92d1-490c-8db9-6f84c3a346ea)

![image](https://github.com/Goomehh/SIV/assets/133666827/3cdabd3a-631e-4f36-baab-9c583e95f7ce)

(Aclaracion: en esta documentacion no esta incluida la PCB mencionada con anterioridad)


