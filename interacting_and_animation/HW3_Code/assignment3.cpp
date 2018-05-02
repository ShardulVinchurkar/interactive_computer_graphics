#define GLEW_STATIC

#include "Angel.h"
#include<math.h>

void
bufferGenerator(struct vec2 polygonPoints[],int polyPoints_size, struct vec3 colorPonts[],int colorPoints_size);
void squares_generator();
void buildsquare(float radius_square , float red_value, float green_value, float blue_value);
void ellipse_generator();
void triangle_generator();
void circle_generator(float radius);
void random_circle_generator(float , float  , vec3 , vec3);
float radius_delta_circle=0.08;
float radius_cirlce = 0.05;
float square_delta = 2.0;
float square_points = 0.0;
float angle_delta ;
float red = 1.0, green = 1.0, blue = 1.0;
float window2_red = 1.0, window2_green = 1.0, window2_blue = 1.0;
float red_subwindow_background = 1.0 , green_subwindow_background = 1.0 , blue_subwindow_background = 1.0;
bool animation_controllor = true , random_circle_flag = false;
vec2 random_circle_center[100];
vec3 random_circle_color[100] , random_circle_fun[100];
int counter=0;
GLuint program;

void processMenuEvents(int option)
{
  switch (option)
   {
     case 1 : red = 1.0 ; green = 0.0 ; blue = 0.0; break;
     case 2 : red = 0.0 ; green = 1.0 ; blue = 0.0; break;
     case 3 : red = 0.0 ; green = 0.0 ; blue = 1.0; break;
     case 4 : red = 1.0 ; green = 1.0 ; blue = 1.0; break;
     case 5 : animation_controllor = false; break;
     case 6 : animation_controllor = true; break;
    }
  glutPostRedisplay();
}


void mouse(int btn, int state, int x, int y)
{
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN) {
        random_circle_flag = true;
        float random_circle_red_value = rand()%10/100.0;
        float random_circle_green_value = rand()%10/100.0;
        float random_circle_blue_value = rand()%10/100.0;
        float fun_red_value = rand()%100/100.0;
        float fun_green_value = rand()%100/100.0;
        float fun_blue_value = rand()%100/100.0;
        random_circle_color[counter] = vec3(random_circle_red_value , random_circle_green_value , random_circle_blue_value);
        random_circle_fun[counter] = vec3(fun_red_value , fun_green_value , fun_blue_value);
        random_circle_center[counter] = vec2((x-250)/250.0 , (250-y)/250.0);
        counter++;
    }
}

void random_circle_generator(float center_x , float center_y ,  vec3 color_vaue , vec3 fun_value) {
    //Circle
    vec2 circlepoints[362];
    vec3 circleColor[362];
    float intoradian = 0.0;
    float x_value_circle, y_value_circle;
    circlepoints[0] = vec2(center_x , center_y);
    circleColor[0] = color_vaue;
    for(int i=1 ; i<362 ; i++) {
        x_value_circle = cos(intoradian) * radius_cirlce + center_x;
        y_value_circle = sin(intoradian) * radius_cirlce + center_y;
        circlepoints[i] = vec2(x_value_circle , y_value_circle);
        circleColor[i] = fun_value;
        intoradian = intoradian+M_PI / 180;
    }
    bufferGenerator(circlepoints, sizeof(circlepoints), circleColor, sizeof(circleColor));
}

void processMenuEvents_subwindow(int option)
{
  switch (option)
   {
     case 1 : red_subwindow_background = 1.0 ; green_subwindow_background = 0.0 ; blue_subwindow_background = 0.0; break;
     case 2 : red_subwindow_background = 0.0 ; green_subwindow_background = 1.0 ; blue_subwindow_background = 0.0; break;
     case 3 : red_subwindow_background = 0.0 ; green_subwindow_background = 0.0 ; blue_subwindow_background = 1.0; break;
     case 4 : red_subwindow_background = 1.0 ; green_subwindow_background = 1.0 ; blue_subwindow_background = 1.0; break;
     case 5 : red_subwindow_background = 0.0 ; green_subwindow_background = 0.0 ; blue_subwindow_background = 0.0; break;
    }
  glutPostRedisplay();
}


void idle_window2() {
    if(animation_controllor){
        square_points += square_delta;
        angle_delta += 2.0;
        if(radius_cirlce >= 0.4 || radius_cirlce <=0.05) {
        radius_delta_circle = -radius_delta_circle;
        }
        radius_cirlce += radius_delta_circle;
        glutPostRedisplay();
    }
}
void
display_mainwindow1()
{
    glClearColor(0.0 , 0.0 , 0.0 , 0.0);
    glClear( GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT );     // clear the window
    for(int i=0 ; i<counter ; i++) {
        random_circle_generator(random_circle_center[i].x , random_circle_center[i].y , random_circle_color[i] , random_circle_fun[i]);
        glDrawArrays( GL_TRIANGLE_FAN, 0, 362 );
    }
    squares_generator();
    glutSwapBuffers();
    glutPostRedisplay();
}

