struct vs_in
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
};

struct vs_out
{
    float4 clipPosition : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
};

// constant buffer 0 
cbuffer VSConstantBuffer0 : register(b0)
{
    float4x4 u_model;
    float4x4 u_view;
    float4x4 u_projection;
}

vs_out vs_main(vs_in input)
{
    vs_out output;
    float4 modelSpace = float4(input.position, 1.0);
    float4 worldSpace = mul(u_model, modelSpace);
    float4 viewSpace = mul(u_view, worldSpace);
    float4 clipSpace = mul(u_projection, viewSpace);
    output.clipPosition = clipSpace;
    output.normal = input.normal;
    output.uv = input.uv;
    return output;
}

float4 ps_main(vs_out input) : SV_TARGET
{
    return float4(input.uv, 0.0, 1.0);

}