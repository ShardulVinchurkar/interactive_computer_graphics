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
int fact_func(int number);
double Basis_func(int i,double u, int degree);
void generate_bezier_vertices();
void fill_face_values();
GLuint program;
void create_object ();
vector<vec4> colors , points , control_points , copy_control_points;
vector<vec3> normals;
mat4 transformed_matrix, scaling_matrix, translating_matrix;
float theta[3] = {0.0 , 0.0 , 0.0} , scale_by = 1.0 , translate_by;
float theta_delta = 1 , scale_delta = 0.1 , translate_delta = 0.1;
vector<vec4> vertices , faces;
vec4 location_eye = vec4(0.0 , 0.0 , 3.0 , 0.0) , at_model = vec4(0.0 , 0.0 , 0.0 , 0.0) , up_axis = vec4(0.0 , 1.0 , 0.0 , 0.0);
vec4 normalized_value;
vec3 vector1 , centroid_value;
mat4 projection_type , viewing_object;
float minX , minY , minZ , maxX , maxY , maxZ;
float min_values[3] , max_values[3];
void find_min(); void find_max();
float range_value , get_max_value , get_min_value;
void get_range();
float eye_x , eye_y , eye_z, light_x , light_y , light_z , light1_x , light1_y , light1_z;
float angle = 90 , height = 0.0 , radius = 3.0, theta_light = 90, light_height = 0.0, light_radius = 1.5;
float angle_delta = 1 , height_delta = 0.5 , radius_delta = 0.1 , theta_light_delta = 3;
int projection_flag = 2;
int shader_flag = 1;
int num_u=10;
int num_v=10;
vector<vec4> points_colors , axes_lines , axes_colors;
int point_number = 0;

vec4 material_diffuse = vec4(0.5, 0.5, 1.0 , 1.0);
vec4 material_ambience = vec4(0.5, 0.5, 0.5 , 1.0);
vec4 material_specular = vec4(0.0, 0.0, 0.0 , 1.0);

vec4 light1_diffuse = vec4(0.8 , 0.8 , 0.8 , 1.0);
vec4 light1_ambience = vec4(0.0, 0.0, 0.0 , 1.0);
vec4 light1_specular = vec4(0.0, 0.0, 0.0 , 1.0);
vec4 light1_pos = vec4(0.0 , 0.0 , 2.0 , 1.0);

vec4 light_diffuse = vec4(0.8 , 0.8 , 0.8 , 1.0);
vec4 light_ambience = vec4(0.0, 0.0, 0.0 , 1.0);
vec4 light_specular = vec4(0.0, 0.0, 0.0 , 1.0);
vec4 light0_pos;
vec4 specular0 = vec4(0.0, 0.0, 0.0 , 1.0);
GLfloat shine = 100.0;


vec4 diffuse1 = light_diffuse * material_diffuse;
vec4 ambient1 = light_ambience * material_ambience;
vec4 specular1 = vec4(1.0, 1.0, 1.0 , 1.0);


void quad( int a, int b, int c )
{
        points.push_back(vertices[a]);
        points.push_back(vertices[b]);
        points.push_back(vertices[c]);

        vec3 get_n = cross((vertices[b] - vertices[a]),(vertices[c] - vertices[a]));
        vec4 normalized_value = normalize(get_n);

        colors.push_back(normalized_value);
        colors.push_back(normalized_value);
        colors.push_back(normalized_value);
}


