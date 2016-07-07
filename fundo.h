// 2 5 5 configura alguns parâmetros do modelo de iluminação: FONTE DE LUZ
const GLfloat light_ambient[]  = { 0.3f, 0.3f,  0.3f, 1.0f };
const GLfloat light_diffuse[]  = { 0.5f, 0.5f,  0.5f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f,  1.0f, 1.0f };
const GLfloat light_position[] = { 5.0f, 6.0f, 5.0f, 0.0f };
// configura alguns parâmetros do modelo de iluminação: MATERIAL
const GLfloat mat_ambient[]    = { 0.2f, 0.2f, 0.2f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.3f, 0.3f, 0.3f, 1.0f };
const GLfloat mat_specular[]   = { 0.5f, 0.5f, 0.5f, 1.0f };
const GLfloat high_shininess[] = { 100.0f};

enum OpcoesDeTela {inicial, jogo, win, gameOver, Tutorial};

int carregar_textura(char const nome[40]);
void desenhaTextura(GLuint textura, int x1, int x2, int y1, int y2, int z1, int z2, int z3, int z4);
void Paredes( GLuint texturaQuadrado1, GLuint texturaQuadrado2, GLuint texturaQuadrado3, GLuint texturaQuadrado4, GLuint texturaQuadrado5);
void Floresta( GLuint texturaFloresta, GLuint texturaArvores);
void Teia(GLuint texturaTeia);
