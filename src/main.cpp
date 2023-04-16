/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
//  Autor: Cesar Tadeu Pozzer
//         05/2020
//
//  Pode ser utilizada para fazer desenhos, animacoes, e jogos simples.
//  Tem tratamento de mouse e teclado
//  Estude o OpenGL antes de tentar compreender o arquivo gl_canvas.cpp
//
//  Versao 2.0
//
//  Instru��es:
//	  Para alterar a animacao, digite numeros entre 1 e 3
// *********************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"

#include "managers/SceneManager.h"
#include "base/vectors/Vector2D.h"

int screenWidth = 800, screenHeight = 800; //largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int mouseX, mouseY; //variaveis globais do mouse para poder exibir dentro da render().
SceneManager* sceneManager = new SceneManager(screenWidth, screenHeight);

//funcao chamada toda vez que uma tecla for pressionada.
void keyboard(int key)
{
    printf("\nTecla: %d" , key);
}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
    printf("\nLiberou: %d" , key);
}

void mouse(int button, int state, int wheel, int direction, int x, int y) {
    sceneManager->mouse(button, state, wheel, direction, ivec2{x, y});
}

void render() {
    sceneManager->render(screenWidth, screenHeight);
}

int main(void) {
    CV::init(&screenWidth, &screenHeight, "Vemp - Vectors Manipulation Program");
    CV::run();
}
