#define GLEW_STATIC

#include "Angel.h"
#include<math.h>

void
bufferGenerator(struct vec4 polygonPoints[],int polyPoints_size, struct vec4 colorPonts[],int colorPoints_size, struct mat4 transformed_matrix);
GLuint program;
vec4 colors[36] , points[36];
mat4 rotatng_matrix_x , rotatng_matrix_y , rotatng_matrix_z , rotatng_matrix, transformed_matrix;
mat4 scaling_matrix, translating_matrix;
int axis=0 , translate_to , scale_to , perform_operation;
float theta[3] = {0.0 , 0.0 , 0.0} , scale_by = 1.0 , translate_by;
float theta_delta = 1 , scale_delta = 0.1 , translate_delta = 0.1;
void rotate_cube();
void translate_cube();
void scale_cube();
void reset();
GLfloat scalingData[3]={1.0,1.0,1.0};
GLfloat rotationData[3]={0.0,0.0,0.0};
GLfloat translationData[3]={0.0,0.0,0.0};
vec4 vertices[8] = {
vec4( -0.5, -0.5,  0.5, 1.0 ),
vec4( -0.5,  0.5,  0.5, 1.0 ),
vec4(  0.5,  0.5,  0.5, 1.0 ),
vec4(  0.5, -0.5,  0.5, 1.0 ),
vec4( -0.5, -0.5, -0.5, 1.0 ),
vec4( -0.5,  0.5, -0.5, 1.0 ),
vec4(  0.5,  0.5, -0.5, 1.0 ),
vec4(  0.5, -0.5, -0.5, 1.0 )
};
vec4 vertex_colors[8] = {
vec4( 0.0, 0.0, 0.0, 1.0 ),  // black
vec4( 1.0, 0.0, 0.0, 1.0 ),  // red
vec4( 1.0, 1.0, 0.0, 1.0 ),  // yellow
vec4( 0.0, 1.0, 0.0, 1.0 ),  // green
vec4( 0.0, 0.0, 1.0, 1.0 ),  // blue
vec4( 1.0, 0.0, 1.0, 1.0 ),  // magenta
vec4( 1.0, 1.0, 1.0, 1.0 ),  // white
vec4( 0.0, 1.0, 1.0, 1.0 )   // cyan

};

int Index = 0;
void quad( int a, int b, int c, int d )
{
    colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
    colors[Index] = vertex_colors[b]; points[Index] = vertices[b]; Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; Index++;
    colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; Index++;
    colors[Index] = vertex_colors[d]; points[Index] = vertices[d]; Index++;
}

void construct_cube () {
    quad( 1, 0, 3, 2 );
    quad( 2, 3, 7, 6 );
    quad( 3, 0, 4, 7 );
    quad( 6, 5, 1, 2 );
    quad( 4, 5, 6, 7 );
    quad( 5, 4, 0, 1 );
}

void idle_window2() {
    glutPostRedisplay();
}
void
display()
{
    glClearColor(1.0 , 1.0 , 1.0 , 1.0);
    glClear( GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT );     // clear the window

    transformed_matrix = translating_matrix * rotatng_matrix * scaling_matrix;
    bufferGenerator(points , sizeof(points) , colors , sizeof(colors), transformed_matrix);
    glDrawArrays( GL_TRIANGLES, 0, 36 );

    glutSwapBuffers();
    glutPostRedisplay();
}

void reset() {
    for(int i=0;i<3;i++){
        scalingData[i]=1.0;
         rotationData[i]=0.0;
         translationData[i]=0.0;
    }

    mat4 identityMatrix;
    rotatng_matrix_x = identityMatrix;
    rotatng_matrix_y = identityMatrix;
    rotatng_matrix_z = identityMatrix;
    rotatng_matrix = identityMatrix;
    transformed_matrix = identityMatrix;
    scaling_matrix = identityMatrix;
    translating_matrix = identityMatrix;
}

void rotate_cube () {
    if(axis < 3){
        rotationData[axis] += theta_delta;
        if(rotationData[axis]>=360.0)
            rotationData[axis]=0.0;
    }

    else if(axis > 2){
        rotationData[axis-3] -= theta_delta;
        if(rotationData[axis-3]<=-360.0)
            rotationData[axis-3]=0.0;
    }


    switch(axis){
        case 0:rotatng_matrix_x=RotateX(rotationData[0]);break;
        case 1:rotatng_matrix_y=RotateY(rotationData[1]);break;
        case 2:rotatng_matrix_z=RotateZ(rotationData[2]);break;
        case 3:rotatng_matrix_x=RotateX(rotationData[0]);break;
        case 4:rotatng_matrix_y=RotateY(rotationData[1]);break;
        case 5:rotatng_matrix_z=RotateZ(rotationData[2]);break;
    }

    rotatng_matrix = rotatng_matrix_x * rotatng_matrix_y * rotatng_matrix_z;
}

void translate_cube() {
    if(translate_to < 3)
        translationData[translate_to] += translate_delta;
    else if(translate_to > 2)
        translationData[translate_to-3] -= translate_delta;

        translating_matrix = Translate(vec3(translationData[0],translationData[1],translationData[2]));
}

