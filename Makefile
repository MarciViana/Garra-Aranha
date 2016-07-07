all: 
	g++ -o programa tp2.cpp aranha.cpp contas.cpp fundo.cpp insetos.cpp botao.cpp -lSOIL -lglut -lGLU -lGL -lsfml-audio -lm
 #regra para a compialção
install:
	sudo apt-get install build-essential
	sudo apt-get install freeglut3-dev
	sudo apt-get install libglew1.6-dev
	sudo apt-get install libsfml-dev
	sudo apt-get install libsoil-dev

run: all
	./programa

clean:
	rm programa #apaga o arquivo prog gerado
