# Ejemplos de Docker

## Creación y despliegue con Dockerfile

Requisitos:
+ Instalación
+ Uso de volumenes
+ Script de inicio
+ Bind de puertos
+ Dockerfile

Ejemplos:
1. Apache 
1. SSH
1. Apache y SSH

## Uso de imágenes construidas

Ejemplos:
1. Apache desde imagen
1. Flask desde imagen
1. NextCloud

# Anexo

Comandos
~~~bash
# Iniciar una imagen de Docker
docker run <image>
# docker run ubuntu:20.04

# Ejecutar un comando sobre una imagen que corre actualmente
docker exec -it <container_id> /bin/bash
# docker exec -it b1ef42b5257b bash

# Volumenes


~~~