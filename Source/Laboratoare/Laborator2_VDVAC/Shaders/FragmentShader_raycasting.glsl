#version 430

layout (location = 0) in vec3 EntryPoint;
layout (location = 1) in vec4 ExitPointCoord;

uniform sampler2D ExitPoints;
uniform sampler3D VolumeTex;
uniform sampler1D TransferFunc;  
uniform float     StepSize;
layout (location = 0) out vec4 FragColor;

void main() {
    vec2 exitFragCoord = (ExitPointCoord.rg / ExitPointCoord.w + 1.0) /
                         2.0; 
    vec3 exitPoint = texture(ExitPoints,
                             exitFragCoord).rgb;  
    if (EntryPoint == exitPoint)
        
        discard;
    vec3 dir = exitPoint - EntryPoint;   
    float len = length(dir);// lungimea razei e calculata pentru terminarea razei
    vec3 deltaDir = normalize(dir) *
                    StepSize;    
    float deltaDirLen = length(deltaDir);
    vec3 voxelCoord = EntryPoint;
    vec4 colorAcum = vec4(0.0);       
    float alphaAcum = 0.0;         
    float intensity;
    float lengthAcum = 0.0;
    vec4 colorSample;              
    float alphaSample;               

    vec4 bgColor = vec4(1.0, 1.0, 1.0, 0.0);    

    for (int i = 0; i < 2000; i++)    
    {
        intensity = texture(VolumeTex,
                            voxelCoord).r;               
      

        colorSample = texture(TransferFunc,
                              intensity); 


        if (colorSample.a > 0.0) {
           
            colorSample.a = 1.0 - pow(1.0 - colorSample.a, StepSize * 200.0f);
            colorSample.rgb *= colorSample.a;

           
            colorAcum.rgb += (1.0 - colorAcum.a) * colorSample.rgb;
            colorAcum.a += (1.0 - colorAcum.a) * colorSample.a;

        }
      
        voxelCoord += deltaDir;

        lengthAcum += deltaDirLen;

        if (lengthAcum >= len) {
            colorAcum.rgb = colorAcum.rgb + (1 - colorAcum.a) * bgColor.rgb;
            break; 
        } else if (colorAcum.a > 1.0) {
            colorAcum.a = 1.0;
            break; 
        }
    }
    FragColor = colorAcum;

}
