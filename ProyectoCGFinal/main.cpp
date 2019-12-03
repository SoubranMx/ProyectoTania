﻿//Semestre 2020 - 1
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
//END MODELOS

//Auxiliares para dejar en su lugar cualquier cosa cuando la mueves con 568 o kli
float  Lx = 0.0;
float  Ly = 0.0;
float  Lz = 0.0;
float aux = 0.0;
//glTranslatef(3.8, 4.5, 9.0);
float trax = 3.6;
float tray = 4.7;
float traz = 8.05;
float textX = 0.0;
float textY = 0.0;

// BANDERAS
bool banderaCG = false;	//para mostrar las PC, son pesadas.
bool banderaCJ = false;	//Visualización de Camara enfocada en el Juego
bool banderaCC = false;	//Visualización de Camara enfocada en el cuarto
bool banderaCO = false;	//Visualización de Camara original
bool banderaPuerta = false;
bool banderaUpDown = false;
// END BANDERAS

//ANIMACION
float rotPuerta = 0.0f;
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

//Carga de Figuras
/*
	streetLamp._3dsLoad("Modelos/streetLamp.3DS");
	streetLamp.VertexNormals();
*/

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

	pos_xJ = -2.69;
	pos_yJ = 6.7;
	pos_zJ = -0.77;
	view_xJ = -2.69;
	view_yJ = 6.7;
	view_zJ = -3.77;
	up_xJ = 0.0;
	up_yJ = 1.0;
	up_zJ = 0.0;
	lookUpDownJ = 90.0;
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
		glTranslatef(0.0, 1.0, 0.0);
		glScalef(2.0, 0.2, 2.0);
		glDisable(GL_LIGHTING);
		mesa.mesa(0, 10.0, 10.0, 0.04);
		glPushMatrix();
		glPopMatrix();
		glEnable(GL_LIGHTING);
	glPopMatrix();
}

void jardineras() {
	glPushMatrix();
		glTranslatef(0.0, 0.5, -5.0);
		glScalef(26.0, 1.0, 10.0);
		glDisable(GL_LIGHTING);
		//jardinera.torreMedia(t_tierra.GLindex, t_concreto.GLindex, 26.0, 1.0, 10.0);
		glEnable(GL_LIGHTING);
	glPopMatrix();
}

