#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>                    
#include <stdio.h> 
#include <stdlib.h> 
#include "SOIL.h"
#include <time.h>
#include <string.h>


#define MAX_NO_TEXTURES 1

GLuint texture_id[MAX_NO_TEXTURES]; // vetor com os números das texturas 

//GAP do contador entre carregamentos
#define GAP 1000

//Personagem
GLuint character;

//Variáveis auxiliares para o contador
static int onTorreMeioCounter = 10, onTorreEsquerdaCounter = 10, onTorreEsquerdaACounter = 10, onTorreEsquerdaBCounter = 10;
static int onTorreMeioBCounter = 10, onTorreDireitaACounter = 10, onTorreDireitaBCounter = 10, onTorreDireitaCounter = 10;
static int onTorreMeioTimerAux = 0, onTorreEsquerdaTimerAux = 0, onTorreEsquerdaATimerAux = 0, onTorreEsquerdaBTimerAux = 0;
static int onTorreMeioBTimerAux = 0, onTorreDireitaATimerAux = 0, onTorreDireitaBTimerAux = 0, onTorreDireitaTimerAux = 0;

//Câmera
float posx = 2.0f, posy = 0.0f, posz = -3.0f, focx = 0.0f, focy = 0.0f, focz = 0.0f, disx = 2.0f, disy = 0.0f, disz = 0.0f;

int status = 0;
//0: Padrão (ainda não chegou na torre)
//1: Iluminada (personagem está nessa torre, aparece em destaque)
//2: Destruida (personagem passou por essa torre e a venceu)
//3: Invisivel

int torreAtual = 0;
int tempoEncerrado = 0;
int recomecar = 1;
int respostaErrada,respostaCorreta,n; 
int respostasCorretas[9] = {-3,9,5,2,8,6,3,7,0};
int start = 0;

int generateNumber(){
    int n;
    srand(time(NULL));
    n = rand() % 3;
    return n;
}


void iluminacao(void){
        GLfloat luzAmbiente[4]={1.0,1.0,1.0,1.0}; 
        GLfloat luzDifusa[4]={1.0,1.0,1.0,1.0}; 
        GLfloat luzEspecular[4]={0.0, 0.0, 0.0, 0.0};
        GLfloat posicaoLuz[4]={50.0, -2.0, -50.0, 1.0}; 
        GLfloat especularidade[4]={0.0,0.0,0.0,0.0}; 
        GLint especMaterial = 60;
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glShadeModel(GL_SMOOTH);
        
        glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade); 
        
        glMateriali(GL_FRONT,GL_SHININESS,especMaterial); 
        glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa ); 
        glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular ); 
        glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz ); 
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_DEPTH_TEST);

}

void loadObj(char *fname)
{
    FILE *fp;
    int read;
    GLfloat x, y, z;
    char ch;
    character=glGenLists(1);
    fp=fopen(fname,"r");
    if (!fp)
    {
        printf("can't open file %s\n", fname);
        exit(1);
    }
    glPointSize(2.0);
    glNewList(character, GL_COMPILE);
    {
        glPushMatrix();
        glBegin(GL_POLYGON);
        while(!(feof(fp)))
        {
            read=fscanf(fp,"%c %f %f %f",&ch,&x,&y,&z);
            if(read==4&&ch=='v')
            {
                glVertex3f(x,y,z);
            }
        }
        glEnd();
    }
    glPopMatrix();
    glEndList();
    fclose(fp);
}

void drawBitmapText(char * string, float x, float y, float z) {
    char * c;
    
    glRasterPos3f(x, y, z);
    //glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, string);

    for (c = string; * c != ';'; c++) {

        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, * c);
        //glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c)
        //glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c)
        //glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c)
        //glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *c)
        //glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c)
        //glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c)
    }
}

void eixos() {

    //eixo x
    //glPushMatrix();
    //glBegin(GL_LINES);
    //glColor3f(1, 0, 0);
    //glVertex3i(0, 0, 0);
    //glVertex3i(50, 0, 0);
    //glEnd();
    //glPopMatrix();

    //eixo y
    //glPushMatrix();
    //glBegin(GL_LINES);
    //glColor3f(0, 1, 0);
    //glVertex3i(0, 0, 0);
    //glVertex3i(0, 50, 0);
    //glEnd();
    //glPopMatrix();

    //eixo z
    //glPushMatrix();
    //glBegin(GL_LINES);
    //glColor3f(0, 0, 1);
    //glVertex3i(0, 0, 0);
    //glVertex3i(0, 0, 50);
    //glEnd();
    //glPopMatrix();
}

void pista() {
    iluminacao();
    
    glEnable ( GL_TEXTURE_2D );
    glBindTexture(GL_TEXTURE_2D, texture_id[0]);
    glBegin (GL_QUADS);
    glColor3f(1.0,1.0,1.0);   
    glTexCoord2d(0.0, 0.0); glVertex3f(-50.0,-50.0,7.0);
    glTexCoord2d(1.0, 0.0); glVertex3f(50.0,-50.0,7.0);
    glTexCoord2d(1.0, 1.0); glVertex3f(50.0,50.0,7.0);
    glTexCoord2d(0.0, 1.0); glVertex3f(-50.0,50.0,7.0);

    glColor3f(1.0,1.0,1.0);   
    glTexCoord2d(0.0, 0.0); glVertex3f(-50.0,7.0,-50.0);
    glTexCoord2d(1.0, 0.0); glVertex3f(50.0,7.0,-50.0);
    glTexCoord2d(1.0, 1.0); glVertex3f(50.0,7.0,50.0);
    glTexCoord2d(0.0, 1.0); glVertex3f(-50.0,7.0,50.0);

    glColor3f(1.0,1.0,1.0);   
    glTexCoord2d(0.0, 0.0); glVertex3f(-50.0,-7.0,-50.0);
    glTexCoord2d(1.0, 0.0); glVertex3f(50.0,-7.0,-50.0);
    glTexCoord2d(1.0, 1.0); glVertex3f(50.0,-7.0,50.0);
    glTexCoord2d(0.0, 1.0); glVertex3f(-50.0,-7.0,50.0);
    glEnd();
    glDisable ( GL_TEXTURE_2D );

    glColor3f(0.1, 0.1, 0.0);

    //Inicio da Pista   
    glPushMatrix();
    glTranslatef(0.0, -2.05, 0.0);
    glScalef(0.1, 0.5, 1.4);
    glutSolidCube(1.0);
    glPopMatrix();

    //Inicio-Meio da Pista   
    glPushMatrix();
    glTranslatef(0.0, -1.40, 0.0);
    glScalef(0.1, 0.8, 2.6);
    glutSolidCube(1.0);
    glPopMatrix();

    //Ponte A Inicio Pista
    glPushMatrix();
    glTranslatef(0.0, -0.9, 0.4);
    glScalef(0.1, 0.2, 0.4);
    glutSolidCube(1.0);
    glPopMatrix();

    //Ponte B Inicio Pista
    glPushMatrix();
    glTranslatef(0.0, -0.9, -0.4);
    glScalef(0.1, 0.2, 0.4);
    glutSolidCube(1.0);
    glPopMatrix();

    //Meio da Pista   
    glPushMatrix();
    glTranslatef(0.0, 0, 0.0);
    glScalef(0.1, 1.6, 2.0);
    glutSolidCube(1.0);
    glPopMatrix();

    //Fim-Meio da Pista   
    glPushMatrix();
    glTranslatef(0.0, 1.40, 0.0);
    glScalef(0.1, 0.8, 2.6);
    glutSolidCube(1.0);
    glPopMatrix();

    //Ponte A Fim Pista
    glPushMatrix();
    glTranslatef(0.0, 0.9, 0.4);
    glScalef(0.1, 0.2, 0.4);
    glutSolidCube(1.0);
    glPopMatrix();

    //Ponte B Fim Pista
    glPushMatrix();
    glTranslatef(0.0, 0.9, -0.4);
    glScalef(0.1, 0.2, 0.4);
    glutSolidCube(1.0);
    glPopMatrix();

    
    //Fim da Pista   
    glPushMatrix();
    glTranslatef(0.0, 2.05, 0.0);
    glScalef(0.1, 0.5, 1.4);
    glutSolidCube(1.0);
    glPopMatrix();

}

