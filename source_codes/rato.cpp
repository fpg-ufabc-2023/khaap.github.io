/*
============================================================
|   Titulo:  Rato 3D - GLUT OpenGL                         |
|   Autor:   Pedro Domingos Napole Certo                   |
|   Data:    10/2023                                       |
|   Comando: g++ -o rato rato.cpp -lglut -lGL -lGLU        |
============================================================
*/

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

#define W_WIDTH 500
#define W_HEIGHT 500

void display(void);
void reshape(int, int);
void timer(int);

void init()
{
    glClearColor(0.0, 0.0, 1.0, 1.0);
    glShadeModel(GL_FLAT);
}


int main(int argc, char** argv)
{
    std::cout << "Iniciando GLUT..." << std::endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);        //Tendo dois buffers, conseguimos alternar entre um e outro (enquanto um é mostrado na tela, o outro é calculado em background), salvando processamento e aumentando a performance das animações
    
    std::cout<< "Configurando a janela" << std::endl;
    glutInitWindowPosition(500,100);
    glutInitWindowSize(W_WIDTH, W_HEIGHT);

    std::cout<< "Criando a janela" << std::endl;
    glutCreateWindow("Rato - KHAP");
    init();
    //Especifica a função de callback para a janela
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape);       //<- Chamado toda vez que a janela é redimensionada
    // glutTimerFunc(1000,timer,0);    //Cada vez que passar 1000 ms, timer é chamado

    glutMainLoop();
    return 0;
}

float x_postition = -10.0;          //Posição inicial do quadrado
int sentido = 1;                     //valor é multiplicado pela posicao (quando negativo, quadrado vai pra trás)

/// @brief Toda vez que chamamos essa função, desenhamos um "frame" na tela. Varios frames rápidamente alteranados geram efeito de animação
void display(void)
{
    //Funcao de display. Callback chamado pelo OpenGL
    //Primeiro devemos limpar o buffer do frame
    glClear(GL_COLOR_BUFFER_BIT);
    //glLoadIdentity();       //Reseta as matrizes do sistema (transformações lineares)
    // glPointSize(5.0);       //Define o tamanho dos pontos

    //AQUI COMEÇAMOS A DESENHAR NA TELA!
    
    glRotatef(0.05, 0.0, 1.0, 0.0);

    //Orelha esquerda
    glPushMatrix();
    glColor3f(0.75, 0.5, 0.5); 
    glTranslatef(1.25, 1.25, -0.6);
    glRotatef((GLfloat)-25.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 2.0, 0.01);
    glutSolidSphere(0.5, 10, 8);
    glPopMatrix();

    //Orelha direita
    glPushMatrix();
    glColor3f(0.75, 0.5, 0.5); 
    glTranslatef(-1.25, 1.25, -0.6);
    glRotatef((GLfloat)25.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 2.0, 0.01);
    glutSolidSphere(0.5, 10, 8);
    glPopMatrix();   

    //Cabeça
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);       //Define as cores do objeto
    glRotatef ((GLfloat) 75.0, 1.0, 0.0, 0.0);
    glScalef(0.85, 1.0, 1.5);
    glutSolidSphere(1.0, 8, 8);
    glPopMatrix();

      //Olho esquerdo
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0); 
    glTranslatef(0.85, 0.2, 0.0);
    glScalef(0.5, 0.5, 0.5);
    glutSolidSphere(0.5, 10, 8);
    glPopMatrix();

     //Olho direito
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0); 
    glTranslatef(-0.85, 0.2, 0.0);
    glScalef(0.5, 0.5, 0.5);
    glutSolidSphere(0.5, 10, 8);
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    std::cout << "Janela redimensionada..." << std::endl;
    //Viewport é a "tela" virtual onde os objetos podem ser renderizados. A janela é como uma "camera" dentro do viewport
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);             //Muda a forma de representação matricial para modo de projeção (utilizado para definir a projeção)
    glLoadIdentity();                               //Reseta os parametros
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);   //Define o modo de renderização para Ortogonal 2D
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();
    gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}