void subwindow_display() {
    glClearColor(red_subwindow_background , green_subwindow_background , blue_subwindow_background , 1.0);
    glClear( GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT );     // clear the window

    ellipse_generator();
    glDrawArrays( GL_TRIANGLE_FAN, 0, 362 );    // draw the points

    glutSwapBuffers();
    glutPostRedisplay();
}


void display_window2(){
    glClearColor(0.0 , 0.0 , 0.0 , 0.0);
    glClear( GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT );     // clear the window

    triangle_generator();
    glDrawArrays( GL_TRIANGLE_FAN, 0, 3);    // draw the points

    circle_generator(radius_cirlce);
    glDrawArrays( GL_TRIANGLE_FAN, 0, 362 );    // draw the points

    glutSwapBuffers();
    glutPostRedisplay();
}


void squares_generator() {
    //Squares
    float radius_square = 0.7;
    for(int k=0 ; k < 6 ; k++) {
        if(k%2 == 0){
            buildsquare(radius_square , red , green , blue );
        }
        else {
            buildsquare(radius_square , 0.0 , 0.0 , 0.0);
        }
        radius_square -= 0.1;
        glDrawArrays( GL_TRIANGLE_FAN, 0, 6 );    // draw the points
    }
}

void buildsquare(float radius_square , float red_value, float green_value, float blue_value)
{
    vec3 squarecolor[6];
    vec2 squarepoints[6];
    squarepoints[0] = vec2(0.2 , -0.2);
    squarecolor[0]= vec3(red_value , green_value , blue_value);
    float x_value_square, y_value_square;
    int j=1;
   for(float i = (45+square_points) ; i <= (406+square_points) ; i+=90 ) {
            x_value_square = ((cos(i*(M_PI / 180))) * radius_square) + 0.2;
            y_value_square = ((sin(i*(M_PI / 180))) * radius_square)+(-0.2);
            squarepoints[j]= vec2(x_value_square , y_value_square);
            squarecolor[j]= vec3(red_value , green_value , blue_value);
            j++;
    }
    bufferGenerator(squarepoints, sizeof(squarepoints), squarecolor, sizeof(squarecolor));
}

void ellipse_generator() {
    //Ellipse
    vec2 ellipsepoints[362];
    vec3 ellipseColor[362];
    float radius = 0.8;
    float intoradian = (M_PI / 180);
    float x_value_ellipse, y_value_ellipse;

    ellipsepoints[0] = vec2(0.0 , 0.0);
    ellipseColor[0] = vec3(1.0, 0.0, 0.0);
    for(int i=1 ; i<362 ; i++) {
        x_value_ellipse = cos(i*intoradian) * radius + (-0.0);
        y_value_ellipse = 0.6*((sin(i*intoradian) * radius)) + 0.0;
        ellipsepoints[i] = vec2(x_value_ellipse , y_value_ellipse);
        ellipseColor[i] = vec3(1.0 , 0.0 , 0.0);
    }
    bufferGenerator(ellipsepoints, sizeof(ellipsepoints), ellipseColor, sizeof(ellipseColor));
}

void triangle_generator() {
    //Triangle
    float intoradian = (M_PI / 180);
    float triangle_side_length = 0.5;
    float main_coordinate_x = (cos(90-angle_delta*intoradian)*triangle_side_length) - 0.5;
    float main_coordinate_y = (sin(90-angle_delta*intoradian)*triangle_side_length) + 0.0;
    float second_coordinate_x  = (cos(180-angle_delta*intoradian)*triangle_side_length) - 0.5;
    float second_coordinate_y  = (sin(180-angle_delta*intoradian)*triangle_side_length) + 0.0;
    float third_coordinate_x  = (cos(270-angle_delta*intoradian)*triangle_side_length) - 0.5;
    float third_coordinate_y  = (sin(270-angle_delta*intoradian)*triangle_side_length) + 0.0;
    vec2 vertices[3] = {
	vec2(main_coordinate_x, main_coordinate_y), vec2(second_coordinate_x, second_coordinate_y), vec2(third_coordinate_x, third_coordinate_y),
    };
    vec3 vertex_color[3] = {
        vec3( window2_red , window2_green , window2_blue ),
        vec3( window2_red , window2_green , window2_blue ),
        vec3( window2_red , window2_green , window2_blue )
    };
    bufferGenerator(vertices, sizeof(vertices), vertex_color, sizeof(vertex_color));
}

void circle_generator(float radius) {
    //Circle
    vec2 circlepoints[362];
    vec3 circleColor[362];
    float intoradian = 0.0;
    float x_value_circle, y_value_circle;
    circlepoints[0] = vec2(0.5 , 0.0);
    circleColor[0] = vec3(window2_red , window2_green , window2_blue);

    for(int i=1 ; i<362 ; i++) {
        x_value_circle = cos(intoradian) * radius + 0.5;
        y_value_circle = sin(intoradian) * radius + 0.0;
        circlepoints[i] = vec2(x_value_circle , y_value_circle);
        circleColor[i] = vec3(window2_red , window2_green , window2_blue);
        intoradian = intoradian+M_PI / 180;
    }
    bufferGenerator(circlepoints, sizeof(circlepoints), circleColor, sizeof(circleColor));
}

