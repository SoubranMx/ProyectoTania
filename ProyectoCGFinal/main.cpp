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

CCamera objCamera;
GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font = (int)GLUT_BITMAP_HELVETICA_18;

GLfloat Diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[] = { 0.0f, 27.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[] = { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = { 18 };

CTexture text1;
CTexture text2;
CTexture text3;	//Flecha
CTexture text4;	//Pavimento
CTexture text5;	//Pasto01
CTexture text6;	//Casa01

CFiguras fig1;
CFiguras fig2;
CFiguras fig3;
CFiguras fig4;	//Pasto01
CFiguras fig5;	//Casa01
CFiguras fig6;

CFiguras fig7; //Para el monito

//Figuras de 3D Studio
CModel kit;
CModel llanta;

//Animaci�n del coche
float movKit = 0.0;
bool g_fanimacion = false;


//MOD MIA
float giro_llanta = 0.0f;
bool loop_animacion = true;

/**************************	ANIMACION REPORTE	***************************/
bool backToFuture = false;	//Indica cuando cierta parte de la animacion (volando) esta ocurriendo.
float movDelante = 0.0f;	//Para moverse adelante/atras
float movArriba = 4.0f;		//Para moverse arriba/abajo		El coche inicia en valor de 4 para estar al ras del suelo
float giroBTF = 0.0f;		//Para hacer el giro a lo Back To the Future

int flagPos = 0;		//0 para el origen, 1 para el movimiento hacia atras, 2 arriba, 3 delante volando, 4 abajo, 5 delante suelo, 6 atras a origen
/**************************	END ANIMACION REPORTE	**************************/

//END MOD

void InitGL(GLvoid)     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	/* setup blending */
	glEnable(GL_BLEND);			// Turn Blending On

	text1.LoadBMP("01.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	text2.LoadBMP("logopumas.bmp");
	text2.BuildGLTexture();
	text2.ReleaseImage();

	text3.LoadTGA("city/arrow.tga");
	text3.BuildGLTexture();
	text3.ReleaseImage();

	text4.LoadTGA("city/pavimento.tga");
	text4.BuildGLTexture();
	text4.ReleaseImage();

	text5.LoadTGA("city/pasto01.tga");
	text5.BuildGLTexture();
	text5.ReleaseImage();

	text6.LoadTGA("city/casa01.tga");
	text6.BuildGLTexture();
	text6.ReleaseImage();

	//Carga de Figuras
	kit._3dsLoad("kitt.3ds");
	//kit.VertexNormals();

	llanta._3dsLoad("k_rueda.3ds");


	objCamera.Position_Camera(10, 2.5f, 13, 10, 2.5f, 10, 0, 1, 0);

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


/**************************	ANIMACION REPORTE	***************************/

void mov1() {
	if (movDelante >= -60.0) {
		movDelante -= 0.3;
		giro_llanta -= 3.0;
	}
	else {
		movDelante = -60.0;		//Exageraci�n mia, obligo al flotante a tomar un valor exacto.
		flagPos = 2;
		backToFuture = true;
		giro_llanta = 0.0;		//Debe quedar en 0, o si no rota raro cuando sube.
	}
}

void mov2() {
	if (movArriba <= 49) {
		movArriba += 0.1;
		if (giroBTF <= 90) {
			giroBTF += 0.2;
		}
	}
	else {
		movArriba = 49.0;
		flagPos = 3;
	}

}

void mov3() {
	if (movDelante <= 40) {
		movDelante += 0.3;
	}
	else {
		movDelante = 40;
		flagPos = 4;
	}
}

void mov4() {
	if (movArriba >= 4.0) {
		movArriba -= 0.1;
		if (giroBTF >= 0.0) {
			giroBTF -= 0.2;
		}
	}
	else {
		movArriba = 4.0;
		flagPos = 5;
		giroBTF = 0.0;
	}
}

void mov5() {
	if (movDelante <= 90.0) {
		movDelante += 0.3;
		giro_llanta += 3.0;
	}
	else {
		movDelante = 90.0;
		flagPos = 6;
	}
}

void mov6() {
	if (movDelante >= 0.0) {
		movDelante -= 0.3;
		giro_llanta -= 3.0;
	}
	else {
		movDelante = 0.0;
		flagPos = 1;
		g_fanimacion = false;	//Para la animaci�n.
	}
}

void movCoche() {
	switch (flagPos) {
	case 1:		//Desde el origen, hacia 60 unidades atras
		mov1();
		break;
	case 2:		//Comienza subida 45 unidades, cambia rotacion de llantas = volando
		mov2();
		break;
	case 3:		//Hacia adelante 100 unidades, llantas = volando.
		mov3();
		break;
	case 4:		//Hacia abajo 45 unidades, cambia rotacion de llantas = suelo
		mov4();
		break;
	case 5:		//Hacia adelante 50 unidades, llantas = suelo
		mov5();
		break;
	case 6:		//Hacia atr�s 90 unidades, al origen y para.
		mov6();
		break;
	default:
		break;
	}
}

/**************************	END ANIMACION REPORTE	**************************/

void display(void)   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glPushMatrix();

	glRotatef(g_lookupdown, 1.0f, 0, 0);

	gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
		objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
		objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);


	glPushMatrix();
	glPushMatrix(); //Creamos cielo
	glDisable(GL_LIGHTING);
	glTranslatef(0, 60, 0);
	fig1.skybox(130.0, 130.0, 130.0, text1.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	//Para que el coche conserve sus colores
	glDisable(GL_COLOR_MATERIAL);
	glRotatef(90, 0, 1, 0);	//Debido a que el coche importado estaba configurado de cierta forma
	glScalef(0.3, 0.3, 0.3);

	glTranslatef(0, movArriba, movDelante);		//movKit es para la animacion
	// -60 <= movDelante <= 40			4 <= movArriba <= 49
	//Pongo aqu� la carroceria del carro
	//kit.GLrender(NULL,_SHADED,1.0);  //_WIRED O _POINTS
	kit.GLrender(NULL, _WIRED, 1.0);
	//	MOD MIA
	glPushMatrix();		//LLANTA	DEL-DER
	glTranslatef(-6.0, -1.0, 7.5);
	glRotatef(giro_llanta, 1.0, 0.0, 0.0);
	//glPushMatrix();
	if (backToFuture == true) {
		glRotatef(giroBTF, 0.0, 0.0, 1.0);	//deben rotar en Z
	}
	//glPopMatrix();
	llanta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();		//LLANTA	DEL-IZQ
	glTranslatef(6.0, -1.0, 7.5);
	glRotatef(giro_llanta, 1.0, 0.0, 0.0);
	glRotatef(180.0, 0.0, 1.0, 0.0);
	//glPushMatrix();
	if (backToFuture == true) {
		glRotatef(giroBTF, 0.0, 0.0, 1.0);	//deben rotar en Z
	}
	//glPopMatrix();
	llanta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();		//LLANTA	TRAS-DER
	glTranslatef(-6.0, -1.0, -9.5);
	glRotatef(giro_llanta, 1.0, 0.0, 0.0);
	//glPushMatrix();
	if (backToFuture == true) {
		glRotatef(giroBTF, 0.0, 0.0, 1.0);	//deben rotar en Z
	}
	//glPopMatrix();
	llanta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();		//LLANTA	TRAS-IZQ
	glTranslatef(6.0, -1.0, -9.5);
	glRotatef(giro_llanta, 1.0, 0.0, 0.0);
	glRotatef(180.0, 0.0, 1.0, 0.0);
	//glPushMatrix();
	if (backToFuture == true) {
		glRotatef(giroBTF, 0.0, 0.0, 1.0);	//deben rotar en Z
	}
	//glPopMatrix();
	llanta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();
	glPopMatrix();
	//	END MOD

		//Para que el comando glColor funcione con iluminacion
	glEnable(GL_COLOR_MATERIAL);

	glPushMatrix(); //Flecha
	glScalef(7, 0.1, 7);
	glDisable(GL_LIGHTING);
	fig3.prisma_anun(text3.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Camino1
	glTranslatef(23.5, 0.0, 0.0);
	glScalef(40, 0.1, 7);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Camino2
	glTranslatef(-23.5, 0.0, 0.0);
	glScalef(40, 0.1, 7);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Pasto
	glTranslatef(0.0, 0.0, -4.0);
	glScalef(87, 0.1, 1);
	glDisable(GL_LIGHTING);
	fig4.prisma2(text5.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Pasto
	glTranslatef(0.0, 0.0, 4.0);
	glScalef(87, 0.1, 1);
	glDisable(GL_LIGHTING);
	fig4.prisma2(text5.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Casa01
	glTranslatef(0.0, 3.0, 7.0);
	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 0, 1);
	glScalef(6, 5.0, 6);
	glDisable(GL_LIGHTING);
	fig5.prisma2(text6.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Casa01
	glTranslatef(0.0, 3.0, -7.0);
	glRotatef(90, 1, 0, 0);
	glScalef(6, 5.0, 6);
	glDisable(GL_LIGHTING);
	fig5.prisma2(text6.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glColor3f(1.0, 1.0, 1.0);

	glPopMatrix();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 0.0, 0.0);
	pintaTexto(-12, 12.0, -14.0, (void*)font, "Practica 10");
	pintaTexto(-12, 10.5, -14, (void*)font, "Poner algo en Movimiento");
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

	/*		ANIMACION DEL DIA DE PR�CTICA
	if(g_fanimacion)
	{
		//Animacion sencilla Space = se mueve hasta 60 y se detiene. Space otra vez y regresa al origen y vuelve la animacion
		/*if (movKit <= 60.0) {
			movKit += 0.5;
			giro_llanta += 3.0;
		}
		else {
			if (g_fanimacion == true && movKit > 60.0) {
				g_fanimacion = false;
			}
			/*else if (g_fanimacion == false && movKit > 60.0){
				movKit = 0.0f;
				giro_llanta = 0.0f;
			}

		}*/
		/*

			//Animacion: Space = coche inicia loop { adelante hasta 50u, atras hasta 0u}
			if (loop_animacion == true && movKit <= 50.0) {
				movKit += 0.5f;
				giro_llanta += 3;
			}
			else {
				if (movKit >= 50.0)
					loop_animacion = false;
				if (loop_animacion == false && movKit >= 0) {
					movKit -= 0.5f;
					giro_llanta -= 3;
				}
				if(movKit == 0) {
					loop_animacion = true;
				}
			}
		}*/

		/**************************	ANIMACION REPORTE	***************************/
	if (g_fanimacion == true) {
		movCoche();
	}
	/**************************	END ANIMACION REPORTE	**************************/
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
		g_fanimacion ^= true; //Activamos/desactivamos la animac�on
		/**************************	ANIMACION REPORTE	***************************/

		//	Inicializa todas las variables, en cualquier momento que se presione space la animaci�n empieza desde 0.

		flagPos = 1;			//Indica que numero de animacion hacer.
		backToFuture = false;	//Indica que el coche en un determinado momento est� volando.
		movDelante = 0.0f;		//Para mover el coche hacia adelante/atr�s
		movArriba = 4.0f;		//Para mover el coche hacia arriba/abajo
		giroBTF = 0.0f;			//Para girar las llantas a lo Back to the Future
		giro_llanta = 0.0f;		//Para girar las llantas simulando tracci�n
		/**************************	END ANIMACION REPORTE	**************************/
		/*movKit = 0.0f;
		giro_llanta = 0.0f;*/
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
	glutInitWindowSize(1600, 900);	// Tama�o de la Ventana
	glutInitWindowPosition(0, 0);	//Posicion de la Ventana
	glutCreateWindow("Practica 10"); // Nombre de la Ventana
	//glutFullScreen     ( );         // Full Screen
	InitGL();						// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);  //Indicamos a Glut funci�n de dibujo
	glutReshapeFunc(reshape);	//Indicamos a Glut funci�n en caso de cambio de tamano
	glutKeyboardFunc(keyboard);	//Indicamos a Glut funci�n de manejo de teclado
	glutSpecialFunc(arrow_keys);	//Otras
	glutIdleFunc(animacion);
	glutMainLoop();          // 

	return 0;
}
