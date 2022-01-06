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


# Conceptos importantes

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
# Obtenemos id
docker ps -a

# Cambiar tag // Solo en caso de ser requerido
docker tag id_image username/image:1.0

# Hacer commit de una imagen de docker
docker commit id_image user/image:1.0
# user/image    1.0       6f5e2d0470ef   9 seconds ago   243MB

# Hacer login en docker
docker login --username=user

# Enviar imagen a Dockerhub
docker push username/image:1.0
~~~

# Construcción de imágenes de Docker
## Hacer commit de los cambios en el contenedor
De esta manera 

~~~bash
# Iniciamos una imagen de debian
docker run -it --name debian-git3 debian

# Dentro del docker descargamos git
apt update
apt install -y git 
git --version
exit

# Docker Commit
# Obtenemos id
docker ps -a

# Hacer commit de una imagen de docker
docker commit debian-git3 elcaza/debian-git3:1.0

# Consultar imagen creada
docker images
~~~

## Dockerfile
A través de un documento `Dockerfile` es posible automatizar ciertas acciones.
Muy parecido a un *Makefile*
+ Consultar sección de Dockerfile

# Dockerfile
Hay que recordar que las imágenes de Docker se componen por capas, cada instrucción genera una nueva capa.

Dado lo anterior, en medida de lo posible es preferible concatenar comandos para evitar hacer lo siguiente:

`Dockerfile` (Ejemplo a evitarse)
~~~Dockerfile
FROM debian
RUN apt-get update
RUN apt intall -y git
RUN apt intall -y curl
~~~
+ Cada ``RUN`` añade una nueva capa a la imagen

`Dockerfile` (Ejemplo a utilizar en su lugar)
~~~Dockerfile
FROM debian
RUN apt-get update && apt-get install -y \
    curl \
    git 
~~~
+ Nota: Se hace uso de `apt-get` para evitar el *warning* que Docker envia con `apt`.

## Contenidos e instrucciones de un Dockerfile
Aunque no hay diferencia entre minusculas y mayusculas, se recomienda el uso de mayusculas para las instrucciones.

### FROM
+ Imágen base
    + `FROM ubuntu`

### RUN 
+ Acción a ejecutar
    + `RUN apt-get update && apt-get install -y git`

### CMD
+ Comando a ejecutar tras inicializar el contenedor
    + `CMD ["echo", "Inicializado"]`

### COPY
+ COPY copia archivos o directorios del contexto de compilación al sistema de archivos del contenedor
    + `COPY files /app/files`

### ADD
+ Puede manejar URLs remotas
+ Puede extraer automaticamente archivos tar
+ Se recomienda usar COPY
    + `ADD <src> <dest>`

### USER
+ USER elecciona con que usuario va a correr la aplicación
    + `USER admin`

### WORKDIR
+ Selecciona el directorio de trabajo que vamos a utilizar
    + `WORKDIR /app`

## Ejemplos de dockerfile
~~~Dockerfile
FROM python:3.7
RUN pip install Flask==0.11.1
RUN useradd -ms /bin/bash admin
USER admin
WORKDIR /app
COPY app /app
CMD ["python", "app.py"]
~~~
+ useradd -ms
    + -m, --create-home
    + -s, --shell SHELL

## Comandos básicos de Dockerfile
### Compilar imagen
~~~bash
# Compilar imagen
docker build -t user/image .
docker build -t user/image /path/to/file

# Compilar imagen sin cache
docker build -t user/image:1.0 . --no-cache=true
~~~

## Docker cache
El cache de Docker es usado para no ejecutar los comandos una vez que estos ya se han ejecutado.

### Ejemplo
Podria causar problemas en instrucciones como:
~~~Dockerfile
# Config inicial
FROM debian
RUN apt-get update
RUN apt-get install -y git

# Config nueva
# cache
FROM debian
# cache
RUN apt-get update
# Estariamos instalando sin antes haber hecho un update, podría descargarse un paquete viejo
RUN apt-get install -y curl git vim

# Posible solución
FROM debian
RUN apt-get update && apt-get install -y \
    curl \
    git \
    vim

# Otra solucion
docker build -t user/image:1.0 . --no-cache=true
~~~


