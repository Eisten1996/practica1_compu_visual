#include <stdlib.h>
#include<conio.h>
#include <gl/glut.h>
#include<math.h>
#include<iostream>
using namespace std;
float delta=0.2;
// declaracion de variables
// GLfloat ...;
// theta[] me indica los ?ngulos iniciales en los 3 ejes
static GLfloat theta[] = {0.0,0.0,0.0};
// eje es el ?ngulo a rotar
static GLint eje = 2;
//inicializamos el valor de L
int L = 30;
//declaramos los metodos de la circunferencia y semicircunferencias
void circunferencia_punto_medio(float,float,int);
void semi_circunferencia_punto_medio_1(float,float,int);
void semi_circunferencia_punto_medio_2(float,float,int);
void semi_circunferencia_punto_medio_3(float,float,int);
void semi_circunferencia_punto_medio_4(float,float,int);
void lienzo(void);

// construya su poligono base

// dibujamos nuestra escena
//
void ejes(void)
{
    //hacemos rotaciones de los ejes X y Y para poder visualizar el eje Z
    glRotatef(45.0,1.0,0.0,0.0);
    glRotatef(-45.0,0.0,1.0,0.0);
    glRotatef(0.0,0.0,0.0,1.0);

    //eje x
    glColor3f(1,0,0);
    glBegin(GL_LINES);
    glVertex3f(0,0,0);
    glVertex3f(60,0,0);
    glEnd();

    //eje y
    glColor3f(1,1,0);
    glBegin(GL_LINES);
    glVertex3f(0,0,0);
    glVertex3f(0,60,0);
    glEnd();

    //eje z
    glColor3f(0,0,1);
    glBegin(GL_LINES);
    glVertex3f(0,0,0);
    glVertex3f(0,0,60);
    glEnd();
}

//creamos la cara del cubo en los ejes X y Y
void cara()
{
    glPointSize(2.0);
    glBegin(GL_POLYGON);

    glVertex3f(0.0,0.0,0.0);
    glVertex3f(L,0.0,0.0);
    glVertex3f(L,L,0.0);
    glVertex3f(0.0,L,0.0);
    glEnd();
    lienzo();

}
// construimos un cubo compuesto por todas las caras
void cubo(void)
{
    //mostramos la primera cara en
    glColor3f(0.301,0.745,0.843);
    cara();

    //rotamos en el eje X
    glRotatef(90.0,1.0,0.0,0.0);
    glRotatef(0.0,0.0,1.0,0.0);
    glRotatef(0.0,0.0,0.0,1.0);
    glColor3f(0.843,0.301,0.843);
    cara();

    //rotamos en el eje Y
    glRotatef(0.0,1.0,0.0,0.0);
    glRotatef(90.0,0.0,1.0,0.0);
    glRotatef(0.0,0.0,0.0,1.0);
    glColor3f(0.843,0.435,0.301);
    cara();

    //hacemos una traslacion en el eje Z
    glTranslatef(0.0,0.0,L);
    glColor3f(0.827,0.843,0.301);
    cara();

    //hacemos una traslacion en el eje Y y rotamos en el eje X
    glTranslatef(0.0,L,0.0);
    glRotatef(-90.0,1.0,0.0,0.0);
    glRotatef(0.0,0.0,1.0,0.0);
    glRotatef(0.0,0.0,0.0,1.0);
    glColor3f(0.321,0.843,0.301);
    cara();

    //hacemos una traslacion en el eje X y rotamos en el eje Y
    glTranslatef(L,0.0,0.0);
    glRotatef(0.0,1.0,0.0,0.0);
    glRotatef(90.0,0.0,1.0,0.0);
    glRotatef(0.0,0.0,0.0,1.0);
    glColor3f(0.207,0.294,0.313);
    cara();

}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    ejes();

    glRotatef(theta[0],1.0,0.0,0.0);
    glRotatef(theta[1],0.0,1.0,0.0);
    glRotatef(theta[2],0.0,0.0,1.0);

    cubo();

    glPopMatrix();


    glFlush();
    // intercambiamos los buffers, el que se muestra y el que esta oculto
    glutSwapBuffers();
}


// esta funcion controla el angulo de rotacion segun el eje de giro
void girar_objeto_geometrico ()
{
    theta[eje] += delta;
    if(theta[eje]>360)
        theta[eje] -= 360.0;
    display();
}

//funcion para el teclado
void teclado(unsigned char tecla,int x,int y)
{
    switch(tecla)
    {
    case 'A' :
        eje = 0;
        break;
    case 'S' :
        eje = 1;
        break;
    case 'D' :
        eje = 2;
        break;
    case '+' :
        if (delta<5.0)
            delta+=0.1;
        break;
    case '-' :
        if (delta>0.2)
            delta-=0.1;
        break;
    case 'X' :
        exit(0) ;
        break;
    }
}

