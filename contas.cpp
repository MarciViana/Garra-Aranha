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

void converteCoordenadas(int x, int y, struct posicao *mouse, struct posicao tamanhoTela){
	mouse->y=-1*(y-(tamanhoTela.y/2));
	mouse->x=x-(tamanhoTela.x/2);
}

bool clique(struct posicao mouse, struct botao botao1){
	if ((mouse.y>=(botao1.coordenadas.y-botao1.tamanho.y))&&(mouse.y<=(botao1.coordenadas.y+botao1.tamanho.y))&&(mouse.x>=(botao1.coordenadas.x-botao1.tamanho.x))&&(mouse.x<=(botao1.coordenadas.x+botao1.tamanho.x))){    
		return true;
	}
	return false;
}

int distanciaEntrePontos(Posicao p, Posicao q){
    int resultado = sqrt((p.x - q.x)*(p.x - q.x)+(p.y - q.y)*(p.y - q.y)+(p.z - q.z)*(p.z - q.z));
    return resultado;
}

bool esferaDentroDaOutra(Colisao aranha, Colisao obj){
	int d = distanciaEntrePontos(aranha.centro, obj.centro);
	if(aranha.raio>(d+obj.raio))
		return true;
	else
		return false;
}

bool esferaEncostaNaOutra(Colisao aranha, Colisao obj){
	int d = distanciaEntrePontos(aranha.centro, obj.centro);
	if(aranha.raio>(d+obj.raio))
		return true;
	else
		return false;
}
