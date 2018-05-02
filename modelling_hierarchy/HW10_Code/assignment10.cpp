#define GLEW_STATIC
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "Angel.h"
#include <math.h>
#include <sstream>
using namespace std;
void
bufferGenerator(struct vec4 polygonPoints[],int polyPoints_size, struct vec4 colorPonts[],int colorPoints_size, struct mat4 , struct mat4);
GLuint program;
void create_object (int , int);
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
void find_min(int , int); void find_max(int , int);
float range_value , get_max_value;
void get_range();
float eye_x , eye_y , eye_z, light_x , light_y , light_z , light1_x , light1_y , light1_z;
float angle = 90 , height = 0.0 , radius = 3.0, theta_light = 90, light_height = 0.0, light_radius = 2.0;
float angle_delta = 1 , height_delta = 0.5 , radius_delta = 0.1 , theta_light_delta = 3;
int projection_flag = 1;
int shader_flag = 0;

vec4 material_diffuse = vec4(0.24725, 0.1995, 0.0745, 1.0);
vec4 material_ambience = vec4(0.75164, 0.60648, 0.2264, 1.0);
vec4 material_specular = vec4(1.0, 1.0, 1.0, 1.0);

vec4 light1_diffuse = vec4(0.8 , 0.8 , 0.8 , 1.0);
vec4 light1_ambience = vec4(0.2 , 0.2 , 0.2 , 1.0);
vec4 light1_specular = vec4(1.0, 1.0, 1.0 , 1.0);
vec4 light1_pos = vec4(0.0 , 0.0 , 2.0 , 1.0);

vec4 light_diffuse = vec4(0.8 , 0.8 , 0.8 , 1.0);
vec4 light_ambience = vec4(0.2 , 0.2 , 0.2 , 1.0);
vec4 light_specular = vec4(1.0, 1.0, 1.0 , 1.0);
vec4 light0_pos;
vec4 specular0 = vec4(1.0, 1.0, 1.0 , 1.0);
GLfloat shine = 100.0;


vec4 diffuse1 = light_diffuse * material_diffuse;
vec4 ambient1 = light_ambience * material_ambience;
vec4 specular1 = vec4(1.0, 1.0, 1.0 , 1.0);

int faces1_size , faces2_size , faces3_size , faces4_size , faces5_size , joint2_angle_counter;
void translate_object(float , float , float , int , int);
float end_effector_change , joint1_angle , joint2_angle;
void all_clear();
void initializeVectors(int , int);
void clear_function();
void rotate_joint_two();
void rotate_joint_one();

void quad( int a, int b, int c )
{
        points.push_back(vertices[a]);
        points.push_back(vertices[b]);
        points.push_back(vertices[c]);

        vec3 get_n = normalize(cross((vertices[b] - vertices[a]),(vertices[c] - vertices[a])));
        vec4 normalized_value = normalize(get_n);
        normalized_value.w = 0;
        colors.push_back(normalized_value);
        colors.push_back(normalized_value);
        colors.push_back(normalized_value);
}


