// glslf output by Cg compiler
// cgc version 3.1.0010, build date Feb  8 2012
// command line args: -profile glslf -po version=140
// source file: data_src/cube/simple.psh
//vendor NVIDIA Corporation
//version 3.1.0.10
//profile glslf
//program ps_main
//var float4 IN.color : $vin.COLOR0 : COLOR0 : 0 : 1
//var float4 ps_main.color : $vout.COLOR0 : COLOR0 : -1 : 1

#version 140

struct PS_INPUT {
    vec4 _color;
};

struct PS_OUTPUT {
    vec4 _color1;
};

in vec4 cg_FrontColor;
out vec4 cg_FragColor;

 // main procedure, the original name was ps_main
void main()
{


    cg_FragColor = cg_FrontColor;
    return;
} // main end
