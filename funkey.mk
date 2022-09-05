CC			= /opt/funkey-sdk/usr/bin/arm-linux-gcc
TINGYGL_LIB = /opt/tinygl/src/libTinyGL-fk.a
CFLAGS     += -march=armv7-a+neon-vfpv4 -mtune=cortex-a7 -mfpu=neon-vfpv4 -DFUNKEY=1