void
init( void )
{
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    program = InitShader( "vshader21.glsl", "fshader21.glsl" );
                                 
}

void keyboard_function( unsigned char key, int x, int y )
{
    switch ( key ) {
        case 'q': exit( EXIT_SUCCESS ); break;
        case 'w': window2_red = 1.0 ; window2_green = 1.0 ; window2_blue = 1.0; break;
        case 'r': window2_red = 1.0 ; window2_green = 0.0 ; window2_blue = 0.0; break;
        case 'g': window2_red = 0.0 ; window2_green = 1.0 ; window2_blue = 0.0; break;
        case 'b': window2_red = 0.0 ; window2_green = 0.0 ; window2_blue = 1.0; break;
        case 'y': window2_red = 1.0 ; window2_green = 1.0 ; window2_blue = 0.0; break;
        case 'o': window2_red = 1.0 ; window2_green = 0.5 ; window2_blue = 0.0; break;
        case 'p': window2_red = 0.5 ; window2_green = 0.0 ; window2_blue = 0.5; break;
    }
}


void
bufferGenerator(struct vec2 polygonPoints[],int polyPoints_size, struct vec3 colorPonts[],int colorPoints_size) {

    GLuint buffer_name_polygon;
    glGenBuffers( 1, &buffer_name_polygon );
    glBindBuffer( GL_ARRAY_BUFFER, buffer_name_polygon );
    glBufferData( GL_ARRAY_BUFFER, polyPoints_size, polygonPoints, GL_STATIC_DRAW );

    GLuint loc = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );

    GLuint buffer_name_color;
    glGenBuffers( 1, &buffer_name_color );
    glBindBuffer( GL_ARRAY_BUFFER, buffer_name_color );
    glBufferData( GL_ARRAY_BUFFER, colorPoints_size, colorPonts, GL_STATIC_DRAW );

    GLuint loc_color = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( loc_color );
    glVertexAttribPointer( loc_color, 3, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );
}

void reshape_window2 (int w  , int h) {
    glViewport(0 , 0 , w , h);
}


int mainwindow1, subwindow1,mainwindow2;
int
main( int argc, char **argv )
{
    printf("\n Once the application is running");
    printf("\n Right click on window with black and white squares you will receive a menu with options \n 1-Stop animation \n 2-Start animation \n choose any one to control the animation ");
    printf("\n Also a submenu is available with all the different colors which change the white color of black and white squares to any one of Red Green Blue or White");
    printf("\n Right click on the subwindow and a menu will drop down for changing the color of the subwindow");
    printf("\n press any of the following keys 'w''r''g''b''y''o''p' which changes the color of triangle and circle in second window respectively");
    printf("\n Left click any where on the main window to generate the random colored circles which appear to be breathing");
    printf("\n To quit the output press 'q'");
    glutInit( &argc, argv );
#ifdef __APPLE__
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA );
#else
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA);
#endif
    glutInitWindowPosition(100,100);
    glutInitWindowSize( 500, 500 );

    mainwindow1 = glutCreateWindow( "assignment 3" );

#ifndef __APPLE__
    GLenum err = glewInit();
    if (GLEW_OK != err)
      fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
#endif

    init();
    glutDisplayFunc( display_mainwindow1 );
    glutKeyboardFunc( keyboard_function );
    int menu,submenu;
    submenu = glutCreateMenu(processMenuEvents);
    glutAddMenuEntry("Red",1);
    glutAddMenuEntry("Green",2);
    glutAddMenuEntry("Blue",3);
    glutAddMenuEntry("White",4);
    menu = glutCreateMenu(processMenuEvents);
    glutAddMenuEntry("Stop Animation",5);
    glutAddMenuEntry("Start Animation",6);
    glutAddSubMenu("Square Color",submenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMouseFunc(mouse);

    subwindow1 = glutCreateSubWindow(mainwindow1,1,1,150,150);
    init();
    glutDisplayFunc(subwindow_display);
    glutKeyboardFunc( keyboard_function );
    int menu_subwindow;
    menu_subwindow = glutCreateMenu(processMenuEvents_subwindow);
    glutAddMenuEntry("Red",1);
    glutAddMenuEntry("Green",2);
    glutAddMenuEntry("Blue",3);
    glutAddMenuEntry("White",4);
    glutAddMenuEntry("Black",5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutInitWindowSize( 400, 400 );
    glutInitWindowPosition(600,100);
    mainwindow2 = glutCreateWindow( "window 2" );
    init();
    glutDisplayFunc( display_window2 );
    glutKeyboardFunc( keyboard_function );
    glutReshapeFunc(reshape_window2);
    glutIdleFunc(idle_window2);
    glutMainLoop();
    return 0;
}
