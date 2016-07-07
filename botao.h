struct botao {
	struct posicao coordenadas;
	struct posicao tamanho;
  	GLuint textura;
};

//bool clique(struct posicao mouse, struct botoes botao);
void desenhaBotao(struct botao botao1);
//void Botoes(GLuint texturaPlay, GLuint texturaPause);