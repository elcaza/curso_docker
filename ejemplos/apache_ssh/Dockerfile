# Imágen base
FROM debian

# Instalamos los paquetes que vamos a utilizar
RUN apt-get update && apt-get install -y \
apache2 \
systemctl \
net-tools \
openssh-server

# Copiamos el contenido del sitio web
COPY ./sitio/index.html /var/www/html/index.html

# Copiamos el script que se encargará de levantar los servicios
COPY apache2-script /usr/local/bin/

# Le damos permisos de ejecución al script que levantará los servicios
RUN chmod +x /usr/local/bin/apache2-script

# Exponemos los puertos que usará el servidor
EXPOSE 80 22

# Ejecutamos el script que correrá los servicios
CMD ["apache2-script"]