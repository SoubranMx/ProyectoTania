#include "figuras.h"


const double PI = 3.1415926535897;
float text_der = 1.0;
float text_izq = 0.0;

void CFiguras::skybox(float largo, float altura, float profundidad, GLuint text)  //Funcion creacion cielo
{

	GLfloat vertice [8][3] = {
				{0.5*largo ,-0.5*altura, 0.5*profundidad},    //Coordenadas Vértice 1 V1
				{-0.5*largo ,-0.5*altura , 0.5*profundidad},    //Coordenadas Vértice 2 V2
				{-0.5*largo ,-0.5*altura , -0.5*profundidad},    //Coordenadas Vértice 3 V3
				{0.5*largo ,-0.5*altura , -0.5*profundidad},    //Coordenadas Vértice 4 V4
				{0.5*largo ,0.5*altura , 0.5*profundidad},    //Coordenadas Vértice 5 V5
				{0.5*largo ,0.5*altura , -0.5*profundidad},    //Coordenadas Vértice 6 V6
				{-0.5*largo ,0.5*altura , -0.5*profundidad},    //Coordenadas Vértice 7 V7
				{-0.5*largo ,0.5*altura , 0.5*profundidad},    //Coordenadas Vértice 8 V8
				};

		glBindTexture(GL_TEXTURE_2D, text);   // choose the texture to use.
		glBegin(GL_POLYGON);	//Front
			//glColor3f(0.0,0.0,1.0);
			glNormal3f( 0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
			glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[4]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[7]);
			glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[1]);
		glEnd();

		glBegin(GL_POLYGON);	//Right
			//glColor3f(0.0,0.0,1.0);
			glNormal3f( -1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
			glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[3]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
			glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[4]);
		glEnd();

		glBegin(GL_POLYGON);	//Back
			//glColor3f(0.0,1.0,0.0);
			glNormal3f( 0.0f, 0.0f,1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[6]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
			glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[3]);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[2]);
		glEnd();

		glBegin(GL_POLYGON);  //Left
			//glColor3f(1.0,1.0,1.0);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[1]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[7]);
			glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[6]);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[2]);
		glEnd();

		glBegin(GL_POLYGON);  //Bottom
			//glColor3f(0.4,0.2,0.6);
			glNormal3f( 0.0f,1.0f, 0.0f);
			glVertex3fv(vertice[0]);
			glVertex3fv(vertice[1]);
			glVertex3fv(vertice[2]);
			glVertex3fv(vertice[3]);
		glEnd();

		glBegin(GL_POLYGON);  //Top
			//glColor3f(0.8,0.2,0.4);
			glNormal3f( 0.0f, -1.0f, 0.0f);
			glVertex3fv(vertice[4]);
			glVertex3fv(vertice[5]);
			glVertex3fv(vertice[6]);
        	glVertex3fv(vertice[7]);
		glEnd();
}