//dibujamos la circunferencia completa
void circunferencia_punto_medio(float xc,float yc,int R)
{
    // discretizacion valida para un octante
    R=R*(sqrt(2)-1)/2;
    int x=0;
    int y=R,d=1-R;
    glBegin(GL_POINTS);
    glColor3f(1,0.0,0.0);
    glVertex2f(x,y);
    while (x<y)
    {
        if (d<0)
        {
            d=d+2*x+3;
        }
        else
        {
            d=d+2*(x-y)+5;
            y=y-1;
        }
        x++;

        //con estos puntos completamos la circunferencia
        glVertex2f(x+xc,y+yc);
        glVertex2f(x+xc,-y+yc);
        glVertex2f(-x+xc,y+yc);
        glVertex2f(-x+xc,-y+yc);
        glVertex2f(y+xc,x+yc);
        glVertex2f(y+xc,-x+yc);
        glVertex2f(-y+xc,x+yc);
        glVertex2f(-y+xc,-x+yc);

    }
    glEnd();
}

//dibujamos el tercer cuadrante
void semi_circunferencia_punto_medio_1(float xc,float yc,int R)
{
// discretizacion valida para un octante octante
    int x=0;
    int y=R,d=1-R;
    glBegin(GL_POINTS);
    glColor3f(1,0.0,0.0);
    while (x<y)
    {
        if (d<0)
        {
            d=d+2*x+3;
        }
        else
        {
            d=d+2*(x-y)+5;
            y=y-1;
        }
        x++;

        //dibujamos el tercer cuadrante
        glVertex2f(-x+xc,-y+yc);
        glVertex2f(-y+xc,-x+yc);

    }
    glEnd();
}

//dibujamos el primer cuadrante
void semi_circunferencia_punto_medio_2(float xc,float yc,int R)
{
// discretizacion valida para un octante
    int x=0;
    int y=R,d=1-R;
    glBegin(GL_POINTS);
    glColor3f(1,0.0,0.0);
    while (x<y)
    {
        if (d<0)
        {
            d=d+2*x+3;
        }
        else
        {
            d=d+2*(x-y)+5;
            y=y-1;
        }
        x++;

        //dibujamos el primer cuadrante
        glVertex2f(x+xc,y+yc);
        glVertex2f(y+xc,x+yc);
    }
    glEnd();
}

//dibujamos el cuarto cuadrante
void semi_circunferencia_punto_medio_3(float xc,float yc,int R)
{
// discretizacion valida para un octante

    int x=0;
    int y=R,d=1-R;
    glBegin(GL_POINTS);
    glColor3f(1,0.0,0.0);
    while (x<y)
    {
        if (d<0)
        {
            d=d+2*x+3;
        }
        else
        {
            d=d+2*(x-y)+5;
            y=y-1;
        }
        x++;

        //dibujamos el cuarto cuadrante
        glVertex2f(x+xc,-y+yc);
        glVertex2f(y+xc,-x+yc);

    }
    glEnd();
}

//dibujampsos el segundo cuadrante
void semi_circunferencia_punto_medio_4(float xc,float yc,int R)
{
// discretizacion valida para un octante

    int x=0;
    int y=R,d=1-R;
    glBegin(GL_POINTS);
    glColor3f(1,0.0,0.0);
    while (x<y)
    {
        if (d<0)
        {
            d=d+2*x+3;
        }
        else
        {
            d=d+2*(x-y)+5;
            y=y-1;
        }
        x++;

        //dibujampsos el segundo cuadrante
        glVertex2f(-x+xc,y+yc);
        glVertex2f(-y+xc,x+yc);

    }
    glEnd();
}

void lienzo()
{
    circunferencia_punto_medio(L/2,L/2,L);
    semi_circunferencia_punto_medio_1(L,L,L/2);
    semi_circunferencia_punto_medio_1(L/2,L/2,L/2);
    semi_circunferencia_punto_medio_2(0,0,L/2);
    semi_circunferencia_punto_medio_2(L/2,L/2,L/2);
    semi_circunferencia_punto_medio_3(0,L,L/2);
    semi_circunferencia_punto_medio_4(L,0,L/2);
}

// control de ventana (recuerde el volumen de visualizacion)
// modifique dicho volumen segun su conveniencia
void myReshape(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w <=h)
        glOrtho(-45.0,40.0,-45.0*(GLfloat)h/(GLfloat)w,
                45.0*(GLfloat)h/(GLfloat)w, -45.0, 45.0);
    else
        glOrtho(-45.0*(GLfloat)w/(GLfloat)h,
                45.0*(GLfloat)w/(GLfloat)h, -45.0,45.0,-45.0,45.0);
    glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600,600);
    glutCreateWindow("mi objeto bajo rotaciones");
    glutReshapeFunc(myReshape);
    // invocamos a display() para dibujar nuestra escena
    glutDisplayFunc(display);
    // esta funcion llama a girar_objeto_geometrico() mientras no haya evento //alguno
    //ocasionado por el usuario
    glutIdleFunc(girar_objeto_geometrico);
    glutKeyboardFunc(teclado);
    /*glutMouseFunc(mouse);*/
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
