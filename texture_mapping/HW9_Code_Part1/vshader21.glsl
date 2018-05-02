#version 130

//vertex shader 
in vec4 vPosition; 
in vec4 vColor; 
in vec2 vTexCoord;
 out vec4 color_data_to_fshader;  //vertex shade
// Light and material properties. Light color * surface color 
uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct; 
uniform vec4 AmbientProduct1, DiffuseProduct1, SpecularProduct1; 
uniform mat4 viewing_object; 
uniform mat4 projection_type; 
uniform vec4 LightPosition; 
uniform vec4 Light1Position;
uniform vec3 EyePosition;
uniform float Shininess; 
uniform int shader_flag;
out vec4 fN; 
out vec4 fE; 
out vec4 fL; 
out vec4 fL1; 
out vec2 texCoord;

void main() 
{ 
		color_data_to_fshader = vColor;
		fN = vColor; 
		fE = vec4(EyePosition - vec3(vPosition.x,vPosition.y,vPosition.z),0.0); 
		//  Light defined in world coordinates 
		fL = (LightPosition - vPosition).xyzw; 
		//fL = LightPosition.xyzw;
		fL1 = (Light1Position - vPosition).xyzw; 
		//fL1 = Light1Position.xyzw;
		gl_Position = projection_type*viewing_object*vPosition; 
		gl_PointSize = 5.0;
		texCoord = vTexCoord;
}
