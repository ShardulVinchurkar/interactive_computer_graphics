#define GLEW_STATIC

#include "Angel.h"
#include<math.h>

void
bufferGenerator(struct vec2 polygonPoints[],int polyPoints_size, struct vec3 colorPonts[],int colorPoints_size, GLuint program_name);
void fname_initial (GLuint program);
void smiley(GLuint program);
void some_shape(GLuint program);
void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );     // clear the window
    GLuint program = InitShader( "vshader21.glsl","fshader21.glsl" );

    fname_initial (program);
    smiley(program);
    some_shape(program);
    glFlush();
}

void fname_initial (GLuint program) {
    vec2 circlepoints[182];
    vec3 circleColor[182];
    float radius = 0.3;
    float x_value_circle, y_value_circle;
    float intoradian = (M_PI / 180);
    circlepoints[0] = vec2(0.0 , 0.0);
    circleColor[0] = vec3(0.0, 1.0, 1.0);
    int j=1;
    for(int i=90 ; i<271 ; i++) {
        x_value_circle = cos(i*intoradian) * radius;
        y_value_circle = (sin(i*intoradian) * radius);
        circlepoints[j] = vec2(x_value_circle , y_value_circle);
        circleColor[j] = vec3(0.0 , 0.0 , 0.0);
        j++;
    }
    bufferGenerator(circlepoints, sizeof(circlepoints), circleColor, sizeof(circleColor), program);
    glDrawArrays( GL_TRIANGLE_FAN, 0, 182 );    // draw the points
    float new_x_value , new_y_value;
    vec2 bottom_of_initial[182];
    vec3 bottom_of_initial_color[182];
    bottom_of_initial[0] = vec2(0.1 , -0.3);
    bottom_of_initial_color[0] = vec3(0.0 , 1.0 , 1.0);
    int k = 1;
        for(int i=270 ; i<451 ; i++) {
        new_x_value = cos(i*intoradian) * radius + 0.1;
        new_y_value = (sin(i*intoradian) * radius) - 0.3;
        bottom_of_initial[k] = vec2(new_x_value , new_y_value);
        bottom_of_initial_color[k] = vec3(0.0 , 0.0 , 0.0);
        k++;
    }
    bufferGenerator(bottom_of_initial, sizeof(bottom_of_initial), bottom_of_initial_color, sizeof(bottom_of_initial_color), program);
    glDrawArrays( GL_TRIANGLE_FAN, 0, 182 );    // draw the points
    vec2 rectangle2_points[4] = {vec2(0.0 , 0.0) , vec2(0.0 , -0.3) , vec2(0.1 , 0.0) , vec2(0.1 , -0.3)};
    vec3 rectangle2_color[4] = {vec3 (0.0 , 0.7 , 0.7),
                                vec3 (0.0 , 0.3 , 0.3),
                                vec3 (0.0 , 0.3 , 0.3),
                                vec3 (0.0 , 0.7 , 0.7)};
    bufferGenerator(rectangle2_points, sizeof(rectangle2_points), rectangle2_color, sizeof(rectangle2_color), program);
    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );
        vec2 rectangle3_points[4] = {vec2(0.0 , 0.3) , vec2(0.0 , 0.1) , vec2(0.3 , 0.3) , vec2(0.3 , 0.1)};
    vec3 rectangle3_color[4] = {vec3 (0.0 , 0.0 , 0.0),
                                vec3 (0.0 , 0.8 , 0.8),
                                vec3 (0.0 , 0.0 , 0.0),
                                vec3 (0.0 , 0.6 , 0.6)};
    bufferGenerator(rectangle3_points, sizeof(rectangle3_points), rectangle3_color, sizeof(rectangle3_color), program);
    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );
    vec2 rectangle1_points[4] = {vec2(0.1 , -0.6) , vec2(0.1 , -0.4) , vec2(-0.2 , -0.6) , vec2(-0.2 , -0.4)};
    vec3 rectangle1_color[4] = {vec3 (0.0 , 0.0 , 0.0),
                                vec3 (0.0 , 0.8 , 0.8),
                                vec3 (0.0 , 0.0 , 0.0),
                                vec3 (0.0 , 0.5 , 0.5)};
    bufferGenerator(rectangle1_points, sizeof(rectangle1_points), rectangle1_color, sizeof(rectangle1_color), program);
    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );
}

