#define GLEW_STATIC

#include "Angel.h"
#include <math.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <sstream>
using namespace std;
void
bufferGenerator(struct vec4 polygonPoints[],int polyPoints_size, struct vec4 colorPonts[],int colorPoints_size, struct mat4 , struct mat4);
GLuint program;
int multiplicationFactor = 0;
void create_object (int , int);
vector<vec4> colors , points ;
vector<vec3> normals;
mat4 transformed_matrix, scaling_matrix, translating_matrix;
float theta[3] = {0.0 , 0.0 , 0.0} , scale_by = 1.0 , translate_by;
float theta_delta = 1 , scale_delta = 0.1 , translate_delta = 0.1;
vector<vec4> vertices , faces;
vec4 location_eye = vec4(0.0 , 0.0 , 1.5 , 0.0) , at_model = vec4(0.0 , 0.0 , 0.0 , 0.0) , up_axis = vec4(0.0 , 1.0 , 0.0 , 0.0);
vec4 normalized_value;
void split(string inText , char space);
vec3 vector1 , centroid_value;
mat4 projection_type , viewing_object;
float minX , minY , minZ , maxX , maxY , maxZ;
float min_values[3] , max_values[3];
void find_min(int , int); void find_max(int , int);
float range_value , get_max_value;
void get_range();
float eye_x , eye_y , eye_z, light_x , light_y , light_z , light1_x , light1_y , light1_z;
float angle = 90 , height = 0.0 , radius = 3.5 , theta_light = 90, light_height = 0.0, light_radius = 1.5;
float angle_delta = 1 , height_delta = 0.5 , radius_delta = 0.1 , theta_light_delta = 3;
int color_flag = 0;
GLuint fb;
void onclick_diffuse_update(int);
int faces1_size , faces2_size , faces3_size;
vec4 material_diffuse1 = vec4(1.0 , 0.0 , 0.0 , 1.0);
vec4 material_diffuse2 = vec4(0.0 , 1.0 , 0.0 , 1.0);
vec4 material_diffuse3 = vec4(0.0 , 0.0 , 1.0 , 1.0);
vec4 material_ambience = vec4(0.75164, 0.60648, 0.2264, 1.0);
vec4 material_specular = vec4(1.0, 1.0, 1.0, 1.0);

vec4 light1_diffuse = vec4(0.8 , 0.8 , 0.8 , 0.0);
vec4 light1_ambience = vec4(0.2 , 0.2 , 0.2 , 0.0);
vec4 light1_specular = vec4(1.0, 1.0, 1.0 , 0.0);
vec4 light1_pos = vec4(0.0 , 0.0 , 2.0 , 0.0);


GLfloat shine = 100.0;

vec4 diffuse0 , diffuse1;
vec4 ambient1 = light1_ambience * material_ambience;
vec4 specular1 = vec4(1.0, 1.0, 1.0 , 0.0);

void quad( int a, int b, int c )
{
        points.push_back(vertices[a]);
        points.push_back(vertices[b]);
        points.push_back(vertices[c]);

        vec3 get_n = normalize(cross((vertices[b] - vertices[a]),(vertices[c] - vertices[a])));
        normals[a] += get_n;
        normals[b] += get_n;
        normals[c] += get_n;

}


void construct_cube () {

    for(int i=0 ; i<faces.size() ; i++) {
        quad( (int)(faces[i].x-1) , (int)(faces[i].y-1), (int)(faces[i].z-1) );
    }
    vec4 normal_data;
    for(int i=0 ; i<faces.size() ; i++) {
        normal_data = normalize(normals[(int)(faces[i].x-1)]);
        normal_data.w = 0.0;
        colors.push_back(normal_data);

        normal_data = normalize(normals[(int)(faces[i].y-1)]);
        normal_data.w = 0.0;
        colors.push_back(normal_data);

        normal_data = normalize(normals[(int)(faces[i].z-1)]);
        normal_data.w = 0.0;
        colors.push_back(normal_data);
    }
}

void change_diffuse(int diffuse_flag) {
    if(diffuse_flag == 1) {
        diffuse1 = light1_diffuse * material_diffuse1;
    }
    else if(diffuse_flag == 2) {
        diffuse1 = light1_diffuse * material_diffuse2;
    }
    else if(diffuse_flag == 3) {
        diffuse1 = light1_diffuse * material_diffuse3;
    }

    GLint uniform_diffuse1 = glGetUniformLocation(program, "DiffuseProduct1");
    glUniform4f(uniform_diffuse1 , diffuse1.x , diffuse1.y , diffuse1.z , diffuse1.w);
}

