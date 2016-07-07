#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <SFML/Audio.hpp>
#include "contas.h"
#include "botao.h"
#include "aranha.h"
#include "fundo.h"

int carregar_textura(char const nome[40]){
    int textura;
    textura = SOIL_load_OGL_texture( nome ,SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
        if (textura == 0 ) { printf("Erro: %s %s'\n", nome, SOIL_last_result()); }  
    return textura;
}

void desenhaTextura(GLuint textura, int x1, int x2, int y1, int y2, int z1, int z2, int z3, int z4) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textura);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f( x1, y1,  z1);
        glTexCoord2f(1, 0); glVertex3f( x2, y1,  z2);
        glTexCoord2f(1, 1); glVertex3f( x2, y2,  z3);
        glTexCoord2f(0, 1); glVertex3f( x1, y2,  z4);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void Paredes( GLuint texturaQuadrado1, GLuint texturaQuadrado2, GLuint texturaQuadrado3, GLuint texturaQuadrado4, GLuint texturaQuadrado5){
    desenhaTextura(texturaQuadrado1,-8, 8,-8, 8,-10,-10,-10,-10);
    desenhaTextura(texturaQuadrado2, 8, 8,-8, 8,-10,  0,  0,-10);
    desenhaTextura(texturaQuadrado3,-8,-8,-8, 8,  0,-10,-10,  0);
    desenhaTextura(texturaQuadrado4,-8, 8,-8,-8,  0,  0,-10,-10);
    desenhaTextura(texturaQuadrado5,-8, 8, 8, 8,-10,-10,  0,  0);
}

void Floresta( GLuint texturaFloresta, GLuint texturaArvores){
    desenhaTextura(texturaFloresta,-10, 10,-8,-8,  6,  6,-10,-10);
    desenhaTextura(texturaArvores,  10, 10,-8,12,-10,  6,  6,-10);
    desenhaTextura(texturaArvores, -10,-10,-8,12,  6,-10,-10,  6);
}
void Teia(GLuint texturaTeia){
	desenhaTextura(texturaTeia,-8,-8,-8, 8,  0,-10,-10,  0);
}
