//Semestre 2020 - 1
//************************************************************//
//************************************************************//
//************** Alumno (s): *********************************//
//*************	Sandoval Juárez Tania					******//
//*************											******//
//************************************************************//
//************************************************************//

#include "Main.h"
#include "Resources/librerias/texture.h"
#include "Resources/librerias/figuras.h"
#include "Resources/librerias/Camera.h"
#include "Resources/librerias/cmodel/CModel.h"



//Solo para Visual Studio 2015 o mayor
#if (_MSC_VER >= 1900)
#   pragma comment( lib, "legacy_stdio_definitions.lib" )
#endif


// Variables used to calculate frames per second: (Windows)
DWORD dwFrames = 0;
DWORD dwCurrentTime = 0;
DWORD dwLastUpdateTime = 0;
DWORD dwElapsedTime = 0;

CCamera objCamera;
GLfloat g_lookupdown = 16.0f;    // Look Position In The Z-Axis (NEW) 

int font = (int)GLUT_BITMAP_HELVETICA_18;

GLfloat Diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[] = { 0.0f, 27.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[] = { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = { 18 };


//TEXTURAS
//CTexture t_pasto;
CTexture cielo;
CFiguras fig1;
CFiguras fig3;

CTexture t_piso;
CTexture t_pared1;
CTexture t_pared2;
CTexture t_pisoM;
CTexture t_wall;
CTexture t_door;
CTexture t_mesa;
CTexture t_silla;
CTexture t_ventana;
CTexture t_techo;
//END TEXTURAS

// MODELOS
/*
	Modelos a tener en cuenta:
	Sofa
	TV
	Mueble TV
	Anaquel
	Foco Techo
	Lámpara

	Arcade?
	Luces?
*/
//Figuras a "mano"
CFiguras pisoGeneral;
CFiguras silla;
CFiguras mesa;
CFiguras cuarto;
CFiguras puerta;

//Figuras de 3D Studio
CModel sofa;
CModel muebleTV;
CModel tv;
CModel librero;
CModel foco;
CModel lampara;
CModel arcade;

CModel chess;

CModel bPeon;
CModel bCaballo;
CModel bTorre;
CModel bAlfil;
CModel bRey;
CModel bReina;

CModel nPeon;
CModel nCaballo;
CModel nTorre;
CModel nAlfil;
CModel nRey;
CModel nReina;
//END MODELOS

//Auxiliares para dejar en su lugar cualquier cosa cuando la mueves con kli
float  Lx = 0.0;
float  Ly = 0.0;
float  Lz = 0.0;
//float aux = 0.0;
//glTranslatef(3.8, 4.5, 9.0);
//Mover posiciones
float trax = 0.0;
float tray = 0.0;
float traz = 0.0;
//Mover texturas
float textX = 0.0;
float textY = 0.0;
float rotSillon = 0.0;

//Mover escalas
float scaleX = 0.0;
float scaleY = 0.0;
float scaleZ = 0.0;
// BANDERAS
bool banderaCG = false;	//para mostrar las PC, son pesadas.
bool banderaCJ = false;	//Visualización de Camara enfocada en el Juego
bool banderaCC = false;	//Visualización de Camara enfocada en el cuarto
bool banderaCO = false;	//Visualización de Camara original
bool banderaPuerta = false;
bool banderaVentana = false;
bool banderaSilla = false;
bool banderaUpDown = false;
bool banderaTrans = true;
// END BANDERAS

//ANIMACION
float rotPuerta = 0.0f;
float rotVentana = 0.0f;
float rotSilla = 0.0f;
float transSilla = 0.0f;
//END ANIMACION

//CAMARA
// C define posiciones de la cámara para la "1a camara" que enfoca el Cuarto general
// J define posiciones de la cámara para la "2a cámara" que enfoca el juego.
// Se guardan en estos valores para que al hacer cambio de vista, se quede donde estaba en el estado anterior.
// Es decir, al cambiar de Cuarto->Juego, la cámara cambia a los valores de Camara de Juego, guardando los valores
// de la Camara de Cuarto.
// Cuando se cambie de Juego->Cuarto, la camara cambia a los valores de Camara de Cuarto.
// Si los valores han sido cambiados anteriormente, la camara se dirigira a las posiciones previamente guardadas.
float pos_xC, pos_yC, pos_zC, view_xC, view_yC, view_zC, up_xC, up_yC, up_zC;
float lookUpDownC;
float pos_xJ, pos_yJ, pos_zJ, view_xJ, view_yJ, view_zJ, up_xJ, up_yJ, up_zJ;
float lookUpDownJ;
//END CAMARA


//	************* KEY FRAMES	************* //
float pBz = 0.0, pCx = 0.0, pCz = 0.0, pDx = 0.0, pDz = 0.0, pFx = 0.0, pFy = 0.0, pFz = 0.0, pGz = 0.0;
#define MAX_FRAMES 15		//15 keyframes
int i_max_steps = 90;		//Cantidad de cuadros intermedios	valores peque�os: animacion r�pida, valores grandes: animaci�n m�s pausada
int i_curr_steps = 0;

typedef struct _frame {
	//Variables para guardar KeyFrames
	float pBz;
	float pCx;
	float pCz;
	float pDx;
	float pDz;
	float pFx;
	float pFy;
	float pFz;
	float pGz;

	//Incrementos
	float pBzInc;
	float pCxInc;
	float pCzInc;
	float pDxInc;
	float pDzInc;
	float pFxInc;
	float pFyInc;
	float pFzInc;
	float pGzInc;
} FRAME;
FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;
int w = 500, h = 500;
int frame = 0, time, timebase = 0;
char s[30];
//	************* END KEY FRAMES	************* //
//	*********************	KEYFRAMES ***************			

void saveFrame(void) {
	printf("frameindex %d\n", FrameIndex);
	KeyFrame[FrameIndex].pBz = pBz;
	KeyFrame[FrameIndex].pCx = pCx;
	KeyFrame[FrameIndex].pCz = pCz;
	KeyFrame[FrameIndex].pDx = pDx;
	KeyFrame[FrameIndex].pDz = pDz;
	KeyFrame[FrameIndex].pFx = pFx;
	KeyFrame[FrameIndex].pFy = pFy;
	KeyFrame[FrameIndex].pFz = pFz;
	KeyFrame[FrameIndex].pGz = pGz;

	FrameIndex++;
}
void resetElements(void)
{
	pBz = KeyFrame[0].pBz;
	pCx = KeyFrame[0].pCx;
	pCz = KeyFrame[0].pCz;
	pDx = KeyFrame[0].pDx;
	pDz = KeyFrame[0].pDz;
	pFx = KeyFrame[0].pFx;
	pFy = KeyFrame[0].pFy;
	pFz = KeyFrame[0].pFz;
	pGz = KeyFrame[0].pGz;
}
void interpolation(void)
{
	//Los incrementos
	KeyFrame[playIndex].pBzInc = (KeyFrame[playIndex + 1].pBz - KeyFrame[playIndex].pBz) / i_max_steps;
	KeyFrame[playIndex].pCxInc = (KeyFrame[playIndex + 1].pCx - KeyFrame[playIndex].pCx) / i_max_steps;
	KeyFrame[playIndex].pCzInc = (KeyFrame[playIndex + 1].pCz - KeyFrame[playIndex].pCz) / i_max_steps;
	KeyFrame[playIndex].pDxInc = (KeyFrame[playIndex + 1].pDx - KeyFrame[playIndex].pDx) / i_max_steps;
	KeyFrame[playIndex].pDzInc = (KeyFrame[playIndex + 1].pDz - KeyFrame[playIndex].pDz) / i_max_steps;
	KeyFrame[playIndex].pFxInc = (KeyFrame[playIndex + 1].pFx - KeyFrame[playIndex].pFx) / i_max_steps;
	KeyFrame[playIndex].pFyInc = (KeyFrame[playIndex + 1].pFy - KeyFrame[playIndex].pFy) / i_max_steps;
	KeyFrame[playIndex].pFzInc = (KeyFrame[playIndex + 1].pFz - KeyFrame[playIndex].pFz) / i_max_steps;
	KeyFrame[playIndex].pGzInc = (KeyFrame[playIndex + 1].pGz - KeyFrame[playIndex].pGz) / i_max_steps;
}

//	*************	KEY FRAMES	*********************
void InitGL(GLvoid)     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

/* setup blending */
	glEnable(GL_BLEND);			// Turn Blending On

	cielo.LoadBMP("Resources/Texturas/cielo.bmp");
	cielo.BuildGLTexture();
	cielo.ReleaseImage();

	t_piso.LoadTGA("Resources/Texturas/piso.tga");
	t_piso.BuildGLTexture();
	t_piso.ReleaseImage();

	t_pared1.LoadTGA("Resources/Texturas/pared1.tga");
	t_pared1.BuildGLTexture();
	t_pared1.ReleaseImage();

	t_pared2.LoadTGA("Resources/Texturas/pared2.tga");
	t_pared2.BuildGLTexture();
	t_pared2.ReleaseImage();

	t_door.LoadTGA("Resources/Texturas/door.tga");
	t_door.BuildGLTexture();
	t_door.ReleaseImage();

	t_wall.LoadTGA("Resources/Texturas/wall.tga");
	t_wall.BuildGLTexture();
	t_wall.ReleaseImage();

	t_pisoM.LoadTGA("Resources/Texturas/pisoMadera.tga");
	t_pisoM.BuildGLTexture();
	t_pisoM.ReleaseImage();

	t_silla.LoadTGA("Resources/Texturas/sillaWood.tga");
	t_silla.BuildGLTexture();
	t_silla.ReleaseImage();

	t_mesa.LoadTGA("Resources/Texturas/mesaWood.tga");
	t_mesa.BuildGLTexture();
	t_mesa.ReleaseImage();

	t_ventana.LoadTGA("Resources/Texturas/ventana.tga");
	t_ventana.BuildGLTexture();
	t_ventana.ReleaseImage();

	t_techo.LoadTGA("Resources/Texturas/techo.tga");
	t_techo.BuildGLTexture();
	t_techo.ReleaseImage();

//Carga de Figuras
	sofa._3dsLoad("Resources/Modelos/sofa2.3DS");
	//sofa.VertexNormals();
	tv._3dsLoad("Resources/Modelos/TVs.3DS");
	librero._3dsLoad("Resources/Modelos/estante3.3DS");
	chess._3dsLoad("Resources/Modelos/Chess/chessboard.3DS");
	bPeon._3dsLoad("Resources/Modelos/Chess/pawnB.3DS");
	nPeon._3dsLoad("Resources/Modelos/Chess/pawnN.3DS");
	bTorre._3dsLoad("Resources/Modelos/Chess/towerB.3DS");
	nTorre._3dsLoad("Resources/Modelos/Chess/towerN.3DS");
	bAlfil._3dsLoad("Resources/Modelos/Chess/bishopB.3DS");
	nAlfil._3dsLoad("Resources/Modelos/Chess/bishopN.3DS");
	bCaballo._3dsLoad("Resources/Modelos/Chess/horseB.3DS");
	nCaballo._3dsLoad("Resources/Modelos/Chess/horseN.3DS");
	bRey._3dsLoad("Resources/Modelos/Chess/kingB.3DS");
	nRey._3dsLoad("Resources/Modelos/Chess/kingN.3DS");
	bReina._3dsLoad("Resources/Modelos/Chess/queenB.3DS");
	nReina._3dsLoad("Resources/Modelos/Chess/queenN.3DS");

	//Posición de cámara inicial
//	mPosX 0.13	mPosY 3.2	mPosZ 8.95
//	mViewX 0.13	mViewY 3.2	mViewZ 5.95
//	mUpX 0.0	mUpY 1.0	mUpZ 0.0
//	glookupdown 0.0
	objCamera.Position_Camera(4.36f, 15.8f, 30.82f, 4.15f, 15.8f, 27.82f, 0, 1, 0);

	//Posiciones de cámaras para Juego y Cuarto iniciales
	pos_xC = 6.945;
	pos_yC = 17.2;
	pos_zC = 7.034;
	view_xC = 5.35;
	view_yC = 17.2;
	view_zC = 4.485;
	up_xC = 0.0;
	up_yC = 1.0;
	up_zC = 0.0;
	lookUpDownC = 46.0;

	pos_xJ = -4.1;
	pos_yJ = 9.5;
	pos_zJ = 0.04;
	view_xJ = -4.1;
	view_yJ = 9.5;
	view_zJ = -2.96;
	up_xJ = 0.0;
	up_yJ = 1.0;
	up_zJ = 0.0;
	lookUpDownJ = 73.0;

	//	**************	KEY FRAMES	**************
	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].pBz = 0;
		KeyFrame[i].pCx = 0;
		KeyFrame[i].pCz = 0;
		KeyFrame[i].pDx = 0;
		KeyFrame[i].pDz = 0;
		KeyFrame[i].pFx = 0;
		KeyFrame[i].pFy = 0;
		KeyFrame[i].pFz = 0;
		KeyFrame[i].pGz = 0;

		KeyFrame[i].pBzInc = 0;
		KeyFrame[i].pCxInc = 0;
		KeyFrame[i].pCzInc = 0;
		KeyFrame[i].pDxInc = 0;
		KeyFrame[i].pDzInc = 0;
		KeyFrame[i].pFxInc = 0;
		KeyFrame[i].pFyInc = 0;
		KeyFrame[i].pFzInc = 0;
		KeyFrame[i].pGzInc = 0;
	}
	
	// Frame 0
		KeyFrame[0].pBz = 0;
		KeyFrame[0].pCx = 0;
		KeyFrame[0].pCz = 0;
		KeyFrame[0].pDx = 0;
		KeyFrame[0].pDz = 0;
		KeyFrame[0].pFx = 0;
		KeyFrame[0].pFy = 0;
		KeyFrame[0].pFz = 0;
		KeyFrame[0].pGz = 0;

		KeyFrame[0].pBzInc = -0.05;
		KeyFrame[0].pCxInc = 0;
		KeyFrame[0].pCzInc = 0;
		KeyFrame[0].pDxInc = 0;
		KeyFrame[0].pDzInc = 0;
		KeyFrame[0].pFxInc = 0;
		KeyFrame[0].pFyInc = 0;
		KeyFrame[0].pFzInc = 0;
		KeyFrame[0].pGzInc = 0;
	// Frame 1
		KeyFrame[1].pBz = -4.5;
		KeyFrame[1].pCx = 0;
		KeyFrame[1].pCz = 0;
		KeyFrame[1].pDx = 0;
		KeyFrame[1].pDz = 0;
		KeyFrame[1].pFx = 0;
		KeyFrame[1].pFy = 0;
		KeyFrame[1].pFz = 0;
		KeyFrame[1].pGz = 0;

		KeyFrame[1].pBzInc = 0;
		KeyFrame[1].pCxInc = 0;
		KeyFrame[1].pCzInc = 0;
		KeyFrame[1].pDxInc = 0;
		KeyFrame[1].pDzInc = 0;
		KeyFrame[1].pFxInc = 0;
		KeyFrame[1].pFyInc = 0;
		KeyFrame[1].pFzInc = 0;
		KeyFrame[1].pGzInc = 0.1;
	// Frame 2
		KeyFrame[2].pBz = -4.5;
		KeyFrame[2].pCx = 0;
		KeyFrame[2].pCz = 0;
		KeyFrame[2].pDx = 0;
		KeyFrame[2].pDz = 0;
		KeyFrame[2].pFx = 0;
		KeyFrame[2].pFy = 0;
		KeyFrame[2].pFz = 0;
		KeyFrame[2].pGz = 9.0;

		KeyFrame[2].pBzInc = 0;
		KeyFrame[2].pCxInc = -0.05;
		KeyFrame[2].pCzInc = -0.05;
		KeyFrame[2].pDxInc = 0;
		KeyFrame[2].pDzInc = 0;
		KeyFrame[2].pFxInc = 0;
		KeyFrame[2].pFyInc = 0;
		KeyFrame[2].pFzInc = 0;
		KeyFrame[2].pGzInc = 0;
	// Frame 3
		KeyFrame[3].pBz = -4.5;
		KeyFrame[3].pCx = -4.5;
		KeyFrame[3].pCz = -4.5;
		KeyFrame[3].pDx = 0;
		KeyFrame[3].pDz = 0;
		KeyFrame[3].pFx = 0;
		KeyFrame[3].pFy = 0;
		KeyFrame[3].pFz = 0;
		KeyFrame[3].pGz = 9.0;

		KeyFrame[3].pBzInc = 0;
		KeyFrame[3].pCxInc = 0;
		KeyFrame[3].pCzInc = 0;
		KeyFrame[3].pDxInc = 0.05;
		KeyFrame[3].pDzInc = 0.1;
		KeyFrame[3].pFxInc = 0;
		KeyFrame[3].pFyInc = 0;
		KeyFrame[3].pFzInc = 0;
		KeyFrame[3].pGzInc = 0;
	// Frame 4
		KeyFrame[4].pBz = -4.5;
		KeyFrame[4].pCx = -4.5;
		KeyFrame[4].pCz = -4.5;
		KeyFrame[4].pDx = 4.5;
		KeyFrame[4].pDz = 9.0;
		KeyFrame[4].pFx = 0;
		KeyFrame[4].pFy = 0;
		KeyFrame[4].pFz = 0;
		KeyFrame[4].pGz = 9.0;

		KeyFrame[4].pBzInc = 0;
		KeyFrame[4].pCxInc = 0.25;
		KeyFrame[4].pCzInc = -0.25;
		KeyFrame[4].pDxInc = 0;
		KeyFrame[4].pDzInc = 0;
		KeyFrame[4].pFxInc = 0;
		KeyFrame[4].pFyInc = 0;
		KeyFrame[4].pFzInc = 0;
		KeyFrame[4].pGzInc = 0;
	// Frame 5
		KeyFrame[5].pBz = -4.5;
		KeyFrame[5].pCx = 18.0;
		KeyFrame[5].pCz = -27.0;
		KeyFrame[5].pDx = 4.5;
		KeyFrame[5].pDz = 9.0;
		KeyFrame[5].pFx = 0;
		KeyFrame[5].pFy = 0;
		KeyFrame[5].pFz = 0;
		KeyFrame[5].pGz = 9.0;

		KeyFrame[5].pBzInc = 0;
		KeyFrame[5].pCxInc = 0;
		KeyFrame[5].pCzInc = 0;
		KeyFrame[5].pDxInc = 0;
		KeyFrame[5].pDzInc = 0;
		KeyFrame[5].pFxInc = 0.005556;
		KeyFrame[5].pFyInc = 0.066667;
		KeyFrame[5].pFzInc = 0.005556;
		KeyFrame[5].pGzInc = 0;

	// Frame 6
		KeyFrame[6].pBz = -4.5;
		KeyFrame[6].pCx = 18.0;
		KeyFrame[6].pCz = -27.0;
		KeyFrame[6].pDx = 4.5;
		KeyFrame[6].pDz = 9.0;
		KeyFrame[6].pFx = 0.5;
		KeyFrame[6].pFy = 6.0;
		KeyFrame[6].pFz = 0.5;
		KeyFrame[6].pGz = 9.0;

		KeyFrame[6].pBzInc = 0;
		KeyFrame[6].pCxInc = 0;
		KeyFrame[6].pCzInc = 0;
		KeyFrame[6].pDxInc = 0;
		KeyFrame[6].pDzInc = 0;
		KeyFrame[6].pFxInc = -0.094444;
		KeyFrame[6].pFyInc = -0.077778;
		KeyFrame[6].pFzInc = -0.094444;
		KeyFrame[6].pGzInc = 0;
	// Frame 7
		KeyFrame[7].pBz = -4.5;
		KeyFrame[7].pCx = 18.0;
		KeyFrame[7].pCz = -27.0;
		KeyFrame[7].pDx = 4.5;
		KeyFrame[7].pDz = 9.0;
		KeyFrame[7].pFx = -8.0;
		KeyFrame[7].pFy = -1.0;
		KeyFrame[7].pFz = -8.0;
		KeyFrame[7].pGz = 9.0;

		KeyFrame[7].pBzInc = 0;
		KeyFrame[7].pCxInc = 0;
		KeyFrame[7].pCzInc = 0;
		KeyFrame[7].pDxInc = 0;
		KeyFrame[7].pDzInc = 0;
		KeyFrame[7].pFxInc = 0;
		KeyFrame[7].pFyInc = 0;
		KeyFrame[7].pFzInc = 0;
		KeyFrame[7].pGzInc = 0;
		
		FrameIndex = 8;
}

