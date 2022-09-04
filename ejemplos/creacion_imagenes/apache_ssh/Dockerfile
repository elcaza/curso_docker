# Imágen base
FROM debian

# Instalamos los paquetes que vamos a utilizar
RUN apt-get update && apt-get install -y \
apache2 \
systemctl \
net-tools \
openssh-server

## SSH
# Creamos un nuevo usuario
RUN useradd -ms /bin/bash sshuser

# Creamos un directorio para las llaves ssh
RUN mkdir -p /home/sshuser/.ssh

# Copiamos la llave pública en el archivo "authorized_keys"
COPY public_key/key.pub /home/sshuser/.ssh/authorized_keys

# Asignamos los privilegios necesarios
RUN chmod 600 /home/sshuser/.ssh/authorized_keys && chown -R sshuser:sshuser /home/sshuser/

# Corregimos el error "Missing privilege separation directory"
RUN mkdir /var/run/sshd

## Apache
# Copiamos el contenido del sitio web
COPY ./sitio/index.html /var/www/html/index.html

# Copiamos el script que se encargará de levantar los servicios
COPY apache-ssh-script /usr/local/bin/

# Le damos permisos de ejecución al script que levantará los servicios
RUN chmod +x /usr/local/bin/apache-ssh-script

# Exponemos los puertos que usará el servidor
EXPOSE 80 22

# Ejecutamos el script que correrá los servicios
CMD ["apache-ssh-script"]