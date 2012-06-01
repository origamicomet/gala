struct VS_INPUT {
    float3 position  : ATTR0;
};

struct VS_OUTPUT {
    float4 position  : POSITION;
    float4 color     : COLOR0;
};

VS_OUTPUT vs_main( VS_INPUT IN )
{
    VS_OUTPUT OUT;
    OUT.position  = float4(IN.position, 1.0);
    OUT.color     = float4(1.0, 1.0, 1.0, 1.0);
    return OUT;
}