void pintaTexto(float x, float y, float z, void* font, char* string)
{

	char* c;     //Almacena los caracteres a escribir
	glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
	//glWindowPos2i(150,100);
	for (c = string; *c != '\0'; c++) //Condicion de fin de cadena
	{
		glutBitmapCharacter(font, *c); //imprime
	}
}

void patas() {
	float disx = 1.0;
	float disy = 0.4;
	float disz = 0.4;
	glPushMatrix();
		glTranslatef(-0.7, 0.0, 0.0);
		glScalef(disx, disy, disz);
		mesa.mesa(t_mesa.GLindex, 1.0, 0.5, 0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.7, 0.0, 0.0);
		glScalef(disx, disy, disz);
		mesa.mesa(t_mesa.GLindex, 1.0, 0.5, 0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 0.0, -0.7);
		glRotatef(90.0, 0.0, 1.0, 0.0);
		glScalef(disx, disy, disz);
		mesa.mesa(t_mesa.GLindex, 1.0, 0.5, 0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.7);
		glRotatef(90.0, 0.0, 1.0, 0.0);
		glScalef(disx, disy, disz);
		mesa.mesa(t_mesa.GLindex, 1.0, 0.5, 0.5);
	glPopMatrix();
}

void palo() {
	glPushMatrix();
		float scaleX = -0.6;
		float scaleY = 3.45;
		float scaleZ = -0.6;
		//glScalef(1.0, 4.0, 1.0);
		glScalef(1.0+scaleX, 1.0+scaleY, 1.0+scaleZ);
		mesa.mesa(t_mesa.GLindex, 1.0, 0.3, 0.3);
	glPopMatrix();
}

