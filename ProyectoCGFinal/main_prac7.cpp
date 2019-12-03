//Semestre 2019 - 1
//************************************************************//
//************************************************************//
//************** Alumno (s): *********************************//
//*************	Estrada Soubran Uriel Alejandro			******//
//*************											******//
//************************************************************//
#include "Main.h"

float angleX = 0.0f;
float angleY = 0.0f;
float angleZ = 0.0f;
float transX = 0.0f;
float transY = 0.0f;
float transZ = 0.0f;

float LightAngle = 50.0f;

bool	light = false;		// Luz ON/OFF
bool	positional = true;

static int spin = 0;
/*
	Las componentes del material explican el tipo de luz que REFLEJAN
	Las componentes de la luz explican el tipo de luz que EMITEN

	Si la luz emite R,B y el material esta configurado para reflejar G
	cuando se activa la luz el objeto se ve negro, pues la luz no emitió
	el color que esperaba reflejar el material.

	Por ello, se suele utilizar una fuente de luz blanca, para obtener todos
	los rangos de frecuencias de la luz y se refleje el color que el material
	espera reflejar.
*/

GLfloat LightAmbient[]= { 1.0f, 1.0f, 1.0f, 1.0f }; 			// Ambient Light Values
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat LightSpecular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat LightPosition[]= { 0.0f, 0.0f, 0.0f, 1.0f };			// Light Position
GLfloat LightPosition1[]= { 0.0f, 0.0f, 1.0f, 0.0f };			// Light Position
GLfloat LightDirection[]= { 0.0f, 0.0f, -2.0f };			// Light Position

// {r,g,b,alpha?}
GLfloat mat_ambient[] = { 0.0, 0.0, 0.0, 1.0 };					// Color background, las caras menos iluminadas tenderán a ser oscuras con 0,0,0,1
GLfloat mat_diffuse[] = { 0.0, 1.0, 0.0, 1.0 };					// Object Color main
GLfloat mat_specular[] = { 0.0, 0.0, 1.0, 1.0 };				// Specular color
GLfloat mat_shininess[] = { 10.0 };								// Mayor = más concentrado, menor = más disperso  MIN = 1 => brillo sobre toda la superficie.

GLfloat mat_ambient1[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_diffuse1[] = { 1.0, 0.7, 0.1, 1.0 };
GLfloat mat_specular1[] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat mat_shininess1[] = { 10.0 };

void InitGL ( GLvoid )     // Inicializamos parametros => se llama antes de dibujar
{
	glShadeModel(GL_SMOOTH);							// Habilitamos Smooth Shading
	//GL_FLAT hace las aproximaciones de luz 1 vez por polígono (caras)
	//GL_SMOOTH (Gouraud) hace aproximaciones 1 vez por vértice.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// OpenGL maneja hasta 8 fuentes de luz diferentes
	// GL_LIGTHX indica la fuente de luz. 0 es la luz default.
	// GL_AMBIENT => LightAmbient es un valor que se le pasa a GL_AMBIENT
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);					// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);					// Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);				// Setup The Diffuse Light

	//glEnable(GL_LIGHTING);		// Iluminación general => switch principal, se activa con L en este programa
	glEnable(GL_LIGHT1);							// Enable Light One	=> es como un apagador de focos.
	//	Como consume muchos recursos, por default esta desactivada.

}
// Si no se pusiera el comando Normal3f, la API gráfica calcula normales de acuerdo a la regla de creación de las caras del objeto.
void prisma (void)  //Funcion creacion prisma
{

	GLfloat vertice [8][3] = {
				{0.5 ,-0.5, 0.5},		//Coordenadas Vértice 1 V1
				{-0.5 ,-0.5, 0.5},		//Coordenadas Vértice 2 V2
				{-0.5 ,-0.5, -0.5},		//Coordenadas Vértice 3 V3
				{0.5 ,-0.5, -0.5},		//Coordenadas Vértice 4 V4
				{0.5 ,0.5, 0.5},		//Coordenadas Vértice 5 V5
				{0.5 ,0.5, -0.5},		//Coordenadas Vértice 6 V6
				{-0.5 ,0.5, -0.5},		//Coordenadas Vértice 7 V7
				{-0.5 ,0.5, 0.5},		//Coordenadas Vértice 8 V8
				};

		glBegin(GL_POLYGON);	//Front
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glVertex3fv(vertice[0]);
			glVertex3fv(vertice[4]);
			glVertex3fv(vertice[7]);
			glVertex3fv(vertice[1]);
		glEnd();

		glBegin(GL_POLYGON);	//Right
			glNormal3f( 1.0f, 0.0f, 0.0f);
			glVertex3fv(vertice[0]);
			glVertex3fv(vertice[3]);
			glVertex3fv(vertice[5]);
			glVertex3fv(vertice[4]);
		glEnd();

		glBegin(GL_POLYGON);	//Back
			glNormal3f( 0.0f, 0.0f,-1.0f);
			glVertex3fv(vertice[6]);
			glVertex3fv(vertice[5]);
			glVertex3fv(vertice[3]);
			glVertex3fv(vertice[2]);
		glEnd();

		glBegin(GL_POLYGON);  //Left
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glVertex3fv(vertice[1]);
			glVertex3fv(vertice[7]);
			glVertex3fv(vertice[6]);
			glVertex3fv(vertice[2]);
		glEnd();

		glBegin(GL_POLYGON);  //Bottom
			glNormal3f( 0.0f,-1.0f, 0.0f);
			glVertex3fv(vertice[0]);
			glVertex3fv(vertice[1]);
			glVertex3fv(vertice[2]);
			glVertex3fv(vertice[3]);
		glEnd();

		glBegin(GL_POLYGON);  //Top
			glNormal3f( 0.0f, 1.0f, 0.0f);
			glVertex3fv(vertice[4]);
			glVertex3fv(vertice[5]);
			glVertex3fv(vertice[6]);
			glVertex3fv(vertice[7]);
		glEnd();
}