void
display()
{
    glClear( GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT );     // clear the window
    glClearColor(0.0 , 0.0 , 0.0 , 0.0);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    eye_x = radius * cos(angle*M_PI/180.0);
    eye_y = height;
    eye_z = radius * sin(angle*M_PI/180.0);
    location_eye = vec4(eye_x , eye_y , eye_z , 1.0);
    viewing_object = LookAt(location_eye , at_model , up_axis);

    light1_pos = vec4(eye_x , eye_y , eye_z , 0.0);

    projection_type = Perspective(82.0 , 1.0 , 0.1 , 15);

    vec4 colors_vec_value[colors.size()];
    vec4 points_vec_value[points.size()];
    copy(points.begin(),points.end(),points_vec_value);
    copy(colors.begin(),colors.end(),colors_vec_value);

    bufferGenerator(points_vec_value , sizeof(points_vec_value) , colors_vec_value , sizeof(colors_vec_value), viewing_object , projection_type);
    GLint uniform1_color_flag = glGetUniformLocation(program, "color_flag");
    glUniform1i(uniform1_color_flag , 0);
    change_diffuse(1);
    glDrawArrays( GL_TRIANGLES, 0, faces1_size*3 );
    change_diffuse(2);
    glDrawArrays( GL_TRIANGLES, faces1_size*3,  faces2_size*3 );
    change_diffuse(3);
    glDrawArrays( GL_TRIANGLES, faces1_size*3 + faces2_size*3,  faces3_size * 3);

    glutPostRedisplay();
    glutSwapBuffers();
}

void render_function () {
    GLuint color_rb;
    GLuint depth_rb;

   //RGBA8 RenderBuffer, 24 bit depth RenderBuffer, 512x512
   glGenFramebuffers(1, &fb);
   glBindFramebuffer(GL_FRAMEBUFFER, fb);

   //Create and attach a color buffer
   glGenRenderbuffers(1, &color_rb);

   //We must bind color_rb before we call glRenderbufferStorage
   glBindRenderbuffer(GL_RENDERBUFFER, color_rb);

   //The storage format is RGBA8
   glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, 512, 512);

   //Attach color buffer to FBO
   glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                                 GL_RENDERBUFFER, color_rb);

   //-------------------------
   glGenRenderbuffers(1, &depth_rb);
   glBindRenderbuffer(GL_RENDERBUFFER, depth_rb);
   glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);

   //-------------------------
   //Attach depth buffer to FBO
   glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
						     GL_RENDERBUFFER, depth_rb);

}

void
init( void )
{
    program = InitShader( "vshader21.glsl", "fshader21.glsl" );
                          
    render_function();

}

void initializeVectors(int start_position , int end_position){
    for(int i=0 ; i<vertices.size() ; i++)
        normals.push_back(vec3(0.0 , 0.0 , 0.0));
    construct_cube();
    create_object(start_position , end_position);
}

void create_object (int start_position , int end_position) {

    find_max(start_position , end_position);
    find_min(start_position , end_position);

    centroid_value = vec3((minX+maxX)/2 , (minY+maxY)/2 , (minZ+maxZ)/2);

    translating_matrix = Translate(-(centroid_value.x + (maxX - minX) * multiplicationFactor * 1.7), -centroid_value.y, -centroid_value.z);

    get_range();
    scaling_matrix = Scale(vec3((1.0/range_value) , (1.0/range_value) , (1.0/range_value)));
    transformed_matrix = scaling_matrix * translating_matrix ;

    for(int i=start_position ; i<end_position ; i++)
        points[i] = transformed_matrix * points[i];
}

void find_min(int start_position , int end_position) {
    minX = 0.0 ; minY = 0.0 ; minZ = 0.0;
        minX = points[start_position].x;
        minY = points[start_position].y;
        minZ = points[start_position].z;
        for(int i = start_position + 1 ; i < end_position ; i++) {
            if(points[i].x < minX)
                minX = points[i].x;
            if(points[i].y < minY)
                minY = points[i].y;
            if(points[i].z < minZ)
                minZ = points[i].z;
        }
}

void find_max(int start_position , int end_position) {
    maxX = 0.0 ; maxY = 0.0 ; maxZ = 0.0;
        maxX = points[start_position].x;
        maxY = points[start_position].y;
        maxZ = points[start_position].z;
        for(int i = start_position + 1 ; i < end_position ; i++) {
            if(points[i].x > maxX)
                maxX = points[i].x;
            if(points[i].y > maxY)
                maxY = points[i].y;
            if(points[i].z > maxZ)
                maxZ = points[i].z;
        }
}

