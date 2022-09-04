# Apache y SSH

Ejemplo de construcción del contenedor Apache & SSH

## ¿Cómo construir el contenedor?
~~~bash
docker build -t username/project .
~~~

## ¿Cómo correr el contenedor?
~~~bash
docker run -p 8080:80 -p 2222:22 <imagen>

# Uso de volumenes
docker run -v /home/user/Downloads/folder/:/var/www/html/ -p 8080:80 -p 2222:22 <imagen>
~~~

## ¿Cómo comprobar que funciona?
~~~bash
# Comprobando el sitio web
curl localhost:8080

# Comprobando el servidor SSH
ssh -p 2222 -i ./public_key/key sshuser@localhost
~~~

## Archivos
+ apache2-script
    + Script utilizado para iniciar todos los servicios del contenedor
+ Dockerfile
    + Archivo para la construcción del contenedor
+ README.md 
    + Documentación 
+ /public_key/key
    + Llave privada para iniciar sesión en el contenedor
+ /public_key/key.pu
    + Llave pública para que se guardará en el servidor