void tabla() {
	float scaleX = 2.0;
	float scaleY = -0.6;
	float scaleZ = 2.0;
	glPushMatrix();
		glTranslatef(0.0, 0.5, 0.0);
		glScalef(1.0 + scaleX, 1.0 + scaleY, 1.0 + scaleZ);
		mesa.mesa(t_mesa.GLindex, 1.0, 0.95, 0.2);
	glPopMatrix();
}

void createMesa() {
	/*Jerarquía:
		* Pivote central
		* Patas
		* Soporte
		* Mesa cuadrada

		De modo que, si gira el pivote, gira todo el modelo.
		Si gira la mesa cuadrada, solo gira ésta.
	*/
	glPushMatrix();
		glTranslatef(1.35, 0.0, -0.3);
		glTranslatef(-5.0, 0.4, -1.0);
		glRotatef(rotSillon, 0.0, 1.0, 0.0);
		glScalef(1.3, 1.3, 1.3);
		patas();
		glTranslatef(0.0, 2.0, 0.0);
		palo();
		glTranslatef(0.0,1.925,0.0);
		tabla();
	glPopMatrix();
}

void createCuarto() {
	glPushMatrix();
		glTranslatef(0.0, 9.15, -1.0);
		glScalef(18.0, 18.0, 18.0);
		glDisable(GL_LIGHTING);
		cuarto.cuarto(t_pared1.GLindex, t_pared2.GLindex, t_pisoM.GLindex, t_techo.GLindex, 1.0);
		glEnable(GL_LIGHTING);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 9.195, -1.0);
		glScalef(18.1, 18.1, 18.1);
		glDisable(GL_LIGHTING);
		cuarto.cuarto(t_wall.GLindex, t_wall.GLindex, t_wall.GLindex, t_wall.GLindex, -1.0);
		glEnable(GL_LIGHTING);
	glPopMatrix();
}

