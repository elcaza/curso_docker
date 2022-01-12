FROM debian
RUN apt-get update && apt-get install -y \
curl
RUN useradd -ms /bin/bash user1
USER user1
WORKDIR /opt/app/
COPY ./c_app /opt/app/
CMD ["./argumentos", "este es un parametro", "este es otro"]
