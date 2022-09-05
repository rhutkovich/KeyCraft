FROM ubuntu:22.04

COPY . /app

# Download necessary tools and libs
RUN apt-get update &&\
    DEBIAN_FRONTEND=noninteractive apt-get install --no-install-recommends -y \
        ca-certificates \
        libsdl1.2-dev \
        libsdl-image1.2-dev \
        libsdl-mixer1.2-dev \
        libmikmod-dev \
        make \
        git \
        wget \
        squashfs-tools &&\
    apt-get clean &&\
    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# Download FunKey SDK
RUN wget --progress=dot:giga "https://github.com/FunKey-Project/FunKey-OS/releases/download/FunKey-OS-2.3.0/FunKey-sdk-2.3.0.tar.gz" && \
    tar -xvf FunKey-sdk-2.3.0.tar.gz && \
    rm FunKey-sdk-2.3.0.tar.gz && \
    mv FunKey-sdk-2.3.0 /opt/funkey-sdk

# Download & build tinygl
# TODO use find & replace to set appropriate values
RUN git clone https://github.com/C-Chads/tinygl.git &&\
    cd tinygl &&\
    git checkout 9651298 &&\
    cp /app/docker/zfeatures.h ./include &&\
    cd .. &&\
    mv tinygl /opt/

RUN cd /opt/tinygl/src &&\
    /opt/funkey-sdk/usr/bin/arm-linux-gcc -O3 -flto -c *.c -march=armv7-a+neon-vfpv4 -mtune=cortex-a7 -mfpu=neon-vfpv4 &&\
    /opt/funkey-sdk/usr/bin/arm-linux-gcc-ar rcs libTinyGL-fk.a *.o
