typedef struct posicao Angulo;
enum Estado {ativo, inativo, colide, voltando};
typedef struct aranha{
   Posicao p;
   Angulo angulosPatas;
   Angulo anguloCima;
   Colisao colide;
   Estado est;
   int anda;
}Aranha;
#define anguloPatasAbertas (Angulo){-205,95,35}
#define anguloPatasFechadas (Angulo){-120,65,40}
#define angCabecaBaixo (Angulo){280,205,0}
#define angCabecaCima (Angulo){80,205,0}

void animaAranha(Aranha *a, int cont[4],  float *tamTeia, float *descer,sf::Music *musicaAranha,sf::Music *musicaInicio);
void desenhaAranha(Aranha a, float cor);

void desenhaTeia(Aranha a,int tamTeia);
void desenhaPata(Angulo aPatas);

void desenhaFalange();
