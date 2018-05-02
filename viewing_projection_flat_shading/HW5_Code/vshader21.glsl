#version 130

in vec4 vPosition;
in vec4 vColor;
out vec4 color_data_to_fshader;
uniform mat4 viewing_object;
uniform mat4 projection_type;
void main()
{
    gl_Position = projection_type * viewing_object * vPosition;
	color_data_to_fshader = vColor ;
}
