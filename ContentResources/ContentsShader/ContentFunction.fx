cbuffer MaskInfo : register(b0)
{
    float UV_MaskingValue;
    float3 MaskingColor;
}; 

cbuffer ColorOption : register(b1)
{
    float4 MulColor;
    float4 AddColor;
};

cbuffer UVData : register(b2)
{
    float2 MulUV;
    float2 AddUV;
};

cbuffer FadeInfo : register(b3)
{
    float Delta;
    float3 FadeColor;
};

float4 Fading(Texture2D _MaskTexture, SamplerState _Sampler, float2 _UV)
{
    float4 Color = _MaskTexture.Sample(_Sampler, _UV);

    if (Color.r <= Delta)
    {
        clip(-1);
    }
    
    return Color;
}

float4 NormalTexCalculate(Texture2D NormalTex, SamplerState Smp, float4 UV, float4 _Tangent, float4 _BiNormal, float4 _Normal)
{
    float4 TexNormal = NormalTex.Sample(Smp, UV.xy);
    
    TexNormal = TexNormal * 2.0f - 1.0f;
    TexNormal.w = 0.0f;
    TexNormal = normalize(TexNormal);
    
    float4 Result = (float4) 0.0f;
        
    float3x3 TangentSpace = float3x3(_Tangent.xyz, _BiNormal.xyz, _Normal.xyz);
    Result.xyz = mul(TexNormal.xyz, TangentSpace);
    
    return Result;
}