void torreEsquerda(int status) {

    switch (status) {
    case 0: //Padrão (ainda não chegou na torre)
        glColor3f(0.0, 0.0, 1.0);
        break;
    case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
        glColor3f(1.0, 1.0, 0.0);
        break;
    case 2: //Destruida (personagem passou por essa torre e a venceu)
        glColor3f(0.5, 0.5, 0.5);
        break;
    case 3: //Invisivel
        glColor3f(0.2, 0.2, 0.2);
        break;
    }

    //Inicio da Base
    glPushMatrix();
    glTranslatef(0.1, -2.05, 0.0);
    glScalef(0.1, 0.1, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    //Meio da Base
    glPushMatrix();
    glTranslatef(0.2, -2.05, 0.0);
    glScalef(0.1, 0.15, 0.3);
    glutSolidCube(1.0);
    glPopMatrix();

    //Topo da Base
    glPushMatrix();
    glTranslatef(0.325, -2.05, 0.0);
    glScalef(0.15, 0.05, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    //Esfera da Torre
    glPushMatrix();
    glTranslatef(0.52, -2.05, 0.0);
    //glScalef(0.05, 0.05, 0.05);
    glutSolidSphere(0.15, 5, 5);
    glPopMatrix();
}

void torreMeioEsquerdaA(int status) {

    switch (status) {
    case 0: //Padrão (ainda não chegou na torre)
        glColor3f(0.7, 0.0, 1.0);
        break;
    case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
        glColor3f(1.0, 1.0, 0.0);
        break;
    case 2: //Destruida (personagem passou por essa torre e a venceu)
        glColor3f(0.5, 0.5, 0.5);
        break;
    case 3: //Invisivel
        glColor3f(0.2, 0.2, 0.2);
        break;
    }

    //Inicio da Base
    glPushMatrix();
    glTranslatef(0.1, -1.40, 0.6);
    glScalef(0.075, 0.075, 0.125);
    glutSolidCube(1.0);
    glPopMatrix();

    //Topo da Base
    glPushMatrix();
    glTranslatef(0.25, -1.40, 0.6);
    glScalef(0.25, 0.05, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    //Torus da Torre
    glPushMatrix();
    glTranslatef(0.45, -1.40, 0.6);
    glutSolidSphere(0.1, 10, 10);
    glPopMatrix();
}

void torreMeioEsquerdaB(int status) {

    switch (status) {
    case 0: //Padrão (ainda não chegou na torre)
        glColor3f(0.7, 0.0, 1.0);
        break;
    case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
        glColor3f(1.0, 1.0, 0.0);
        break;
    case 2: //Destruida (personagem passou por essa torre e a venceu)
        glColor3f(0.5, 0.5, 0.5);
        break;
    case 3: //Invisivel
        glColor3f(0.2, 0.2, 0.2);
        break;
    }

    //Inicio da Base
    glPushMatrix();
    glTranslatef(0.1, -1.40, -0.6);
    glScalef(0.075, 0.075, 0.125);
    glutSolidCube(1.0);
    glPopMatrix();

    //Topo da Base
    glPushMatrix();
    glTranslatef(0.25, -1.40, -0.6);
    glScalef(0.25, 0.05, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    //Torus da Torre
    glPushMatrix();
    glTranslatef(0.45, -1.40, -0.6);
    glutSolidSphere(0.1, 10, 10);
    glPopMatrix();
}

void torreMeioA(int status) {

    switch (status) {
    case 0: //Padrão (ainda não chegou na torre)
        glColor3f(1.0, 0.0, 1.0);
        break;
    case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
        glColor3f(1.0, 1.0, 0.0);
        break;
    case 2: //Destruida (personagem passou por essa torre e a venceu)
        glColor3f(0.5, 0.5, 0.5);
        break;
    case 3: //Invisivel
        glColor3f(0.2, 0.2, 0.2);
        break;
    }

    //Inicio da Base
    glPushMatrix();
    glTranslatef(0.1, -0.4, 0.0);
    glScalef(0.075, 0.075, 0.125);
    glutSolidCube(1.0);
    glPopMatrix();

    //Topo da Base
    glPushMatrix();
    glTranslatef(0.25, -0.4, 0.0);
    glScalef(0.25, 0.05, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    //Torus da Torre
    glPushMatrix();
    glTranslatef(0.425, -0.4, 0.0);
    glutSolidSphere(0.15, 3, 3);
    glPopMatrix();
}

void torreMeioB(int status) {

    switch (status) {
    case 0: //Padrão (ainda não chegou na torre)
        glColor3f(1.0, 0.0, 1.0);
        break;
    case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
        glColor3f(1.0, 1.0, 0.0);
        break;
    case 2: //Destruida (personagem passou por essa torre e a venceu)
        glColor3f(0.5, 0.5, 0.5);
        break;
    case 3: //Invisivel
        glColor3f(0.2, 0.2, 0.2);
        break;
    }

    //Inicio da Base
    glPushMatrix();
    glTranslatef(0.1, 0.4, 0.0);
    glScalef(0.075, 0.075, 0.125);
    glutSolidCube(1.0);
    glPopMatrix();

    //Topo da Base
    glPushMatrix();
    glTranslatef(0.25, 0.4, 0.0);
    glScalef(0.25, 0.05, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    //Torus da Torre
    glPushMatrix();
    glTranslatef(0.425, 0.4, 0.0);
    glutSolidSphere(0.15, 3, 3);
    glPopMatrix();
}

void torreMeioDireitaA(int status) {

    switch (status) {
    case 0: //Padrão (ainda não chegou na torre)
        glColor3f(1.0, 0.0, 0.5);
        break;
    case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
        glColor3f(1.0, 1.0, 0.0);
        break;
    case 2: //Destruida (personagem passou por essa torre e a venceu)
        glColor3f(0.5, 0.5, 0.5);
        break;
    case 3: //Invisivel
        glColor3f(0.2, 0.2, 0.2);
        break;
    }

    //Inicio da Base
    glPushMatrix();
    glTranslatef(0.1, 1.40, 0.6);
    glScalef(0.075, 0.075, 0.125);
    glutSolidCube(1.0);
    glPopMatrix();

    //Topo da Base
    glPushMatrix();
    glTranslatef(0.25, 1.40, 0.6);
    glScalef(0.25, 0.05, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    //Torus da Torre
    glPushMatrix();
    glTranslatef(0.45, 1.40, 0.6);
    glutSolidSphere(0.1, 10, 10);
    glPopMatrix();
}

void torreMeioDireitaB(int status) {

    switch (status) {
    case 0: //Padrão (ainda não chegou na torre)
        glColor3f(1.0, 0.0, 0.5);
        break;
    case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
        glColor3f(1.0, 1.0, 0.0);
        break;
    case 2: //Destruida (personagem passou por essa torre e a venceu)
        glColor3f(0.5, 0.5, 0.5);
        break;
    case 3: //Invisivel
        glColor3f(0.2, 0.2, 0.2);
        break;
    }

    //Inicio da Base
    glPushMatrix();
    glTranslatef(0.1, 1.40, -0.6);
    glScalef(0.075, 0.075, 0.125);
    glutSolidCube(1.0);
    glPopMatrix();

    //Topo da Base
    glPushMatrix();
    glTranslatef(0.25, 1.40, -0.6);
    glScalef(0.25, 0.05, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    //Torus da Torre
    glPushMatrix();
    glTranslatef(0.45, 1.40, -0.6);
    glutSolidSphere(0.1, 10, 10);
    glPopMatrix();
}

void torreDireita(int status) {

    switch (status) {
    case 0: //Padrão (ainda não chegou na torre)
        glColor3f(1.0, 0.0, 0.0);
        break;
    case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
        glColor3f(1.0, 1.0, 0.0);
        break;
    case 2: //Destruida (personagem passou por essa torre e a venceu)
        glColor3f(0.5, 0.5, 0.5);
        break;
    case 3: //Invisivel
        glColor3f(0.2, 0.2, 0.2);
        break;
    }

    //Inicio da Base
    glPushMatrix();
    glTranslatef(0.1, 2.05, 0.0);
    glScalef(0.1, 0.1, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    //Meio da Base
    glPushMatrix();
    glTranslatef(0.2, 2.05, 0.0);
    glScalef(0.1, 0.15, 0.3);
    glutSolidCube(1.0);
    glPopMatrix();

    //Topo da Base
    glPushMatrix();
    glTranslatef(0.325, 2.05, 0.0);
    glScalef(0.15, 0.05, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    //Esfera da Torre
    glPushMatrix();
    glTranslatef(0.52, 2.05, 0.0);
    glutSolidSphere(0.15, 5, 5);
    glPopMatrix();
}

void chefeTorreDireita(int status) {

    switch (status) {
    case 0: //Padrão (ainda não chegou na torre)
        glColor3f(1.0, 0.0, 0.0);
        break;
    case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
        glColor3f(1.0, 1.0, 0.0);
        break;
    case 2: //Destruida (personagem passou por essa torre e a venceu)
        glColor3f(0.5, 0.5, 0.5);
        break;
    case 3: //Invisivel
        glColor3f(0.2, 0.2, 0.2);
        break;
    }

    glPushMatrix();
    glTranslatef(1.0, 1.75, 0.0);
    glScalef(0.03, 0.03, 0.03);
    glCallList(character);
    glPopMatrix();
}

void chefeTorreMeioDireitaB(int status) {

    switch (status) {
    case 0: //Padrão (ainda não chegou na torre)
        glColor3f(1.0, 0.0, 0.5);
        break;
    case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
        glColor3f(1.0, 1.0, 0.0);
        break;
    case 2: //Destruida (personagem passou por essa torre e a venceu)
        glColor3f(0.5, 0.5, 0.5);
        break;
    case 3: //Invisivel
        glColor3f(0.2, 0.2, 0.2);
        break;
    }

    glPushMatrix();
    glTranslatef(0.8, 1.20, -0.6);
    glScalef(0.03, 0.03, 0.03);
    glCallList(character);
    glPopMatrix();
}

void chefeTorreMeioDireitaA(int status) {

    switch (status) {
    case 0: //Padrão (ainda não chegou na torre)
        glColor3f(1.0, 0.0, 0.5);
        break;
    case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
        glColor3f(1.0, 1.0, 0.0);
        break;
    case 2: //Destruida (personagem passou por essa torre e a venceu)
        glColor3f(0.5, 0.5, 0.5);
        break;
    case 3: //Invisivel
        glColor3f(0.2, 0.2, 0.2);
        break;
    }

    glPushMatrix();
    glTranslatef(0.8, 1.20, 0.6);
    glScalef(0.03, 0.03, 0.03);
    glCallList(character);
    glPopMatrix();
}

void chefeTorreMeioB(int status) {

    switch (status) {
    case 0: //Padrão (ainda não chegou na torre)
        glColor3f(1.0, 0.0, 1.0);
        break;
    case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
        glColor3f(1.0, 1.0, 0.0);
        break;
    case 2: //Destruida (personagem passou por essa torre e a venceu)
        glColor3f(0.5, 0.5, 0.5);
        break;
    case 3: //Invisivel
        glColor3f(0.2, 0.2, 0.2);
        break;
    }

    glPushMatrix();
    glTranslatef(0.8, -0.1, 0.0);
    glScalef(0.03, 0.03, 0.03);
    glRotatef(180, 1, 0, 0);
    glCallList(character);
    glPopMatrix();
}

void chefeTorreMeioA(int status) {

    switch (status) {
    case 0: //Padrão (ainda não chegou na torre)
        glColor3f(1.0, 0.0, 1.0);
        break;
    case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
        glColor3f(1.0, 1.0, 0.0);
        break;
    case 2: //Destruida (personagem passou por essa torre e a venceu)
        glColor3f(0.5, 0.5, 0.5);
        break;
    case 3: //Invisivel
        glColor3f(0.2, 0.2, 0.2);
        break;
    }

    glPushMatrix();
    glTranslatef(0.8, 0.1, 0.0);
    glScalef(0.03, 0.03, 0.03);
    glCallList(character);
    glPopMatrix();
}




void chefeTorreMeioEsquerdaB(int status) {

    switch (status) {
    case 0: //Padrão (ainda não chegou na torre)
        glColor3f(0.7, 0.0, 1.0);
        break;
    case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
        glColor3f(1.0, 1.0, 0.0);
        break;
    case 2: //Destruida (personagem passou por essa torre e a venceu)
        glColor3f(0.5, 0.5, 0.5);
        break;
    case 3: //Invisivel
        glColor3f(0.2, 0.2, 0.2);
        break;
    }

    glPushMatrix();
    glTranslatef(0.8, -1.20, -0.6);
    glScalef(0.03, 0.03, 0.03);
    glRotatef(180, 1, 0, 0);
    glCallList(character);
    glPopMatrix();
}

void chefeTorreMeioEsquerdaA(int status) {

    switch (status) {
    case 0: //Padrão (ainda não chegou na torre)
        glColor3f(0.7, 0.0, 1.0);
        break;
    case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
        glColor3f(1.0, 1.0, 0.0);
        break;
    case 2: //Destruida (personagem passou por essa torre e a venceu)
        glColor3f(0.5, 0.5, 0.5);
        break;
    case 3: //Invisivel
        glColor3f(0.2, 0.2, 0.2);
        break;
    }

    glPushMatrix();
    glTranslatef(0.8, -1.20, 0.6);
    glScalef(0.03, 0.03, 0.03);
    glRotatef(180, 1, 0, 0);
    glCallList(character);
    glPopMatrix();
}

void chefeTorreEsquerda(int status) {

    switch (status) {
    case 0: //Padrão (ainda não chegou na torre)
        glColor3f(0.0, 0.0, 1.0);
        break;
    case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
        glColor3f(1.0, 1.0, 0.0);
        break;
    case 2: //Destruida (personagem passou por essa torre e a venceu)
        glColor3f(0.5, 0.5, 0.5);
        break;
    case 3: //Invisivel
        glColor3f(0.2, 0.2, 0.2);
        break;
    }

    glPushMatrix();
    glTranslatef(1.0, -1.75, 0.0);
    glScalef(0.03, 0.03, 0.03);
    glRotatef(180, 1, 0, 0);
    glCallList(character);
    glPopMatrix();
}

void textoCentralizadoTopo() {
    glColor3f(1.0, 1.0, 1.0);
    drawBitmapText("Escolha a dificuldade.  Digite 'd' para dificil e 'n' para normal;", 1.5, -0.35, 0.0); //texto com final ';', x, y, z (centralizar na tela mexendo no z e no y, altura mexe no x)
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Estrutura
    eixos();
    pista();

    //Textos
    textoCentralizadoTopo();

    //Torres (Ordem contrária para fazer sobreposição)
    torreEsquerda(0);
    torreMeioEsquerdaB(0);
    torreMeioEsquerdaA(0);
    torreMeioB(0);
    torreMeioA(0);
    torreMeioDireitaB(0);
    torreMeioDireitaA(0);
    torreDireita(0);

    //Chefões das Torres (Ordem contrária para fazer sobreposição)
    chefeTorreEsquerda(0);
    chefeTorreMeioEsquerdaB(0);
    chefeTorreMeioEsquerdaA(0);
    chefeTorreMeioB(0);
    chefeTorreMeioA(0);
    chefeTorreMeioDireitaB(0);
    chefeTorreMeioDireitaA(0);
    chefeTorreDireita(0);

    glutSwapBuffers();
}

void onTorreMeioTimer(int value) {
    if (onTorreMeioTimerAux == 0) {
        onTorreMeioCounter = value - 1;
    }
    if (onTorreMeioCounter != -1) {
        glutPostRedisplay();
        glutTimerFunc(GAP, onTorreMeioTimer, onTorreMeioCounter);
    }       
}

void onTorreMeio(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    torreAtual = 1;

    //Estrutura
    eixos();
    pista();

    if(onTorreMeioCounter == 0){
        tempoEncerrado = 1;
        recomecar = 1;
        drawBitmapText("Seu tempo acabou;", 1.5, -0.85, 0.0);
        drawBitmapText("Sabia que voce nao era rapido o bastante!;", 1.4, -0.85, 0.0);
        drawBitmapText("VOCE PERDEU!!!!!!!;", 1.3, -0.85, 0.0);
    } else{
        //Textos
        recomecar = 0;
        drawBitmapText("Brand: Um Intruso!!!! Voce queimara ao tentar me desafiar!!!!;", 1.5, -0.85, 0.0);
        //Contador
        char text[100];
	switch(n){
		case 0:
			    sprintf(text, "Resolva 7+2 em %d segundos;", onTorreMeioCounter);
		break;
		case 1:
			    sprintf(text, "Resolva 5+4 em %d segundos;", onTorreMeioCounter);
		break;
		case 2:
			    sprintf(text, "Resolva 14-5 em %d segundos;", onTorreMeioCounter);
		break;
		
	}
        drawBitmapText(text, 1.4, -0.85, 0.0);
    }

    //Torres (Ordem contrária para fazer sobreposição)
    torreEsquerda(0);
    torreMeioEsquerdaB(0);
    torreMeioEsquerdaA(0);
    torreMeioB(0);
    torreMeioA(1);
    torreMeioDireitaB(0);
    torreMeioDireitaA(0);
    torreDireita(0);

    //Chefões das Torres (Ordem contrária para fazer sobreposição)
    if(onTorreMeioCounter % 2 != 0){
        glPushMatrix();
        glScalef(1.03, 1.03, 1.03);
        chefeTorreEsquerda(0);
        chefeTorreMeioEsquerdaB(0);
        chefeTorreMeioEsquerdaA(0);
        chefeTorreMeioB(1);
        chefeTorreMeioA(0);
        chefeTorreMeioDireitaB(0);
        chefeTorreMeioDireitaA(0);
        chefeTorreDireita(0);
        glPopMatrix();
    } else{
        chefeTorreEsquerda(0);
        chefeTorreMeioEsquerdaB(0);
        chefeTorreMeioEsquerdaA(0);
        chefeTorreMeioB(1);
        chefeTorreMeioA(0);
        chefeTorreMeioDireitaB(0);
        chefeTorreMeioDireitaA(0);
        chefeTorreDireita(0);
    }
    

    glutSwapBuffers();
}

void onTorreEsquerdaATimer(int value) {
    if (onTorreEsquerdaATimerAux == 0) {
        onTorreEsquerdaACounter = value - 1;
    }
    if (onTorreEsquerdaACounter != -1) {
        glutPostRedisplay();
        glutTimerFunc(GAP, onTorreEsquerdaATimer, onTorreEsquerdaACounter);
    }       
}

void onTorreEsquerdaA(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    torreAtual = 2;

    //Estrutura
    eixos();
    pista();

    if(onTorreEsquerdaACounter == 0){
        tempoEncerrado = 1;
        recomecar = 1;
        drawBitmapText("Seu tempo acabou;", 1.5, -0.85, 0.0);
        drawBitmapText("Sabia que voce nao era rapido o bastante!;", 1.4, -0.85, 0.0);
        drawBitmapText("VOCE PERDEU!!!!!!!;", 1.3, -0.85, 0.0);
    } else{
        //Textos
        recomecar = 0;
        drawBitmapText("Brand: NAOOO Vinguem-me Irmaos!!!!;", 1.5, -0.85, 0.0);
        drawBitmapText("Ziggs: Vou adorar apresentar voce às minhas amigas estouradas!!!!;", 1.4, -0.85, 0.0);
        //Contador
        char text[100];
	switch(n){
		case 0:
			sprintf(text, "Resolva 10-5 em %d segundos;", onTorreEsquerdaACounter);
		break;
		case 1:
			sprintf(text, "Resolva 12-7 em %d segundos;", onTorreEsquerdaACounter);
		break;
		case 2:
			sprintf(text, "Resolva 41-36 em %d segundos;", onTorreEsquerdaACounter);
		break;
			
	}
        
        drawBitmapText(text, 1.3, -0.85, 0.0);
    }

    //Torres (Ordem contrária para fazer sobreposição)
    torreEsquerda(0);
    torreMeioEsquerdaB(0);
    torreMeioEsquerdaA(1);
    torreMeioB(0);
    torreMeioA(3);
    torreMeioDireitaB(0);
    torreMeioDireitaA(0);
    torreDireita(0);

    //Chefões das Torres (Ordem contrária para fazer sobreposição)
    if(onTorreEsquerdaACounter % 2 != 0){
        glPushMatrix();
        glScalef(1.03, 1.03, 1.03);
        chefeTorreEsquerda(0);
        chefeTorreMeioEsquerdaB(0);
        chefeTorreMeioEsquerdaA(1);
        chefeTorreMeioB(3);
        chefeTorreMeioA(0);
        chefeTorreMeioDireitaB(0);
        chefeTorreMeioDireitaA(0);
        chefeTorreDireita(0);
        glPopMatrix();
    } else{
        chefeTorreEsquerda(0);
        chefeTorreMeioEsquerdaB(0);
        chefeTorreMeioEsquerdaA(1);
        chefeTorreMeioB(3);
        chefeTorreMeioA(0);
        chefeTorreMeioDireitaB(0);
        chefeTorreMeioDireitaA(0);
        chefeTorreDireita(0);
    }

    glutSwapBuffers();

}

void onTorreEsquerdaBTimer(int value) {
    if (onTorreEsquerdaBTimerAux == 0) {
        onTorreEsquerdaBCounter = value - 1;
    }
    if (onTorreEsquerdaBCounter != -1) {
        glutPostRedisplay();
        glutTimerFunc(GAP, onTorreEsquerdaBTimer, onTorreEsquerdaBCounter);
    }       
}

void onTorreEsquerdaB(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    torreAtual = 3;

    //Estrutura
    eixos();
    pista();

    if(onTorreEsquerdaBCounter == 0){
        tempoEncerrado = 1;
        recomecar = 1;
        drawBitmapText("Seu tempo acabou;", 1.5, -0.85, 0.0);
        drawBitmapText("Sabia que voce nao era rapido o bastante!;", 1.4, -0.85, 0.0);
        drawBitmapText("VOCE PERDEU!!!!!!!;", 1.3, -0.85, 0.0);
    } else{
        //Textos
        recomecar = 0;
        drawBitmapText("Ziggs: Cedo ou tarde você conhecerá a sua dor!;", 1.5, -0.85, 0.0);
        drawBitmapText("Malzahar: O Poder do vazio mostrara o seu destino;", 1.4, -0.85, 0.0);

        //Contador
        char text[100];
	switch(n){
		case 0:
			    sprintf(text, "Resolva 7 + 7 - 21 + 9 em %d segundos;", onTorreEsquerdaBCounter);
		break;
		case 1:
			  sprintf(text, "Resolva 11 + 8 -17 em %d segundos;", onTorreEsquerdaBCounter);
		break;
		case 2:
			  sprintf(text, "Resolva 14-5-7 em %d segundos;", onTorreEsquerdaBCounter);
		break;
	}
    
        drawBitmapText(text, 1.3, -0.85, 0.0);
    }

    //Torres (Ordem contrária para fazer sobreposição)
    torreEsquerda(0);
    torreMeioEsquerdaB(1);
    torreMeioEsquerdaA(3);
    torreMeioB(0);
    torreMeioA(3);
    torreMeioDireitaB(0);
    torreMeioDireitaA(0);
    torreDireita(0);

    //Chefões das Torres (Ordem contrária para fazer sobreposição)
    if(onTorreEsquerdaBCounter % 2 != 0){
        glPushMatrix();
        glScalef(1.03, 1.03, 1.03);
        chefeTorreEsquerda(0);
        chefeTorreEsquerda(0);
        chefeTorreMeioEsquerdaB(1);
        chefeTorreMeioEsquerdaA(3);
        chefeTorreMeioB(3);
        chefeTorreMeioA(0);
        chefeTorreMeioDireitaB(0);
        chefeTorreMeioDireitaA(0);
        chefeTorreDireita(0);
        glPopMatrix();
    } else{
        chefeTorreEsquerda(0);
        chefeTorreEsquerda(0);
        chefeTorreMeioEsquerdaB(1);
        chefeTorreMeioEsquerdaA(3);
        chefeTorreMeioB(3);
        chefeTorreMeioA(0);
        chefeTorreMeioDireitaB(0);
        chefeTorreMeioDireitaA(0);
        chefeTorreDireita(0);
    }

    glutSwapBuffers();
}

void onTorreEsquerdaTimer(int value) {
    if (onTorreEsquerdaTimerAux == 0) {
        onTorreEsquerdaCounter = value - 1;
    }
    if (onTorreEsquerdaCounter != -1) {
        glutPostRedisplay();
        glutTimerFunc(GAP, onTorreEsquerdaTimer, onTorreEsquerdaCounter);
    }       
}

void onTorreEsquerda() {
    glClear(GL_COLOR_BUFFER_BIT);

    torreAtual = 4;

    //Estrutura
    eixos();
    pista();


    if(onTorreEsquerdaCounter == 0){
        tempoEncerrado = 1;
        recomecar = 1;
        drawBitmapText("Seu tempo acabou;", 1.5, -0.85, 0.0);
        drawBitmapText("Sabia que voce nao era rapido o bastante!;", 1.4, -0.85, 0.0);
        drawBitmapText("VOCE PERDEU!!!!!!!;", 1.3, -0.85, 0.0);
    } else{
        //Textos
        recomecar = 0;
        drawBitmapText("Malzahar: O vazio te espera!;", 1.5, -0.85, 0.0);
        drawBitmapText("Veigar: Como ousa me desafiar, meu poder e mais de 9000;", 1.4, -0.85, 0.0);

        //Contador
        char text[100];
	switch(n){
		case 0:
			   sprintf(text, "Resolva 7 + 5 - 14 + 21 + 3 - 14 em %d segundos;", onTorreEsquerdaCounter);
		break;
		case 1:
			   sprintf(text, "Resolva 8 + 6 - 6 + 28 -28 em %d segundos;", onTorreEsquerdaCounter);	
		break;
		case 2:
			   sprintf(text, "Resolva 0 + 2 -2 +2 -2 + 8 em %d segundos;", onTorreEsquerdaCounter);	
		break;

	}
    
        drawBitmapText(text, 1.3, -0.85, 0.0);
    }

    //Torres (Ordem contrária para fazer sobreposição)
    torreEsquerda(1);
    torreMeioEsquerdaB(3);
    torreMeioEsquerdaA(3);
    torreMeioB(0);
    torreMeioA(3);
    torreMeioDireitaB(0);
    torreMeioDireitaA(0);
    torreDireita(0);

    //Chefões das Torres (Ordem contrária para fazer sobreposição)
    if(onTorreEsquerdaCounter % 2 != 0){
        glPushMatrix();
        glScalef(1.03, 1.03, 1.03);
        chefeTorreEsquerda(1);
        chefeTorreMeioEsquerdaB(3);
        chefeTorreMeioEsquerdaA(3);
        chefeTorreMeioB(3);
        chefeTorreMeioA(0);
        chefeTorreMeioDireitaB(0);
        chefeTorreMeioDireitaA(0);
        chefeTorreDireita(0);
        glPopMatrix();
    } else{
        chefeTorreEsquerda(1);
        chefeTorreMeioEsquerdaB(3);
        chefeTorreMeioEsquerdaA(3);
        chefeTorreMeioB(3);
        chefeTorreMeioA(0);
        chefeTorreMeioDireitaB(0);
        chefeTorreMeioDireitaA(0);
        chefeTorreDireita(0);
    }

    glutSwapBuffers();
}

void onTorreMeioBTimer(int value) {
    if (onTorreMeioBTimerAux == 0) {
        onTorreMeioBCounter = value - 1;
    }
    if (onTorreMeioBCounter != -1) {
        glutPostRedisplay();
        glutTimerFunc(GAP, onTorreMeioBTimer, onTorreMeioBCounter);
    }       
}

void onTorreMeioB() {
    glClear(GL_COLOR_BUFFER_BIT);

    torreAtual = 5;

    //Estrutura
    eixos();
    pista();

    if(onTorreMeioBCounter == 0){
        tempoEncerrado = 1;
        recomecar = 1;
        drawBitmapText("Seu tempo acabou;", 1.75, 0.95, 0.0);
        drawBitmapText("Sabia que voce nao era rapido o bastante!;", 1.65, 0.95, 0.0);
        drawBitmapText("VOCE PERDEU!!!!!!!;", 1.55, 0.95, 0.0);
    } else{
        recomecar = 0;
        //Textos
        drawBitmapText("Brand: Um Intruso!!!! Voce queimara ao tentar me desafiar!!!!;", 1.75, 0.95, 0.0);

        //Contador
        char text[100];
	switch(n){
		case 0:
			    sprintf(text, "Resolva 60/10 em %d segundos;", onTorreMeioBCounter);
		break;
		case 1:
			    sprintf(text, "Resolva 1.2 * 5 em %d segundos;", onTorreMeioBCounter);
		break;
		case 2:
			    sprintf(text, "Resolva 36/6 em %d segundos;", onTorreMeioBCounter);
		break;
	}
    
        drawBitmapText(text, 1.65, 0.95, 0.0);
    }

    //Torres (Ordem contrária para fazer sobreposição)
    torreEsquerda(0);
    torreMeioEsquerdaB(0);
    torreMeioEsquerdaA(0);
    torreMeioB(1);
    torreMeioA(0);
    torreMeioDireitaB(0);
    torreMeioDireitaA(0);
    torreDireita(0);

    //Chefões das Torres (Ordem contrária para fazer sobreposição)
    if(onTorreMeioBCounter % 2 != 0){
        glPushMatrix();
        glScalef(1.03, 1.03, 1.03);
        chefeTorreEsquerda(0);
        chefeTorreMeioEsquerdaB(0);
        chefeTorreMeioEsquerdaA(0);
        chefeTorreMeioB(0);
        chefeTorreMeioA(1);
        chefeTorreMeioDireitaB(0);
        chefeTorreMeioDireitaA(0);
        chefeTorreDireita(0);
        glPopMatrix();
    } else {
        chefeTorreEsquerda(0);
        chefeTorreMeioEsquerdaB(0);
        chefeTorreMeioEsquerdaA(0);
        chefeTorreMeioB(0);
        chefeTorreMeioA(1);
        chefeTorreMeioDireitaB(0);
        chefeTorreMeioDireitaA(0);
        chefeTorreDireita(0);
    }

    glutSwapBuffers();
}

void onTorreDireitaATimer(int value) {
    if (onTorreDireitaATimerAux == 0) {
        onTorreDireitaACounter = value - 1;
    }
    if (onTorreDireitaACounter != -1) {
        glutPostRedisplay();
        glutTimerFunc(GAP, onTorreDireitaATimer, onTorreDireitaACounter);
    }       
}

void onTorreDireitaA() {
    glClear(GL_COLOR_BUFFER_BIT);

    torreAtual = 6;

    //Estrutura
    eixos();
    pista();

    if(onTorreDireitaACounter == 0){
        tempoEncerrado = 1;
        recomecar = 1;
        drawBitmapText("Seu tempo acabou;", 1.75, 0.95, 0.0);
        drawBitmapText("Sabia que voce nao era rapido o bastante!;", 1.65, 0.95, 0.0);
        drawBitmapText("VOCE PERDEU!!!!!!!;", 1.55, 0.95, 0.0);
    } else{
        recomecar = 0;
        //Textos
        drawBitmapText("Brand: Naoooo, vinguem-me irmaos;", 1.75, 0.95, 0.0);
        drawBitmapText("Ziggs: Vou adorar aprender voces às minhas amigas estouradas;", 1.65, 0.95, 0.0);

        //Contador
        char text[100];
	switch(n){
		case 0:
			sprintf(text, "Resolva 18/6 em %d segundos;", onTorreDireitaACounter);
		break;
		case 1:
			sprintf(text, "Resolva 27/9 em %d segundos;", onTorreDireitaACounter);
		break;
		case 2: 
			sprintf(text, "Resolva 9/3 em %d segundos;", onTorreDireitaACounter);
		break;
		
	}
        
        drawBitmapText(text, 1.55, 0.95, 0.0);
    }

    //Torres (Ordem contrária para fazer sobreposição)
    torreEsquerda(0);
    torreMeioEsquerdaB(0);
    torreMeioEsquerdaA(0);
    torreMeioB(3);
    torreMeioA(0);
    torreMeioDireitaB(0);
    torreMeioDireitaA(1);
    torreDireita(0);

    //Chefões das Torres (Ordem contrária para fazer sobreposição)
    if(onTorreDireitaACounter % 2 != 0){
        glPushMatrix();
        glScalef(1.03, 1.03, 1.03);
        chefeTorreEsquerda(0);
        chefeTorreMeioEsquerdaB(0);
        chefeTorreMeioEsquerdaA(0);
        chefeTorreMeioB(0);
        chefeTorreMeioA(3);
        chefeTorreMeioDireitaB(0);
        chefeTorreMeioDireitaA(1);
        chefeTorreDireita(0);
        glPopMatrix();
    } else {
        chefeTorreEsquerda(0);
        chefeTorreMeioEsquerdaB(0);
        chefeTorreMeioEsquerdaA(0);
        chefeTorreMeioB(0);
        chefeTorreMeioA(3);
        chefeTorreMeioDireitaB(0);
        chefeTorreMeioDireitaA(1);
        chefeTorreDireita(0);
    }

    glutSwapBuffers();
}

void onTorreDireitaBTimer(int value) {
    if (onTorreDireitaBTimerAux == 0) {
        onTorreDireitaBCounter = value - 1;
    }
    if (onTorreDireitaBCounter != -1) {
        glutPostRedisplay();
        glutTimerFunc(GAP, onTorreDireitaBTimer, onTorreDireitaBCounter);
    }       
}

void onTorreDireitaB() {
    glClear(GL_COLOR_BUFFER_BIT);

    torreAtual = 7;

    //Estrutura
    eixos();
    pista();

    if(onTorreDireitaBCounter == 0){
        tempoEncerrado = 1;
        recomecar = 1;
        drawBitmapText("Seu tempo acabou;", 1.75, 0.95, 0.0);
        drawBitmapText("Sabia que voce nao era rapido o bastante!;", 1.65, 0.95, 0.0);
        drawBitmapText("VOCE PERDEU!!!!!!!;", 1.55, 0.95, 0.0);
    } else{
        recomecar = 0;
        //Textos
        drawBitmapText("Ziggs: Cedo ou tarde você conhecerá a sua dor!;", 1.75, 0.95, 0.0);
        drawBitmapText("Malzahar: O Poder do vazio mostrara o seu destino;", 1.65, 0.95, 0.0);

        //Contador
        char text[100];
        sprintf(text, "Resolva ((((8 * 9) / 4) + 21) / 7) em %d segundos;", onTorreDireitaBCounter);
        drawBitmapText(text, 1.55, 0.95, 0.0);
    }

    //Torres (Ordem contrária para fazer sobreposição)
    torreEsquerda(0);
    torreMeioEsquerdaB(0);
    torreMeioEsquerdaA(0);
    torreMeioB(3);
    torreMeioA(0);
    torreMeioDireitaB(1);
    torreMeioDireitaA(3);
    torreDireita(0);

    //Chefões das Torres (Ordem contrária para fazer sobreposição)
    if(onTorreDireitaBCounter % 2 != 0){
        glPushMatrix();
        glScalef(1.03, 1.03, 1.03);
        chefeTorreEsquerda(0);
        chefeTorreMeioEsquerdaB(0);
        chefeTorreMeioEsquerdaA(0);
        chefeTorreMeioB(0);
        chefeTorreMeioA(3);
        chefeTorreMeioDireitaB(1);
        chefeTorreMeioDireitaA(3);
        chefeTorreDireita(0);
        glPopMatrix();
    } else {
        chefeTorreEsquerda(0);
        chefeTorreMeioEsquerdaB(0);
        chefeTorreMeioEsquerdaA(0);
        chefeTorreMeioB(0);
        chefeTorreMeioA(3);
        chefeTorreMeioDireitaB(1);
        chefeTorreMeioDireitaA(3);
        chefeTorreDireita(0);
    }

    glutSwapBuffers();
}

void onTorreDireitaTimer(int value) {
    if (onTorreDireitaTimerAux == 0) {
        onTorreDireitaCounter = value - 1;
    }
    if (onTorreDireitaCounter != -1) {
        glutPostRedisplay();
        glutTimerFunc(GAP, onTorreDireitaTimer, onTorreDireitaCounter);
    }       
}

void onTorreDireita() {
    glClear(GL_COLOR_BUFFER_BIT);

    torreAtual = 8;

    //Estrutura
    eixos();
    pista();

    if(onTorreDireitaCounter == 0){
        tempoEncerrado = 1;
        recomecar = 1;
        drawBitmapText("Seu tempo acabou;", 1.75, 0.95, 0.0);
        drawBitmapText("Sabia que voce nao era rapido o bastante!;", 1.65, 0.95, 0.0);
        drawBitmapText("VOCE PERDEU!!!!!!!;", 1.55, 0.95, 0.0);
    } else{
        recomecar = 0;
        //Textos
        drawBitmapText("Malzahar: O vazio te espera!;", 1.75, 0.95, 0.0);
        drawBitmapText("Veigar: Como ousa me desafiar, meu poder eh mais de 9000;", 1.65, 0.95, 0.0);

        //Contador
        char text[100];
	switch(n){
		case 0:
			       sprintf(text, "Resolva (((((8 * 9) / 4) + 21 ) * 0) / 7)) em %d segundos;", onTorreDireitaCounter);
		break;
		case 1:
			       sprintf(text, "Resolva (((((6 * 9) / 27) + 21 ) * 0) / 11)) em %d segundos;", onTorreDireitaCounter);
		break;
		case 2:
			       sprintf(text, "Resolva (((((9 * 9) / 3) + 27 ) * 0) / 9)) em %d segundos;", onTorreDireitaCounter);
		break;
	}
        drawBitmapText(text, 1.55, 0.95, 0.0);
    }

    //Torres (Ordem contrária para fazer sobreposição)
    torreEsquerda(0);
    torreMeioEsquerdaB(0);
    torreMeioEsquerdaA(0);
    torreMeioB(3);
    torreMeioA(0);
    torreMeioDireitaB(3);
    torreMeioDireitaA(3);
    torreDireita(1);

    //Chefões das Torres (Ordem contrária para fazer sobreposição)
    if(onTorreDireitaCounter % 2 != 0){
        glPushMatrix();
        glScalef(1.03, 1.03, 1.03);
        chefeTorreEsquerda(0);
        chefeTorreMeioEsquerdaB(0);
        chefeTorreMeioEsquerdaA(0);
        chefeTorreMeioB(0);
        chefeTorreMeioA(3);
        chefeTorreMeioDireitaB(3);
        chefeTorreMeioDireitaA(3);
        chefeTorreDireita(1);
        glPopMatrix();
    } else {
        chefeTorreEsquerda(0);
        chefeTorreMeioEsquerdaB(0);
        chefeTorreMeioEsquerdaA(0);
        chefeTorreMeioB(0);
        chefeTorreMeioA(3);
        chefeTorreMeioDireitaB(3);
        chefeTorreMeioDireitaA(3);
        chefeTorreDireita(1);
    }

    glutSwapBuffers();

}
void fimDeJogoD() {

    glClear(GL_COLOR_BUFFER_BIT);

    //Estrutura
    eixos();
    pista();

    //Textos
    drawBitmapText("COMO? ISSO EH IMPOSSIVEL!!!!!!;", 1.75, 0.95, 0.0);
    drawBitmapText("VOCE VENCEU;", 1.65, 0.95, 0.0);
    recomecar = 1;

    //Torres (Ordem contrária para fazer sobreposição)
    torreEsquerda(0);
    torreMeioEsquerdaB(0);
    torreMeioEsquerdaA(0);
    torreMeioB(3);
    torreMeioA(0);
    torreMeioDireitaB(3);
    torreMeioDireitaA(3);
    torreDireita(3);

    //Chefões das Torres (Ordem contrária para fazer sobreposição)
    chefeTorreEsquerda(0);
    chefeTorreMeioEsquerdaB(0);
    chefeTorreMeioEsquerdaA(0);
    chefeTorreMeioB(0);
    chefeTorreMeioA(3);
    chefeTorreMeioDireitaB(3);
    chefeTorreMeioDireitaA(3);
    chefeTorreDireita(3);

    glutSwapBuffers();

}
void renderBitmapString(float x, float y, void *font,const char *string){
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
} 
void gameOver() {
    glClear(GL_COLOR_BUFFER_BIT);

    //Estrutura
    eixos();
    pista();
    //Textos 
    if(start == 1){
	    char buffer[10]={'\0'};
	    sprintf(buffer, "%d", respostaErrada); 
	    drawBitmapText("Respota Errada;", 1.5, -0.35, 0.0);
	    drawBitmapText("Voce digitou a resposta:;", 1.45, -0.35, 0.0);
	    renderBitmapString(1.4f, -0.35f, GLUT_BITMAP_HELVETICA_18, buffer);
	    char buffer2[10] = {'\0'};
	    sprintf(buffer2, "%d", respostaCorreta); 
	    drawBitmapText("A resposta correta seria:;", 1.35, -0.35, 0.0);
	    renderBitmapString(1.3f, -0.35f, GLUT_BITMAP_HELVETICA_18, buffer2);
	    drawBitmapText("VOCE PERDEU!!!!!!!;", 1.25, -0.35, 0.0);

    }
    recomecar = 1;

    //Torres (Ordem contrária para fazer sobreposição)
    torreEsquerda(3);
    torreMeioEsquerdaB(3);
    torreMeioEsquerdaA(3);
    torreMeioB(3);
    torreMeioA(3);
    torreMeioDireitaB(3);
    torreMeioDireitaA(3);
    torreDireita(3);

    //Chefões das Torres (Ordem contrária para fazer sobreposição)
    chefeTorreEsquerda(3);
    chefeTorreMeioEsquerdaB(3);
    chefeTorreMeioEsquerdaA(3);
    chefeTorreMeioB(3);
    chefeTorreMeioA(3);
    chefeTorreMeioDireitaB(3);
    chefeTorreMeioDireitaA(3);
    chefeTorreDireita(3);

    glutSwapBuffers();
}

void fimDeJogo() {
    glClear(GL_COLOR_BUFFER_BIT);

    //Estrutura
    eixos();
    pista();

    //Textos
    drawBitmapText("Veigar: COMO? ISSO EH IMPOSSÌVEL ;", 1.5, -0.85, 0.0);
    drawBitmapText("VOCE VENCEU!!!!!;", 1.4, -0.85, 0.0);
    recomecar = 1;

    //Torres (Ordem contrária para fazer sobreposição)
    torreEsquerda(3);
    torreMeioEsquerdaB(3);
    torreMeioEsquerdaA(3);
    torreMeioB(0);
    torreMeioA(3);
    torreMeioDireitaB(0);
    torreMeioDireitaA(0);
    torreDireita(0);

    //Chefões das Torres (Ordem contrária para fazer sobreposição)
    chefeTorreEsquerda(3);
    chefeTorreMeioEsquerdaB(3);
    chefeTorreMeioEsquerdaA(3);
    chefeTorreMeioB(3);
    chefeTorreMeioA(0);
    chefeTorreMeioDireitaB(0);
    chefeTorreMeioDireitaA(0);
    chefeTorreDireita(0);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(55.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(posx, posy, posz, focx, focy, focz, disx, disy, disz);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'd': //Seleciona lado direito
	n = generateNumber();
	start = 1;
        if(recomecar == 1){
            posx = 2.0f;
            posy = -1.0f;
            posz = -1.0f;
            focx = 0.0f;
            focy = 2.0f;
            focz = 0.0f;
            disx = 1.0f;
            disy = 0.0f;
            disz = 0.0f;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            tempoEncerrado = 0;
            glutTimerFunc(GAP, onTorreMeioBTimer, 10);
            gluLookAt(posx, posy, posz, focx, focy, focz, disx, disy, disz);
            glutDisplayFunc(onTorreMeioB);
        }
        break;
    case 'n': //Seleciona lado esquerdo
	n = generateNumber();
	start = 1;
        if(recomecar == 1){
            posx = 2.0f;
            posy = 1.0f;
            posz = -1.0f;
            focx = 0.0f;
            focy = -2.0f;
            focz = 0.0f;
            disx = 1.0f;
            disy = 0.0f;
            disz = 0.0f;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            tempoEncerrado = 0;
            gluLookAt(posx, posy, posz, focx, focy, focz, disx, disy, disz);
            status = 1;
            glutTimerFunc(GAP, onTorreMeioTimer, 10);
            glutDisplayFunc(onTorreMeio);
        }
        break;
    case '9':
	n = generateNumber();
        if(tempoEncerrado == 0){
            if (torreAtual == 1) {
                glutTimerFunc(GAP, onTorreEsquerdaATimer, 10);
                glutDisplayFunc(onTorreEsquerdaA);
            } else {
		respostaErrada = 9;
		respostaCorreta = respostasCorretas[torreAtual];
                glutDisplayFunc(gameOver);

            }
        }
        break;
    case '5':
	n = generateNumber();
        if(tempoEncerrado == 0){
            if (torreAtual == 2) {
                glutTimerFunc(GAP, onTorreEsquerdaBTimer, 10);
                glutDisplayFunc(onTorreEsquerdaB);
            } else {
		respostaErrada = 5;
		respostaCorreta = respostasCorretas[torreAtual];
                glutDisplayFunc(gameOver);
            }
        }
        break;
    case '2':
	n = generateNumber();
        if(tempoEncerrado == 0){
            if (torreAtual == 3) {
                glutTimerFunc(GAP, onTorreEsquerdaTimer, 10);
                glutDisplayFunc(onTorreEsquerda);
            } else {
		respostaErrada = 2;
		respostaCorreta = respostasCorretas[torreAtual];
                glutDisplayFunc(gameOver);
            }
        }
        break;
    case '8':
	n = generateNumber();
        if(tempoEncerrado == 0){
            if (torreAtual == 4) {
                glutDisplayFunc(fimDeJogo);
            } else {
		respostaErrada = 8;
		respostaCorreta = respostasCorretas[torreAtual];
                glutDisplayFunc(gameOver);
            }
        }
        break;
    case '6':
	n = generateNumber();
        if(tempoEncerrado == 0){
            if (torreAtual == 5) {
                glutTimerFunc(GAP, onTorreDireitaATimer, 10);
                glutDisplayFunc(onTorreDireitaA);
            } else {
		respostaErrada = 6;
		respostaCorreta = respostasCorretas[torreAtual];
                glutDisplayFunc(gameOver);
            }
        }

        break;
    case '3':
	n = generateNumber();
        if(tempoEncerrado == 0){
            if (torreAtual == 6) {
                glutTimerFunc(GAP, onTorreDireitaBTimer, 10);
                glutDisplayFunc(onTorreDireitaB);
            } else {
		respostaErrada = 3;
		respostaCorreta = respostasCorretas[torreAtual];
                glutDisplayFunc(gameOver);
            }
        }
        break;
    case '7':
	n = generateNumber();
        if(tempoEncerrado == 0){
            if (torreAtual == 7) {
                glutTimerFunc(GAP, onTorreDireitaTimer, 10);
                glutDisplayFunc(onTorreDireita);
            } else {
		respostaErrada = 7;
		respostaCorreta = respostasCorretas[torreAtual];
                glutDisplayFunc(gameOver);
            }
        }
        break;
    case '0':
	n = generateNumber();
        if(tempoEncerrado == 0){
            if (torreAtual == 8) {
                glutDisplayFunc(fimDeJogoD);
            } else {
		respostaErrada = 0;
		respostaCorreta = respostasCorretas[torreAtual];
                glutDisplayFunc(gameOver);
            }
        }
        break;

    default:
        if(tempoEncerrado == 0){
	    if(key == '4'){
	    	respostaErrada = 4;
	    } else if (key == '1'){
	    	respostaErrada = 1;
	    }
	    respostaCorreta = respostasCorretas[torreAtual];
            glutDisplayFunc(gameOver);
        }
        break;
    }


    if(tempoEncerrado == 0){
       glutPostRedisplay(); 
   }
}

void init(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Habilitar o uso de texturas 
    
    glShadeModel(GL_FLAT);
    // Definir a forma de armazenamento dos pixels na textura (1= alinhamento por byte) 
    glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );

    // Definir quantas texturas serão usadas no programa 
    glGenTextures (1, texture_id);  // 1 = uma textura; 
                                     // texture_id = vetor que guarda os números das texturas

    // Carrega um arquivo de imagem diretamente como uma nova textura OpenGL
    texture_id[0] = SOIL_load_OGL_texture
    (
        "background.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    
    /* check for an error during the load process */
    if( 0 == texture_id[0] )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
}

int main(int argc, char * * argv) {
    glutInit( & argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Projeto CG - 41406133 e 41404998");
    init();
    glutDisplayFunc(display);
    loadObj("objs/janna.obj");
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