void get_range() {
    range_value=0.0;
    range_value = maxX - minX;
    if((maxY - minY) > (maxX - minX) && (maxY - minY) > (maxZ - minZ)){
        range_value = maxY - minY;
    }
    else if((maxZ - minZ) > (maxX - minX) && (maxZ - minZ) > (maxY - minY)) {
        range_value = maxZ - minZ;
    }
}

void keyboard_function( unsigned char key, int x, int y )
{
        switch ( key ) {
        case 'q': exit( EXIT_SUCCESS ); break;
        case 'x': angle += angle_delta;
                  if(angle > 360.0)
                    angle = 0.0;
                  break;
        case 's': angle -= angle_delta;
                  if(angle < -360.0)
                    angle = 0.0;
                  break;
        case 'y': height += height_delta;
                  break;
        case 'h': height -= height_delta;
                  break;
        case 'z': radius += radius_delta;
                  break;
        case 'a': radius -= radius_delta;
                  if(radius < 1.0)
                    radius = 1.0;
                  break;
        case 'r': angle = 90.0 ; height = 0.0 ; radius = 3.5;
                  material_diffuse1 = vec4(1.0 , 0.0 , 0.0 , 1.0);
                  material_diffuse2 = vec4(0.0 , 1.0 , 0.0 , 1.0);
                  material_diffuse3 = vec4(0.0 , 0.0 , 1.0 , 1.0);
                  break;
        }
        glutPostRedisplay();
}

void
bufferGenerator(struct vec4 polygonPoints[],int polyPoints_size, struct vec4 colorPonts[],int colorPoints_size, struct mat4 viewing_object , struct mat4 projection_type) {

    GLuint buffer_name_polygon;
    glGenBuffers( 1, &buffer_name_polygon );
    glBindBuffer( GL_ARRAY_BUFFER, buffer_name_polygon );
    glBufferData( GL_ARRAY_BUFFER, polyPoints_size, polygonPoints, GL_STATIC_DRAW );

    GLuint loc = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 4, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );

    GLuint buffer_name_color;
    glGenBuffers( 1, &buffer_name_color );
    glBindBuffer( GL_ARRAY_BUFFER, buffer_name_color );
    glBufferData( GL_ARRAY_BUFFER, colorPoints_size, colorPonts, GL_STATIC_DRAW );

    GLuint loc_color = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( loc_color );
    glVertexAttribPointer( loc_color, 4, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );

    GLint uniform_m_transform_vo = glGetUniformLocation(program, "viewing_object");
    glUniformMatrix4fv(uniform_m_transform_vo , 1 , GL_TRUE , &viewing_object[0][0]);

    GLint uniform_m_transform_pt = glGetUniformLocation(program, "projection_type");
    glUniformMatrix4fv(uniform_m_transform_pt , 1 , GL_TRUE , &projection_type[0][0]);


    vec4 ambient1 = light1_ambience * material_ambience;
    GLint uniform_ambient1 = glGetUniformLocation(program, "AmbientProduct1");
    glUniform4f(uniform_ambient1 , ambient1.x , ambient1.y , ambient1.z , ambient1.w);


    GLint uniform_spec1 = glGetUniformLocation(program, "SpecularProduct1");
    glUniform4f(uniform_spec1 , specular1.x , specular1.y , specular1.z , specular1.w);

    GLint uniform_shine = glGetUniformLocation(program, "Shininess");
    glUniform1f(uniform_shine , shine);


    GLint uniform_light1 = glGetUniformLocation(program, "Light1Position");
    glUniform4f(uniform_light1 , light1_pos.x , light1_pos.y , light1_pos.z , light1_pos.w);

    GLint uniform_eye_loc = glGetUniformLocation(program, "EyePosition");
    glUniform3f(uniform_eye_loc , location_eye.x , location_eye.y , location_eye.z);

}

void onclick_diffuse_update (int option) {
    vec4 onclick_diffuse = vec4(0.0 , 0.0 , 0.0 , 1.0);
    if(option ==  1){
        onclick_diffuse =  vec4(0.0 , 0.0 , 10.0 / 255.0 , 1.0);
    }
    else if(option == 2){
        onclick_diffuse = vec4(0.0 , 0.0 , 20.0 / 255.0 , 1.0);
    }
    else if(option == 3){
        onclick_diffuse = vec4(0.0 , 0.0 , 30.0 / 255.0 , 1.0);
    }
    GLint uniform_diffuse_onclick = glGetUniformLocation(program, "uniform_diffuse_onclick");
    glUniform4f(uniform_diffuse_onclick , onclick_diffuse.x , onclick_diffuse.y , onclick_diffuse.z , onclick_diffuse.w);
}

