enum Tipo{arainha, mosca};
typedef struct insetos{
   Colisao p;
   Angulo angulosPatas;
   Angulo anguloCima;
   Estado est;
   Tipo tipo;
}Insetos;
#define qntInsetos 10

void desenhaArainha(Insetos i);

void desenhaMosca(Insetos i);

void moveInseto(Aranha *a, Insetos *m, sf::Music *musicaInseto, int indiceDoInseto );

void criaMosca(Insetos *m);

void criaArainha(Insetos *m);

// retorna qnt de insetos inativos
int animaInsetos(Aranha *a,Insetos m[qntInsetos], sf::Music *musicaInseto);