void CFiguras::prisma (float altura, float largo, float profundidad, GLuint text)  //Funcion creacion prisma
{

	GLfloat vertice [8][3] = {
				{0.5*largo ,-0.5*altura, 0.5*profundidad},    //Coordenadas Vértice 1 V1
				{-0.5*largo ,-0.5*altura , 0.5*profundidad},    //Coordenadas Vértice 2 V2
				{-0.5*largo ,-0.5*altura , -0.5*profundidad},    //Coordenadas Vértice 3 V3
				{0.5*largo ,-0.5*altura , -0.5*profundidad},    //Coordenadas Vértice 4 V4
				{0.5*largo ,0.5*altura , 0.5*profundidad},    //Coordenadas Vértice 5 V5
				{0.5*largo ,0.5*altura , -0.5*profundidad},    //Coordenadas Vértice 6 V6
				{-0.5*largo ,0.5*altura , -0.5*profundidad},    //Coordenadas Vértice 7 V7
				{-0.5*largo ,0.5*altura , 0.5*profundidad},    //Coordenadas Vértice 8 V8
				};

		glBindTexture(GL_TEXTURE_2D, text);   // choose the texture to use.
		glBegin(GL_POLYGON);	//Front
			//glColor3f(0.0,0.0,1.0);
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.5f, 0.66f); glVertex3fv(vertice[0]);
			glTexCoord2f(0.5f, 1.0f); glVertex3fv(vertice[4]);
			glTexCoord2f(0.25f, 1.0f); glVertex3fv(vertice[7]);
			glTexCoord2f(0.25f, 0.66f); glVertex3fv(vertice[1]);
		glEnd();

		glBegin(GL_POLYGON);	//Right
			//glColor3f(0.0,0.0,1.0);
			glNormal3f( 1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.5f, 0.66f); glVertex3fv(vertice[0]);
			glTexCoord2f(0.5f, 0.33f); glVertex3fv(vertice[3]);
			glTexCoord2f(0.75f, 0.33f); glVertex3fv(vertice[5]);
			glTexCoord2f(0.75f, 0.66f); glVertex3fv(vertice[4]);
		glEnd();

		glBegin(GL_POLYGON);	//Back
			//glColor3f(0.0,1.0,0.0);
			glNormal3f( 0.0f, 0.0f,-1.0f);
			glTexCoord2f(0.25f, 0.0f); glVertex3fv(vertice[6]);
			glTexCoord2f(0.5f, 0.0f); glVertex3fv(vertice[5]);
			glTexCoord2f(0.5f, 0.33f); glVertex3fv(vertice[3]);
			glTexCoord2f(0.25f, 0.33f); glVertex3fv(vertice[2]);
		glEnd();

		glBegin(GL_POLYGON);  //Left
			//glColor3f(1.0,1.0,1.0);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.25f, 0.66f); glVertex3fv(vertice[1]);
			glTexCoord2f(0.0f, 0.66f); glVertex3fv(vertice[7]);
			glTexCoord2f(0.0f, 0.33f); glVertex3fv(vertice[6]);
			glTexCoord2f(0.25f, 0.33f); glVertex3fv(vertice[2]);
		glEnd();

		glBegin(GL_POLYGON);  //Bottom
			//glColor3f(0.4,0.2,0.6);
			glNormal3f( 0.0f,-1.0f, 0.0f);
			glTexCoord2f(0.5f, 0.66f); glVertex3fv(vertice[0]);
			glTexCoord2f(0.25f, 0.66f); glVertex3fv(vertice[1]);
			glTexCoord2f(0.25f, 0.33f); glVertex3fv(vertice[2]);
			glTexCoord2f(0.5f, 0.33f); glVertex3fv(vertice[3]);
		glEnd();

		glBegin(GL_POLYGON);  //Top
			//glColor3f(0.8,0.2,0.4);
			glNormal3f( 0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.75f, 0.66f); glVertex3fv(vertice[4]);
			glTexCoord2f(0.75f, 0.33f); glVertex3fv(vertice[5]);
			glTexCoord2f(1.0f, 0.33f); glVertex3fv(vertice[6]);
			glTexCoord2f(1.0f, 0.66f); glVertex3fv(vertice[7]);
		glEnd();
}

void CFiguras::prisma3(GLuint text, GLuint text2)  //Funcion creacion prisma
{
	GLfloat vertice[8][3] = {
				{0.5 ,-0.5, 0.5},    //Coordenadas Vértice 0 V0
				{-0.5 ,-0.5, 0.5},    //Coordenadas Vértice 1 V1
				{-0.5 ,-0.5, -0.5},    //Coordenadas Vértice 2 V2
				{0.5 ,-0.5, -0.5},    //Coordenadas Vértice 3 V3
				{0.5 ,0.5, 0.5},    //Coordenadas Vértice 4 V4
				{0.5 ,0.5, -0.5},    //Coordenadas Vértice 5 V5
				{-0.5 ,0.5, -0.5},    //Coordenadas Vértice 6 V6
				{-0.5 ,0.5, 0.5},    //Coordenadas Vértice 7 V7
	};


	glBindTexture(GL_TEXTURE_2D, text2);   // choose the texture to use.
	glBegin(GL_POLYGON);	//Front
		//glColor3f(0.0,0.0,1.0);
		//glNormal3f(0.0f, 0.0f, 1.0f);
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
		glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[4]);
		glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[7]);
		glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[1]);
	glEnd();

	glBegin(GL_POLYGON);	//Right
		//glColor3f(0.0,0.0,1.0);
		//glNormal3f(1.0f, 0.0f, 0.0f);
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
		glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[3]);
		glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
		glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[4]);
	glEnd();

	glBegin(GL_POLYGON);	//Back
		//glColor3f(0.0,1.0,0.0);
		//glNormal3f(0.0f, 0.0f, -1.0f);
		glNormal3f( 0.0f, 0.0f,1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[6]);
		glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[5]);
		glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[3]);
		glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Left
		//glColor3f(1.0,1.0,1.0);
		//glNormal3f(-1.0f, 0.0f, 0.0f);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[1]);
		glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[7]);
		glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[6]);
		glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Bottom
		//glColor3f(0.4,0.2,0.6);
		//glNormal3f(0.0f, -1.0f, 0.0f);
		glNormal3f( 0.0f,1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
		glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[1]);
		glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[2]);
		glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[3]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, text);   // choose the texture to use.
	glBegin(GL_POLYGON);  //Top
		//glColor3f(0.8,0.2,0.4);
		//glNormal3f(0.0f, 1.0f, 0.0f);
		glNormal3f( 0.0f,-1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[4]);
		glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
		glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[6]);
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[7]);
	glEnd();
}

