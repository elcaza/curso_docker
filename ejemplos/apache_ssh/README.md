# Apache

Ejemplo de construcción de servicio Apache

## ¿Cómo correr el contenedor?
~~~bash
docker run -p 8080:80 -p 2222:22 <contenedor>
~~~

## ¿Cómo comprobar que funciona?
~~~bash
# Comprobando el sitio web
curl localhost:8080

# Comprobando el servidor SSH
nc localhost 2222
~~~

## Archivos
+ apache2-script
    + Script utilizado para iniciar todos los servicios del contenedor
+ Dockerfile
    + Archivo para la construcción del contenedor
+ README.md 
    + Documentación 