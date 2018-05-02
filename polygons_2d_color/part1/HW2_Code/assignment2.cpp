#define GLEW_STATIC

#include "Angel.h"
#include<math.h>

void
bufferGenerator(struct vec2 polygonPoints[],int polyPoints_size, struct vec3 colorPonts[],int colorPoints_size, GLuint program_name);
void triangle_generator(GLuint program);
void circle_generator(GLuint program);
void ellipse_generator(GLuint program);
void squares_generator(GLuint program);
void buildsquare(float radius_square , float fillColor, GLuint program);

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );     // clear the window
    GLuint program = InitShader( "vshader21.glsl" , "fshader21.glsl" );

    triangle_generator(program);
    glDrawArrays( GL_TRIANGLE_FAN, 0, 3 );    // draw the points
    circle_generator(program);
    glDrawArrays( GL_TRIANGLE_FAN, 0, 362 );    // draw the points
    ellipse_generator(program);
    glDrawArrays( GL_TRIANGLE_FAN, 0, 362 );    // draw the points
    squares_generator(program);
    glFlush();
}

void triangle_generator(GLuint program) {
    //Triangle
    vec2 vertices[3] = {
	vec2(0.0, 1.0), vec2(-0.2, 0.60), vec2(0.2, 0.60),
    };
    vec3 vertex_color[3] = {
        vec3(1.0 , 0.0 , 0.0 ),
        vec3(0.0 , 1.0 , 0.0 ),
        vec3(0.0 , 0.0 , 1.0 )
    };
    bufferGenerator(vertices, sizeof(vertices), vertex_color, sizeof(vertex_color), program);
}
void circle_generator(GLuint program) {
    //Circle
    vec2 circlepoints[362];
    vec3 circleColor[362];
    float radius = 0.2;
    float intoradian = 0.0;
    float x_value_circle, y_value_circle;
    circlepoints[0] = vec2(0.6 , 0.78);
    circleColor[0] = vec3(0.0, 0.0, 0.0);

    for(int i=1 ; i<362 ; i++) {
        x_value_circle = cos(intoradian) * radius + 0.6;
        y_value_circle = (sin(intoradian) * radius) + 0.78;
        circlepoints[i] = vec2(x_value_circle , y_value_circle);
        circleColor[i] = vec3(intoradian*radius, 0.0 , 0.0);
        intoradian = intoradian+M_PI / 180;
    }
    bufferGenerator(circlepoints, sizeof(circlepoints), circleColor, sizeof(circleColor), program);
}

void ellipse_generator(GLuint program) {
    //Ellipse
    vec2 ellipsepoints[362];
    vec3 ellipseColor[362];
    float radius = 0.2;
    float intoradian = (M_PI / 180);
    float x_value_ellipse, y_value_ellipse;

    ellipsepoints[0] = vec2(-0.6 , 0.78);
    ellipseColor[0] = vec3(1.0, 0.0, 0.0);

    for(int i=1 ; i<362 ; i++) {
        x_value_ellipse = cos(i*intoradian) * radius + (-0.6);
        y_value_ellipse = 0.6*((sin(i*intoradian) * radius)) + 0.78;
        ellipsepoints[i] = vec2(x_value_ellipse , y_value_ellipse);
        ellipseColor[i] = vec3(1.0 , 0.0 , 0.0);
    }
    bufferGenerator(ellipsepoints, sizeof(ellipsepoints), ellipseColor, sizeof(ellipseColor), program);
}

void squares_generator(GLuint program) {
    //Squares
    float radius_square = 0.9;
    for(int k=0 ; k < 6 ; k++) {
        if(k%2 == 0){
            buildsquare(radius_square , 1.0 , program);
        }
        else {
            buildsquare(radius_square , 0.0 , program);
        }
        radius_square -= 0.15;
        glDrawArrays( GL_TRIANGLE_FAN, 0, 362 );    // draw the points
    }
}

void buildsquare(float radius_square , float fillColor , GLuint program)
{
    vec3 squarecolor[6];
    vec2 squarepoints[6];
    squarepoints[0] = vec2(0.0 , -0.1);
    float x_value_square, y_value_square;
    int j=0;
   for(int i = 45; i <= 405 ; i+=90 ) {
            x_value_square = (cos(i*(M_PI / 180))) * radius_square;
            y_value_square = ((sin(i*(M_PI / 180))) * radius_square)+(-0.1);
            squarepoints[j]= vec2(x_value_square , y_value_square);
            squarecolor[j]= vec3(fillColor , fillColor , fillColor);
            j++;
        bufferGenerator(squarepoints, sizeof(squarepoints), squarecolor, sizeof(squarecolor), program);
    }
}

void
init( void )
{
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
}

void
bufferGenerator(struct vec2 polygonPoints[],int polyPoints_size, struct vec3 colorPonts[],int colorPoints_size, GLuint program_name) {

    GLuint buffer_name_polygon;
    glGenBuffers( 1, &buffer_name_polygon );
    glBindBuffer( GL_ARRAY_BUFFER, buffer_name_polygon );
    glBufferData( GL_ARRAY_BUFFER, polyPoints_size, polygonPoints, GL_STATIC_DRAW );

    GLuint loc = glGetAttribLocation( program_name, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );

    GLuint buffer_name_color;
    glGenBuffers( 1, &buffer_name_color );
    glBindBuffer( GL_ARRAY_BUFFER, buffer_name_color );
    glBufferData( GL_ARRAY_BUFFER, colorPoints_size, colorPonts, GL_STATIC_DRAW );

    GLuint loc_color = glGetAttribLocation( program_name, "vColor" );
    glEnableVertexAttribArray( loc_color );
    glVertexAttribPointer( loc_color, 3, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );
}


void
keyboard( unsigned char key, int x, int y )
{
    switch ( key ) {
    case 'q':
        exit( EXIT_SUCCESS );
        break;
    }
}


int
main( int argc, char **argv )
{
    glutInit( &argc, argv );
#ifdef __APPLE__
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA );
#else
    glutInitDisplayMode( GLUT_RGBA | GLUT_SINGLE);
#endif
    glutInitWindowSize( 500, 500 );

    glutCreateWindow( "Assgnment 2" );

#ifndef __APPLE__
    GLenum err = glewInit();
    if (GLEW_OK != err)
      fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
#endif

    init();

    glutDisplayFunc( display );
    glutIdleFunc(display);
    glutKeyboardFunc( keyboard );

    glutMainLoop();
    return 0;
}