void CFiguras::prisma2 (GLuint text, GLuint text2)  //Funcion creacion prisma
{

	GLfloat vertice [8][3] = {
				{0.5 ,-0.5, 0.5},    //Coordenadas Vértice 0 V0
				{-0.5 ,-0.5, 0.5},    //Coordenadas Vértice 1 V1
				{-0.5 ,-0.5, -0.5},    //Coordenadas Vértice 2 V2
				{0.5 ,-0.5, -0.5},    //Coordenadas Vértice 3 V3
				{0.5 ,0.5, 0.5},    //Coordenadas Vértice 4 V4
				{0.5 ,0.5, -0.5},    //Coordenadas Vértice 5 V5
				{-0.5 ,0.5, -0.5},    //Coordenadas Vértice 6 V6
				{-0.5 ,0.5, 0.5},    //Coordenadas Vértice 7 V7
				};

		
		glBindTexture(GL_TEXTURE_2D, text2);   // choose the texture to use.
		glBegin(GL_POLYGON);	//Front
			//glColor3f(0.0,0.0,1.0);
			glNormal3f( 0.0f, 0.0f, 1.0f);
			//glNormal3f( 0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
			glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[4]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[7]);
			glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[1]);
		glEnd();
	
		glBegin(GL_POLYGON);	//Right
			//glColor3f(0.0,0.0,1.0);
			glNormal3f( 1.0f, 0.0f, 0.0f);
			//glNormal3f( -1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
			glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[3]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
			glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[4]);
		glEnd();

		glBegin(GL_POLYGON);	//Back
			//glColor3f(0.0,1.0,0.0);
			glNormal3f( 0.0f, 0.0f,-1.0f);
			//glNormal3f( 0.0f, 0.0f,1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[6]);
			glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[5]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[3]);
			glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[2]);
		glEnd();

		glBegin(GL_POLYGON);  //Left
			//glColor3f(1.0,1.0,1.0);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			//glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[1]);
			glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[7]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[6]);
			glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[2]);
		glEnd();

		glBegin(GL_POLYGON);  //Bottom
			//glColor3f(0.4,0.2,0.6);
			glNormal3f( 0.0f,-1.0f, 0.0f);
			//glNormal3f( 0.0f,1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
			glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[1]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[2]);
			glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[3]);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, text);   // choose the texture to use.
		glBegin(GL_POLYGON);  //Top
			//glColor3f(0.8,0.2,0.4);
			glNormal3f( 0.0f,1.0f, 0.0f);
			//glNormal3f( 0.0f,-1.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[4]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
			glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[6]);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[7]);
		glEnd();
}

void CFiguras::prisma_anun (GLuint text, GLuint text2)  //Funcion creacion prisma
{

	GLfloat vertice [8][3] = {
				{0.5 ,-0.5, 0.5},    //Coordenadas Vértice 0 V0
				{-0.5 ,-0.5, 0.5},    //Coordenadas Vértice 1 V1
				{-0.5 ,-0.5, -0.5},    //Coordenadas Vértice 2 V2
				{0.5 ,-0.5, -0.5},    //Coordenadas Vértice 3 V3
				{0.5 ,0.5, 0.5},    //Coordenadas Vértice 4 V4
				{0.5 ,0.5, -0.5},    //Coordenadas Vértice 5 V5
				{-0.5 ,0.5, -0.5},    //Coordenadas Vértice 6 V6
				{-0.5 ,0.5, 0.5},    //Coordenadas Vértice 7 V7
				};

		
		glBindTexture(GL_TEXTURE_2D, text2);   // choose the texture to use.
		//glBindTexture(GL_TEXTURE_2D, texture[filter]);   // choose the texture to use.
		glBegin(GL_POLYGON);	//Front
			//glColor3f(0.0,0.0,1.0);
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
			glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[4]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[7]);
			glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[1]);
		glEnd();
	
		glBegin(GL_POLYGON);	//Right
			//glColor3f(0.0,0.0,1.0);
			glNormal3f( 1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
			glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[3]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
			glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[4]);
		glEnd();

		glBegin(GL_POLYGON);	//Back
			//glColor3f(0.0,1.0,0.0);
			glNormal3f( 0.0f, 0.0f,-1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[6]);
			glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[5]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[3]);
			glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[2]);
		glEnd();

		glBegin(GL_POLYGON);  //Left
			//glColor3f(1.0,1.0,1.0);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[1]);
			glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[7]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[6]);
			glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[2]);
		glEnd();

		glBegin(GL_POLYGON);  //Bottom
			//glColor3f(0.4,0.2,0.6);
			glNormal3f( 0.0f,-1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
			glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[1]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[2]);
			glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[3]);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, text);   // choose the texture to use.
		glBegin(GL_POLYGON);  //Top
			//glColor3f(0.8,0.2,0.4);
		glNormal3f( 0.0f,1.0f, 0.0f);
			glTexCoord2f(text_der, 0.0f); glVertex3fv(vertice[4]);
			glTexCoord2f(text_der, 1.0f); glVertex3fv(vertice[5]);
			glTexCoord2f(text_izq, 1.0f); glVertex3fv(vertice[6]);
			glTexCoord2f(text_izq, 0.0f); glVertex3fv(vertice[7]);
		glEnd();
}