void mouse(int btn, int state, int x, int y)
{
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN) {
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER , fb);
        GLint uniform1_color_flag = glGetUniformLocation(program, "color_flag");
        glUniform1i(uniform1_color_flag , 1);

        onclick_diffuse_update(1);
        glDrawArrays( GL_TRIANGLES, 0, faces1_size*3 );

        onclick_diffuse_update(2);
        glDrawArrays( GL_TRIANGLES, faces1_size*3,  faces2_size*3 );

        onclick_diffuse_update(3);
        glDrawArrays( GL_TRIANGLES, faces1_size*3 + faces2_size*3,  faces3_size * 3);

        unsigned char pixels[4];
        glBindFramebuffer(GL_READ_FRAMEBUFFER, fb);
        glReadPixels(x, glutGet(GLUT_WINDOW_WIDTH) - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);
        switch((int)pixels[2]) {
            case 10:
                material_diffuse1 = vec4(rand()%100/100.0 , rand()%100/100.0 , rand()%100/100.0 , 1.0);
                break;
            case 20:
                material_diffuse2 = vec4(rand()%100/100.0 , rand()%100/100.0 , rand()%100/100.0 , 1.0);
                break;
            case 30:
                material_diffuse3 = vec4(rand()%100/100.0 , rand()%100/100.0 , rand()%100/100.0 , 1.0);
                break;
        }
        glutPostRedisplay();
    }
}


void getInput(string input_file) {
	string inText;
    vertices.clear();
    faces.clear();
    normals.clear();
	ifstream reader(input_file.c_str());
	if(!reader) {
		cout<<"\n Error opening the file";
	}
	else {
		while(!reader.eof()) {
			getline(reader,inText);
			if(inText[0] == 'v') {
				split(inText,' ');
				vertices.push_back(vector1);
			}
			else if(inText[0] == 'f') {
				split(inText,' ');
				faces.push_back(vector1);
			}
		}
	}
}



void split(string inText , char space)
{
	int position = inText.find(space,2);
	int i=2;
	int iterating_pointer = 0;
	float temp[3];
	while(iterating_pointer<2)
	{
		temp[iterating_pointer] = ::atof((inText.substr(i, position)).c_str());
		i=++position;
		position=inText.find(space,i);
		iterating_pointer++;
	}
	temp[2] = ::atof((inText.substr(i, inText.size())).c_str());
	vector1 = vec3(temp[0] , temp[1] , temp[2]);
}



int window_id;
int
main( int argc, char **argv )
{
    printf("\n Once the program is up and running : ");
    printf("\n The default value is set at Perspective With Objects in RGB");
    printf("\n To change - Left click of mouse button will change the color of the object.");
    printf("\n key press 'x' : Increases the angle to rotate around the object");
    printf("\n key press 's' : Decreases the angle to rotate around the object");
    printf("\n key press 'y' : Increases the height of the camera");
    printf("\n key press 'h' : Decreases the height of the camera");
    printf("\n key press 'z' : The camera goes away from the object");
    printf("\n key press 'a' : The camera goes near to the object");
    printf("\n key press 'r' : Resets to default values");
    printf("\n key press 'q' : Quits from output window\n\n");


    glutInit( &argc, argv );
#ifdef __APPLE__
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA );
#else
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
#endif
    glutInitWindowPosition(100,100);
    glutInitWindowSize( 500, 500 );

    window_id = glutCreateWindow( "assignment 8" );

#ifndef __APPLE__
    GLenum err = glewInit();
    if (GLEW_OK != err)
      fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
#endif
	getInput("sphere.smf");
	faces1_size = faces.size();
	multiplicationFactor = -1;
	initializeVectors(0 , faces1_size * 3);

	getInput("bunny.smf");
	faces2_size = faces.size();
	multiplicationFactor = 0;
	initializeVectors((faces1_size * 3) , ((faces1_size + faces2_size) * 3));

	getInput("pot.smf");
	faces3_size = faces.size();
	multiplicationFactor = 1;
	initializeVectors(((faces1_size + faces2_size) * 3) , ((faces1_size + faces2_size + faces3_size) * 3));


    init();
    glutKeyboardFunc( keyboard_function );
    glutMouseFunc(mouse);
    glutDisplayFunc(display);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}
