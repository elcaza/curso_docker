# PHP
~~~bash
# Ejecutar un servidor de PHP
docker run -p 8080:80 php

# Ejecutar un servidor de PHP con una carpeta en especifico
docker run -p 80:80 --rm --name php-app -v "$PWD"/sitio:/var/www/html/ php:7.2-apache
~~~