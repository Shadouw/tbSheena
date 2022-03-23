FROM debian:buster
MAINTAINER Rolf Schatten <Rolf.Schatten@gmail.com>

RUN apt-get -qq update && \
    apt-get -qq install -y g++ make binutils cmake libssl-dev libboost-system-dev libcurl4-openssl-dev zlib1g-dev

WORKDIR /usr/src/sheena
#COPY include include
COPY src src
COPY lib lib
COPY CMakeLists.txt ./

RUN cmake . && \
    make -j$(nproc) && \
    make install && \
    rm -rf /usr/src/sheena/*

ENTRYPOINT ["tbsheena", "/etc/tbsheena/token.secret"]