void CFiguras::esfera(GLfloat radio, int meridianos, int paralelos, GLuint text )
{
	
	GLdouble angulop = 3.1415/paralelos;
	GLdouble angulom = 3.1415/meridianos;
	GLdouble theta, phi;
	//bool even = true;
	
	glBindTexture(GL_TEXTURE_2D, text);   // choose the texture to use.

	for(double p =-3.14/2; p < 3.14/2; p += angulop)
	{
		for(double m = 0; m < 3.14*2; m+=angulom)
		{
			//glBegin(GL_LINE_LOOP);
			glBegin(GL_POLYGON);
			
			//glBegin(GL_POINTS);
			glNormal3f( radio*cos(p + angulop)*cos(m), radio*sin(p + angulop), radio*cos(p + angulop)*sin(m));			
			glVertex3f( radio*cos(p + angulop)*cos(m), radio*sin(p + angulop), radio*cos(p + angulop)*sin(m));	

			glNormal3f( radio*cos(p + angulop)*cos(m + angulom), radio*sin(p + angulop), radio*cos(p + angulop)*sin(m + angulom));
			glVertex3f( radio*cos(p + angulop)*cos(m + angulom), radio*sin(p + angulop), radio*cos(p + angulop)*sin(m + angulom));

			glNormal3f( radio*cos(p)*cos(m + angulom), radio*sin(p), radio*cos(p)*sin(m + angulom));
			glVertex3f( radio*cos(p)*cos(m + angulom), radio*sin(p), radio*cos(p)*sin(m + angulom));

			glNormal3f(radio*cos(p)*cos(m), radio*sin(p), radio*cos(p)*sin(m));
			glVertex3f( radio*cos(p)*cos(m), radio*sin(p), radio*cos(p)*sin(m));
				
			glEnd();
		}
	}
}

void CFiguras::torus(GLfloat radioM, GLfloat radiom, int meridianos, int paralelos )
{

	float R = 0;
	float r = 0;

	float v1[]={0.0, 0.0, 0.0};
	float v2[]={0.0, 0.0, 0.0};
	float v3[]={0.0, 0.0, 0.0};
	float v4[]={0.0, 0.0, 0.0};

	int i,j;

	GLdouble angulop = 2*3.1415/paralelos;
	GLdouble angulom = 2*3.1415/meridianos;

	r = (radioM - radiom)/2;
	R = radiom + r;

	for(i=0;i<meridianos;i++)
	{
		for(j=0;j<paralelos;j++)
		{
			
			v1[0]=R*cos(angulom*i) + r*cos(angulom*i)*cos(angulop*j);
			v1[2]=R*sin(angulom*i)+ r*sin(angulom*i)*cos(angulop*j);
			v1[1]=r*sin(angulop*j);

			glNormal3f(v1[0], v1[1], v1[2]);
			
			v2[0]=R*cos(angulom*i) + r*cos(angulom*i)*cos(angulop*(j+1));
			v2[2]=R*sin(angulom*i) + r*sin(angulom*i)*cos(angulop*(j+1));
			v2[1]=r*sin(angulop*(j+1));

			glNormal3f(v2[0], v2[1], v2[2]);

			v3[0]=R*cos(angulom*(i+1)) + r*cos(angulom*(i+1))*cos(angulop*(j+1));
			v3[2]=R*sin(angulom*(i+1)) + r*sin(angulom*(i+1))*cos(angulop*(j+1));
			v3[1]=r*sin(angulop*(j+1));

			glNormal3f(v3[0], v3[1], v3[2]);

			v4[0]=R*cos(angulom*(i+1)) + r*cos(angulom*(i+1))*cos(angulop*j);
			v4[2]=R*sin(angulom*(i+1)) + r*sin(angulom*(i+1))*cos(angulop*j);
			v4[1]=r*sin(angulop*j);

			glNormal3f(v4[0], v4[1], v4[2]);
			
			//glBegin(GL_LINE_LOOP);
			glBegin(GL_POLYGON);
				glVertex3fv(v1);
				glVertex3fv(v2);
				glVertex3fv(v3);
				glVertex3fv(v4);
			glEnd();
		}
	}
}

