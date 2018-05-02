#version 130
in vec4 color_data_to_fshader;
out vec4 FragColor;

void main()
{
    FragColor = color_data_to_fshader;
	//FragColor = vec4(1.0 , 0.0 , 0.0 , 0.0);
}
