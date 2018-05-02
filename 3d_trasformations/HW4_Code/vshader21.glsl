#version 130

in vec4 vPosition;
in vec4 vColor;
out vec4 color_data_to_fshader;
uniform mat4 rot;
void main()
{
    gl_Position = rot * vPosition;
	color_data_to_fshader = vColor ;
}
