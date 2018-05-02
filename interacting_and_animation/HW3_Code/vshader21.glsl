#version 130

in vec2 vPosition;
in vec3 vColor;

out vec4 color_data_to_fshader;
void main()
{
    gl_Position = vec4(vPosition,0.0,1.0);
	color_data_to_fshader = vec4(vColor , 1.0);
}
