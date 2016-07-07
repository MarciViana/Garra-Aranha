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

void animaAranha(Aranha *a, int cont[4], float *tamTeia, float *descer,sf::Music *musicaAranha ,sf::Music *musicaInicio){
	//gira a aranha para ela descer	
	if (a->est==colide&&*descer==0){
		*descer=1;
		a->anguloCima=angCabecaCima;
	}
	//desce a aranha
	if(*descer==1){
		a->p.y=a->p.y-0.1;
		cont[0]+=1;
		*tamTeia=*tamTeia+0.1;
		desenhaTeia(*a,*tamTeia);
	}
	//sobe a aranha
	if((cont[0]==110|| a->est==inativo)&& a->anguloCima.x==angCabecaCima.x){
		a->est=inativo;
		*descer=0;
		a->p.y=a->p.y+0.1;
		*tamTeia=*tamTeia-0.1;
		desenhaTeia(*a,*tamTeia);
		cont[1]+=1;
	}
	//vai pro lado esquerdo
	if(cont[1]==cont[0] &&  a->est==inativo ){
		//cont[0]=0;
		if(a->angulosPatas.x==anguloPatasFechadas.x){
			a->p.x=a->p.x-0.1;
			cont[2]+=1;
		}
		else{
			cont[3]=69;
			cont[2]=70+(a->anda*10);
		}
		a->anguloCima = angCabecaBaixo;
	}
	//vai pro lado direito
	if(cont[2]==70+(a->anda*10)){
		/*cont[1]=0;*/
		cont[0]=0;
		a->p.x=a->p.x+0.1;
		cont[3]+=1;
		a->est=voltando;
		a->angulosPatas = anguloPatasAbertas;
	}
	if(cont[3]==70){
		cont[2]=0;
		cont[1]=0;
		a->est=ativo;
		musicaAranha->stop();
		musicaInicio->setLoop(true);
		musicaInicio->play();
		cont[3]=0;
		a->anda=0;
		
	}
	a->colide.centro=a->p;
	a->colide.centro.y = a->p.y+a->colide.raio;
}

void desenhaAranha(Aranha a, float cor){
   glPushMatrix();
        glColor3f(0.25,0.1,0.2);
        glTranslatef(a.p.x,a.p.y,a.p.z);
   		// glRotatef((GLfloat)a.anguloCima.x,(GLfloat)a.anguloCima.y,(GLfloat)a.anguloCima.z,1.0); // colocar aranha para mexer p os lados, girar em y
   		glRotatef((GLfloat)a.anguloCima.x,(GLfloat)a.anguloCima.y,(GLfloat)a.anguloCima.z,1.0);
      	//tronco da aranha
      	glScalef (0.5, 0.5, 0.5);
      	glutSolidSphere(1,10,10);
      	for (int i = 0; i < 4 ; i++){
         	glPushMatrix();
	            glRotatef((GLfloat)360/12*i,0.0,0.0,1.0);
	            desenhaPata(a.angulosPatas);
	        glPopMatrix();
	        glPushMatrix();
	            glRotatef((GLfloat)((360/12*i)-180),0.0,0.0,1.0);
	            desenhaPata(a.angulosPatas);
	        glPopMatrix();
	    }
	    //bunda
	    glPushMatrix();
		
	        glRotatef((GLfloat)360/12*5,0.0,0.0,1.0);
	        glTranslatef(1.0+1.3-0.3,0.0,0.0);
	        glutSolidSphere(1.3,10,10);
	    glPopMatrix();
	    //cabeça
	    glPushMatrix();
		
	        glRotatef((GLfloat)(360/12*5)-180,0.0,0.0,1.0);
	        glTranslatef(1.0+0.5-0.2,0.0,0.0);
	        glutSolidSphere(0.5,10,10);
	      	glPopMatrix();
	   
	glPopMatrix();
}

void desenhaTeia(Aranha a, int tamTeia){
	glColor3f(1,1,1);
   	glPushMatrix();
        glTranslatef (a.p.x,12-tamTeia,a.p.z);
        glScalef (0.05, 15, 0.05);
     	glutSolidCube(1.0);
   	glPopMatrix();
}

void desenhaPata(Angulo aPatas){
   glPushMatrix();
      glScalef (0.5, 0.5, 0.5);
      glTranslatef(-1.0,-0.7,0);
      glRotatef( (GLfloat)-90,45,0.0,1.0);
      glTranslatef (-1.0, 0.0, 0.0);
      glRotatef ((GLfloat) aPatas.x, 0.0, 0.0, 1.0);
      glTranslatef (2.0, 0.0, 0.0);
      desenhaFalange();

      glTranslatef (2.0, 0.0, 0.0);
      glScalef (0.9, 0.9, 1.0);
      glRotatef ((GLfloat) aPatas.y, 0.0, 0.0, 1.0);
      glTranslatef (2.0, 0.0, 0.0);
      desenhaFalange();

      glTranslatef (2.0, 0.0, 0.0);
      glScalef (0.9, 0.9, 1.0);
      glRotatef ((GLfloat) aPatas.z, 0.0, 0.0, 1.0);
      glTranslatef (2.0, 0.0, 0.0);
      desenhaFalange();
   glPopMatrix();
}

void desenhaFalange(){
   glPushMatrix();
         glTranslatef (-2.0, 0.0, 0.0);
         glutSolidSphere(0.25,7,7);
   glPopMatrix();
   glPushMatrix();
      glScalef (4.0, 0.4, 0.4);
      glutSolidCube(1.0);
   glPopMatrix();
}
