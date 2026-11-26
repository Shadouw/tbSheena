ARG APP_VERSION=dev
ARG GIT_COMMIT=unknown

FROM debian:bookworm

ARG APP_VERSION
ARG GIT_COMMIT

LABEL org.opencontainers.image.author="Rolf Schatten <Rolf.Schatten@gmail.com>" \ 
      org.opencontainers.image.version="${APP_VERSION}" \
      org.opencontainers.image.revision="${GIT_COMMIT}"

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

CMD ["tbsheena", "-t", "123456:ABC-DEF1234ghIkl-zyx57W2v1u123ew11"]
