#version 420 core

uniform vec4 lineColor;
void main(void)
{
    //vec4 _lineColor;
    //_lineColor= vec4(1, 1, 0, 1);
    gl_FragColor = lineColor;
};
