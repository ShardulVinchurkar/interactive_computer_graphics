#version 130

//vertex shader 
in vec4 vPosition; 
in vec4 vColor; 
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

void main() 
{ 
	if(shader_flag == 0) {
		// Transform vertex  position into eye coordinates 
		vec4 pos = (viewing_object * vPosition).xyzw; 
		//Light defined in camera frame 
		vec4 L = normalize( LightPosition.xyzw - pos ); 
		vec4 L1 = normalize( LightPosition.xyzw - pos ); 
		vec4 E = normalize( -pos ); 
		vec4 H = normalize( L + E );
		vec4 H1 = normalize( L1 + E );
		
		// Transform vertex normal into eye coordinates 
		vec4 N = normalize( viewing_object* vColor).xyzw; 
		// Compute terms in the illumination equation 
		vec4 ambient = AmbientProduct; 
		float dTerm = max( dot(L, N), 0.0 ); 
		vec4  diffuse = dTerm*DiffuseProduct; 
		float sTerm = pow( max(dot(N, H), 0.0), Shininess ); 
		vec4  specular = sTerm * SpecularProduct; 
		if( dot(L, N) < 0.0 )  specular = vec4(0.0, 0.0, 0.0, 0.0);  
		gl_Position = projection_type * viewing_object * vPosition;
		
		
		// Transform vertex normal into eye coordinates 
		// Compute terms in the illumination equation 
		vec4 ambient1 = AmbientProduct1; 
		float dTerm1 = max( dot(L1, N), 0.0 ); 
		vec4  diffuse1 = dTerm1*DiffuseProduct1; 
		float sTerm1 = pow( max(dot(N, H1), 0.0), Shininess ); 
		vec4  specular1 = sTerm1 * SpecularProduct1; 
		if( dot(L1, N) < 0.0 )  specular1 = vec4(0.0, 0.0, 0.0, 0.0);  
		//gl_Position = projection_type * viewing_object * vPosition;
		
		color_data_to_fshader = ambient + diffuse + specular + ambient1 + diffuse1 + specular1; 
		//color_data_to_fshader = vColor;
	}
	else if(shader_flag == 1) {
		fN = vColor; 
		fE = vec4(EyePosition - vec3(vPosition.x,vPosition.y,vPosition.z),0.0); 
		//  Light defined in world coordinates 
				fL = vec4(LightPosition.x,LightPosition.y,LightPosition.z,LightPosition.w); 
				fL1 = vec4(Light1Position.x,Light1Position.y,Light1Position.z,Light1Position.w); 
		gl_Position = projection_type*viewing_object*vPosition; 
	}
}