void construct_cube () {
    for(int i=0 ; i<faces.size() ; i++) {
        quad( (int)(faces[i].x) , (int)(faces[i].y), (int)(faces[i].z) );
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

    GLint uniform_color_flag = glGetUniformLocation(program, "color_flag");
    glUniform1i(uniform_color_flag , 0);
    glDrawArrays( GL_TRIANGLES, 0, points.size()-control_points.size()-6 );

    uniform_color_flag = glGetUniformLocation(program, "color_flag");
    glUniform1i(uniform_color_flag , 1);
    glDrawArrays(GL_POINTS , points.size()-control_points.size()-6 , points.size()-6);

    uniform_color_flag = glGetUniformLocation(program, "color_flag");
    glUniform1i(uniform_color_flag , 1);
    glDrawArrays(GL_LINES , points.size()-6 , points.size());

    glutSwapBuffers();
}


void
init( void )
{
    for(int i = 0 ; i < 16 ; i++) {
        if(i == 0)
            points_colors.push_back(vec4(1.0 , 0.0 , 0.0 , 1.0));
        else
            points_colors.push_back(vec4(1.0 , 1.0 , 1.0 , 1.0));
        }
    axes_lines.push_back(vec4(0.0 , 0.0 , 0.0 , 1.0));
    axes_lines.push_back(vec4(1.0 , 0.0 , 0.0 , 1.0));
    axes_lines.push_back(vec4(0.0 , 0.0 , 0.0 , 1.0));
    axes_lines.push_back(vec4(0.0 , 1.0 , 0.0 , 1.0));
    axes_lines.push_back(vec4(0.0 , 0.0 , 0.0 , 1.0));
    axes_lines.push_back(vec4(0.0 , 0.0 , 1.0 , 1.0));
    axes_colors.push_back(vec4(1.0 , 0.0 , 0.0 , 1.0));
    axes_colors.push_back(vec4(1.0 , 0.0 , 0.0 , 1.0));
    axes_colors.push_back(vec4(0.0 , 1.0 , 0.0 , 1.0));
    axes_colors.push_back(vec4(0.0 , 1.0 , 0.0 , 1.0));
    axes_colors.push_back(vec4(0.0 , 0.0 , 1.0 , 1.0));
    axes_colors.push_back(vec4(0.0 , 0.0 , 1.0 , 1.0));
    generate_bezier_vertices();
    for(int i = 0 ; i < vertices.size() ; i++)
        normals.push_back(vec3(1.0 , 1.0 , 1.0));
    fill_face_values();
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
    for(int i=0 ; i < control_points.size() ; i++) {
        points.push_back(control_points[i]);
        colors.push_back(points_colors[i]);
    }
    for(int i = 0 ; i < 6 ; i++) {
        points.push_back(axes_lines[i]);
        colors.push_back(axes_colors[i]);
    }
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
    range_value = abs(maxX - minX);
    if((maxY - minY) > (maxX - minX) && (maxY - minY) > (maxZ - minZ)){
        range_value = abs(maxY - minY);
    }
    else if((maxZ - minZ) > (maxX - minX) && (maxZ - minZ) > (maxY - minY)) {
        range_value = abs(maxZ - minZ);
    }
}

void update_tessalation(int u_v , int inc_dec) {
    if(inc_dec == 0){
        if(u_v == 0) {
            num_u += 1;
        }
        else {
            num_v += 1;
        }
    }
    else if(inc_dec == 1){
        if(u_v == 0) {
            num_u -= 1;
            if(num_u < 2)
                num_u = 2;
        }
        else {
            num_v -= 1;
            if(num_v < 2)
                num_v = 2;
        }
    }
    vertices.clear();
    faces.clear();
    points.clear();
    colors.clear();
    generate_bezier_vertices();
    fill_face_values();
    construct_cube();
    create_object();
}

void update_controlpoints(int axis, int i_d){
    if(i_d == 0){
        switch(axis){
            case 0: control_points[point_number].x+=0.1;break;
            case 1: control_points[point_number].y+=0.1;break;
            case 2: control_points[point_number].z+=0.1;break;
        }
    }
    else{
        switch(axis){
            case 0: control_points[point_number].x-=0.1;break;
            case 1: control_points[point_number].y-=0.1;break;
            case 2: control_points[point_number].z-=0.1;break;
        }
    }
    vertices.clear();
    faces.clear();
    points.clear();
    colors.clear();
    generate_bezier_vertices();

    fill_face_values();
    construct_cube();
    create_object();

}

void calling_all_func () {
    vertices.clear();
    faces.clear();
    points.clear();
    colors.clear();
    generate_bezier_vertices();

    fill_face_values();
    construct_cube();
    create_object();
}

void reset() {
control_points.clear();
points_colors.clear();
num_u=10;
num_v=10;
point_number = 0;
angle = 90 , height = 0.0 , radius = 3.0, theta_light = 90, light_height = 0.0, light_radius = 1.5;
for(int i = 0 ; i < copy_control_points.size() ; i++)
    control_points.push_back(copy_control_points[i]);
init();
calling_all_func();
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
        case 'r': angle = 90.0 ; height = 0.0 ; radius = 3.0; projection_flag = 2;
                  reset();
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
        case 'f': update_tessalation(0 , 0);
                break;
        case 'v': update_tessalation(0 , 1);
                break;
        case 'g': update_tessalation(1 , 0);
                break;
        case 'b': update_tessalation(1 , 1);
                break;
        case '+':
                points_colors[point_number] = vec4(1.0 , 1.0 , 1.0 , 1.0);
                point_number++;
                if(point_number >= control_points.size())
                    point_number = control_points.size() - 1;
                points_colors[point_number] = vec4(1.0 , 0.0 , 0.0 , 1.0);
                calling_all_func();
                break;
        case '-': points_colors[point_number] = vec4(1.0 , 1.0 , 1.0 , 1.0);
                point_number--;
                if(point_number <= 0)
                    point_number = 0;
                points_colors[point_number] = vec4(1.0 , 0.0 , 0.0 , 1.0);
                calling_all_func();
                break;
        case 'd': update_controlpoints(0,0);break;
        case 'c': update_controlpoints(0,1);break;
        case 'w': update_controlpoints(1,0);break;
        case 'e': update_controlpoints(1,1);break;
        case 'n': update_controlpoints(2,0);break;
        case 'm': update_controlpoints(2,1);break;
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
    //vec4 light_pos = viewing_object * light0_pos;
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
    }
    glutPostRedisplay();
}

