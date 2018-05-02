#version 130

//vertex shader 
in vec4 vPosition; 
in vec4 vColor; 

// Light and material properties. Light color * surface color 
uniform vec4 AmbientProduct1, DiffuseProduct1, SpecularProduct1; 
uniform mat4 viewing_object; 
uniform mat4 projection_type; 
uniform vec4 Light1Position;
uniform vec3 EyePosition;
uniform float Shininess; 
uniform int shader_flag;
out vec4 fN; 
out vec4 fE;  
out vec4 fL1; 
out vec4 color_data_to_fshader;  //vertex shade 

void main() 
{ 
		fN = vColor; 
		fE = vec4(EyePosition - vec3(vPosition.x,vPosition.y,vPosition.z),0.0); 
		//  Light defined in world coordinates 
		fL1 = Light1Position - vPosition; 
		gl_Position = projection_type*viewing_object*vPosition; 
}
