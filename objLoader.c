    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/glut.h>

    //Câmera
    float posx = 2.0f, posy = 0.0f, posz = -3.0f, focx = 0.0f, focy = 0.0f, focz = 0.0f, disx = 2.0f, disy = 0.0f, disz = 0.0f;
    
    int status = 0; 
        //0: Padrão (ainda não chegou na torre)
        //1: Iluminada (personagem está nessa torre, aparece em destaque)
        //2: Destruida (personagem passou por essa torre e a venceu)
        //3: Invisivel

    void init(void) 
    {
      glClearColor (0.0, 0.0, 0.0, 0.0);
      glShadeModel (GL_FLAT);
    }

    void drawBitmapText(char *string,float x,float y,float z) 
    {  
        char *c;
        glRasterPos3f(x, y,z);

        for (c=string; *c != ';'; c++) 
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
            //glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c)
            //glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c)
            //glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c)
            //glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c)
            //glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *c)
            //glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c)
            //glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c)
        }
    }

    void eixos(){

        //eixo x
       glPushMatrix();
          glBegin(GL_LINES);
             glColor3f(1,0,0);
             glVertex3i(0,0,0);
             glVertex3i(50,0,0);
          glEnd();
       glPopMatrix();

       //eixo y
       glPushMatrix();   
          glBegin(GL_LINES);
             glColor3f(0,1,0);
             glVertex3i(0,0,0);
             glVertex3i(0,50,0);
          glEnd();
       glPopMatrix();

       //eixo z
       glPushMatrix();
          glBegin(GL_LINES);
             glColor3f(0,0,1);
             glVertex3i(0,0,0);
             glVertex3i(0,0,50);
          glEnd();
       glPopMatrix();
    }

    void pista() {
        glColor3f(1.0,1.0,1.0);

       //Inicio da Pista   
       glPushMatrix();
           glTranslatef(0.0, -2.05, 0.0);
           glScalef (0.1, 0.5, 1.4);
           glutWireCube (1.0);
       glPopMatrix();

       //Inicio-Meio da Pista   
       glPushMatrix();
           glTranslatef(0.0, -1.40, 0.0);
           glScalef (0.1, 0.8, 2.6);
           glutWireCube (1.0);
       glPopMatrix();

       //Ponte A Inicio Pista
       glPushMatrix();
           glTranslatef(0.0, -0.9, 0.4);
           glScalef (0.1, 0.2, 0.4);
           glutWireCube (1.0);
       glPopMatrix();

       //Ponte B Inicio Pista
       glPushMatrix();
           glTranslatef(0.0, -0.9, -0.4);
           glScalef (0.1, 0.2, 0.4);
           glutWireCube (1.0);
       glPopMatrix();

       //Meio da Pista   
       glPushMatrix();
           glTranslatef(0.0, 0, 0.0);
           glScalef (0.1, 1.6, 2.0);
           glutWireCube (1.0);
       glPopMatrix();

       //Fim-Meio da Pista   
       glPushMatrix();
           glTranslatef(0.0, 1.40, 0.0);
           glScalef (0.1, 0.8, 2.6);
           glutWireCube (1.0);
       glPopMatrix();

       //Ponte A Fim Pista
       glPushMatrix();
           glTranslatef(0.0, 0.9, 0.4);
           glScalef (0.1, 0.2, 0.4);
           glutWireCube (1.0);
       glPopMatrix();

       //Ponte B Fim Pista
       glPushMatrix();
           glTranslatef(0.0, 0.9, -0.4);
           glScalef (0.1, 0.2, 0.4);
           glutWireCube (1.0);
       glPopMatrix();

       //Fim da Pista   
       glPushMatrix();
           glTranslatef(0.0, 2.05, 0.0);
           glScalef (0.1, 0.5, 1.4);
           glutWireCube (1.0);
       glPopMatrix();
    }

    void torreEsquerda(int status){

        switch (status){
            case 0: //Padrão (ainda não chegou na torre)
                glColor3f(0.0,0.0,1.0);
                break;
            case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
                glColor3f(1.0,1.0,0.0);
                break;
            case 2: //Destruida (personagem passou por essa torre e a venceu)
                glColor3f(0.5,0.5,0.5);
                break;
            case 3: //Invisivel
                glColor3f(0.0,0.0,0.0);
                break;
        }

        //Inicio da Base
        glPushMatrix();
            glTranslatef(0.1, -2.05, 0.0);
            glScalef(0.1, 0.1, 0.2);
            glutWireCube(1.0);
        glPopMatrix();

        //Meio da Base
        glPushMatrix();
            glTranslatef(0.2, -2.05, 0.0);
            glScalef(0.1, 0.15, 0.3);
            glutWireCube(1.0);
        glPopMatrix();

        //Topo da Base
        glPushMatrix();
            glTranslatef(0.325, -2.05, 0.0);
            glScalef(0.15, 0.05, 0.05);
            glutWireCube(1.0);
        glPopMatrix();

        //Esfera da Torre
        glPushMatrix();
            glTranslatef(0.52, -2.05, 0.0);
            //glScalef(0.05, 0.05, 0.05);
            glutWireSphere(0.15, 5, 5);
        glPopMatrix();
    }

    void torreMeioEsquerdaA(int status){
        
        switch (status){
            case 0: //Padrão (ainda não chegou na torre)
                glColor3f(0.7,0.0,1.0);
                break;
            case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
                glColor3f(1.0,1.0,0.0);
                break;
            case 2: //Destruida (personagem passou por essa torre e a venceu)
                glColor3f(0.5,0.5,0.5);
                break;
            case 3: //Invisivel
                glColor3f(0.0,0.0,0.0);
                break;

        }

        //Inicio da Base
        glPushMatrix();
            glTranslatef(0.1, -1.40, 0.6);
            glScalef(0.075, 0.075, 0.125);
            glutWireCube(1.0);
        glPopMatrix();

        //Topo da Base
        glPushMatrix();
            glTranslatef(0.25, -1.40, 0.6);
            glScalef(0.25, 0.05, 0.05);
            glutWireCube(1.0);
        glPopMatrix();

        //Torus da Torre
        glPushMatrix();
            glTranslatef(0.45, -1.40, 0.6);
            glutWireSphere(0.1, 10, 10);
        glPopMatrix();
    }

    void torreMeioEsquerdaB(int status){
        
        switch (status){
            case 0: //Padrão (ainda não chegou na torre)
                glColor3f(0.7,0.0,1.0);
                break;
            case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
                glColor3f(1.0,1.0,0.0);
                break;
            case 2: //Destruida (personagem passou por essa torre e a venceu)
                glColor3f(0.5,0.5,0.5);
                break;
            case 3: //Invisivel
                glColor3f(0.0,0.0,0.0);
                break;

        }

        //Inicio da Base
        glPushMatrix();
            glTranslatef(0.1, -1.40, -0.6);
            glScalef(0.075, 0.075, 0.125);
            glutWireCube(1.0);
        glPopMatrix();

        //Topo da Base
        glPushMatrix();
            glTranslatef(0.25, -1.40, -0.6);
            glScalef(0.25, 0.05, 0.05);
            glutWireCube(1.0);
        glPopMatrix();

        //Torus da Torre
        glPushMatrix();
            glTranslatef(0.45, -1.40, -0.6);
            glutWireSphere(0.1, 10, 10);
        glPopMatrix();
    }

    void torreMeioA(int status){

        switch (status){
            case 0: //Padrão (ainda não chegou na torre)
                glColor3f(1.0,0.0,1.0);
                break;
            case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
                glColor3f(1.0,1.0,0.0);
                break;
            case 2: //Destruida (personagem passou por essa torre e a venceu)
                glColor3f(0.5,0.5,0.5);
                break;
            case 3: //Invisivel
                glColor3f(0.0,0.0,0.0);
                break;

        }

        //Inicio da Base
        glPushMatrix();
            glTranslatef(0.1, -0.4, 0.0);
            glScalef(0.075, 0.075, 0.125);
            glutWireCube(1.0);
        glPopMatrix();

        //Topo da Base
        glPushMatrix();
            glTranslatef(0.25, -0.4, 0.0);
            glScalef(0.25, 0.05, 0.05);
            glutWireCube(1.0);
        glPopMatrix();

        //Torus da Torre
        glPushMatrix();
            glTranslatef(0.425, -0.4, 0.0);
            glutWireSphere(0.15, 3, 3);
        glPopMatrix();
    }

    void torreMeioB(int status){

        switch (status){
            case 0: //Padrão (ainda não chegou na torre)
                glColor3f(1.0,0.0,1.0);
                break;
            case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
                glColor3f(1.0,1.0,0.0);
                break;
            case 2: //Destruida (personagem passou por essa torre e a venceu)
                glColor3f(0.5,0.5,0.5);
                break;
            case 3: //Invisivel
                glColor3f(0.0,0.0,0.0);
                break;

        }

        //Inicio da Base
        glPushMatrix();
            glTranslatef(0.1, 0.4, 0.0);
            glScalef(0.075, 0.075, 0.125);
            glutWireCube(1.0);
        glPopMatrix();

        //Topo da Base
        glPushMatrix();
            glTranslatef(0.25, 0.4, 0.0);
            glScalef(0.25, 0.05, 0.05);
            glutWireCube(1.0);
        glPopMatrix();

        //Torus da Torre
        glPushMatrix();
            glTranslatef(0.425, 0.4, 0.0);
            glutWireSphere(0.15, 3, 3);
        glPopMatrix();
    }

    void torreMeioDireitaA(int status){
        
        switch (status){
            case 0: //Padrão (ainda não chegou na torre)
                glColor3f(1.0,0.0,0.5);
                break;
            case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
                glColor3f(1.0,1.0,0.0);
                break;
            case 2: //Destruida (personagem passou por essa torre e a venceu)
                glColor3f(0.5,0.5,0.5);
                break;
            case 3: //Invisivel
                glColor3f(0.0,0.0,0.0);
                break;

        }

        //Inicio da Base
        glPushMatrix();
            glTranslatef(0.1, 1.40, 0.6);
            glScalef(0.075, 0.075, 0.125);
            glutWireCube(1.0);
        glPopMatrix();

        //Topo da Base
        glPushMatrix();
            glTranslatef(0.25, 1.40, 0.6);
            glScalef(0.25, 0.05, 0.05);
            glutWireCube(1.0);
        glPopMatrix();

        //Torus da Torre
        glPushMatrix();
            glTranslatef(0.45, 1.40, 0.6);
            glutWireSphere(0.1, 10, 10);
        glPopMatrix();
    }

    void torreMeioDireitaB(int status){
        
        switch (status){
            case 0: //Padrão (ainda não chegou na torre)
                glColor3f(1.0,0.0,0.5);
                break;
            case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
                glColor3f(1.0,1.0,0.0);
                break;
            case 2: //Destruida (personagem passou por essa torre e a venceu)
                glColor3f(0.5,0.5,0.5);
                break;
            case 3: //Invisivel
                glColor3f(0.0,0.0,0.0);
                break;

        }

        //Inicio da Base
        glPushMatrix();
            glTranslatef(0.1, 1.40, -0.6);
            glScalef(0.075, 0.075, 0.125);
            glutWireCube(1.0);
        glPopMatrix();

        //Topo da Base
        glPushMatrix();
            glTranslatef(0.25, 1.40, -0.6);
            glScalef(0.25, 0.05, 0.05);
            glutWireCube(1.0);
        glPopMatrix();

        //Torus da Torre
        glPushMatrix();
            glTranslatef(0.45, 1.40, -0.6);
            glutWireSphere(0.1, 10, 10);
        glPopMatrix();
    }

    void torreDireita(int status){
        
        switch (status){
            case 0: //Padrão (ainda não chegou na torre)
                glColor3f(1.0,0.0,0.0);
                break;
            case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
                glColor3f(1.0,1.0,0.0);
                break;
            case 2: //Destruida (personagem passou por essa torre e a venceu)
                glColor3f(0.5,0.5,0.5);
                break;
            case 3: //Invisivel
                glColor3f(0.0,0.0,0.0);
                break;

        }

        //Inicio da Base
        glPushMatrix();
            glTranslatef(0.1, 2.05, 0.0);
            glScalef(0.1, 0.1, 0.2);
            glutWireCube(1.0);
        glPopMatrix();

        //Meio da Base
        glPushMatrix();
            glTranslatef(0.2, 2.05, 0.0);
            glScalef(0.1, 0.15, 0.3);
            glutWireCube(1.0);
        glPopMatrix();

        //Topo da Base
        glPushMatrix();
            glTranslatef(0.325, 2.05, 0.0);
            glScalef(0.15, 0.05, 0.05);
            glutWireCube(1.0);
        glPopMatrix();

        //Esfera da Torre
        glPushMatrix();
            glTranslatef(0.52, 2.05, 0.0);
            glutWireSphere(0.15, 5, 5);
        glPopMatrix();
    }

    void chefeTorreDireita(int status){
         
        switch (status){
            case 0: //Padrão (ainda não chegou na torre)
                glColor3f(1.0,0.0,0.0);
                break;
            case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
                glColor3f(1.0,1.0,0.0);
                break;
            case 2: //Destruida (personagem passou por essa torre e a venceu)
                glColor3f(0.5,0.5,0.5);
                break;
            case 3: //Invisivel
                glColor3f(0.0,0.0,0.0);
                break;

        }

        glPushMatrix();
            glTranslatef(1.0, 2.05, 0.0);
            glutWireCube(0.4);
        glPopMatrix();
    }

    void chefeTorreMeioDireitaB(int status){

        switch (status){
            case 0: //Padrão (ainda não chegou na torre)
                glColor3f(1.0,0.0,0.5);
                break;
            case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
                glColor3f(1.0,1.0,0.0);
                break;
            case 2: //Destruida (personagem passou por essa torre e a venceu)
                glColor3f(0.5,0.5,0.5);
                break;
            case 3: //Invisivel
                glColor3f(0.0,0.0,0.0);
                break;

        }

         glPushMatrix();
            glTranslatef(0.8, 1.40, -0.6);
            glutWireCube(0.3);
        glPopMatrix();
    }

    void chefeTorreMeioDireitaA(int status){

        switch (status){
            case 0: //Padrão (ainda não chegou na torre)
                glColor3f(1.0,0.0,0.5);
                break;
            case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
                glColor3f(1.0,1.0,0.0);
                break;
            case 2: //Destruida (personagem passou por essa torre e a venceu)
                glColor3f(0.5,0.5,0.5);
                break;
            case 3: //Invisivel
                glColor3f(0.0,0.0,0.0);
                break;

        }

         glPushMatrix();
            glTranslatef(0.8, 1.40, 0.6);
            glutWireCube(0.3);
        glPopMatrix();
    }

    void chefeTorreMeioB(int status){

        switch (status){
            case 0: //Padrão (ainda não chegou na torre)
                glColor3f(1.0,0.0,1.0);
                break;
            case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
                glColor3f(1.0,1.0,0.0);
                break;
            case 2: //Destruida (personagem passou por essa torre e a venceu)
                glColor3f(0.5,0.5,0.5);
                break;
            case 3: //Invisivel
                glColor3f(0.0,0.0,0.0);
                break;

        }

        glPushMatrix();
            glTranslatef(0.8, -0.4, 0.0);
            glutWireCube(0.3);
        glPopMatrix();
    }

    void chefeTorreMeioA(int status){

        switch (status){
            case 0: //Padrão (ainda não chegou na torre)
                glColor3f(1.0,0.0,1.0);
                break;
            case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
                glColor3f(1.0,1.0,0.0);
                break;
            case 2: //Destruida (personagem passou por essa torre e a venceu)
                glColor3f(0.5,0.5,0.5);
                break;
            case 3: //Invisivel
                glColor3f(0.0,0.0,0.0);
                break;

        }

        glPushMatrix();
            glTranslatef(0.8, 0.4, 0.0);
            glutWireCube(0.3);
        glPopMatrix();
    }

    void chefeTorreMeioEsquerdaB(int status){
        
        switch (status){
            case 0: //Padrão (ainda não chegou na torre)
                glColor3f(0.7,0.0,1.0);
                break;
            case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
                glColor3f(1.0,1.0,0.0);
                break;
            case 2: //Destruida (personagem passou por essa torre e a venceu)
                glColor3f(0.5,0.5,0.5);
                break;
            case 3: //Invisivel
                glColor3f(0.0,0.0,0.0);
                break;

        }

         glPushMatrix();
            glTranslatef(0.8, -1.40, -0.6);
            glutWireCube(0.3);
        glPopMatrix();
    }

    void chefeTorreMeioEsquerdaA(int status){
        
        switch (status){
            case 0: //Padrão (ainda não chegou na torre)
                glColor3f(0.7,0.0,1.0);
                break;
            case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
                glColor3f(1.0,1.0,0.0);
                break;
            case 2: //Destruida (personagem passou por essa torre e a venceu)
                glColor3f(0.5,0.5,0.5);
                break;
            case 3: //Invisivel
                glColor3f(0.0,0.0,0.0);
                break;

        }

         glPushMatrix();
            glTranslatef(0.8, -1.40, 0.6);
            glutWireCube(0.3);
        glPopMatrix();
    }

    void chefeTorreEsquerda(int status){
        
        switch (status){
            case 0: //Padrão (ainda não chegou na torre)
                glColor3f(0.0,0.0,1.0);
                break;
            case 1: //Iluminada (personagem está nessa torre, aparece em destaque)
                glColor3f(1.0,1.0,0.0);
                break;
            case 2: //Destruida (personagem passou por essa torre e a venceu)
                glColor3f(0.5,0.5,0.5);
                break;
            case 3: //Invisivel
                glColor3f(0.0,0.0,0.0);
                break;

        }

        glPushMatrix();
            glTranslatef(1.0, -2.05, 0.0);
            glutWireCube(0.4);
        glPopMatrix();
    }

    void textoCentralizadoTopo(){
        glColor3f(1.0,1.0,1.0);
        drawBitmapText("Texto de exemplo;",1.5,-0.35,0.0); //texto com final ';', x, y, z (centralizar na tela mexendo no z e no y, altura mexe no x)
    }

    void display(void)
    {
       glClear (GL_COLOR_BUFFER_BIT);

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

    void reshape (int w, int h)
    {
       glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
       glMatrixMode (GL_PROJECTION);
       glLoadIdentity ();
       gluPerspective(55.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
       glMatrixMode(GL_MODELVIEW);
       glLoadIdentity();
       gluLookAt(posx, posy, posz, focx, focy, focz, disx, disy, disz);
    }

    void keyboard (unsigned char key, int x, int y)
    {
        switch (key) {
            case 'd': //Seleciona lado direito
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
                gluLookAt(posx, posy, posz, focx, focy, focz, disx, disy, disz);
                break;
            case 'e': //Seleciona lado esquerdo
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
                gluLookAt(posx, posy, posz, focx, focy, focz, disx, disy, disz);
                break;
            default:
                break;
            }

       glutPostRedisplay();
    }

    int main(int argc, char** argv)
    {
       glutInit(&argc, argv);
       glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
       glutInitWindowSize(1280, 720); 
       glutInitWindowPosition(100, 100);
       glutCreateWindow("Projeto CG - 41406133 e 41404998");
       init();
       glutDisplayFunc(display);
       glutReshapeFunc(reshape);
       glutKeyboardFunc(keyboard);
       glutMainLoop();
       return 0;
    }