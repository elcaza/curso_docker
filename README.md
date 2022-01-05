# Curso Docker
Un conjunto de notas sobre Docker

# Instalación de docker

Desde su sitio web oficial seguimos la guía de instalación
+ https://docs.docker.com/engine/install/ubuntu/
+ Corroborar para qué sistema operativo se instala

Una vez instalado probamos que tengamos docker con:

```
docker --version
```
+ Si no se puede visualizar probar con `sudo docker --version`

Pasos de post instalación
+ https://docs.docker.com/engine/install/linux-postinstall/

## Hello word en docker

**Repositorio**
+ https://hub.docker.com/_/hello-world

~~~bash
# Descarga la imagen
docker pull hello-world

# Ejecuta Hello world
docker run hello-world
~~~


# Conceptos importaes

## Imágenes
+ Plantillas utilizadas para crear contenedores; comando _build_
+ Están compuestas por capas de otras imágenes
+ Se almacenan en un registro docker 

## Contenedor
+ Si una imagen la relacionamos a una clase, entonces una instancia sería un contenedor
+ Los contenedores solamente almacenan los binarios y dependencias que se necesitan para la ejeución.

## Registro
+ Lugar donde se almacenan las imagenes
    + Puede ser público o privado (DockerHub o Propio)
    + El registro contiene **repositorios** donde vive cada imágen

## Descripción gráfica
~~~markdown
+ El **registro** Docker de Apache
    + Tiene un **repositorio**
    + https://hub.docker.com/_/httpd
        + Donde vive cada **imágen** de Docker
            + Para que tú crees tus propios **contenedores**
        

~~~

## Tipos de contendores

### Primer plano
+ Salen por salida estándar

### Segundo plano
+ Inician en modo detached y salen cuando el proceso raiz utilizado para ejecutar el contenedor termina

## Imagenes de docker
Al igual que en github, docker tiene imagenes que puedes usar como base en:
+ https://hub.docker.com/


## Creación de contenedores
1. Primero se busca localmente la imágen
2. Si no se tiene se busca en línea

## Persistencia
+ docker run crea nuevos contenedores, no hay persistencia. Tal cual una instancia de una clase.

# Comandos básicos

## Listar imagenes, descargar y correr
~~~bash
# Corroborar qué imagenes se tienen en nuestra computadora
docker images

# Descarga la imagen
docker pull hello-world

# Correr imagen
docker run hello-world

# Ejecutar contenedor y borrar
docker run --rm ubuntu

# Ejecutar un contenedor y añadir un nombre
docker run --name hello_ubuntu ubuntu 

# Abrir un contenedor que se ha cerrado
    # Obtenemos el ID
docker ps -a
    # Inicializamos la imagen
docker start -i <name/id>
    # If the container wasn't started with an interactive shell to connect to, you need to do this to run a shell:
docker exec -it <name/id> /bin/sh

# Entrar a un contenedor que está corriendo
docker ps
docker exec -it id_docker /bin/bash
~~~

## Detener contenedores y borrar
~~~bash
# Detener un contenedor
docker ps
docker stop id_name_contenedor 
~~~

## Entrar a un contenedor
~~~bash
# Entrar al contenedor en modo interactivo
docker run -it ubuntu

# Entrar al contenedor y ejecutar un comando
sudo docker run ubuntu echo "hello world!"
~~~

## Ver contenedores que se están/han ejecutado

~~~bash
# Ver que contenedores se ejecutan en background
docker ps
# sudo docker run ubuntu sleep 3

# Ver todos los que contenedores se han ejecutado
docker ps -a
~~~

## Listar información de un contenedor

~~~bash
# Listar información a bajo nivel de una imagen
sudo docker run -d ubuntu sleep 60
sudo docker inspect id_image

# Ver imagenes que conforman una capa de docker
docker history ubuntu
~~~

## Revisar logs
~~~bash
# Checar logs de una imagen
docker logs id_image
~~~

## Commits & Login a Dockerhub

### Cosas a tomar en cuenta para hacer login en cuenta de Docker
+  Tener el nombre correcto de la imagen
    + username/image

~~~bash
# Ver imagenes que tienes
docker images
# Obtenemos id
docker ps -a

# Cambiar tag
docker tag id_image username/image:1.0

# Hacer commit de una imagen de docker
docker commit id_image user/image:1.0
# user/image    1.0       6f5e2d0470ef   9 seconds ago   243MB

# Hacer login en docker
docker login --username=user

# Enviar imagen a Dockerhub
docker push username/image:1.0
~~~
