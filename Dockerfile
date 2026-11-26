FROM debian:bookworm AS build

RUN apt-get -qq update && \
    apt-get -qq install -y --no-install-recommends g++ make binutils cmake libssl-dev libboost-system-dev libcurl4-openssl-dev zlib1g-dev && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /usr/src/sheena
COPY src src
COPY lib lib
COPY CMakeLists.txt ./

RUN cmake . && \
    make -j"$(nproc)" && \
    make install

FROM debian:bookworm

ARG APP_VERSION=dev
ARG GIT_COMMIT=unknown

LABEL org.opencontainers.image.author="Rolf Schatten <Rolf.Schatten@gmail.com>" \
      org.opencontainers.image.version="${APP_VERSION}" \
      org.opencontainers.image.revision="${GIT_COMMIT}"

RUN apt-get -qq update && \
    apt-get -qq install -y --no-install-recommends ca-certificates libssl3 && \
    rm -rf /var/lib/apt/lists/*

COPY --from=build /usr/local/bin/tbsheena /usr/local/bin/tbsheena

CMD ["tbsheena", "-t", "123456:ABC-DEF1234ghIkl-zyx57W2v1u123ew11"]