void CFiguras::cono(float altura, float radio, int resolucion, GLuint text)
{
	
	float v1[]={0.0, 0.0, 0.0};
	float v2[]={0.0, 0.0, 0.0};
	float v3[]={0.0, 0.0, 0.0};
	float v4[]={0.0, 0.0, 0.0};

	float angulo=2*3.14/resolucion;
	
	glBindTexture(GL_TEXTURE_2D, text);   // choose the texture to use.
	for(int i=0; i <resolucion; i++)
	{
		
		v2[0]=radio*cos(angulo*i);
		v2[1]=0;
		v2[2]=radio*sin(angulo*i);

		v3[0]=radio*cos(angulo*(i+1));
		v3[1]=0;
		v3[2]=radio*sin(angulo*(i+1));
		
		//glBegin(GL_LINE_LOOP);
        glBegin(GL_POLYGON); //Construye Base
			glNormal3f( 0.0f, -1.0f, 0.0f);
			glVertex3f(0.0,0.0,0.0);
			glVertex3fv(v2);
			glVertex3fv(v3);
		glEnd();

		glBegin(GL_POLYGON);  //Construye Cuerpo
			glNormal3f( v2[0], 0.25f, v2[2]);
			//glNormal3fv(v2);
			glVertex3fv(v2);
			//glNormal3fv(v3);
			glVertex3fv(v3);
			//glNormal3f(0.0,altura,0);
			glVertex3f(0.0,altura,0.0);
			
		glEnd();
	}
}

void CFiguras::cilindro(float radio, float altura, int resolucion, GLuint text)
{
	
	float v1[]={0.0, 0.0, 0.0};
	float v2[]={0.0, 0.0, 0.0};
	float v3[]={0.0, 0.0, 0.0};
	float v4[]={0.0, 0.0, 0.0};
	float v5[]={0.0, 0.0, 0.0};

	float angulo=2*3.14/resolucion;

	//float ctext_s = 1/resolucion-1;
	float ctext_s = 1/resolucion;
	float ctext_t = 0.0;

	//glBindTexture(GL_TEXTURE_2D, text);   // choose the texture to use.
	for(int i=0; i <resolucion; i++)
	{
		 
		v2[0]=radio*cos(angulo*i);
		v2[1]=0;
		v2[2]=radio*sin(angulo*i);

		v3[0]=radio*cos(angulo*(i+1));
		v3[1]=0;
		v3[2]=radio*sin(angulo*(i+1));
//	
		v4[0]=radio*cos(angulo*i);
		v4[1]=altura;
		v4[2]=radio*sin(angulo*i);

		v5[0]=radio*cos(angulo*(i+1));
		v5[1]=altura;
		v5[2]=radio*sin(angulo*(i+1));

		//glBegin(GL_LINE_LOOP);
		glBegin(GL_POLYGON);
			glNormal3f( 0.0f, -1.0f, 0.0f);
			glVertex3f(0.0,0.0,0.0);
			glVertex3fv(v2);
			glVertex3fv(v3);
		glEnd();

		glBegin(GL_POLYGON);
			glNormal3f( 0.0f, 1.0f, 0.0f);
			glVertex3f(0.0,altura,0.0);
			glVertex3fv(v4);
			glVertex3fv(v5);
		glEnd();

		/*glBegin(GL_POLYGON);
			glBindTexture(GL_TEXTURE_2D, text);
			glNormal3f( v2[0], 0.0f, v2[2]);
			glTexCoord2f(ctext_s*i, 0.0f);		glVertex3fv(v2);
			glTexCoord2f(ctext_s*(i+1), 0.0f);	glVertex3fv(v3);
			glTexCoord2f(ctext_s*(i+1), 1.0f);	glVertex3fv(v5);
			glTexCoord2f(ctext_s*i, 1.0f);		glVertex3fv(v4);
		glEnd();*/
		glBegin(GL_POLYGON);
			glNormal3f( v2[0], 0.0f, v2[2]);
			glVertex3fv(v2);
			glVertex3fv(v3);
			glVertex3fv(v5);
			glVertex3fv(v4);
		glEnd();
	}
}	