void createPuerta() {
	glPushMatrix();
		glTranslatef(3.6, 4.7, 8.05);
		glRotatef(rotPuerta, 0.0, 1.0, 0.0);	//rotPuerta sirve para la animación de abrir y cerrar puerta con tecla 3
		glScalef(18.1, 18.1, 1.0);
		glDisable(GL_LIGHTING);
		puerta.puerta(t_door.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();
}

void createVentana() {
	glPushMatrix();
		glTranslatef(0.0, 14.5, -10.0);
		glRotatef(rotVentana, 1.0, 0.0, 0.0);	//rotVentana sirve para la animación de abrir y cerrar puerta con tecla 4
		glScalef(18.0+scaleX, 18.0+scaleY, 1.0);
		glDisable(GL_LIGHTING);
		puerta.ventana(t_ventana.GLindex, 0.0, 0.0);
		glEnable(GL_LIGHTING);
	glPopMatrix();
}

void createMuebles() {
	glPushMatrix();
		glPushMatrix();
			//SOFA
			glPushMatrix();
				glTranslatef(39.0, 0.0, -61.5);
				glScalef(0.003, 0.007, 0.004);
				glRotatef(180.0, 0.0, 1.0, 0.0);
				sofa.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();
			//TV
			glPushMatrix();
				glTranslatef(8.52, 6.0, 5.0);
				glScalef(0.01, 0.012, 0.01);
				glRotatef(-90.0, 0.0, 1.0, 0.0);
				tv.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();
				//LIBRERO
				glScalef(0.03, 0.08, 0.08);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				//glTranslatef(0.0, 0.0, -95.0);
				glTranslatef(7.0, 0.0, -281.0);
				librero.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();
	glPopMatrix();
}

void cSilla(float rotS) {
	glPushMatrix();
		//Pivote a 3.1 de distancia del centro del origen de la mesa
		glTranslatef(3.1, 0.0, 0.0);
		glRotatef(rotS, 0.0, 1.0, 0.0);
		//glTranslatef(0.0 + trax, 0.0 + tray, 0.0 + traz);
		//PATAS
		float xx = 2.4;
		float yy = 0.35;
		float zz = 2.35;
		glPushMatrix();
			glTranslatef(0.0, 0.55, 0.0);
			//P1
			glPushMatrix();
				glTranslatef(1.0, 1.5, -1.0);
				//glScalef(xx, yy, zz);
				glScalef(0.25, 3.8, 0.25);
				silla.mesa(t_silla.GLindex, 1.0, 0.2, 0.3);
			glPopMatrix();
			//P2
			glPushMatrix();
				glTranslatef(1.0, 1.5, 1.0);
				glScalef(0.25, 3.8, 0.25);
				silla.mesa(t_silla.GLindex, 1.0, 0.2, 0.3);
			glPopMatrix();
			//P3
			glPushMatrix();
				glTranslatef(-1.0, 1.5, 1.0);
				glScalef(0.25, 3.8, 0.25);
				silla.mesa(t_silla.GLindex, 1.0, 0.2, 0.3);
			glPopMatrix();
			//P4
			glPushMatrix();
				glTranslatef(-1.0, 1.5, -1.0);
				glScalef(0.25, 3.8, 0.25);
				silla.mesa(t_silla.GLindex, 1.0, 0.2, 0.3);
			glPopMatrix();
		glPopMatrix();

		//Base
		glPushMatrix();
			glTranslatef(0.0, 0.55, 0.0);
			glTranslatef(0.0, 3.6, 0.0);
			glScalef(2.4, 0.35, 2.35);
			silla.mesa(t_silla.GLindex, 1.0, 1.55, 0.06);
		glPopMatrix();
		//Respaldo
		glPushMatrix();
			glTranslatef(0.0, 0.55, 0.0);
			glPushMatrix();
				glTranslatef(1.1, 7.6, -0.01);
				glScalef(0.25, 0.3, 2.33);
				silla.mesa(t_silla.GLindex, 1.0, 1.45, 0.25);
			glPopMatrix();
			glTranslatef(1.1, 5.6, -1.1);
			glScalef(0.25, 3.7, 0.15);
			silla.mesa(t_silla.GLindex, 1.0, 0.4, 0.35);
			glTranslatef(0.0, 0.0, 2.5);
			silla.mesa(t_silla.GLindex, 1.0, 0.4, 0.35);
			glTranslatef(0.0, 0.0, 2.5);
			silla.mesa(t_silla.GLindex, 1.0, 0.4, 0.35);
			glTranslatef(0.0, 0.0, 2.5);
			silla.mesa(t_silla.GLindex, 1.0, 0.4, 0.35);
			glTranslatef(0.0, 0.0, 2.5);
			silla.mesa(t_silla.GLindex, 1.0, 0.4, 0.35);
			glTranslatef(0.0, 0.0, 2.5);
			silla.mesa(t_silla.GLindex, 1.0, 0.4, 0.35);
			glTranslatef(0.0, 0.0, 2.0);
			silla.mesa(t_silla.GLindex, 1.0, 0.4, 0.35);
		glPopMatrix();
		//silla.prisma(1.0, 1.0, 1.0, 0);
	glPopMatrix();
}

void createSillas() {
	glPushMatrix();
		//Origen
		glTranslatef(-3.65, 0.0, -1.3);
		glPushMatrix();
			//Rotacion de una silla
			cSilla(0.0);
			glRotatef(90.0, 0.0, 1.0, 0.0);
			cSilla(0.0);
			glRotatef(90.0, 0.0, 1.0, 0.0);
			cSilla(0.0);
			glPushMatrix();
				glTranslatef(0.0, 0.0, 0.0 + transSilla);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				cSilla(rotSilla);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void peonBl() {
	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		bPeon.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(4.5, 0.0, 0.0+pBz);
		bPeon.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(9.0, 0.0, 0.0);
		bPeon.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(13.5, 0.0, 0.0);
		bPeon.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(18.0, 0.0, 0.0);
		bPeon.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(22.5, 0.0, 0.0);
		bPeon.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(27.0, 0.0, 0.0);
		bPeon.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(31.5, 0.0, 0.0);
		bPeon.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();
	/*glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		bPeon.GLrender(NULL, _SHADED, 1.0);
		glPushMatrix();
			glTranslatef(4.5+trax, 0.0, 0.0+traz);
			bPeon.GLrender(NULL, _SHADED, 1.0);
			glPushMatrix();
				glTranslatef(4.5, 0.0, 0.0);
				bPeon.GLrender(NULL, _SHADED, 1.0);
				glPushMatrix();
					glTranslatef(4.5, 0.0, 0.0);
					bPeon.GLrender(NULL, _SHADED, 1.0);
					glPushMatrix();
						glTranslatef(4.5, 0.0, 0.0);
						bPeon.GLrender(NULL, _SHADED, 1.0);
						glPushMatrix();
							glTranslatef(4.5, 0.0, 0.0);
							bPeon.GLrender(NULL, _SHADED, 1.0);
							glPushMatrix();
								glTranslatef(4.5, 0.0, 0.0);
								bPeon.GLrender(NULL, _SHADED, 1.0);
								glPushMatrix();
									glTranslatef(4.5, 0.0, 0.0);
									bPeon.GLrender(NULL, _SHADED, 1.0);
								glPopMatrix();
							glPopMatrix();
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();*/

	/*for (int i = 0; i <= 7; i++) {
		bPeon.GLrender(NULL, _SHADED, 1.0);
		glTranslatef(4.5,0.0,0.0);
	}*/
}

void peonNe() {
	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0 + pGz);
		nPeon.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-4.5+pFx, 0.0+pFy, 0.0 + pFz);
		nPeon.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-9.0, 0.0, 0.0);
		nPeon.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-13.5, 0.0, 0.0);
		nPeon.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-18.0, 0.0, 0.0);
		nPeon.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-22.5, 0.0, 0.0);
		nPeon.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-27.0, 0.0, 0.0);
		nPeon.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-31.5, 0.0, 0.0);
		nPeon.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();
	/*glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		nPeon.GLrender(NULL, _SHADED, 1.0);
		glPushMatrix();
			glTranslatef(-4.5, 0.0, 0.0);
			nPeon.GLrender(NULL, _SHADED, 1.0);
			glPushMatrix();
				glTranslatef(-4.5, 0.0, 0.0);
				nPeon.GLrender(NULL, _SHADED, 1.0);
				glPushMatrix();
					glTranslatef(-4.5, 0.0, 0.0);
					nPeon.GLrender(NULL, _SHADED, 1.0);
					glPushMatrix();
						glTranslatef(-4.5, 0.0, 0.0);
						nPeon.GLrender(NULL, _SHADED, 1.0);
						glPushMatrix();
							glTranslatef(-4.5, 0.0, 0.0);
							nPeon.GLrender(NULL, _SHADED, 1.0);
							glPushMatrix();
								glTranslatef(-4.5, 0.0, 0.0);
								nPeon.GLrender(NULL, _SHADED, 1.0);
								glPushMatrix();
									glTranslatef(-4.5, 0.0, 0.0);
									nPeon.GLrender(NULL, _SHADED, 1.0);
								glPopMatrix();
							glPopMatrix();
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();*/

	/*for (int i = 0; i <= 7; i++) {
		bPeon.GLrender(NULL, _SHADED, 1.0);
		glTranslatef(4.5,0.0,0.0);
	}*/
}