/*
void laboratorio() {

	glPushMatrix();
	glTranslatef(-8.0, 3.0, -5.0);
	salon.labCG(t_LabCG, 8.0, 3.0, 7.0);

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);	//Fix? en realidad no tendria que funcionar pero ... bueno. Arregla el problema de la posición del laboratorio.
	glPushMatrix();
	glTranslatef(0.0, 0.0, -3.495);
	glPushMatrix();//Pizarron
	glBindTexture(GL_TEXTURE_2D, t_pizarron.GLindex);
	glTranslatef(-1.5, -1.2, 0.0);
	glScalef(4.5, 4.5, 1.0);
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0, 0.5, 0.0);	//6
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5, 0.5, 0.0);	//5
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5, 0.0, 0.0);	//3
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 0.0);	//2
	glEnd();
	// ANIMACION
	glBindTexture(GL_TEXTURE_2D, t_pizarronCG.GLindex);
	glTranslatef(0.03, 0.03, 0.0);
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(jPizCG, iPizCG);		glVertex3f(0.0, 0.4, 0.1);
	glTexCoord2f(jPizCG + 0.166, iPizCG);		glVertex3f(0.4, 0.4, 0.1);
	glTexCoord2f(jPizCG + 0.166, iPizCG - 0.2); glVertex3f(0.4, 0.0, 0.1);
	glTexCoord2f(jPizCG, iPizCG - 0.2); glVertex3f(0.0, 0.0, 0.1);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	//NoFumar
	glBindTexture(GL_TEXTURE_2D, t_fumar.GLindex);
	glTranslatef(-1.2, 1.13, -3.490);
	glScalef(0.5, 0.5, 1.0);
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0, 0.5, 0.0);	//6
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5, 0.5, 0.0);	//5
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5, 0.0, 0.0);	//3
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 0.0);	//2
	glEnd();
	//NoComer
	glTranslatef(-0.6, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, t_comer.GLindex);
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0, 0.5, 0.0);	//6
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5, 0.5, 0.0);	//5
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5, 0.0, 0.0);	//3
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 0.0);	//2
	glEnd();
	//NoHablar
	glTranslatef(3.4, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, t_hablar.GLindex);
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0, 0.5, 0.0);	//6
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5, 0.5, 0.0);	//5
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5, 0.0, 0.0);	//3
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 0.0);	//2
	glEnd();
	//NoCelular
	glTranslatef(0.6, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, t_celular.GLindex);
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0, 0.5, 0.0);	//6
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5, 0.5, 0.0);	//5
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5, 0.0, 0.0);	//3
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 0.0);	//2
	glEnd();
	glPopMatrix();

	//MetalCG
	glPushMatrix();
	glTranslatef(-0.8, -1.49, -3.5);
	glBindTexture(GL_TEXTURE_2D, t_metalCG.GLindex);
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 7.0f); glVertex3f(0.0, 0.0, 7.0);	//6
	glTexCoord2f(1.0f, 7.0f); glVertex3f(0.5, 0.0, 7.0);	//5
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5, 0.0, 0.0);	//3
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 0.0);	//2
	glEnd();
	glPopMatrix();

	//	FIGURAS 3D
	glDisable(GL_COLOR_MATERIAL);

	//No puedo poner las PC con push y pop, desaparecen los renders ???
	glPushMatrix();	//Desk4	frente
	glTranslatef(0.5, -1.5, -1.7);
	glScalef(0.010, 0.005, 0.005);
	desk.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();	//Desk3 frente
	glTranslatef(-3.5, -1.5, -1.7);
	glScalef(0.008, 0.005, 0.005);
	desk.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();	//Desk4 medio
	glTranslatef(0.5, -1.5, 0.0);
	glScalef(0.01, 0.005, 0.005);
	desk.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();	//Desk3 medio
	glTranslatef(-3.5, -1.5, 0.0);
	glScalef(0.008, 0.005, 0.005);
	desk.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();	//Desk4 atras
	glTranslatef(0.5, -1.5, 2.0);
	glScalef(0.01, 0.005, 0.005);
	desk.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();	//Desk3 atras
	glTranslatef(-3.5, -1.5, 1.8);
	glScalef(0.008, 0.005, 0.005);
	desk.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();


	//PC's
	if (banderaCG == true) {
		aux = -1.8;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				glPushMatrix();
				glTranslatef(-3.5 + j, -0.81, aux);	//-3.5, -0.8, -1.8
				//glTranslatef(Lx, -0.8, -1.8);
				glScalef(0.008, 0.008, 0.008);
				pc_Pro.GLrender(NULL, _SHADED, 1.0);
				glPopMatrix();
			}
			aux += 1.8;
		}

		aux = -1.8;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 4; j++) {
				glPushMatrix();
				glTranslatef(0.5 + j, -0.81, aux);	//-3.5, -0.8, -1.8
				//glTranslatef(-3.5+Lx, -0.8+Ly, -1.8+1.8+1.8);
				glScalef(0.008, 0.008, 0.008);
				pc_Pro.GLrender(NULL, _SHADED, 1.0);
				glPopMatrix();
			}
			aux += 1.8;
		}

		//	SILLAS
		aux = -1.0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				glPushMatrix();
				glTranslatef(-3.5 + j * 0.98, -1.5, aux);
				glRotatef(180, 0.0, 1.0, 0.0);
				//glScalef(0.01, 0.015, 0.01);
				glScalef(0.03, 0.04, 0.02);
				sillaLab.GLrender(NULL, _SHADED, 1.0);
				glPopMatrix();
			}
			aux += 1.8;
		}

		aux = -1.0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 4; j++) {
				glPushMatrix();
				glTranslatef(0.5 + j * 0.9, -1.5, aux);
				glRotatef(180, 0.0, 1.0, 0.0);
				//glScalef(0.01, 0.015, 0.01);
				glScalef(0.03, 0.04, 0.02);
				sillaLab.GLrender(NULL, _SHADED, 1.0);
				glPopMatrix();
			}
			aux += 1.8;
		}
	}//	If
	glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}
*/
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
		//createCuarto();
		glPushMatrix();
			glTranslatef(0.0, 9.15, -1.0);
			glScalef(18.0, 18.0, 18.0);
			glDisable(GL_LIGHTING);
			cuarto.cuarto(t_pared1.GLindex, t_pared2.GLindex, t_pisoM.GLindex, 1.0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0, 9.195, -1.0);
			glScalef(18.1, 18.1, 18.1);
			glDisable(GL_LIGHTING);
			cuarto.cuarto(t_wall.GLindex, t_wall.GLindex, t_wall.GLindex, -1.0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(trax, tray, traz);
			glRotatef(rotPuerta, 0.0, 1.0, 0.0);
			glScalef(18.1, 18.1, 1.0);
			glDisable(GL_LIGHTING);
			puerta.puerta(t_door.GLindex);
			glEnable(GL_LIGHTING);
		glPopMatrix();
		//createPuerta();
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
		dwLastUpdateTime = dwCurrentTime;
	}
	if (dwElapsedTime >= 30)
	{
		
		dwLastUpdateTime = dwCurrentTime;
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

	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 170.0);

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

	case ' ':		//Poner algo en movimiento
		//Commit?
		printf("mPos.x = %f\tmPos.y = %f\tmPos.z = %f\n",objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z);
		printf("mView.x = %f\tmView.y = %f\tmView.z = %f\n", objCamera.mView.x, objCamera.mView.y, objCamera.mView.z);
		printf("mUp.x = %f\tmUp.y = %f\tmUp.z = %f\n", objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);
		printf("glookupdown = %f\n", g_lookupdown);
		printf("CAMERASPEED: %f\n", CAMERASPEED);
		printf("******************************************\n");

		break;
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
		break;
	case '5':
		break;
	case '6':
		
		break;
	case '7':
		
		break;
	case 'j':
		
		break;
	case 'i':
		
		break;
	case 'k':
		
		break;
	case 'J':
		
		break;
	case 'I':
		
		break;
	case 'K':
		
		break;
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