void getInput() {
    control_points.push_back(vec4(0.0 , 0.0 , 0.0  , 1.0));
    control_points.push_back(vec4(2.0 , 0.0 , 1.5  , 1.0));
    control_points.push_back(vec4(4.0 , 0.0 , 2.9  , 1.0));
    control_points.push_back(vec4(6.0 , 0.0 , 0.0  , 1.0));
    control_points.push_back(vec4(0.0 , 2.0 , 1.1  , 1.0));
    control_points.push_back(vec4(2.0 , 2.0 , 3.9  , 1.0));
    control_points.push_back(vec4(4.0 , 2.0 , 3.1  , 1.0));
    control_points.push_back(vec4(6.0 , 2.0 , 0.7  , 1.0));
    control_points.push_back(vec4(0.0 , 4.0 , -0.5 , 1.0));
    control_points.push_back(vec4(2.0 , 4.0 , 2.6  , 1.0));
    control_points.push_back(vec4(4.0 , 4.0 , 2.4  , 1.0));
    control_points.push_back(vec4(6.0 , 4.0 , 0.4  , 1.0));
    control_points.push_back(vec4(0.0 , 6.0 , 0.3  , 1.0));
    control_points.push_back(vec4(2.0 , 6.0 , -1.1 , 1.0));
    control_points.push_back(vec4(4.0 , 6.0 , 1.3  , 1.0));
    control_points.push_back(vec4(6.0 , 6.0 , -0.2 , 1.0));
}

double roundOffDecimals(string increment)
{
    double roundedDecimal=0.0;
    string digitsAfterDecimal=increment.substr(increment.find('.')+1);
    if(digitsAfterDecimal.length()>6)
    {
        digitsAfterDecimal=digitsAfterDecimal.substr(0, 6);
        roundedDecimal=::atof(("0."+digitsAfterDecimal).c_str());
    }
    else
    {
        roundedDecimal=::atof((increment).c_str());
    }
    return roundedDecimal;
}

void generate_bezier_vertices() {
    int degree = 3;
    int i=0 ;
    double u = 0.0 , v = 0.0;
    double du = 1.0/(num_u-1.0) , dv = 1.0/(num_v-1.0);

    std::ostringstream stringVal;
    stringVal << du;
    std::string deltaU = stringVal.str();

    std::ostringstream stringVal1;
    stringVal1 << dv;
    std::string deltaV = stringVal1.str();

    du=roundOffDecimals(deltaU);
    dv=roundOffDecimals(deltaV);
    double sumx = 0.0 , sumy = 0.0 , sumz = 0.0;
    int index = 0;
    double condition_sum_v = 0.0 , condition_sum_u = 0.0;
    int condition_counter_u = 0 , condition_counter_v = 0;
    for(u = 0.0 ; u <= 1.0 ; u += du)//Blending Function of the curve
    {
        condition_counter_v = 0;
        for(v = 0.0 ; v <= 1.0 ; v += dv)
        {
            for(i = 0 ; i <= 12 ; i += 4)
            {
                int k=0;
                if(i<12)
                    k=i%3;
                else if(i==12)
                    k=3;
                for(int j = 0 ; j < 4 ; j++)
                {
                    sumx += control_points[i+j].x * (Basis_func(k,u,degree) * Basis_func(j,v,degree));
                    sumy += control_points[i+j].y * (Basis_func(k,u,degree) * Basis_func(j,v,degree));
                    sumz += control_points[i+j].z * (Basis_func(k,u,degree) * Basis_func(j,v,degree));
                }
            }
            sumx = round(sumx*1000000.0)/1000000.0;
            sumy = round(sumy*1000000.0)/1000000.0;
            sumz = round(sumz*1000000.0)/1000000.0;

            vertices.push_back(vec4(sumx , sumy , sumz , 1.0));
            sumx=0;sumy=0;sumz=0;
            condition_sum_v = v+dv;
            condition_counter_v++;
            if(condition_sum_v > 1 && condition_counter_v == num_v-1) {
                v = 1-dv;
            }
        }
        condition_counter_u++;
        condition_sum_u = u+du;
        if(condition_sum_u > 1 && condition_counter_u == num_u-1) {
            u = 1-du;
        }
    }
}

