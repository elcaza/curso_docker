# SSH

Ejemplo de construcción del contenedor SSH

## ¿Cómo construir el contenedor?
~~~bash
docker build -t username/project .
~~~

## ¿Cómo correr el contenedor?
~~~bash
docker run -p 2222:22 <imagen>
~~~

## ¿Cómo comprobar que funciona?
~~~bash
# Comprobando el contenedor
ssh -p 2222 -i ./public_key/key sshuser@localhost
~~~

## Archivos
+ ssh-script
    + Script utilizado para iniciar todos los servicios del contenedor
+ Dockerfile
    + Archivo para la construcción del contenedor
+ README.md 
    + Documentación 
+ /public_key/key
    + Llave privada para iniciar sesión en el contenedor
+ /public_key/key.pu
    + Llave pública para que se guardará en el servidor