void CFiguras::piso(GLuint text) {
	GLfloat vertice[8][3] = {
				{0.5 ,-0.5, 0.5},    //Coordenadas Vertice 0 V0
				{-0.5 ,-0.5, 0.5},    //Coordenadas Vertice 1 V1
				{-0.5 ,-0.5, -0.5},    //Coordenadas Vertice 2 V2
				{0.5 ,-0.5, -0.5},    //Coordenadas Vertice 3 V3
				{0.5 ,0.5, 0.5},    //Coordenadas Vertice 4 V4
				{0.5 ,0.5, -0.5},    //Coordenadas Vertice 5 V5
				{-0.5 ,0.5, -0.5},    //Coordenadas Vertice 6 V6
				{-0.5 ,0.5, 0.5},    //Coordenadas Vertice 7 V7
	};
	float f = 6.0f;
	float lx = 6.0f;
	float ly = 0.04f;

	glBindTexture(GL_TEXTURE_2D, text);   // choose the texture to use.
	glBegin(GL_POLYGON);	//Front
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
		glTexCoord2f(0.0f, ly); glVertex3fv(vertice[4]);
		glTexCoord2f(lx, ly); glVertex3fv(vertice[7]);
		glTexCoord2f(lx, 0.0f); glVertex3fv(vertice[1]);
	glEnd();
	//glBindTexture(GL_TEXTURE_2D, 0);
	glBegin(GL_POLYGON);	//Right
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
		glTexCoord2f(lx, 0.0f); glVertex3fv(vertice[3]);
		glTexCoord2f(lx, ly); glVertex3fv(vertice[5]);
		glTexCoord2f(0.0f, ly); glVertex3fv(vertice[4]);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, text);
	glBegin(GL_POLYGON);	//Back
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, ly); glVertex3fv(vertice[6]);
		glTexCoord2f(lx, ly); glVertex3fv(vertice[5]);
		glTexCoord2f(lx, 0.0f); glVertex3fv(vertice[3]);
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(lx, 0.0f); glVertex3fv(vertice[1]);
	glTexCoord2f(lx, ly); glVertex3fv(vertice[7]);
	glTexCoord2f(0.0f, ly); glVertex3fv(vertice[6]);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Bottom
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
		glTexCoord2f(f, 0.0f); glVertex3fv(vertice[1]);
		glTexCoord2f(f, f); glVertex3fv(vertice[2]);
		glTexCoord2f(0.0f, f); glVertex3fv(vertice[3]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, text);   // choose the texture to use.
	glBegin(GL_POLYGON);  //Top
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[7]);
		glTexCoord2f(f, 0.0f); glVertex3fv(vertice[4]);
		glTexCoord2f(f, f); glVertex3fv(vertice[5]);
		glTexCoord2f(0.0f, f); glVertex3fv(vertice[6]);
		
	glEnd();
}

void CFiguras::mesa(GLuint text, float f, float lx, float ly) {
	GLfloat vertice[8][3] = {
				{0.5 ,-0.5, 0.5},    //Coordenadas V�rtice 0 V0
				{-0.5 ,-0.5, 0.5},    //Coordenadas V�rtice 1 V1
				{-0.5 ,-0.5, -0.5},    //Coordenadas V�rtice 2 V2
				{0.5 ,-0.5, -0.5},    //Coordenadas V�rtice 3 V3
				{0.5 ,0.5, 0.5},    //Coordenadas V�rtice 4 V4
				{0.5 ,0.5, -0.5},    //Coordenadas V�rtice 5 V5
				{-0.5 ,0.5, -0.5},    //Coordenadas V�rtice 6 V6
				{-0.5 ,0.5, 0.5},    //Coordenadas V�rtice 7 V7
	};
	/*float f = 10.0f;
	float lx = 10.0f;
	float ly = 0.04f;*/
	glBindTexture(GL_TEXTURE_2D, text);
	glBegin(GL_POLYGON);	//Front
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(lx, 0.0f); glVertex3fv(vertice[0]);
		glTexCoord2f(lx, ly); glVertex3fv(vertice[4]);
		glTexCoord2f(0.0f, ly); glVertex3fv(vertice[7]);
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[1]);
	glEnd();
	
	glBegin(GL_POLYGON);	//Right
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
		glTexCoord2f(lx, 0.0f); glVertex3fv(vertice[3]);
		glTexCoord2f(lx, ly); glVertex3fv(vertice[5]);
		glTexCoord2f(0.0f, ly); glVertex3fv(vertice[4]);
	glEnd();
	
	glBegin(GL_POLYGON);	//Back
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(lx, ly); glVertex3fv(vertice[6]);
		glTexCoord2f(0.0f, ly); glVertex3fv(vertice[5]);
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[3]);
		glTexCoord2f(lx, 0.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Left
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(lx, 0.0f); glVertex3fv(vertice[1]);
		glTexCoord2f(lx, ly); glVertex3fv(vertice[7]);
		glTexCoord2f(0.0f, ly); glVertex3fv(vertice[6]);
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Bottom
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
		glTexCoord2f(f, 0.0f); glVertex3fv(vertice[1]);
		glTexCoord2f(f, f); glVertex3fv(vertice[2]);
		glTexCoord2f(0.0f, f); glVertex3fv(vertice[3]);
	glEnd();

	glBegin(GL_POLYGON);  //Top
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[7]);
		glTexCoord2f(f, 0.0f); glVertex3fv(vertice[4]);
		glTexCoord2f(f, f); glVertex3fv(vertice[5]);
		glTexCoord2f(0.0f, f); glVertex3fv(vertice[6]);
	glEnd();
}

