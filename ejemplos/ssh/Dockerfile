# Imágen base
FROM debian

# Instalamos los paquetes que vamos a utilizar
RUN apt-get update && apt-get install -y \
openssh-server \
systemctl \
net-tools \
sudo

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

# Copiamos el script que se encargará de levantar los servicios
COPY ssh-script /usr/local/bin/

# Le damos permisos de ejecución al script que levantará los servicios
RUN chmod +x /usr/local/bin/ssh-script

# Exponemos los puertos que usará el servidor
EXPOSE 22

# Ejecutamos el script que correrá los servicios
CMD ["ssh-script"]