//#include <windows.h>  //Solo para Windows
//#include <GL/gl.h>     // The GL Header File
//#include <stdio.h>

//#include <math.h>
#include "Main.h"


class CFiguras
{
	public:

	float text_der;
	float text_izq;

	void esfera(GLfloat radio, int meridianos, int paralelos, GLuint text); //Funcíon creacion esfera
	void cilindro(float radio, float altura, int resolucion, GLuint text);	//Funcíon creacion cilindro
	void cono(float altura, float radio, int resolucion, GLuint text);		//Funcíon creacion cono
	void prisma_anun (GLuint text, GLuint text2);							//Funcíon creacion movimiento
	void prisma (float altura, float largo, float profundidad, GLuint text);//Funcíon creacion prisma
	void prisma2 (GLuint text, GLuint text2);
	void prisma3 (GLuint text, GLuint text2);
	void skybox(float altura, float largo, float profundidad, GLuint text);	//Funcion creacion cielo
	

	//void torus(GLfloat radioM, GLfloat radiom, int meridianos, int paralelos, GLuint text );
	void torus(GLfloat radioM, GLfloat radiom, int meridianos, int paralelos);

	void piso(GLuint text);
	void mesa(GLuint text, float f, float lx, float ly);
	void silla(GLuint text, float f, float lx, float ly);
	void cuarto(GLuint pared1, GLuint pared2, GLuint piso, GLuint techo, float normal);
	void puerta(GLuint text);
	void ventana(GLuint text, float textX, float textY);
};
/*
	00,01,11,10		0471	00,10,11,01
	00,10,11,01		0354	00,10,11,01
	01,11,10,00		6532	00,10,11,01
	10,11,01,00		1762	00,10,11,01
*/