double Basis_func(int i,double u, int degree)
{
	double temp = 0;
	int ncr = fact_func(degree) / (fact_func(degree-i) * fact_func(i));
	double term1 = pow((1-u) , (degree-i));
	double term2 = pow(u, i);
	temp = (ncr) * term1 * term2;
	return temp;
}

int fact_func(int number)
{
	if(number==0)
		return 1;
	else
		return number * fact_func(number-1);
}

void fill_face_values() {
    int increamenter = 0;
    int n=(int)num_u;
    int m=(int)num_v;
    float faceting[num_u][num_v];
    for(int i=0 ; i<num_u ; i++)
    {
        for(int j=0 ; j<num_v ; j++)
        {
            faceting[i][j] = increamenter;
            increamenter++;
        }
    }
    for(int i=0 ; i<n ; i++ )
    {
        for(int j=0 ; j<m ; j++)
        {
            if(i < n-1 && j < m-1)
            {
                faces.push_back(vec4(faceting[i][j] , faceting[i+1][j] , faceting[i][j+1] , 1.0));
                faces.push_back(vec4(faceting[i][j+1] , faceting[i+1][j] , faceting[i+1][j+1] , 1.0));
            }
        }
    }
}

int window_id;
int
main( int argc, char **argv )
{
    printf("\n Once the program is up and running : ");
    printf("\n The default value is set at Perspective Gouroud and Gold material with white light");
    printf("\n To change - Right click of mouse button will show you a drop down menu containing \n Projection Type \n Shading Type \n Light Type \n Material Type");
    printf("\n On selecting any one from the menu you will be able to perform the following : ");
    printf("\n key press 'x' : Increases the angle of camera to rotate around the object");
    printf("\n key press 's' : Decreases the angle of camera to rotate around the object");
    printf("\n key press 'y' : Increases the height of the camera");
    printf("\n key press 'h' : Decreases the height of the camera");
    printf("\n key press 'z' : The camera goes away from the object");
    printf("\n key press 'a' : The camera goes near the object");
    printf("\n key press 'l' : Increases the angle of light to rotate around the object");
    printf("\n key press 'o' : Decreases the angle of light to rotate around the object");
    printf("\n key press 'k' : Increases the height of the light");
    printf("\n key press 'i' : Decreases the height of the light");
    printf("\n key press 'j' : The light goes away from the object");
    printf("\n key press 'u' : The light goes near to the object");

    printf("\n key press 'f OR v' : U tessellation increase OR decrease respectively");
    printf("\n key press 'g OR b' : V tessellation increase OR decrease respectively");

    printf("\n key press '+' : Selects the next control point");
    printf("\n key press '-' : Selects the previous control point");

    printf("\n key press 'd' : Changes the x factor of the selected control point in positive direction");
    printf("\n key press 'c' : Changes the x factor of the selected control point in negative direction");
    printf("\n key press 'w' : Changes the y factor of the selected control point in positive direction");
    printf("\n key press 'e' : Changes the y factor of the selected control point in negative direction");
    printf("\n key press 'n' : Changes the z factor of the selected control point in positive direction");
    printf("\n key press 'm' : Changes the z factor of the selected control point in negative direction");

    printf("\n key press 'r' : Resets to default values");
    printf("\n key press 'q' : Quits from output window\n\n");

	getInput();
	    for(int i = 0 ; i < control_points.size() ; i++)
        copy_control_points.push_back(control_points[i]);

    glutInit( &argc, argv );
#ifdef __APPLE__
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA );
#else
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
#endif
    glutInitWindowPosition(100,100);
    glutInitWindowSize( 500, 500 );

    window_id = glutCreateWindow( "assignment 5" );

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

    glutCreateMenu(process_menu_events);
    glutAddSubMenu("Projection Type", projection_menu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutDisplayFunc(display);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glutMainLoop();
    return 0;
}