void construct_cube () {

    for(int i=0 ; i<faces.size() ; i++) {
        quad( (int)(faces[i].x-1) , (int)(faces[i].y-1), (int)(faces[i].z-1) );
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
    light0_pos = vec4(light_x , light_y , light_z , 1.0);

    light1_pos = vec4(eye_x , eye_y , eye_z , 1.0);

    if(projection_flag == 1)
        projection_type = Perspective(82.0 , 1.0 , 0.1 , 15);
    else if(projection_flag == 2)
        projection_type = Ortho(-1.0 , 1.0 , -1.0 , 1.0 , 0.01 , 10.0);

    vec4 colors_vec_value[colors.size()];
    vec4 points_vec_value[points.size()];
    copy(points.begin(),points.end(),points_vec_value);
    copy(colors.begin(),colors.end(),colors_vec_value);

    bufferGenerator(points_vec_value , sizeof(points_vec_value) , colors_vec_value , sizeof(colors_vec_value), viewing_object , projection_type);
    glDrawArrays( GL_TRIANGLES, 0 , faces1_size * 3);
    glDrawArrays( GL_TRIANGLES, (faces1_size * 3) , (faces2_size * 3));
    glDrawArrays( GL_TRIANGLES, ((faces1_size + faces2_size) * 3) , (faces3_size * 3));
    glDrawArrays( GL_TRIANGLES, ((faces1_size + faces2_size + faces3_size) * 3) , (faces4_size * 3));
    glDrawArrays( GL_TRIANGLES, ((faces1_size + faces2_size + faces3_size + faces4_size) * 3) , (faces5_size * 3));

    glutSwapBuffers();
}


void
init( void )
{
    program = InitShader( "vshader21.glsl",
                          "fshader21.glsl" );
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

    translating_matrix = Translate(-centroid_value.x, -centroid_value.y, -centroid_value.z);

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
        case 'x': end_effector_change = 0.0;joint2_angle = 0.0;joint1_angle = 0.0;
                    angle += angle_delta;
                  if(angle > 360.0)
                    angle = 0.0;
                  break;
        case 's': end_effector_change = 0.0;joint2_angle = 0.0;joint1_angle = 0.0;
                 angle -= angle_delta;
                  if(angle < -360.0)
                    angle = 0.0;
                  break;
        case 'y': height += height_delta;
        end_effector_change = 0.0;joint2_angle = 0.0;joint1_angle = 0.0;
                  break;
        case 'h': height -= height_delta;
            end_effector_change = 0.0;joint2_angle = 0.0;joint1_angle = 0.0;
                  break;
        case 'z': radius += radius_delta;
                end_effector_change = 0.0;joint2_angle = 0.0;joint1_angle = 0.0;
                  break;
        case 'a': radius -= radius_delta;
                end_effector_change = 0.0;joint2_angle = 0.0;joint1_angle = 0.0;
                  if(radius < 1.0)
                    radius = 1.0;
                  break;
        case 'r': angle = 90.0 ; height = 0.0 ; radius = 3.0; projection_flag = 1;//joint2_angle = 0.0;joint1_angle = 0.0;
                    all_clear();
                  break;
        case 'l': theta_light += theta_light_delta;
                    end_effector_change = 0.0;joint2_angle = 0.0;joint1_angle = 0.0;
                  if(theta_light > 360.0)
                    theta_light = 0.0;
                  break;
        case 'o': theta_light -= theta_light_delta;
                end_effector_change = 0.0;joint2_angle = 0.0;joint1_angle = 0.0;
                  if(theta_light < -360.0)
                    theta_light = 0.0;
                  break;
        case 'k': light_height += height_delta;
                    end_effector_change = 0.0;joint2_angle = 0.0;joint1_angle = 0.0;
                  break;
        case 'i': light_height -= height_delta;
                    end_effector_change = 0.0;joint2_angle = 0.0;joint1_angle = 0.0;
                  break;
        case 'j': light_radius += radius_delta;
                    end_effector_change = 0.0;joint2_angle = 0.0;joint1_angle = 0.0;
                  if(light_radius < 1.0)
                    light_radius = 1.0;
                  break;
        case 'u': light_radius -= radius_delta;
                end_effector_change = 0.0;joint2_angle = 0.0;joint1_angle = 0.0;
                  if(light_radius < 1.0)
                    light_radius = 1.0;
                  break;
        case '1':
                end_effector_change = 0.1;joint1_angle = 0.0;joint2_angle = 0.0;

                find_min(((faces1_size + faces2_size + faces3_size + faces4_size) * 3) , ((faces1_size + faces2_size + faces3_size + faces4_size + faces5_size) * 3));
                find_max(((faces1_size + faces2_size + faces3_size) * 3) , ((faces1_size + faces2_size + faces3_size + faces4_size) * 3));

                if(minY < maxY)
                    translate_object(0.0 , end_effector_change , 0.0 ,((faces1_size + faces2_size + faces3_size + faces4_size) * 3) , ((faces1_size + faces2_size + faces3_size + faces4_size + faces5_size) * 3));
                else
                    translate_object(0.0 , 0.0 , 0.0 ,((faces1_size + faces2_size + faces3_size + faces4_size) * 3) , ((faces1_size + faces2_size + faces3_size + faces4_size + faces5_size) * 3));

                break;
        case '2':
                end_effector_change = -0.1;joint1_angle = 0.0;joint2_angle = 0.0;

                find_max(((faces1_size + faces2_size + faces3_size + faces4_size) * 3) , ((faces1_size + faces2_size + faces3_size + faces4_size + faces5_size) * 3));
                find_min(((faces1_size + faces2_size + faces3_size) * 3) , ((faces1_size + faces2_size + faces3_size + faces4_size) * 3));

                if(maxY > minY)
                    translate_object(0.0 , end_effector_change , 0.0 ,((faces1_size + faces2_size + faces3_size + faces4_size) * 3) , ((faces1_size + faces2_size + faces3_size + faces4_size + faces5_size) * 3));
                else
                    translate_object(0.0 , 0.0 , 0.0 ,((faces1_size + faces2_size + faces3_size + faces4_size) * 3) , ((faces1_size + faces2_size + faces3_size + faces4_size + faces5_size) * 3));

                break;
        case '3': if(joint2_angle_counter < 150) {
                joint2_angle = 1.0;end_effector_change = 0.0;joint1_angle = 0.0;
                rotate_joint_two();
                joint2_angle_counter++; }
                break;
        case '4': if(joint2_angle_counter > -150) {
                joint2_angle = -1.0;end_effector_change = 0.0;joint1_angle = 0.0;
                rotate_joint_two();
                joint2_angle_counter--; }
                break;
        case '5':
                joint1_angle = 1.0;end_effector_change = 0.0; joint2_angle = 0.0;
                rotate_joint_one();
                break;
        case '6':
                joint1_angle = -1.0;end_effector_change = 0.0; joint2_angle = 0.0;
                rotate_joint_one();
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
    glVertexAttribPointer( loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

    GLuint buffer_name_color;
    glGenBuffers( 1, &buffer_name_color );
    glBindBuffer( GL_ARRAY_BUFFER, buffer_name_color );
    glBufferData( GL_ARRAY_BUFFER, colorPoints_size, colorPonts, GL_STATIC_DRAW );

    GLuint loc_color = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( loc_color );
    glVertexAttribPointer( loc_color, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

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

void base_points() {
    vertices.push_back(vec3( -3.00000,-0.300000 , -1.50000));
    vertices.push_back(vec3( -3.00000,-0.300000 , 1.50000 ));
    vertices.push_back(vec3(  3.00000,-0.300000 , 1.50000 ));
    vertices.push_back(vec3(  3.00000,-0.300000 , -1.50000));
    vertices.push_back(vec3( -3.00000, 0.300000 , -1.50000));
    vertices.push_back(vec3(-3.00000 ,0.300000  , 1.50000 ));
    vertices.push_back(vec3( 3.00000 ,0.300000  , 1.50000 ));
    vertices.push_back(vec3( 3.00000 ,0.300000  , -1.50000));
    faces.push_back(vec3(1 ,  3 ,  2));
    faces.push_back(vec3(1 ,  4 ,  3));
    faces.push_back(vec3(8 ,  6 ,  7));
    faces.push_back(vec3(8 ,  5 ,  6));
    faces.push_back(vec3(1 ,  8 ,  4));
    faces.push_back(vec3(1 ,  5 ,  8));
    faces.push_back(vec3(2 ,  7 ,  6));
    faces.push_back(vec3(2 ,  3 ,  7));
    faces.push_back(vec3(1 ,  6 ,  5));
    faces.push_back(vec3(1 ,  2 ,  6));
    faces.push_back(vec3(4 ,  7 ,  3));
    faces.push_back(vec3(4 ,  8 ,  7));
}

void post_points() {
    vertices.push_back(vec3( 0.200000  , 1.00000  , 0.00000  ));
    vertices.push_back(vec3( 0.141421  , 1.00000  , 0.141421 ));
    vertices.push_back(vec3( 0.00000   , 1.00000  , 0.200000 ));
    vertices.push_back(vec3( -0.141421 , 1.00000  , 0.141421 ));
    vertices.push_back(vec3( -0.200000 , 1.00000  , 0.00000  ));
    vertices.push_back(vec3( -0.141421 , 1.00000  , -0.141421));
    vertices.push_back(vec3( 0.00000   , 1.00000  , -0.200000));
    vertices.push_back(vec3( 0.141421  , 1.00000  , -0.141421));
    vertices.push_back(vec3( 0.200000  , 1.00000  , 0.00000  ));
    vertices.push_back(vec3( 0.200000  , -1.00000 , 0.00000  ));
    vertices.push_back(vec3( 0.141421  , -1.00000 , 0.141421 ));
    vertices.push_back(vec3( 0.00000   , -1.00000 , 0.200000 ));
    vertices.push_back(vec3( -0.141421 , -1.00000 , 0.141421 ));
    vertices.push_back(vec3( -0.200000 , -1.00000 , 0.00000  ));
    vertices.push_back(vec3( -0.141421 , -1.00000 , -0.141421));
    vertices.push_back(vec3( 0.00000   , -1.00000 , -0.200000));
    vertices.push_back(vec3( 0.141421  , -1.00000 , -0.141421));
    vertices.push_back(vec3( 0.200000  , -1.00000 , 0.00000  ));
    vertices.push_back(vec3( 0.00000   , 1.00000  , 0.00000  ));
    vertices.push_back(vec3( 0.00000   , -1.00000 , 0.00000  ));
    faces.push_back(vec3( 1  , 2   , 19));
    faces.push_back(vec3( 2  , 3   , 19));
    faces.push_back(vec3( 3  , 4   , 19));
    faces.push_back(vec3( 4  , 5   , 19));
    faces.push_back(vec3( 5  , 6   , 19));
    faces.push_back(vec3( 6  , 7   , 19));
    faces.push_back(vec3( 7  , 8   , 19));
    faces.push_back(vec3( 8  , 9   , 19));
    faces.push_back(vec3( 10 , 20  , 11));
    faces.push_back(vec3( 11 , 20  , 12));
    faces.push_back(vec3( 12 , 20  , 13));
    faces.push_back(vec3( 13 , 20  , 14));
    faces.push_back(vec3( 14 , 20  , 15));
    faces.push_back(vec3( 15 , 20  , 16));
    faces.push_back(vec3( 16 , 20  , 17));
    faces.push_back(vec3( 17 , 20  , 18));
    faces.push_back(vec3( 1  , 10  , 11));
    faces.push_back(vec3( 1  , 11  , 2 ));
    faces.push_back(vec3( 2  , 11  , 12));
    faces.push_back(vec3( 2  , 12  , 3 ));
    faces.push_back(vec3( 3  , 12  , 13));
    faces.push_back(vec3( 3  , 13  , 4 ));
    faces.push_back(vec3( 4  , 13  , 14));
    faces.push_back(vec3( 4  , 14  , 5 ));
    faces.push_back(vec3( 5  , 14  , 15));
    faces.push_back(vec3( 5  , 15  , 6 ));
    faces.push_back(vec3( 6  , 15  , 16));
    faces.push_back(vec3( 6  , 16  , 7 ));
    faces.push_back(vec3( 7  , 16  , 17));
    faces.push_back(vec3( 7  , 17  , 8 ));
    faces.push_back(vec3( 8  , 17  , 18));
    faces.push_back(vec3( 8  , 18  , 9 ));
}

void link_one_points() {
    vertices.push_back(vec3( -3.00000,-0.500000 , -0.50000));
    vertices.push_back(vec3( -3.00000,-0.500000 , 0.50000 ));
    vertices.push_back(vec3(  3.00000,-0.500000 , 0.50000 ));
    vertices.push_back(vec3(  3.00000,-0.500000 , -0.50000));
    vertices.push_back(vec3( -3.00000, 0.500000 , -0.50000));
    vertices.push_back(vec3(-3.00000 ,0.500000  , 0.50000 ));
    vertices.push_back(vec3( 3.00000 ,0.500000  , 0.50000 ));
    vertices.push_back(vec3( 3.00000 ,0.500000  , -0.50000));
    faces.push_back(vec3(1 ,  3 ,  2));
    faces.push_back(vec3(1 ,  4 ,  3));
    faces.push_back(vec3(8 ,  6 ,  7));
    faces.push_back(vec3(8 ,  5 ,  6));
    faces.push_back(vec3(1 ,  8 ,  4));
    faces.push_back(vec3(1 ,  5 ,  8));
    faces.push_back(vec3(2 ,  7 ,  6));
    faces.push_back(vec3(2 ,  3 ,  7));
    faces.push_back(vec3(1 ,  6 ,  5));
    faces.push_back(vec3(1 ,  2 ,  6));
    faces.push_back(vec3(4 ,  7 ,  3));
    faces.push_back(vec3(4 ,  8 ,  7));
}

void link_two_points() {
    vertices.push_back(vec3( -3.00000,-0.500000 , -0.50000));
    vertices.push_back(vec3( -3.00000,-0.500000 , 0.50000 ));
    vertices.push_back(vec3(  3.00000,-0.500000 , 0.50000 ));
    vertices.push_back(vec3(  3.00000,-0.500000 , -0.50000));
    vertices.push_back(vec3( -3.00000, 0.500000 , -0.50000));
    vertices.push_back(vec3(-3.00000 ,0.500000  , 0.50000 ));
    vertices.push_back(vec3( 3.00000 ,0.500000  , 0.50000 ));
    vertices.push_back(vec3( 3.00000 ,0.500000  , -0.50000));
    faces.push_back(vec3(1 ,  3 ,  2));
    faces.push_back(vec3(1 ,  4 ,  3));
    faces.push_back(vec3(8 ,  6 ,  7));
    faces.push_back(vec3(8 ,  5 ,  6));
    faces.push_back(vec3(1 ,  8 ,  4));
    faces.push_back(vec3(1 ,  5 ,  8));
    faces.push_back(vec3(2 ,  7 ,  6));
    faces.push_back(vec3(2 ,  3 ,  7));
    faces.push_back(vec3(1 ,  6 ,  5));
    faces.push_back(vec3(1 ,  2 ,  6));
    faces.push_back(vec3(4 ,  7 ,  3));
    faces.push_back(vec3(4 ,  8 ,  7));
}

void end_effector_points() {
    vertices.push_back(vec3( 0.200000  / 10 , 0.30000  , 0.00000   / 10));
    vertices.push_back(vec3( 0.141421  / 10 , 0.30000  , 0.141421  / 10));
    vertices.push_back(vec3( 0.00000   / 10 , 0.30000  , 0.200000  / 10));
    vertices.push_back(vec3( -0.141421 / 10 , 0.30000  , 0.141421  / 10));
    vertices.push_back(vec3( -0.200000 / 10 , 0.30000  , 0.00000   / 10));
    vertices.push_back(vec3( -0.141421 / 10 , 0.30000  , -0.141421 / 10));
    vertices.push_back(vec3( 0.00000   / 10 , 0.30000  , -0.200000 / 10));
    vertices.push_back(vec3( 0.141421  / 10 , 0.30000  , -0.141421 / 10));
    vertices.push_back(vec3( 0.200000  / 10 , 0.30000  , 0.00000   / 10));
    vertices.push_back(vec3( 0.200000  / 10 , -0.30000 , 0.00000   / 10));
    vertices.push_back(vec3( 0.141421  / 10 , -0.30000 , 0.141421  / 10));
    vertices.push_back(vec3( 0.00000   / 10 , -0.30000 , 0.200000  / 10));
    vertices.push_back(vec3( -0.141421 / 10 , -0.30000 , 0.141421  / 10));
    vertices.push_back(vec3( -0.200000 / 10 , -0.30000 , 0.00000   / 10));
    vertices.push_back(vec3( -0.141421 / 10 , -0.30000 , -0.141421 / 10));
    vertices.push_back(vec3( 0.00000   / 10 , -0.30000 , -0.200000 / 10));
    vertices.push_back(vec3( 0.141421  / 10 , -0.30000 , -0.141421 / 10));
    vertices.push_back(vec3( 0.200000  / 10 , -0.30000 , 0.00000   / 10));
    vertices.push_back(vec3( 0.00000   / 10 , 0.30000  , 0.00000   / 10));
    vertices.push_back(vec3( 0.00000   / 10 , -0.30000 , 0.00000   / 10));
    faces.push_back(vec3( 1  , 2   , 19));
    faces.push_back(vec3( 2  , 3   , 19));
    faces.push_back(vec3( 3  , 4   , 19));
    faces.push_back(vec3( 4  , 5   , 19));
    faces.push_back(vec3( 5  , 6   , 19));
    faces.push_back(vec3( 6  , 7   , 19));
    faces.push_back(vec3( 7  , 8   , 19));
    faces.push_back(vec3( 8  , 9   , 19));
    faces.push_back(vec3( 10 , 20  , 11));
    faces.push_back(vec3( 11 , 20  , 12));
    faces.push_back(vec3( 12 , 20  , 13));
    faces.push_back(vec3( 13 , 20  , 14));
    faces.push_back(vec3( 14 , 20  , 15));
    faces.push_back(vec3( 15 , 20  , 16));
    faces.push_back(vec3( 16 , 20  , 17));
    faces.push_back(vec3( 17 , 20  , 18));
    faces.push_back(vec3( 1  , 10  , 11));
    faces.push_back(vec3( 1  , 11  , 2 ));
    faces.push_back(vec3( 2  , 11  , 12));
    faces.push_back(vec3( 2  , 12  , 3 ));
    faces.push_back(vec3( 3  , 12  , 13));
    faces.push_back(vec3( 3  , 13  , 4 ));
    faces.push_back(vec3( 4  , 13  , 14));
    faces.push_back(vec3( 4  , 14  , 5 ));
    faces.push_back(vec3( 5  , 14  , 15));
    faces.push_back(vec3( 5  , 15  , 6 ));
    faces.push_back(vec3( 6  , 15  , 16));
    faces.push_back(vec3( 6  , 16  , 7 ));
    faces.push_back(vec3( 7  , 16  , 17));
    faces.push_back(vec3( 7  , 17  , 8 ));
    faces.push_back(vec3( 8  , 17  , 18));
    faces.push_back(vec3( 8  , 18  , 9 ));
}

void clear_function () {
    vertices.clear();
    faces.clear();
    normals.clear();
}

void translate_object(float x , float y , float z , int start , int finish) {
    mat4 translate_to_position = Translate(x,y,z);
    for(int i = start ; i < finish ; i++)
        points[i] = translate_to_position * points[i];
}

void all_clear() {
    colors.clear();
    points.clear();
    joint2_angle_counter = 0;
    clear_function();
    base_points();
    faces1_size = faces.size();
    initializeVectors(0 , faces1_size * 3);
    translate_object(-0.6 , -0.7 , 0.0 , 0 , faces1_size * 3);
    clear_function();
    post_points();
    faces2_size = faces.size();
    initializeVectors((faces1_size * 3) , ((faces1_size + faces2_size) * 3));
    translate_object(-0.6 , -0.25 , 0.0 , (faces1_size * 3) , ((faces1_size + faces2_size) * 3));
    clear_function();
    link_one_points();
    faces3_size = faces.size();
    initializeVectors(((faces1_size + faces2_size) * 3) , ((faces1_size + faces2_size + faces3_size) * 3));
    translate_object( -0.2 , 0.33 , 0.0 , ((faces1_size + faces2_size) * 3) , ((faces1_size + faces2_size + faces3_size) * 3));
    clear_function();
    link_two_points();
    faces4_size = faces.size();
    initializeVectors(((faces1_size + faces2_size + faces3_size) * 3) , ((faces1_size + faces2_size + faces3_size + faces4_size) * 3));
    translate_object(0.7 , 0.499 , 0.0 ,((faces1_size + faces2_size + faces3_size) * 3) , ((faces1_size + faces2_size + faces3_size + faces4_size) * 3));
    clear_function();
    end_effector_points();
    faces5_size = faces.size();
    initializeVectors(((faces1_size + faces2_size + faces3_size + faces4_size) * 3) , ((faces1_size + faces2_size + faces3_size + faces4_size + faces5_size) * 3));
    translate_object(1.1 , 0.5 , 0.0 ,((faces1_size + faces2_size + faces3_size + faces4_size) * 3) , ((faces1_size + faces2_size + faces3_size + faces4_size + faces5_size) * 3));
}

void rotate_joint_one() {
    int start_index = ((faces1_size + faces2_size) * 3);
    int finish_index = ((faces1_size + faces2_size + faces3_size + faces4_size + faces5_size) * 3);
    find_max(((faces1_size + faces2_size) * 3) , ((faces1_size + faces2_size + faces3_size + faces4_size + faces5_size) * 3));
    find_min(((faces1_size + faces2_size) * 3) , ((faces1_size + faces2_size + faces3_size + faces4_size + faces5_size) * 3));

    centroid_value = vec3((minX+maxX)/2 , (minY+maxY)/2 , (minZ+maxZ)/2);

    mat4 translating_to_origin = Translate(-points[start_index].x, -points[start_index].y, -points[start_index].z);

    mat4 rotating_matrix = RotateY(joint1_angle);

    mat4 translate_back = Translate(points[start_index].x, points[start_index].y, points[start_index].z);

    mat4 trt_matrix = translate_back * rotating_matrix * translating_to_origin;

    for(int i = start_index ; i < finish_index ; i++)
        points[i] = trt_matrix * points[i];
}

void rotate_joint_two() {
    int start_index = ((faces1_size + faces2_size + faces3_size) * 3);
    int finish_index = ((faces1_size + faces2_size + faces3_size + faces4_size + faces5_size) * 3);
    find_max(((faces1_size + faces2_size + faces3_size) * 3) , ((faces1_size + faces2_size + faces3_size + faces4_size + faces5_size) * 3));
    find_min(((faces1_size + faces2_size + faces3_size) * 3) , ((faces1_size + faces2_size + faces3_size + faces4_size + faces5_size) * 3));

    centroid_value = vec3((minX+maxX)/2 , (minY+maxY)/2 , (minZ+maxZ)/2);

    mat4 translating_to_origin = Translate(-points[start_index].x, -points[start_index].y, -points[start_index].z);

    mat4 rotating_matrix = RotateY(joint2_angle);

    mat4 translate_back = Translate(points[start_index].x, points[start_index].y, points[start_index].z);

    mat4 trt_matrix = translate_back * rotating_matrix * translating_to_origin;

    for(int i = start_index ; i < finish_index ; i++)
        points[i] = trt_matrix * points[i];
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

    printf("\n key press '1' : Translates the end effector up");
    printf("\n key press '2' : Translates the end effector down");

    printf("\n key press '5 and 6' : Rotates the First link");
    printf("\n key press '3 and 4' : Rotates the second link\n\n");

clear_function();
base_points();
faces1_size = faces.size();
initializeVectors(0 , faces1_size * 3);
translate_object(-0.6 , -0.7 , 0.0 , 0 , faces1_size * 3);

clear_function();

post_points();
faces2_size = faces.size();
initializeVectors((faces1_size * 3) , ((faces1_size + faces2_size) * 3));
translate_object(-0.6 , -0.25 , 0.0 , (faces1_size * 3) , ((faces1_size + faces2_size) * 3));

clear_function();

link_one_points();
faces3_size = faces.size();
initializeVectors(((faces1_size + faces2_size) * 3) , ((faces1_size + faces2_size + faces3_size) * 3));
translate_object( -0.2 , 0.33 , 0.0 , ((faces1_size + faces2_size) * 3) , ((faces1_size + faces2_size + faces3_size) * 3));

clear_function();

link_two_points();
faces4_size = faces.size();
initializeVectors(((faces1_size + faces2_size + faces3_size) * 3) , ((faces1_size + faces2_size + faces3_size + faces4_size) * 3));
translate_object(0.7 , 0.499 , 0.0 ,((faces1_size + faces2_size + faces3_size) * 3) , ((faces1_size + faces2_size + faces3_size + faces4_size) * 3));

clear_function();

end_effector_points();
faces5_size = faces.size();
initializeVectors(((faces1_size + faces2_size + faces3_size + faces4_size) * 3) , ((faces1_size + faces2_size + faces3_size + faces4_size + faces5_size) * 3));
translate_object(1.15 , 0.5 , 0.0 ,((faces1_size + faces2_size + faces3_size + faces4_size) * 3) , ((faces1_size + faces2_size + faces3_size + faces4_size + faces5_size) * 3));

    glutInit( &argc, argv );
#ifdef __APPLE__
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA );
#else
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
#endif
    glutInitWindowPosition(100,100);
    glutInitWindowSize( 500, 500 );

    window_id = glutCreateWindow( "assignment 10" );

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
    glutAddSubMenu("Light", light_menu);
    glutAddSubMenu("Material", material_menu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutDisplayFunc(display);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}

