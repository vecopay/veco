FROM debian:stretch
LABEL maintainer="Veco Developers <dev@veco.org>"
LABEL description="Dockerised VecoCore, built from Travis"

RUN apt-get update && apt-get -y upgrade && apt-get clean && rm -fr /var/cache/apt/*

COPY bin/* /usr/bin/
