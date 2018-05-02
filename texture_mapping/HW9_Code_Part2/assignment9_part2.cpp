#define GLEW_STATIC
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "../include/Angel.h"
#include <math.h>
#include <sstream>
using namespace std;
using namespace std;
void
bufferGenerator(struct vec4 polygonPoints[],int polyPoints_size, struct vec4 colorPonts[],int colorPoints_size, struct mat4 , struct mat4);
GLuint program;
void create_object ();
vector<vec4> colors , points ;
vector<vec3> normals;
mat4 transformed_matrix, scaling_matrix, translating_matrix;
float theta[3] = {0.0 , 0.0 , 0.0} , scale_by = 1.0 , translate_by;
float theta_delta = 1 , scale_delta = 0.1 , translate_delta = 0.1;
vector<vec4> vertices , faces;
vec4 location_eye = vec4(0.0 , 0.0 , 3.0 , 0.0) , at_model = vec4(0.0 , 0.0 , 0.0 , 0.0) , up_axis = vec4(0.0 , 1.0 , 0.0 , 0.0);
vec4 normalized_value;
void split(string inText , char space);
vec3 vector1 , centroid_value;
mat4 projection_type , viewing_object;
float minX , minY , minZ , maxX , maxY , maxZ;
float min_values[3] , max_values[3];
void find_min(); void find_max();
float range_value , get_max_value;
void get_range();
float eye_x , eye_y , eye_z, light_x , light_y , light_z , light1_x , light1_y , light1_z;
float angle = 90 , height = 0.0 , radius = 3.0, theta_light = 90, light_height = 0.0, light_radius = 2.0;
float angle_delta = 1 , height_delta = 0.5 , radius_delta = 0.1 , theta_light_delta = 3;
int projection_flag = 1;
int shader_flag = 1;

vec4 material_diffuse = vec4(0.24725, 0.1995, 0.0745, 1.0);
vec4 material_ambience = vec4(0.75164, 0.60648, 0.2264, 1.0);
vec4 material_specular = vec4(1.0, 1.0, 1.0, 1.0);

vec4 light1_diffuse = vec4(0.8 , 0.8 , 0.8 , 0.0);
vec4 light1_ambience = vec4(0.2 , 0.2 , 0.2 , 0.0);
vec4 light1_specular = vec4(1.0, 1.0, 1.0 , 0.0);
vec4 light1_pos = vec4(0.0 , 0.0 , 2.0 , 0.0);

vec4 light_diffuse = vec4(0.8 , 0.8 , 0.8 , 0.0);
vec4 light_ambience = vec4(0.2 , 0.2 , 0.2 , 0.0);
vec4 light_specular = vec4(1.0, 1.0, 1.0 , 0.0);
vec4 light0_pos;
vec4 specular0 = vec4(1.0, 1.0, 1.0 , 0.0);
GLfloat shine = 100.0;


vec4 diffuse1 = light_diffuse * material_diffuse;
vec4 ambient1 = light_ambience * material_ambience;
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
        vec4 temporay_var = normals[(int)(faces[i].x-1)];

        normal_data = normalize(normals[(int)(faces[i].y-1)]);
        normal_data.w = 0.0;
        colors.push_back(normal_data);

        normal_data = normalize(normals[(int)(faces[i].z-1)]);
        normal_data.w = 0.0;
        colors.push_back(normal_data);
    }
}

void
display()
{
    glClearColor(0.0 , 0.0 , 0.0 , 0.0);
    glClear( GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT );     // clear the window

    eye_x = radius * cos(angle*M_PI/180.0);
    eye_y = height;
    eye_z = radius * sin(angle*M_PI/180.0);
    location_eye = vec4(eye_x , eye_y , eye_z , 1.0);
    viewing_object = LookAt(location_eye , at_model , up_axis);

    light_x = light_radius * cos(theta_light*M_PI/180.0);
    light_y = light_height;
    light_z = light_radius * sin(theta_light*M_PI/180.0);
    light0_pos = vec4(eye_x , eye_y , eye_z , 1.0);

    light1_pos = vec4(light_x , light_y , light_z , 1.0);

    if(projection_flag == 1)
        projection_type = Perspective(82.0 , 1.0 , 0.1 , 15);
    else if(projection_flag == 2)
        projection_type = Ortho(-1.0 , 1.0 , -1.0 , 1.0 , 0.01 , 10.0);

    vec4 colors_vec_value[colors.size()];
    vec4 points_vec_value[points.size()];
    copy(points.begin(),points.end(),points_vec_value);
    copy(colors.begin(),colors.end(),colors_vec_value);

    bufferGenerator(points_vec_value , sizeof(points_vec_value) , colors_vec_value , sizeof(colors_vec_value), viewing_object , projection_type);
    glDrawArrays( GL_TRIANGLES, 0, points.size() );

    glutSwapBuffers();
}


