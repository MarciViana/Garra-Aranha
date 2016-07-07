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

void desenhaBotao(struct botao botao1){
  	glPushMatrix();
	  	glTranslatef(botao1.coordenadas.x, botao1.coordenadas.y, 0);
	  	glEnable(GL_BLEND);
		    glEnable(GL_TEXTURE_2D);
			    glBindTexture(GL_TEXTURE_2D, botao1.textura);
			    glBegin(GL_QUADS);
			        glTexCoord2f(0, 0); glVertex3f(-botao1.tamanho.x/2, -botao1.tamanho.y/2,  0);
			        glTexCoord2f(1, 0); glVertex3f( botao1.tamanho.x/2, -botao1.tamanho.y/2,  0);
			        glTexCoord2f(1, 1); glVertex3f( botao1.tamanho.x/2,  botao1.tamanho.y/2,  0);
			        glTexCoord2f(0, 1); glVertex3f(-botao1.tamanho.x/2,  botao1.tamanho.y/2,  0);
			    glEnd();
		    glDisable(GL_TEXTURE_2D);
	    glDisable(GL_BLEND);
   	glPopMatrix();
}