void scale_cube() {
    if(scale_to < 3)
        scalingData[scale_to] += scale_delta;
    else if(scale_to > 2){
        scalingData[scale_to-3] -= scale_delta;
        if(scalingData[scale_to-3]<=0.0)
            scalingData[scale_to-3]=0.0;
    }

    scaling_matrix = Scale(vec3(scalingData[0],scalingData[1],scalingData[2]));
}

void
init( void )
{
    construct_cube();
    program = InitShader( "vshader21.glsl", "fshader21.glsl" );
                          
}

void keyboard_function( unsigned char key, int x, int y )
{
    if(perform_operation == 1) {
        switch ( key ) {
        case 'q': exit( EXIT_SUCCESS ); break;
        case 'x': scale_to = 0 ; scale_cube() ; break;
        case 'y': scale_to = 1 ; scale_cube() ; break;
        case 'z': scale_to = 2 ; scale_cube() ; break;
        case 's': scale_to = 3 ; scale_cube() ; break;
        case 'h': scale_to = 4 ; scale_cube() ; break;
        case 'a': scale_to = 5 ; scale_cube() ; break;
        case 'p': scale_delta += 0.1 ; break;
        case 'm': scale_delta -= 0.1 ;if(scale_delta<=0)scale_delta=0;break;
        case 'r': reset() ; break;
        }
    }
    else if(perform_operation == 2) {
        switch ( key ) {
            case 'q': exit( EXIT_SUCCESS ); break;
            case 'x': axis = 0 ; rotate_cube() ; break;
            case 'y': axis = 1 ; rotate_cube() ; break;
            case 'z': axis = 2 ; rotate_cube() ; break;
            case 's': axis = 3 ; rotate_cube() ; break;
            case 'h': axis = 4 ; rotate_cube() ; break;
            case 'a': axis = 5 ; rotate_cube() ; break;
            case 'p': theta_delta += 1.0 ; if(theta_delta>=360.0)theta_delta=0.0;break;
            case 'm': theta_delta -= 1.0 ;if(theta_delta<=0.0)theta_delta=0.0; break;
            case 'r': reset() ; break;
        }
    }
    else if(perform_operation == 3) {
        switch ( key ) {
            case 'q': exit( EXIT_SUCCESS ); break;
            case 'x': translate_to = 0 ; translate_cube() ; break;
            case 'y': translate_to = 1 ; translate_cube() ; break;
            case 'z': translate_to = 2 ; translate_cube() ; break;
            case 's': translate_to = 3 ; translate_cube() ; break;
            case 'h': translate_to = 4 ; translate_cube() ; break;
            case 'a': translate_to = 5 ; translate_cube() ; break;
            case 'p': translate_delta += 0.1 ; break;
            case 'm': translate_delta -= 0.1 ; if(translate_delta<=0)translate_delta=0;break;
            case 'r': reset() ; break;
        }
    }
}


void
bufferGenerator(struct vec4 polygonPoints[],int polyPoints_size, struct vec4 colorPonts[],int colorPoints_size, struct mat4 transformed_matrix) {

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

    GLint uniform_m_transform = glGetUniformLocation(program, "rot");
    glUniformMatrix4fv(uniform_m_transform , 1 , GL_TRUE , &transformed_matrix[0][0]);
}

void process_menu_events(int option) {
    switch (option) {
        case 1: perform_operation = 1 ; glutKeyboardFunc( keyboard_function ) ; break;
        case 2: perform_operation = 2 ; glutKeyboardFunc( keyboard_function ) ; break;
        case 3: perform_operation = 3 ; glutKeyboardFunc( keyboard_function ) ; break;
    }
    glutPostRedisplay();
}

int window_id;
int
main( int argc, char **argv )
{
    printf("\n Once the program is up and running : ");
    printf("\n No animation or changes will happen");
    printf("\n To change - Right click of mouse button will show you a drop down menu containing \n Scale \n Rotate \n Translate");
    printf("\n On selecting any one from the menu you will be able to perform the following : ");
    printf("\n key press 'x' : scale/rotate/translate along positive x-axis");
    printf("\n key press 's' : scale/rotate/translate along negative x-axis");
    printf("\n key press 'y' : scale/rotate/translate along positive y-axis");
    printf("\n key press 'h' : scale/rotate/translate along negative y-axis");
    printf("\n key press 'z' : scale/rotate/translate along positive z-axis");
    printf("\n key press 'a' : scale/rotate/translate along negative z-axis");
    printf("\n key press 'p' : Increases speed of rotation / delta of scaling / delta of translating respectively");
    printf("\n key press 'm' : Decreases speed of rotation / delta of scaling / delta of translating respectively");
    printf("\n key press 'r' : Resets the cube to origin resetting all the values to default");
    printf("\n key press 'q' : Quits from output window");
    glutInit( &argc, argv );
#ifdef __APPLE__
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA );
#else
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
#endif
    glutInitWindowPosition(100,100);
    glutInitWindowSize( 500, 500 );

    window_id = glutCreateWindow( "assignment 4" );

#ifndef __APPLE__
    GLenum err = glewInit();
    if (GLEW_OK != err)
      fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
#endif

    init();
    glutDisplayFunc( display );
    int window_menu;
    window_menu = glutCreateMenu(process_menu_events);
    glutAddMenuEntry("Scale",1);
    glutAddMenuEntry("Rotate",2);
    glutAddMenuEntry("Translate",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutIdleFunc(idle_window2);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