void
init( void )
{
    for(int i=0 ; i<vertices.size() ; i++)
        normals.push_back(vec3(0.0 , 0.0 , 0.0));
    construct_cube();
    program = InitShader( "vshader21.glsl",
                          "fshader21.glsl" );
    create_object();
}

void create_object () {

    find_max();
    find_min();
    centroid_value = vec3((minX+maxX)/2 , (minY+maxY)/2 , (minZ+maxZ)/2);
    translating_matrix = Translate(vec3(-centroid_value.x , -centroid_value.y , -centroid_value.z));
    get_range();
    scaling_matrix = Scale(vec3((1.0/range_value) , (1.0/range_value) , (1.0/range_value)));
    transformed_matrix = scaling_matrix * translating_matrix ;

    for(int i=0 ; i<points.size(); i++)
        points[i] = transformed_matrix * points[i];
}

void find_min() {
    minX = points[0].x;
    minY = points[0].y;
    minZ = points[0].z;
    for(int i=1 ; i<points.size() ; i++) {
        if(points[i].x < minX)
            minX = points[i].x;
        if(points[i].y < minY)
            minY = points[i].y;
        if(points[i].z < minZ)
            minZ = points[i].z;
    }
}

void find_max() {
    maxX = points[0].x;
    maxY = points[0].y;
    maxZ = points[0].z;
    for(int i=1 ; i<points.size() ; i++) {
        if(points[i].x > maxX)
            maxX = points[i].x;
        if(points[i].y > maxY)
            maxY = points[i].y;
        if(points[i].z > maxZ)
            maxZ = points[i].z;
    }
}