void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(positional)
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, LightAngle);			// Position The Light
	

	glPushMatrix ();

		glTranslatef (0.0, 0.0, -5.0);
	
		glPushMatrix(); //Esfera que representa a nuestra fuente de Luz
						//Este código es para que la fuente de luz gire
			glRotatef (spin, 1.0, 0.0, 0.0);
			glTranslatef (0.0, 0.0, 4.5);
			if(positional)
			{
				glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
				glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION,LightDirection);			
			}
			else
				glLightfv(GL_LIGHT1, GL_POSITION, LightPosition1);

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glColor3f (1.0, 1.0, 0.0);
				
				glutSolidSphere(0.07,10,10);
				if (!light)
				{
					glDisable(GL_LIGHTING);
				}
				else
				{
					glEnable(GL_LIGHTING);
				}
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
				glTranslatef (transX, transY, transZ);
				glRotatef(angleX, 1.0f, 0.0f, 0.0f);
				glRotatef(angleZ, 0.0f, 0.0f, 1.0f);
				glRotatef(angleY, 0.0f, 1.0f, 0.0f);
				glColor3f(1.0, 0.0, 0.0);
				//En cuanto la luz se activa, glColor ya no es utilizado, en cambio se utilizan los materiales.
				//GL_FRONT hace referencia a la dirección de la normal. Existia GL_BACK, para utilizar la normal inversa, pero ya no se usa.
				glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
				glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
				/*glutSolidSphere(2.0, 50, 50);*/
				prisma();
				//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);		//No es necesario otra componente ambiental, pues es casi global.
				glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
				glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
				glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess1);
				glTranslatef(4.0, 0.0, 0.0);
				glutSolidSphere(2.0, 50, 50);
				//prisma();
				
		glPopMatrix();


	glPopMatrix ();
	glutSwapBuffers ( );

}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 50.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix						
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) {
		case 'w':   //Movimientos de camara
		case 'W':
			transZ +=0.5f;
			break;
		case 's':
		case 'S':
			transZ -=0.5f;
			break;
		case 'a':
		case 'A':
			transX -=0.5f;
			break;
		case 'd':
		case 'D':
			transX +=0.5f;
			break;

		//Agregar aquí teclas para movimiento de luz
		case 'i':		//Movimientos de Luz
		case 'I':
			spin = (spin - 20) % 360;
			break;
		case 'k':
		case 'K':
			spin = (spin + 20) % 360;
			break;;


		case 'l':   //Activamos/desactivamos luz
		case 'L':
			light=!light;
			break;

		case 'p':   //Activamos/desactivamos luz
		case 'P':
			positional=!positional;
			break;

		case 'c':
			LightAngle += 2.0f;
			printf("Angulo = %f\n", LightAngle);
			break;
		case 'v':
			LightAngle -= 2.0f;
			printf("Angulo = %f\n", LightAngle);
			break;
		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
			break;        
		default:        // Cualquier otra
			break;
  }
	glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		angleX += 2.0f;
		break;
    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		angleX -= 2.0f;
		break;
	case GLUT_KEY_LEFT:
		angleY -= 2.0f;
		break;
	case GLUT_KEY_RIGHT:
		angleY += 2.0f;
		break;
    default:
      break;
  }
  glutPostRedisplay();
}


int main ( int argc, char** argv )   // Main Function
{
  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (1500, 700);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Practica 7"); // Nombre de la Ventana
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutMainLoop        ( );          // 

  return 0;
}