void smiley(GLuint program) {
    vec2 smiley_face[362];
    vec3 smiley_face_Color[362];
    float radius = 0.3;
    float x_value_circle, y_value_circle;
    float intoradian = (M_PI / 180);
    smiley_face[0] = vec2(-0.5 , 0.4);
    smiley_face_Color[0] = vec3(1.0, 1.0, 0.0);
    for(int i=1 ; i<362 ; i++) {
        x_value_circle = (cos(i*intoradian) * radius) - 0.5;
        y_value_circle = ((sin(i*intoradian) * radius)) + 0.4;
        smiley_face[i] = vec2(x_value_circle , y_value_circle);
        smiley_face_Color[i] = vec3(1.0 , 1.0 , 0.0);
    }
    bufferGenerator(smiley_face, sizeof(smiley_face), smiley_face_Color, sizeof(smiley_face_Color), program);
    glDrawArrays( GL_TRIANGLE_FAN, 0, 362 );    // draw the points

    vec2 smiley_eye1[362];
    vec3 smiley_eye1_Color[362];
    float radius_eye1 = 0.05;
    float x_value_circle_eye1, y_value_circle_eye1;
    smiley_eye1[0] = vec2(-0.6 , 0.5);
    smiley_eye1_Color[0] = vec3(0.0, 0.0, 0.0);
    for(int i=1 ; i<362 ; i++) {
        x_value_circle_eye1 = (cos(i*intoradian) * radius_eye1) - 0.6;
        y_value_circle_eye1 = ((sin(i*intoradian) * radius_eye1)) + 0.5;
        smiley_eye1[i] = vec2(x_value_circle_eye1 , y_value_circle_eye1);
        smiley_eye1_Color[i] = vec3(0.0 , 0.0 , 0.0);
    }
    bufferGenerator(smiley_eye1, sizeof(smiley_eye1), smiley_eye1_Color, sizeof(smiley_eye1_Color), program);
    glDrawArrays( GL_TRIANGLE_FAN, 0, 362 );    // draw the points

    vec2 smiley_eye2[362];
    vec3 smiley_eye2_Color[362];
    float radius_eye2 = 0.05;
    float x_value_circle_eye2, y_value_circle_eye2;
    smiley_eye2[0] = vec2(-0.4 , 0.5);
    smiley_eye2_Color[0] = vec3(0.0, 0.0, 0.0);
    for(int i=1 ; i<362 ; i++) {
        x_value_circle_eye2 = (cos(i*intoradian) * radius_eye2) - 0.4;
        y_value_circle_eye2 = ((sin(i*intoradian) * radius_eye2)) + 0.5;
        smiley_eye2[i] = vec2(x_value_circle_eye2 , y_value_circle_eye2);
        smiley_eye2_Color[i] = vec3(0.0 , 0.0 , 0.0);
    }
    bufferGenerator(smiley_eye2, sizeof(smiley_eye2), smiley_eye2_Color, sizeof(smiley_eye2_Color), program);
    glDrawArrays( GL_TRIANGLE_FAN, 0, 362 );    // draw the points

    vec2 smiley_mouth[362];
    vec3 smiley_mouth_Color[362];
    float radius_mouth = 0.1;
    float x_value_circle_mouth, y_value_circle_mouth;
    smiley_mouth[0] = vec2(-0.5 , 0.3);
    smiley_mouth_Color[0] = vec3(0.0, 0.0, 0.0);
    for(int i=1 ; i<362 ; i++) {
        x_value_circle_mouth = (cos(i*intoradian) * radius_mouth) - 0.5;
        y_value_circle_mouth = 0.2*(((sin(i*intoradian) * radius_mouth))) + 0.3;
        smiley_mouth[i] = vec2(x_value_circle_mouth , y_value_circle_mouth);
        smiley_mouth_Color[i] = vec3(0.0 , 0.0 , 0.0);
    }
    bufferGenerator(smiley_mouth, sizeof(smiley_mouth), smiley_mouth_Color, sizeof(smiley_mouth_Color), program);
    glDrawArrays( GL_TRIANGLE_FAN, 0, 362 );    // draw the points

    vec2 smiley_nose[362];
    vec3 smiley_nose_Color[362];
    float radius_nose = 0.03;
    float x_value_circle_nose, y_value_circle_nose;
    smiley_nose[0] = vec2(-0.5 , 0.4);
    smiley_nose_Color[0] = vec3(1.0, 0.0, 0.0);
    for(int i=1 ; i<362 ; i++) {
        x_value_circle_nose = (cos(i*intoradian) * radius_nose) - 0.5;
        y_value_circle_nose = ((sin(i*intoradian) * radius_nose)) + 0.4;
        smiley_nose[i] = vec2(x_value_circle_nose , y_value_circle_nose);
        smiley_nose_Color[i] = vec3(1.0 , 1.0 , 0.0);
    }
    bufferGenerator(smiley_nose, sizeof(smiley_nose), smiley_nose_Color, sizeof(smiley_nose_Color), program);
    glDrawArrays( GL_TRIANGLE_FAN, 0, 362 );    // draw the points
}
void some_shape(GLuint program) {
    vec2 shape_points[8] = {vec2(0.7 , 0.6) , vec2(0.4 , 0.6) , vec2(0.4 , 0.3) , vec2(0.7 , 0.3),
                            vec2(0.8 , 0.4) , vec2(0.8 , 0.7) , vec2(0.5 , 0.7) , vec2(0.4 , 0.6)};
    vec3 shape_points_color[8] = {vec3 (1.0 , 0.0 , 0.0),
								  vec3 (0.0 , 1.0 , 0.0),
								  vec3 (0.0 , 0.0 , 1.0),
								  vec3 (0.0 , 1.0 , 0.0),
								  vec3 (0.0 , 0.0 , 1.0),
								  vec3 (0.0 , 1.0 , 0.0),
								  vec3 (0.0 , 0.0 , 1.0),
								  vec3 (0.0 , 1.0 , 0.0)};
    bufferGenerator(shape_points, sizeof(shape_points), shape_points_color, sizeof(shape_points_color), program);
    glDrawArrays( GL_TRIANGLE_FAN, 0, 8 );
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

    glutCreateWindow( "Blue Square" );

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