void caballoBl() {
	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		bCaballo.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(22.5, 0.0, 0.0);
		bCaballo.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();
}

void caballoNe() {
	glPushMatrix();
		glTranslatef(0.0 + pDx, 0.0, 0.0 + pDz);
		nCaballo.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(22.5, 0.0, 0.0);
		nCaballo.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();
}

void alfilBl() {
	glPushMatrix();
		glTranslatef(0.0 +pCx , 0.0, 0.0 + pCz);	/////////////////////////
		bAlfil.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(13.5, 0.0, 0.0);
		bAlfil.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();
}

void alfilNe() {
	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		nAlfil.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(13.5, 0.0, 0.0);
		nAlfil.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();
}

void torreBl() {
	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		bTorre.GLrender(NULL, _SHADED, 1.0);
		glPushMatrix();
			glTranslatef(31.5, 0.0, 0.0);
			bTorre.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();
	glPopMatrix();
}

void torreNe() {
	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		nTorre.GLrender(NULL, _SHADED, 1.0);
		glPushMatrix();
			glTranslatef(31.5, 0.0, 0.0);
			nTorre.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();
	glPopMatrix();
}

void createChess() {
	glPushMatrix();
		glTranslatef(-3.6, 6.4, -1.4);
		glScalef(0.08, 0.08, 0.08);
		chess.GLrender(NULL, _SHADED, 1.0);
		peonBl();
		peonNe();
		alfilBl();
		alfilNe();
		caballoBl();
		caballoNe();
		torreBl();
		torreNe();
		bReina.GLrender(NULL, _SHADED, 1.0);
		bRey.GLrender(NULL, _SHADED, 1.0);
		nReina.GLrender(NULL, _SHADED, 1.0);
		nRey.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();
}

