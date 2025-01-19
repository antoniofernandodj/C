FROM gcc:latest AS cmake-builder

ENV APP=cmake \
    VERSION=3.28 \
    BUILD=1 \
    BUILD_DIR=/tmp/cmake_build

RUN DOWNLOAD_URL=https://cmake.org/files/v$VERSION/cmake-$VERSION.$BUILD.tar.gz && \
    apt update && \
    apt install -y build-essential libtool autoconf unzip wget && \
    apt remove --purge --auto-remove $APP && \
    mkdir $BUILD_DIR && \
    cd $BUILD_DIR && \
    wget $DOWNLOAD_URL && \
    tar -xzvf $APP-$VERSION.$BUILD.tar.gz && \
    cd $APP-$VERSION.$BUILD/ && \
    ./bootstrap && \
    make -j$(nproc) && \
    make install