void CFiguras::cuarto(GLuint pared1, GLuint pared2, GLuint piso, GLuint techo, float normal) {
	GLfloat vertice[22][3] = {
				{0.5 ,-0.5, 0.5},    //Coordenadas Vértice 0 V0
				{-0.5 ,-0.5, 0.5},   //Coordenadas Vértice 1 V1
				{-0.5 ,-0.5, -0.5},  //Coordenadas Vértice 2 V2
				{0.5 ,-0.5, -0.5},   //Coordenadas Vértice 3 V3
				{0.5 ,0.5, 0.5},	 //Coordenadas Vértice 4 V4
				{0.5 ,0.5, -0.5},    //Coordenadas Vértice 5 V5
				{-0.5 ,0.5, -0.5},   //Coordenadas Vértice 6 V6
				{-0.5 ,0.5, 0.5},    //Coordenadas Vértice 7 V7
				{0.4 ,-0.5, 0.5},	 //Coordenadas Vertice 8 Va		Puerta
				{0.4 ,0.0, 0.5},	 //Coordenadas Vertice 9 Vb
				{0.2 ,0.0, 0.5},	 //Coordenadas Vertice 10 Vc
				{0.2 ,-0.5, 0.5},	 //Coordenadas Vertice 11 Vd
				{-0.4 ,0.3, -0.5},	 //Coordenadas Vertice 12 Vea	Ventana
				{0.4 ,0.3, -0.5},	 //Coordenadas Vertice 13 Veb
				{0.4 ,-0.1, -0.5},	 //Coordenadas Vertice 14 Vec
				{-0.4 ,-0.1, -0.5},	 //Coordenadas Vertice 15 Ved
				{-0.5 ,-0.1, -0.5},	 //Coordenadas Vertice 16 Ved*
				{0.5 ,-0.1, -0.5},	 //Coordenadas Vertice 17 Vec*
				{0.5 ,0.3, -0.5},	 //Coordenadas Vertice 18 Veb*
				{-0.5 ,0.3, -0.5},	 //Coordenadas Vertice 19 Vea*
				{0.5 ,0.0, 0.5},	 //Coordenadas Vertice 20 Vbe
				{-0.5 ,0.0, 0.5},	 //Coordenadas Vertice 21 Vce
	};
	glBindTexture(GL_TEXTURE_2D, pared1);
	glBegin(GL_QUADS);//Front con puerta
	//Creacion en 3 cuadros
	/*
	*	1	v7,v4,Vbe,Vce
	*	2	Vce,c,d,v1
	*	3	b-Vbe,v0,a
	*/
	//Orden de formación: v0-v4-v7-v1-d-c-b-a
		glNormal3f(0.0f, 0.0f, normal);
		glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[7]);
		glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[4]);
		glTexCoord2f(1.0f, 0.5f); glVertex3fv(vertice[20]);
		glTexCoord2f(0.0f, 0.5f); glVertex3fv(vertice[21]);

		glTexCoord2f(0.0f, 0.5f); glVertex3fv(vertice[21]);
		glTexCoord2f(0.7f, 0.5f); glVertex3fv(vertice[10]);
		glTexCoord2f(0.7f, 0.0f); glVertex3fv(vertice[11]);
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[1]);

		glTexCoord2f(0.9f, 0.5f); glVertex3fv(vertice[9]);
		glTexCoord2f(1.0f, 0.5f); glVertex3fv(vertice[20]);
		glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[0]);
		glTexCoord2f(0.9f, 0.0f); glVertex3fv(vertice[8]);
	glEnd();

	glBegin(GL_QUADS);	//Back con ventana
		//Creación en 4 cuadros
		/*
		*1	V6-V5-Veb*-Vea*
		*2	Vea*-Vea-Ved-Ved*
		*3	Veb-Veb*-Vec*-Vec
		*4	Ved*-Vec*-V3-V2
		*/
		glNormal3f(0.0f, 0.0f, -normal);
		glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[6]);	//6
		glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);	//5
		glTexCoord2f(1.0f, 0.8f); glVertex3fv(vertice[18]);	//Veb*
		glTexCoord2f(0.0f, 0.8f); glVertex3fv(vertice[19]);	//Vea*

		glTexCoord2f(0.0f, 0.8f); glVertex3fv(vertice[19]);	//Vea*
		glTexCoord2f(0.1f, 0.8f); glVertex3fv(vertice[12]);	//Vea
		glTexCoord2f(0.1f, 0.4f); glVertex3fv(vertice[15]);	//Ved
		glTexCoord2f(0.0f, 0.4f); glVertex3fv(vertice[16]);	//Ved*

		glTexCoord2f(0.9f, 0.8f); glVertex3fv(vertice[13]);	//b
		glTexCoord2f(1.0f, 0.8f); glVertex3fv(vertice[18]);	//b*
		glTexCoord2f(1.0f, 0.4f); glVertex3fv(vertice[17]);	//c*
		glTexCoord2f(0.9f, 0.4f); glVertex3fv(vertice[14]);	//c

		glTexCoord2f(0.0f, 0.4f); glVertex3fv(vertice[16]);	//d*
		glTexCoord2f(1.0f, 0.4f); glVertex3fv(vertice[17]);	//c*
		glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[3]);	//3
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[2]);	//2
	glEnd();

	glBindTexture(GL_TEXTURE_2D, pared2);
	glBegin(GL_POLYGON);	//Right
		glNormal3f(normal, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
		glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[3]);
		glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
		glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[4]);
	glEnd();
	
	glBegin(GL_POLYGON);  //Left
		glNormal3f(-normal, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[1]);
		glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[7]);
		glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[6]);
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, techo);
	glBegin(GL_POLYGON);  //Top
		glNormal3f(0.0f, normal, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[4]);
		glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[5]);
		glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[6]);
		glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[7]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, piso);
	glBegin(GL_POLYGON);  //Bottom
		glNormal3f(0.0f, -normal, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
		glTexCoord2f(3.0f, 0.0f); glVertex3fv(vertice[1]);
		glTexCoord2f(3.0f, 3.0f); glVertex3fv(vertice[2]);
		glTexCoord2f(0.0f, 3.0f); glVertex3fv(vertice[3]);
	glEnd();
}