void display(void)   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glPushMatrix();	//General

		glRotatef(g_lookupdown, 1.0f, 0, 0);
		gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
			objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
			objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);

		glPushMatrix(); //Piso primario
			glTranslatef(0.0, 0.0, 0.0);
			glScalef(20, 0.2, 20);
			glDisable(GL_LIGHTING);
			pisoGeneral.piso(t_piso.GLindex);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix();
			glPushMatrix(); //Creamos cielo
				glDisable(GL_LIGHTING);
				glTranslatef(0, 60, 0);
				fig1.skybox(130.0, 130.0, 130.0, cielo.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();
		glPopMatrix();
		//Pivot 0,0,0
		
		createCuarto();
		createPuerta();
		createVentana();
		createMuebles();
		createChess();
		//Sin esto, se queda el color del material del estante? why???
		glDisable(GL_LIGHTING);
		glDisable(GL_COLOR_MATERIAL);
		createMesa();
		createSillas();

		
	glPopMatrix();	//General

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	// Pintar texto en pantalla
	glColor3f(1.0, 0.0, 0.0);
	pintaTexto(-12, 12.0, -14.0, (void*)font, "Proyecto Final");
	pintaTexto(-12, 10.5, -14, (void*)font, "Cuarto de Juegos");
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glutSwapBuffers();

}

void animacion()
{
	fig3.text_izq -= 0.001;
	fig3.text_der -= 0.001;
	if (fig3.text_izq < -1)
		fig3.text_izq = 0;
	if (fig3.text_der < 0)
		fig3.text_der = 1;
	// Calculate the number of frames per one second:
	//dwFrames++;
	dwCurrentTime = GetTickCount(); // Even better to use timeGetTime()
	dwElapsedTime = dwCurrentTime - dwLastUpdateTime;

	if (dwElapsedTime >= 150)
	{
		//Animacion Puerta
		/*if (rotPuerta == 0)
			rotPuerta += 1;
		else if (rotPuerta == 90)
			rotPuerta -= 1;*/
		dwLastUpdateTime = dwCurrentTime;
	}
	if (dwElapsedTime >= 30)
	{
		if (banderaPuerta == true) {
			if (banderaUpDown == true) {	//Va de 0 a 90
				rotPuerta += 2.0;
				if (rotPuerta == 90.0)
					banderaPuerta = false;
			}
			else {
				rotPuerta -= 2.0;
				if (rotPuerta == 0.0)
					banderaPuerta = false;
			}
		}
		if (banderaVentana == true) {
			if (banderaUpDown == true) {	//Va de 0 a 90
				rotVentana += 2.0;
				if (rotVentana == 66.0)
					banderaVentana = false;
			}
			else {
				rotVentana -= 2.0;
				if (rotVentana == 0.0)
					banderaVentana = false;
			}
		}
		/*
			Basicamente, si banderaSilla es true, se presionó la tecla 5. Como Z = 0.0:
			Primero se mueve en -z hasta -2.0, luego rota hasta -90.0 y pone banderaSilla en false

			Si banderaSilla vuelve a ser true, ahora como Z = -2.0:
			Primero rota hasta 0.0, luego se mueve en Z hasta 0.0
		*/
		if (banderaSilla == true) {
			if (banderaTrans == true) {
				transSilla -= 0.1;
				if (transSilla <= -2.0) {
					transSilla = -2.0f;
					banderaUpDown = true;
				}
				if (banderaUpDown == true) {	//Va de 0 a 90
					rotSilla -= 2.0;
					if (rotSilla <= -90.0) {
						rotSilla = -90.0;
						banderaSilla = false;
					}

				}
			}
			else {

				rotSilla += 2.0;
				if (rotSilla >= 0.0) {
					rotSilla = 2.0;
					banderaUpDown = false;
				}
				if (banderaUpDown == false) {
					transSilla += 0.1;
					if (transSilla >= 0.0) {
						transSilla = 0.0f;
						banderaSilla = false;
					}
				}
			}
		}
		dwLastUpdateTime = dwCurrentTime;
	}
	if (dwElapsedTime >= 30)
	{
		
		dwLastUpdateTime = dwCurrentTime;
	}

	if (play)
	{

		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();

			}
		}
		else
		{
			//Draw animation
			pBz += KeyFrame[playIndex].pBzInc;
			pCx += KeyFrame[playIndex].pCxInc;
			pCz += KeyFrame[playIndex].pCzInc;
			pDx += KeyFrame[playIndex].pDxInc;
			pDz += KeyFrame[playIndex].pDzInc;
			pFx += KeyFrame[playIndex].pFxInc;
			pFy += KeyFrame[playIndex].pFyInc;
			pFz += KeyFrame[playIndex].pFzInc;
			pGz += KeyFrame[playIndex].pGzInc;

			i_curr_steps++;
		}

	}

	glutPostRedisplay();
}

