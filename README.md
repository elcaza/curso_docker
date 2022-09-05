# Curso Docker
Docker 101

# CheatSheet
[cheatsheet.md](./cheatsheet.md)

# Ejemplos
[Ejemplos de Dockerfile](./ejemplos/)

# Teoría
## ¿Qué hace un contenedor?
+ Los contenedores comparten el kernel del host
+ Los contenedores usan la capacidad del kernel para agrupar procesos para el control de recursos
+ Los contenedores garantizan aislamento a través de namespaces
+ Los contendores se sienten ligeros como una VM ligera, pero no son VM

## Docker provee
+ Image management
+ Resource Isolation
+ File System Isolation
+ Network Isolation
+ Change Management
+ Sharing
+ Process Management
+ Service Discovery (DNS since 1.10)

## Kernel Namespaces
+ Process trees (PID Namespace)
+ Mounts (MNT namespace) wc -l /proc/mounts
+ Network (Net namespace) ip addr
+ Users / UIDs (User Namespace)
+ Hostnames (UTS Namespace) hostname
+ Inter Process Communication (IPC Namespace) ipcs

## Más información
+ https://docker-saigon.github.io/post/Docker-Internals/#how:cb6baf67dddd3a71c07abfd705dc7d4b

# Instalación de docker

Desde su sitio web oficial seguimos la guía de instalación
+ https://docs.docker.com/engine/install/ubuntu/
+ Corroborar para qué sistema operativo se instala

Una vez instalado probamos que tengamos docker con:

```
docker --version
```
+ Si no se puede visualizar probar con `sudo docker --version`

## Pasos de post instalación
+ https://docs.docker.com/engine/install/linux-postinstall/

### Agregar a un usuario al grupo docker
~~~bash
usermod -aG docker ${USUARIO}
~~~
+ Requiere reiniciar la máquina o abrir y cerrar sesión para obtener los nuevos privilegios

### Switch temporal
~~~bash
sudo su - ${USER}
~~~
+ Realiza una nueva sesión de tu usuario vía sudo y te da un shell interactivo

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

## Ejecución de contenedores en 1er y 2do plano

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

## Buildkit Docker
+ https://docs.docker.com/develop/develop-images/build_enhancements/

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
RUN apt install -y git
RUN apt install -y curl
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

### EXPOSE
+ Informa que el contenedor va a estar a la escucha en un puerto especifico
    + `EXPOSE <port>`

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


# Enlaces entre contenedores
Es utilizado para crear microservicios
Docker crea un túnel seguro entre contenedores para que estos no expongan puertos externamente
~~~bash
# Se crea un contenedor especificando un nombre
docker run -d --name redis redis:3.2.0
# Comprobar que esté corriendo bajo el nombre correcto
docker ps
# Construye la app en que se encuentre la app
docker build -t dockerapp:1.0 .
# Ejecuta el contenedor
docker run -d -p 5000:5000 --link nombre_contenedor dockerapp:2.0
~~~

## ¿Por qué funciona esto?
~~~bash
cat /etc/hosts
# IP id_contendor nombre_contenedor
~~~

# Redes en Docker

## Inspeccionar tipo de redes
~~~bash
docker network ls
# 0b38e00cff30   bridge    bridge    local
# 713b2164fa61   host      host      local
# f0a5ab3ecf2a   none      null      local
~~~

## Inspeccionar red
~~~bash
docker network inspect bridge
~~~

## Red none
~~~bash
docker run -d --net none ubuntu sleep 60
~~~

## Red Bridge
Parecido a red NAT
~~~bash
docker run -d --name nombre ubuntu sleep 60
~~~
+ se omite el `--net` porque se asigna esta red por defecto

## Crear/Borrar tu propia red
~~~bash
# Creamos la red
docker network create --driver bridge mi_nueva_bridge
# Inspeccionamos las redes
docker network ls
# Inspeccionamos la que queremos
docker network inpect mi_nueva_bridge
# Asociación
docker run -d --net mi_nueva_bridge ubuntu sleep 60
~~~

## Gestión de redes
### Añadir una nueva red a un contenedor existente
~~~bash
# Conectar a red existente
docker network connect bridge contenedor_nombre
# Desconectar
docker network disconnect bridge contenedor_nombre
# Corroborar (ping o ifconfig)
docker exec -it contenedor_nombre ifconfig
~~~

## Red Host 
Parecida a bridge de vmware
+ En teoría no es necesario, porque para eso existe la opción -p (?)
+ No está aislado

~~~bash
# Crear contenedor abierto
docker run -d --name contenedor_abierto --net host busybox sleep 100
~~~

## Red Overlay  
Soporta múltiples maquinas host
Requiere condiciones preexistentes
+ Docker engine en modo Swarm

# Almacenamiento de datos
~~~bash
# Crear un nuevo volumen
docker volume create ejemplo
# Eliminar volumen
docker volume rm ejemplo

# Ver volumenes creados
docker volume ls

# docker volume inspect ejemplo
docker volume inspect ejemplo

# Asignar un volumen a una imagen
docker run -p 8000:8000 -v ejemplo:/app -d --name name user/imagen:1.0
~~~