void CFiguras::puerta(GLuint text) {
	GLfloat vertice[4][3] = {
			{0.2 ,-0.25, 0.0},	 //Coordenadas Vertice 0 Va		Puerta
			{0.2 ,0.25, 0.0},	 //Coordenadas Vertice 1 Vb
			{0.0 ,0.25, 0.0},	 //Coordenadas Vertice 2 Vc
			{0.0 ,-0.25, 0.0},	 //Coordenadas Vertice 3 Vd
	};

	glBindTexture(GL_TEXTURE_2D, text);
	glBegin(GL_POLYGON);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.678f, 0.96f); glVertex3fv(vertice[1]);
		glTexCoord2f(0.678f, 0.0f);	 glVertex3fv(vertice[0]);
		glTexCoord2f(0.31f, 0.0f);	 glVertex3fv(vertice[3]);
		glTexCoord2f(0.31f, 0.96f);  glVertex3fv(vertice[2]);
	glEnd();
}

void CFiguras::ventana(GLuint text, float textX, float textY) {
	GLfloat vertice[4][3] = {
			{-0.4 ,0.0, 0.0},	 //Coordenadas Vertice 12 Vea	Ventana
			{0.4 ,0.0, 0.0},	 //Coordenadas Vertice 13 Veb
			{0.4 ,-0.4, 0.0},	 //Coordenadas Vertice 14 Vec
			{-0.4 ,-0.4, 0.0},	 //Coordenadas Vertice 15 Ved
	};

	glBindTexture(GL_TEXTURE_2D, text);
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.75f); glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.75f);	 glVertex3fv(vertice[1]);
	glTexCoord2f(1.0f, 0.25f);	 glVertex3fv(vertice[2]);
	glTexCoord2f(0.0f, 0.25f);  glVertex3fv(vertice[3]);
	glEnd();
}