void reshape(int width, int height)   // Creamos funcion Reshape
{
	if (height == 0)										// Prevenir division entre cero
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista

	//glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 170.0);
	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 1000.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	switch (key) {
		case 'w':   //Movimientos de camara
		case 'W':
			objCamera.Move_Camera(CAMERASPEED + 0.2);
			break;

		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED + 0.2));
			break;

		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED + 0.4));
			break;

		case 'd':
		case 'D':
			objCamera.Strafe_Camera(CAMERASPEED + 0.4);
			break;

		/*case ' ':		//Poner algo en movimiento
			//Commit?
			printf("mPos.x = %f\tmPos.y = %f\tmPos.z = %f\n",objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z);
			printf("mView.x = %f\tmView.y = %f\tmView.z = %f\n", objCamera.mView.x, objCamera.mView.y, objCamera.mView.z);
			printf("mUp.x = %f\tmUp.y = %f\tmUp.z = %f\n", objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);
			printf("glookupdown = %f\n", g_lookupdown);
			printf("CAMERASPEED: %f\n", CAMERASPEED);
			printf("******************************************\n");

			break;*/
		case '0':	//Original
			banderaCO = true;	//Estamos en camara original
			//Posiciona la camara a la posición original. Si viene de cualquier otra cámara, no debe borrar los anteriores estados.
			if (banderaCC == true) {
				//Viene de Camara Juego
				banderaCC = false;//quitamos bandera CJ
				//Guardo valores de la camara anterior (Cuarto)
				pos_xC = objCamera.mPos.x;
				pos_yC = objCamera.mPos.y;
				pos_zC = objCamera.mPos.z;
				view_xC = objCamera.mView.x;
				view_yC = objCamera.mView.y;
				view_zC = objCamera.mView.z;
				up_xC = objCamera.mUp.x;
				up_yC = objCamera.mUp.y;
				up_zC = objCamera.mUp.z;
				lookUpDownC = g_lookupdown;
			}
			if (banderaCJ == true) {
				//Viene de Camara Juego
				banderaCJ = false;//quitamos bandera CJ
				//Guardo valores de la camara anterior (Juego)
				pos_xJ = objCamera.mPos.x;
				pos_yJ = objCamera.mPos.y;
				pos_zJ = objCamera.mPos.z;
				view_xJ = objCamera.mView.x;
				view_yJ = objCamera.mView.y;
				view_zJ = objCamera.mView.z;
				up_xJ = objCamera.mUp.x;
				up_yJ = objCamera.mUp.y;
				up_zJ = objCamera.mUp.z;
				lookUpDownJ = g_lookupdown;
			}
			g_lookupdown = 16.0;
			//objCamera.Position_Camera(0.13f, 3.2f, 8.95f, 0.13f, 3.2f, 5.95f, 0, 1, 0);
			objCamera.Position_Camera(4.36f, 15.8f, 30.82f, 4.15f, 15.8f, 27.82f, 0, 1, 0);
			break;
		case '1':	//Cuarto
			banderaCC = true;	//Estamos en camara cuarto.
			if (banderaCO == true) {
				//Si viene de cámara original, no debe cambiar nada de los estados anteriores de la cámara para Cuarto y Juego
				pos_xC = pos_xC;
				pos_yC = pos_yC;
				pos_zC = pos_zC;
				view_xC = view_xC;
				view_yC = view_yC;
				view_zC = view_zC;
				up_xC = up_xC;
				up_yC = up_yC;
				up_zC = up_zC;
				lookUpDownC = lookUpDownC;

				banderaCO = false;
				g_lookupdown = lookUpDownC;
				objCamera.Position_Camera(pos_xC, pos_yC, pos_zC, view_xC, view_yC, view_zC, up_xC, up_yC, up_zC);
			}
			else {
				//Reviso el estado de las otras cámaras. De por si, banderaCO ya se sabe es false.
				//Primero, reviso si CJ estaba previamente true, de modo que se sabe que viene de esa cámara.
				if (banderaCJ == true) {
					//Viene de Camara Juego
					banderaCJ = false;//quitamos bandera CJ
					//Guardo valores de la camara anterior (Juego)
					pos_xJ = objCamera.mPos.x;
					pos_yJ = objCamera.mPos.y;
					pos_zJ = objCamera.mPos.z;
					view_xJ = objCamera.mView.x;
					view_yJ = objCamera.mView.y;
					view_zJ = objCamera.mView.z;
					up_xJ = objCamera.mUp.x;
					up_yJ = objCamera.mUp.y;
					up_zJ = objCamera.mUp.z;
					lookUpDownJ = g_lookupdown;
				}
				//Si es false, quiere decir que es o la primera vez que entra o viene de CO sin haberse metido a CJ
				g_lookupdown = lookUpDownC;
				objCamera.Position_Camera(pos_xC, pos_yC, pos_zC, view_xC, view_yC, view_zC, up_xC, up_yC, up_zC);
			}
		
			break;
		case '2':	//Juego
			banderaCJ = true;
			if (banderaCO == true) {
				//Si viene de cámara original, no debe cambiar nada de los estados anteriores de la cámara para Cuarto y Juego
				pos_xJ = pos_xJ;
				pos_yJ = pos_yJ;
				pos_zJ = pos_zJ;
				view_xJ = view_xJ;
				view_yJ = view_yJ;
				view_zJ = view_zJ;
				up_xJ = up_xJ;
				up_yJ = up_yJ;
				up_zJ = up_zJ;
				lookUpDownJ = lookUpDownJ;
				banderaCO = false;
				g_lookupdown = lookUpDownJ;
				objCamera.Position_Camera(pos_xJ, pos_yJ, pos_zJ, view_xJ, view_yJ, view_zJ, up_xJ, up_yJ, up_zJ);
			}
			else {
				//Reviso el estado de las otras cámaras. De por si, banderaCO ya se sabe es false.
				//Primero, reviso si CC estaba previamente true, de modo que se sabe que viene de esa cámara.
				if (banderaCC == true) {
					//Viene de Camara Juego
					banderaCC = false;//quitamos bandera CJ
					//Guardo valores de la camara anterior (Cuarto)
					pos_xC = objCamera.mPos.x;
					pos_yC = objCamera.mPos.y;
					pos_zC = objCamera.mPos.z;
					view_xC = objCamera.mView.x;
					view_yC = objCamera.mView.y;
					view_zC = objCamera.mView.z;
					up_xC = objCamera.mUp.x;
					up_yC = objCamera.mUp.y;
					up_zC = objCamera.mUp.z;
					lookUpDownC = g_lookupdown;
				}
				//Si es false, quiere decir que es o la primera vez que entra o viene de CO sin haberse metido a CC
				g_lookupdown = lookUpDownJ;
				objCamera.Position_Camera(pos_xJ, pos_yJ, pos_zJ, view_xJ, view_yJ, view_zJ, up_xJ, up_yJ, up_zJ);
			}
			break;
		case '3':	//
			if (banderaPuerta == false) {
				banderaPuerta = true;
				if (rotPuerta == 0)
					banderaUpDown = true;	//Va de 0 a 90
				else
					banderaUpDown = false;	//Va de 90 a 0;
			}
			break;
		case '4':	//
			if (banderaVentana == false) {
				banderaVentana = true;
				if (rotVentana == 0)
					banderaUpDown = true;	//Va de 0 a 90
				else
					banderaUpDown = false;
			}
			break;
		case '5':
			if (banderaSilla == false) {
				banderaSilla = true;
				if (transSilla == 0.0)	//Va de 0 a -2.0
					banderaTrans = true;	//Va de 0 a 90
				else
					banderaTrans = false;
			}
			break;
		/*case '6':
			rotSilla += 2.0;
			printf("rot = %f\n", rotSilla);
			break;
		case '7':
			rotSilla -= 2.0;
			printf("rot = %f\n", rotSilla);
			break;*/
		/*case 'j':
			trax += 0.1;
			printf("x = %f\ty = %f\tz = %f\n", trax,tray,traz);
			break;
		case 'i':
			tray += 0.1;
			printf("x = %f\ty = %f\tz = %f\n", trax, tray, traz);
			break;
		case 'k':
			traz += 0.1;
			printf("x = %f\ty = %f\tz = %f\n", trax, tray, traz);
			break;
		case 'J':
			trax -= 0.1;
			printf("x = %f\ty = %f\tz = %f\n", trax, tray, traz);
			break;
		case 'I':
			tray -= 0.1;
			printf("x = %f\ty = %f\tz = %f\n", trax, tray, traz);
			break;
		case 'K':
			traz -= 0.1;
			printf("x = %f\ty = %f\tz = %f\n", trax, tray, traz);
			break;
		case 'b':
			scaleX += 0.01;
			printf("Sx = %f\tSy = %f\tSz = %f\n", scaleX, scaleY, scaleZ);
			break;
		case 'B':
			scaleX -= 0.01;
			printf("Sx = %f\tSy = %f\tSz = %f\n", scaleX, scaleY, scaleZ);
			break;
		case 'n':
			scaleY += 0.01;
			printf("Sx = %f\tSy = %f\tSz = %f\n", scaleX, scaleY, scaleZ);
			break;
		case 'N':
			scaleY -= 0.01;
			printf("Sx = %f\tSy = %f\tSz = %f\n", scaleX, scaleY, scaleZ);
			break;
		case 'm':
			scaleZ += 0.01;
			printf("Sx = %f\tSy = %f\tSz = %f\n", scaleX, scaleY, scaleZ);
			break;
		case 'M':
			scaleZ -= 0.01;
			printf("Sx = %f\tSy = %f\tSz = %f\n", scaleX, scaleY, scaleZ);
			break;*/

		/*case ' ':	//Salvar Frame
			if (FrameIndex < MAX_FRAMES)
			{
				saveFrame();
			}

			break;*/
		case '6':
			if (play == false && (FrameIndex > 1))
			{

				resetElements();
				//First Interpolation
				interpolation();

				play = true;
				playIndex = 0;
				i_curr_steps = 0;
			}
			else
			{
				play = false;
			}
			break;

		/*case '.':
			for (int i = 0; i < FrameIndex; i++) {
				printf("Frame [%d]\n", i);
				printf("pBz = %f  pCx = %f  pCz = %f  pDx = %f  pDz = %f\n", KeyFrame[i].pBz, KeyFrame[i].pCx, KeyFrame[i].pCz, KeyFrame[i].pDx, KeyFrame[i].pDz);
				printf("pFx = %f  pFy = %f  pFz = %f  pGz = %f\n", KeyFrame[i].pFz, KeyFrame[i].pFy, KeyFrame[i].pFz, KeyFrame[i].pGz);

				printf("\nIncrementos:\n\n");
				printf("pBzInc = %f  pCxInc = %f  pCzInc = %f  pDxInc = %f  pDzInc = %f\n", KeyFrame[i].pBzInc, KeyFrame[i].pCxInc, KeyFrame[i].pCzInc, KeyFrame[i].pDxInc, KeyFrame[i].pDzInc);
				printf("pFxInc = %f  pFyInc = %f  pFzInc = %f  pGzInc = %f\n", KeyFrame[i].pFzInc, KeyFrame[i].pFyInc, KeyFrame[i].pFzInc, KeyFrame[i].pGzInc);
				printf("******************************************\n\n");
			}
			break;*/
