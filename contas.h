typedef struct posicao{
   float x, y, z;
} Posicao, Direcao;

typedef struct colisao{
   int raio;
   Posicao centro;
} Colisao;

#define tempoMaximoJogo 8000

void converteCoordenadas(int x, int y, struct posicao *mouse, struct posicao tamanhoTela);
bool clique(struct posicao mouse, struct botao botao1);
int distanciaEntrePontos(Posicao p, Posicao q);
bool esferaDentroDaOutra(Colisao aranha, Colisao obj);
bool esferaEncostaNaOutra(Colisao aranha, Colisao obj);