void get_range() {
    get_max_value = maxX;
    range_value = maxX - minX;
    if(maxY > get_max_value && maxY > maxZ){
        get_max_value = maxY;
        range_value = maxY - minY;
    }
    if(maxZ > get_max_value && maxZ > maxY) {
        get_max_value = maxZ;
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
        case 'r': angle = 90.0 ; height = 0.0 ; radius = 3.0; projection_flag = 1;
                  break;
        case 'l': theta_light += theta_light_delta;
                  if(theta_light > 360.0)
                    theta_light = 0.0;
                  break;
        case 'o': theta_light -= theta_light_delta;
                  if(theta_light < -360.0)
                    theta_light = 0.0;
                  break;
        case 'k': light_height += height_delta;
                  break;
        case 'i': light_height -= height_delta;
                  break;
        case 'j': light_radius += radius_delta;
                  if(light_radius < 1.0)
                    light_radius = 1.0;
                  break;
        case 'u': light_radius -= radius_delta;
                  if(light_radius < 1.0)
                    light_radius = 1.0;
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

    vec4 diffuse0 = light_diffuse * material_diffuse;
    vec4 ambient0 = light_ambience * material_ambience;
    GLint uniform_ambient = glGetUniformLocation(program, "AmbientProduct");
    glUniform4f(uniform_ambient , ambient0.x , ambient0.y , ambient0.z , ambient0.w);

    GLint uniform_diffuse = glGetUniformLocation(program, "DiffuseProduct");
    glUniform4f(uniform_diffuse , diffuse0.x , diffuse0.y , diffuse0.z , diffuse0.w);

    GLint uniform_spec = glGetUniformLocation(program, "SpecularProduct");
    glUniform4f(uniform_spec , specular0.x , specular0.y , specular0.z , specular0.w);

    //light1_pos = viewing_object * light1_pos;
    vec4 diffuse1 = light1_diffuse * material_diffuse;
    vec4 ambient1 = light1_ambience * material_ambience;
    GLint uniform_ambient1 = glGetUniformLocation(program, "AmbientProduct1");
    glUniform4f(uniform_ambient1 , ambient1.x , ambient1.y , ambient1.z , ambient1.w);

    GLint uniform_diffuse1 = glGetUniformLocation(program, "DiffuseProduct1");
    glUniform4f(uniform_diffuse1 , diffuse1.x , diffuse1.y , diffuse1.z , diffuse1.w);

    GLint uniform_spec1 = glGetUniformLocation(program, "SpecularProduct1");
    glUniform4f(uniform_spec1 , specular1.x , specular1.y , specular1.z , specular1.w);

    GLint uniform_shine = glGetUniformLocation(program, "Shininess");
    glUniform1f(uniform_shine , shine);

    vec4 light_pos = light0_pos;
    GLint uniform_light = glGetUniformLocation(program, "LightPosition");
    glUniform4f(uniform_light , light_pos.x , light_pos.y , light_pos.z , light_pos.w);

    GLint uniform_light1 = glGetUniformLocation(program, "Light1Position");
    glUniform4f(uniform_light1 , light1_pos.x , light1_pos.y , light1_pos.z , light1_pos.w);

    GLint uniform_eye_loc = glGetUniformLocation(program, "EyePosition");
    glUniform3f(uniform_eye_loc , location_eye.x , location_eye.y , location_eye.z);

    GLint uniform_shader_flag = glGetUniformLocation(program, "shader_flag");
    glUniform1i(uniform_shader_flag , shader_flag);
}

void process_menu_events(int option) {
    switch (option) {
        case 1: projection_flag = 1;
                break;
        case 2: projection_flag = 2;
                break;
        case 5: light_diffuse = vec4(0.8 , 0.8 , 0.8 , 0.0);
                light_ambience = vec4(0.2 , 0.2 , 0.2 , 0.0);
                light_specular = vec4(1.0, 1.0, 1.0 , 0.0);
                break;
        case 6: light_diffuse = vec4(1.0 , 0.4 , 0.6 , 0.0);
                light_ambience = vec4(0.2 , 0.2 , 0.2 , 0.0);
                light_specular = vec4(1.0, 1.0, 1.0 , 0.0);
                break;
        case 7: material_diffuse = vec4(0.8, 0.8, 0.8 , 0.0);
                material_ambience = vec4(0.5, 0.5, 0.5 , 0.0);
                material_specular = vec4(1.0, 1.0, 1.0 , 0.0);
                break;
        case 8: material_diffuse = vec4(0.24725, 0.1995, 0.0745, 1.0);
                material_ambience = vec4(0.75164, 0.60648, 0.2264, 1.0);
                material_specular = vec4(1.0, 1.0, 1.0, 1.0);
                break;
        case 9: material_diffuse = vec4(0.0, 1.0, 1.0 , 0.0);
                material_ambience = vec4(0.0, 0.5, 0.5 , 0.0);
                material_specular = vec4(1.0, 1.0, 1.0 , 0.0);
                break;
    }
    glutPostRedisplay();
}

void getInput(string input_file) {
	string inText;

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
    printf("\n The default value is set at Perspective Gouroud and Gold material with white light");
    printf("\n To change - Right click of mouse button will show you a drop down menu containing \n Projection Type \n Shading Type \n Light Type \n Material Type");
    printf("\n On selecting any one from the menu you will be able to perform the following : ");
    printf("\n key press 'x' : Increases the angle to rotate around the object");
    printf("\n key press 's' : Decreases the angle to rotate around the object");
    printf("\n key press 'y' : Increases the height of the camera");
    printf("\n key press 'h' : Decreases the height of the camera");
    printf("\n key press 'z' : The camera goes away from the object");
    printf("\n key press 'a' : The camera goes near to the object");
    printf("\n key press 'l' : Increases the angle to rotate around the object");
    printf("\n key press 'o' : Decreases the angle to rotate around the object");
    printf("\n key press 'k' : Increases the height of the light");
    printf("\n key press 'i' : Decreases the height of the light");
    printf("\n key press 'j' : The light goes away from the object");
    printf("\n key press 'u' : The light goes near to the object");
    printf("\n key press 'r' : Resets to default values");
    printf("\n key press 'q' : Quits from output window");

if(argv[1] == NULL)
	getInput("bunny.smf");
else
	getInput(argv[1]);

    glutInit( &argc, argv );
#ifdef __APPLE__
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA );
#else
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
#endif
    glutInitWindowPosition(100,100);
    glutInitWindowSize( 500, 500 );

    window_id = glutCreateWindow( "assignment 9 Part 2" );

#ifndef __APPLE__
    GLenum err = glewInit();
    if (GLEW_OK != err)
      fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
#endif

    init();
    glutKeyboardFunc( keyboard_function );
    int window_menu , projection_menu , shading_menu , light_menu , material_menu;
    projection_menu = glutCreateMenu(process_menu_events);
    glutAddMenuEntry("Perspective",1);
    glutAddMenuEntry("Parallel",2);

    light_menu = glutCreateMenu(process_menu_events);
    glutAddMenuEntry("White light",5);
    glutAddMenuEntry("Colored light",6);

    material_menu = glutCreateMenu(process_menu_events);
    glutAddMenuEntry("White Shiny",7);
    glutAddMenuEntry("Gold",8);
    glutAddMenuEntry("Cyan",9);

    glutCreateMenu(process_menu_events);
    glutAddSubMenu("Projection Type", projection_menu);
    glutAddSubMenu("Shading", shading_menu);
    glutAddSubMenu("Light", light_menu);
    glutAddSubMenu("Material", material_menu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutDisplayFunc(display);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}


