# Apache

Ejemplo de construcción de servicio Apache

## ¿Cómo construir el contenedor?
~~~bash
docker build -t username/tag .
~~~

## ¿Cómo correr el contenedor?
~~~bash
docker run -p 8080:80 <contenedor>
~~~

## ¿Cómo comprobar que funciona?
~~~bash
# Comprobando el sitio web
curl localhost:8080
~~~

## Archivos
+ apache2-script
    + Script utilizado para iniciar todos los servicios del contenedor
+ Dockerfile
    + Archivo para la construcción del contenedor
+ README.md 
    + Documentación 