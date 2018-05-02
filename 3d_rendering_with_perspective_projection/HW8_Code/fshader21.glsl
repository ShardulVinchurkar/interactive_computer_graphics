#version 130

in vec4 color_data_to_fshader;
in vec4 fN; 
in vec4 fL1; 
in vec4 fE;

uniform vec4 AmbientProduct1, DiffuseProduct1, SpecularProduct1; 
uniform mat4 viewing_object; 
uniform float Shininess;
uniform int color_flag;
uniform vec4 uniform_diffuse_onclick;

out vec4 FragColor;

void main()
{
		if(color_flag == 0) {
			// Normalize the input lighting vectors 
			vec4 N = normalize(fN); 
			vec4 E = normalize(fE); 
			vec4 L1 = normalize(fL1); 
			vec4 H1 = normalize( L1 + E ); 
			vec4 ambient1 = AmbientProduct1;  
			float dTerm1 = max(dot(L1, N), 0.0); 
			vec4 diffuse1 = dTerm1*DiffuseProduct1;
			float sTerm1 = pow(max(dot(N, H1), 0.0), Shininess);
			vec4 specular1 = sTerm1*SpecularProduct1;
			// discard the specular highlight if the light's behind the vertex 
			if( dot(L1, N) < 0.0 )  
				specular1 = vec4(0.0, 0.0, 0.0 , 0.0); 
			
			FragColor = ambient1 + diffuse1 + specular1;	
		}
		else {
			FragColor = uniform_diffuse_onclick;
		}
}

