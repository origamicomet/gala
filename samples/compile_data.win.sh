#!/bin/bash

case "$1" in

opengl)
        cgc -entry vs_main -profile glslv -po version=140 -o ../bin/data/cube/simple.opengl.vsc data_src/cube/simple.vsh
        cgc -entry ps_main -profile glslf -po version=140 -o ../bin/data/cube/simple.opengl.psc data_src/cube/simple.psh
    ;;

directx)
        echo TODO
    ;;

esac