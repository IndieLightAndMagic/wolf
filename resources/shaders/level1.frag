#version 410 core
out vec4 FragColor;
in vec4 col;
in vec2 TexCoord;



uint getcoord(float c){
    c = c * 64.0;
    uint ic = floatBitsToUint(c);
    
    if (ic == 64u)
        ic = 63u; 
    
    return ic;
}
uvec2 quotient_modulo(uint dividend, uint divisor){

    return uvec2(dividend / divisor, dividend % divisor);

}
void main() {
    FragColor = col;
}      