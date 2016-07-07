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
#include "insetos.h"

float virar=0.0, cor=0, descer=0, tamTeia=0;
int abaixa=0, music=0, gira=0, cima, cont[4]={0}, light0Ligada=1, volume = 75, tempoDeJogo;
GLuint texturaQuadrado1,texturaQuadrado2,texturaQuadrado3,texturaQuadrado4,texturaQuadrado5,texturaFloresta,texturaArvores,texturaTeia, texturaWin, texturaInicial, texturaGamaOver, texturaTutorial;
GLuint texturaPlay, texturaMenu;
Aranha a;
Insetos i[qntInsetos];
Posicao tamTela;
sf::Music musicaInicio,musicaAranha, musicaInseto, musicaGameOver;
OpcoesDeTela menu;
struct botao play, tutorial;

void redimensiona(int w, int h){
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   //glTranslatef (0.0, 0.0, -5.0);
   tamTela.x=w;
   tamTela.y=h;
}

void desenhaJogo(){
	glLoadIdentity ();
	float down=0;
	gluPerspective(65.0, (GLfloat) tamTela.x/(GLfloat) tamTela.y, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glColor3f(1,1,1);
	if(abaixa>0)
		down=3.5;
	if(virar>=3.5)
		virar--;
	else if(virar<=-5)
		virar++;
    	glLoadIdentity();
	if(cima>0)
		gira=0;
	if(gira>0)
		gluLookAt(0-gira, 1+cima, 7.0-gira-cima, 0.0+virar+gira, 0.0-down, 0.0-gira-cima, 0.0, 1.0, 0.0);
	else if(gira<0)
		gluLookAt(0-gira, 1+cima, 7.0+gira-cima, 0.0+virar+gira, 0.0-down, 0.0+gira-cima, 0.0, 1.0, 0.0);
		else
        	gluLookAt(0, 1.0+cima, 7.0-cima, 0.0+virar, 0-down, 0-cima, 0.0, 1.0, 0.0);
	//glEnable(GL_LIGHTING);
  	glEnable(GL_DEPTH_TEST);

	Floresta(texturaFloresta, texturaArvores);
	Paredes(texturaQuadrado1, texturaQuadrado2, texturaQuadrado3, texturaQuadrado4, texturaQuadrado5);
	Teia(texturaTeia);
	if(animaInsetos(&a,i, &musicaInseto)==qntInsetos){
		menu = win;
		musicaAranha.stop();
		musicaInicio.stop();
	}
	else{
		animaAranha(&a, cont, &tamTeia, &descer, &musicaAranha, &musicaInicio);
		desenhaAranha(a, cor);
	}
	glDisable(GL_DEPTH_TEST);
	//glDisable(GL_LIGHTING);

}

//inspirada na funcao desenha 2D do tulio e arthur
void desenha2D(){
	glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode (GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        glOrtho(-tamTela.x/2, tamTela.x/2, -tamTela.y/2, tamTela.y/2, -3.0, 3.0);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();
            desenhaTextura(texturaInicial, -tamTela.x/2, tamTela.x/2, -tamTela.y/2, tamTela.y/2, 0, 0, 0, 0);
			switch(menu){
				case inicial:
					desenhaBotao(play);
					desenhaBotao(tutorial);
					break;
				case Tutorial:
					desenhaTextura(texturaTutorial, -tamTela.x/2, tamTela.x/2, -tamTela.y/2, tamTela.y/2, 0, 0, 0, 0);
					break;
				case win:
					desenhaTextura(texturaWin, -tamTela.x/6+10, tamTela.x/6+10, -tamTela.y/6, tamTela.y/6, 0, 0, 0, 0);
					break;
				case gameOver:
					desenhaTextura(texturaGamaOver, -tamTela.x/5, tamTela.x/5, -tamTela.y/6, tamTela.y/6, 0, 0, 0, 0);
					break;
				}
            glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 1, 0, 0, 0, -9.0, 0, 1, 0);
}

void desenha(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor4f(1, 1, 1, 1);
    glLoadIdentity();

	switch(menu){
		case jogo:
			desenhaJogo();
			break;
			default:
				desenha2D();
	}
	    glutSwapBuffers();
}

void inicializa(){
	glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	musicaInicio.setVolume(volume);	musicaAranha.setVolume(volume); musicaInseto.setVolume(volume); musicaGameOver.setVolume(volume);
	musicaInicio.setLoop(true);
  	musicaInicio.play();

  	tempoDeJogo=0;
    menu = inicial;

  	a.angulosPatas = anguloPatasAbertas; a.anguloCima = angCabecaBaixo;
  	a.est = ativo;
  	for(int b=0;b<qntInsetos/2;b++){
  		i[b].est=inativo; i[b+(qntInsetos/2)].est=inativo;
  		criaMosca(&i[b]);	criaArainha(&i[b+(qntInsetos/2)]);
  	}
  	a.est= ativo;	a.p.x=0; 	a.p.y=5;	a.p.z=-5;	a.colide.raio = 3; a.anda=0;
}

void init(){
    glClearColor (1, 1, 1, 0);
    texturaQuadrado1 = carregar_textura("imagens/quadrado1.png");    texturaQuadrado2 = carregar_textura("imagens/quadrado2.png");
    texturaQuadrado3 = carregar_textura("imagens/quadrado3.png");    texturaQuadrado4 = carregar_textura("imagens/quadrado4.png");
	texturaQuadrado5 = carregar_textura("imagens/quadrado5.jpg");
	texturaFloresta  = carregar_textura("imagens/chao.jpg");		 texturaArvores = carregar_textura("imagens/floresta.jpg");
	texturaTeia = carregar_textura("imagens/teia.png");
	texturaInicial = carregar_textura("imagens/forest.png");		texturaTutorial = carregar_textura("imagens/tutorial2.png");	
	play.textura=carregar_textura("imagens/playbutton.png");		tutorial.textura=carregar_textura("imagens/tutorial.png");
	texturaWin = carregar_textura("imagens/win.png");				texturaGamaOver = carregar_textura("imagens/gameover.png");


  	musicaInicio.openFromFile("audios/casa.ogg");	musicaAranha.openFromFile("audios/aranha.ogg");		musicaInseto.openFromFile("audios/grito.ogg"); 	musicaGameOver.openFromFile("audios/GameOver.ogg");

  	play.tamanho.x=150; play.coordenadas.x=0;	play.tamanho.y=150; 	play.coordenadas.y=0;
  	tutorial.tamanho.x = 400 ; tutorial.coordenadas.x =0 ;  	tutorial.tamanho.y = 200; tutorial.coordenadas.y= -200;
  	inicializa();

   	glClearColor(1,1,1,1);
   	glEnable(GL_CULL_FACE);
   	glCullFace(GL_BACK);

   	glDepthFunc(GL_LESS);

   	glEnable(GL_LIGHT0);
   	glEnable(GL_NORMALIZE);
   	glEnable(GL_COLOR_MATERIAL);
   	glEnable(GL_LIGHTING);

   	glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
   	glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
   	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
   	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

   	glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
   	glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
   	glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
   	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

void mouseClick (int button, int state, int x, int y) { 
  struct posicao mouse;
  converteCoordenadas(x, y,&mouse, tamTela);
  if (button==GLUT_LEFT_BUTTON){
    switch(menu){
      case inicial:
        if(clique(mouse, play)){
          inicializa();
          menu=jogo;
        }
        else if(clique(mouse, tutorial))
        	menu=Tutorial;
        break;
    }
  }
}

//glutPassiveMotionFunc
void mouse ( int x, int y) {
	switch(menu){
		case jogo:
			if(x>=790)
				virar++;
			else if(x<=10)
				virar--;
			if(y>=585)
				abaixa++;
			else if(y<=15)
				abaixa--;
			break;
		case inicial:
		case win:
		case gameOver:
			break;
	}
}

void teclaEspecialJogo(int key){
	switch(key) {
		case GLUT_KEY_RIGHT:
			a.p.x++;
			a.anda++;
			break;
		case GLUT_KEY_LEFT:
			a.p.x--;
			a.anda--;
			break;
		case GLUT_KEY_UP:
			a.p.z--;
			break;
		case GLUT_KEY_DOWN:
			a.p.z++;
			break;
	}
	if(a.p.z>=5)
		a.p.z--;
	else if(a.p.z<=-7)
			a.p.z++;
	if(a.p.x>=6)
		a.p.x--;
	else if(a.p.x<=-6)
			a.p.x++;
}

void teclaEspecial(int key, int x, int y){
	switch(menu){
		case jogo:
			if(a.est==ativo){ teclaEspecialJogo(key);}
			break;
		case Tutorial:
		case win:
		case gameOver:
			menu = inicial;
			break;
	}
	glutPostRedisplay();
}

void teclaNormalJogo(unsigned char key){
	switch (key){
        case '.':
            virar++;
            break;
		case ',':
	    	virar--;
	    	break;
      	case 'p':
	  		abaixa++;
	    	break;
		case 'd':
			gira=-8;
			break;
		case 'a':
			gira=8;
			break;
		case 's':
			gira=0;
			virar=0;
			abaixa=0;
			cima=0;
			break;
		case 'w':
	    	cima=8;
	    	break;
		case ' ':
			if(a.est==ativo){
				a.est=colide;
				musicaInicio.stop();
				musicaAranha.setLoop(true);
				musicaAranha.play();
			}
			break;
		case '+':
			cor+=0.1;
			break;
		case 'l':
			light0Ligada=0;
			break;
    }
}

static void teclado(unsigned char key, int x, int y){
	if( key == 27)
        exit(0);
	switch(menu){
		case jogo:
			teclaNormalJogo(key);
			break;
		case inicial:
			break;
		case Tutorial:
		case win:
		case gameOver:
			menu = inicial;
			break;
	}
    glutPostRedisplay();
}

static void idle(void){
	if(menu==jogo){
		tempoDeJogo++;
		if(tempoDeJogo==tempoMaximoJogo){
			menu=gameOver;
			musicaAranha.stop();
			musicaInicio.stop();
			musicaGameOver.play();
		}
	}
   	glutPostRedisplay();
}

int main(int argc, char** argv){
   	glutInit(&argc, argv);
   	glutInitContextVersion(1,1);
   	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
   	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   	glutInitWindowSize (800, 600);
   	glutInitWindowPosition (100, 100);
   	glutCreateWindow ("Tp2 Luiza e Marcela");
    srand(time(NULL));

   	init();
   	glutDisplayFunc(desenha);
   	glutReshapeFunc(redimensiona);
   	glutKeyboardFunc(teclado);
   	glutSpecialFunc(teclaEspecial);
   	glutPassiveMotionFunc(mouse);
   	glutMouseFunc(mouseClick);
   	glutIdleFunc(idle);

   	glutMainLoop();
   	return 0;
}
