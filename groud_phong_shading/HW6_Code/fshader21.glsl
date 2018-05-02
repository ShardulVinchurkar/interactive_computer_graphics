#version 130

in vec4 color_data_to_fshader;
in vec4 fN; 
in vec4 fL;
in vec4 fL1; 
in vec4 fE;
out vec4 FragColor;
uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct; 
uniform vec4 AmbientProduct1, DiffuseProduct1, SpecularProduct1; 
uniform mat4 viewing_object; 
uniform float Shininess;
uniform int shader_flag;
void main()
{
	if(shader_flag == 0) {
		FragColor = color_data_to_fshader;
	}
	else if(shader_flag ==1) {
		// Normalize the input lighting vectors 
		vec4 N = normalize(fN); 
		vec4 E = normalize(fE); 
		vec4 L = normalize(fL);
		vec4 L1 = normalize(fL1);
		vec4 H = normalize( L + E ); 
		vec4 H1 = normalize( L1 + E ); 
		vec4 ambient = AmbientProduct; 
		vec4 ambient1 = AmbientProduct1; 
			float dTerm = max(dot(L, N), 0.0); 
			float dTerm1 = max(dot(L1, N), 0.0); 
		vec4 diffuse = dTerm*DiffuseProduct;
		vec4 diffuse1 = dTerm1*DiffuseProduct1;
		float sTerm = pow(max(dot(N, H), 0.0), Shininess);
		float sTerm1 = pow(max(dot(N, H1), 0.0), Shininess);
		vec4 specular = sTerm*SpecularProduct;
		vec4 specular1 = sTerm1*SpecularProduct1;
		// discard the specular highlight if the light's behind the vertex 
		if( dot(L, N) < 0.0 )  
			specular = vec4(0.0, 0.0, 0.0 , 0.0); 
		if( dot(L1, N) < 0.0 )  
			specular1 = vec4(0.0, 0.0, 0.0 , 0.0); 
			
		FragColor = ambient + diffuse + specular + ambient1 + diffuse1 + specular1;	
	}
}