//Casos utilizados para mover las fichas de Ajedrez
		/*case 'g':
			pBz -= 0.5;
			break;
		case 'h':
			pGz += 0.5;
			break;
		case 'j':
			pCx += 0.5;
			break;
		case 'J':
			pCx -= 0.5;
			break;
		case 'k':
			pCz += 0.5;
			break;
		case 'K':
			pCz -= 0.5;
			break;
		case 'i':
			pDx += 0.5;
			break;
		case 'I':
			pDz += 0.5;
			break;
		case 'l':
			pFx += 0.5;
			break;
		case 'L':
			pFx -= 0.5;
			break;
		case 'p':
			pFz += 0.5;
			break;
		case 'P':
			pFz -= 0.5;
			break;
		case 'o':
			pFy += 0.5;
			break;
		case 'O':
			pFy -= 0.5;
			break;*/
		case 27:        // Cuando Esc es presionado...
			exit(0);   // Salimos del programa
			break;
		default:        // Cualquier otra
			break;
	}

	glutPostRedisplay();
}

void arrow_keys(int a_keys, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)
{
	switch (a_keys) {
		case GLUT_KEY_PAGE_UP:
			objCamera.UpDown_Camera(CAMERASPEED);
			break;

		case GLUT_KEY_PAGE_DOWN:
			objCamera.UpDown_Camera(-CAMERASPEED);
			break;

		case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
			g_lookupdown -= 1.0f;
			break;

		case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
			g_lookupdown += 1.0f;
			break;

		case GLUT_KEY_LEFT:
			objCamera.Rotate_View(-CAMERASPEED);
			break;

		case GLUT_KEY_RIGHT:
			objCamera.Rotate_View(CAMERASPEED);
			break;

		default:
			break;
	}
	glutPostRedisplay();
}


int main(int argc, char** argv)   // Main Function
{
	glutInit(&argc, argv); // Inicializamos OpenGL
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
	glutInitWindowSize(1600, 900);	// Tamaño de la Ventana
	glutInitWindowPosition(0, 0);	//Posicion de la Ventana
	glutCreateWindow("Proyecto Final"); // Nombre de la Ventana
	//glutFullScreen     ( );         // Full Screen
	InitGL();						// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);  //Indicamos a Glut función de dibujo
	glutReshapeFunc(reshape);	//Indicamos a Glut función en caso de cambio de tamano
	glutKeyboardFunc(keyboard);	//Indicamos a Glut función de manejo de teclado
	glutSpecialFunc(arrow_keys);	//Otras
	glutIdleFunc(animacion);
	glutMainLoop();          // 

	return 0;
}
