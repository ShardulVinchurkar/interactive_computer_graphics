#define GLEW_STATIC

#include "Angel.h"
#include<math.h>
#include<fstream>
#include<vector>
#include<string>
using namespace std;
void
bufferGenerator(struct vec4 polygonPoints[],int polyPoints_size, struct vec4 colorPonts[],int colorPoints_size, struct mat4 , struct mat4);
GLuint program;
void create_object ();
vector<vec4> colors , points;
mat4 transformed_matrix, scaling_matrix, translating_matrix;
float theta[3] = {0.0 , 0.0 , 0.0} , scale_by = 1.0 , translate_by;
float theta_delta = 1 , scale_delta = 0.1 , translate_delta = 0.1;
vector<vec4> vertices , faces;
vec4 location_eye = vec4(0.0 , 0.0 , 3.0 , 0.0) , at_model = vec4(0.0 , 0.0 , 0.0 , 0.0) , up_axis = vec4(0.0 , 1.0 , 0.0 , 0.0);
void split(string inText , char space);
vec3 vector1 , centroid_value;
mat4 projection_type , viewing_object;
float minX , minY , minZ , maxX , maxY , maxZ;
float min_values[3] , max_values[3];
void find_min(); void find_max();
float range_value , get_max_value;
void get_range();
float eye_x , eye_y , eye_z;
float angle = 90 , height = 0.0 , radius = 3.0;
float angle_delta = 1 , height_delta = 0.01 , radius_delta = 0.1;
int projection_flag = 1;

void quad( int a, int b, int c )
{
        points.push_back(vertices[a]);
        points.push_back(vertices[b]);
        points.push_back(vertices[c]);

        vec3 get_n = cross((vertices[c] - vertices[a]),(vertices[b] - vertices[a]));
        vec4 normalized_value = normalize(get_n);
        normalized_value.x = abs(normalized_value.x);
        normalized_value.y = abs(normalized_value.y);
        normalized_value.z = abs(normalized_value.z);
        colors.push_back(normalized_value);
        colors.push_back(normalized_value);
        colors.push_back(normalized_value);
}

void construct_cube () {

    for(int i=0 ; i<faces.size() ; i++) {
        quad( (int)(faces[i].x-1) , (int)(faces[i].y-1), (int)(faces[i].z-1) );
    }
}

void idle_window2() {
    glutPostRedisplay();
}
void
display()
{
    glClearColor(1.0 , 1.0 , 1.0 , 1.0);
    glClear( GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT );     // clear the window

    eye_x = radius * cos(angle*M_PI/180.0);
    eye_y = height;
    eye_z = radius * sin(angle*M_PI/180.0);
    location_eye = vec4(eye_x , eye_y , eye_z , 1.0);
    viewing_object = LookAt(location_eye , at_model , up_axis);

    if(projection_flag == 1)
        projection_type = Perspective(82.0 , 1.0 , 0.1 , 15);
    else if(projection_flag == 2)
        projection_type = Ortho(-1.0 , 1.0 , -1.0 , 1.0 , 0.01 , 7.0);

    vec4 colors_vec_value[colors.size()];
    vec4 points_vec_value[points.size()];
    copy(points.begin(),points.end(),points_vec_value);
    copy(colors.begin(),colors.end(),colors_vec_value);

    bufferGenerator(points_vec_value , sizeof(points_vec_value) , colors_vec_value , sizeof(colors_vec_value), viewing_object , projection_type);
    glDrawArrays( GL_TRIANGLES, 0, points.size() );

    glutSwapBuffers();
    glutPostRedisplay();
}


void
init( void )
{
    construct_cube();
    program = InitShader( "vshader21.glsl", "fshader21.glsl" );
                          
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
        }
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
    printf("\n The default value is set at Perspective");
    printf("\n To change - Right click of mouse button will show you a drop down menu containing \n Perspective \n Parallel");
    printf("\n On selecting any one from the menu you will be able to perform the following : ");
    printf("\n key press 'x' : Increases the angle to rotate around the object");
    printf("\n key press 's' : Decreases the angle to rotate around the object");
    printf("\n key press 'y' : Increases the height of the camera");
    printf("\n key press 'h' : Decreases the height of the camera");
    printf("\n key press 'z' : The camera goes away from the object");
    printf("\n key press 'a' : The camera goes near to the object");
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

    window_id = glutCreateWindow( "assignment 5" );

#ifndef __APPLE__
    GLenum err = glewInit();
    if (GLEW_OK != err)
      fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
#endif

    init();
    glutKeyboardFunc( keyboard_function );
    int window_menu;
    window_menu = glutCreateMenu(process_menu_events);
    glutAddMenuEntry("Perspective",1);
    glutAddMenuEntry("Parallel",2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutDisplayFunc(display);

    glutIdleFunc(idle_window2);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
