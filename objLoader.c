    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/glut.h>

    static int shoulder = 0, elbow = 0, finger1 = 0, finger2 = 0, finger3 = 0, finger4 = 0, 
    finger5 = 0, finger6 = 0;

    void init(void) 
    {
      glClearColor (0.0, 0.0, 0.0, 0.0);
      glShadeModel (GL_FLAT);
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

       //Meio da Pista   
       glPushMatrix();
           glTranslatef(0.0, 0, 0.0);
           glScalef (0.1, 2.0, 2.0);
           glutWireCube (1.0);
       glPopMatrix();

       //Fim-Meio da Pista   
       glPushMatrix();
           glTranslatef(0.0, 1.40, 0.0);
           glScalef (0.1, 0.8, 2.6);
           glutWireCube (1.0);
       glPopMatrix();

       //Fim da Pista   
       glPushMatrix();
           glTranslatef(0.0, 2.05, 0.0);
           glScalef (0.1, 0.5, 1.4);
           glutWireCube (1.0);
       glPopMatrix();
    }

    void torreInicio(){
        glColor3f(1.0,0.0,0.0);

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

    void torreMeioInicioA(){
        glColor3f(1.0,0.0,1.0);

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

    void torreMeioInicioB(){
        glColor3f(1.0,0.0,1.0);

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

    void torreMeioA(){
        glColor3f(1.0,1.0,0.0);

        //Inicio da Base
        glPushMatrix();
            glTranslatef(0.1, -0.45, 0.0);
            glScalef(0.075, 0.075, 0.125);
            glutSolidCube(1.0);
        glPopMatrix();

        //Topo da Base
        glPushMatrix();
            glTranslatef(0.25, -0.45, 0.0);
            glScalef(0.25, 0.05, 0.05);
            glutSolidCube(1.0);
        glPopMatrix();

        //Torus da Torre
        glPushMatrix();
            glTranslatef(0.425, -0.45, 0.0);
            glutSolidSphere(0.15, 3, 3);
        glPopMatrix();
    }

    void torreMeioCentralA(){
        glColor3f(0.0,1.0,1.0);

        //Inicio da Base
        glPushMatrix();
            glTranslatef(0.1, 0, 0.4);
            glScalef(0.075, 0.075, 0.125);
            glutSolidCube(1.0);
        glPopMatrix();

        //Topo da Base
        glPushMatrix();
            glTranslatef(0.25, 0, 0.4);
            glScalef(0.25, 0.05, 0.05);
            glutSolidCube(1.0);
        glPopMatrix();

        //Torus da Torre
        glPushMatrix();
            glTranslatef(0.45, 0, 0.4);
            glutSolidSphere(0.1, 4, 4);
        glPopMatrix();
    }

    void torreMeioCentralB(){
        glColor3f(0.0,1.0,1.0);

        //Inicio da Base
        glPushMatrix();
            glTranslatef(0.1, 0, -0.4);
            glScalef(0.075, 0.075, 0.125);
            glutSolidCube(1.0);
        glPopMatrix();

        //Topo da Base
        glPushMatrix();
            glTranslatef(0.25, 0, -0.4);
            glScalef(0.25, 0.05, 0.05);
            glutSolidCube(1.0);
        glPopMatrix();

        //Torus da Torre
        glPushMatrix();
            glTranslatef(0.45, 0, -0.4);
            glutSolidSphere(0.1, 4, 4);
        glPopMatrix();
    }

    void torreMeioB(){
        glColor3f(1.0,1.0,0.0);

        //Inicio da Base
        glPushMatrix();
            glTranslatef(0.1, 0.45, 0.0);
            glScalef(0.075, 0.075, 0.125);
            glutSolidCube(1.0);
        glPopMatrix();

        //Topo da Base
        glPushMatrix();
            glTranslatef(0.25, 0.45, 0.0);
            glScalef(0.25, 0.05, 0.05);
            glutSolidCube(1.0);
        glPopMatrix();

        //Torus da Torre
        glPushMatrix();
            glTranslatef(0.425, 0.45, 0.0);
            glutSolidSphere(0.15, 3, 3);
        glPopMatrix();
    }

    void torreMeioFimA(){
        glColor3f(1.0,0.0,1.0);

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

    void torreMeioFimB(){
        glColor3f(1.0,0.0,1.0);

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

    void torreFim(){
        glColor3f(1.0,0.0,0.0);

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

    void display(void)
    {
       glClear (GL_COLOR_BUFFER_BIT);

       //Estrutura
       eixos();
       pista();

       //Torres (Ordem contrária para fazer sobreposição)
       torreFim();
       torreMeioFimB();
       torreMeioFimA();
       torreMeioB();
       torreMeioCentralB();
       torreMeioCentralA();
       torreMeioA();
       torreMeioInicioB();
       torreMeioInicioA();
       torreInicio();

       glutSwapBuffers();

    }

    void reshape (int w, int h)
    {
       glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
       glMatrixMode (GL_PROJECTION);
       glLoadIdentity ();
       gluPerspective(45.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
       glMatrixMode(GL_MODELVIEW);
       glLoadIdentity();
       gluLookAt(1.6f, -3.0f, -4.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f); //Câmera 3D legalzona
       //gluLookAt(1.4f, 0.0f, -5.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f); // Visão do lado
       //gluLookAt(1.4f, -5.0f, -0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f); // Visão do início
    }

    void keyboard (unsigned char key, int x, int y)
    {
       switch (key) {
          case 's':   //Exemplo
             shoulder = (shoulder + 5) % 360;
             glutPostRedisplay();
             break;
          default:
             break;
       }
    }

    int main(int argc, char** argv)
    {
       glutInit(&argc, argv);
       glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
       glutInitWindowSize(1280, 720); 
       glutInitWindowPosition(100, 100);
       glutCreateWindow(argv[0]);
       init();
       glutDisplayFunc(display); 
       glutReshapeFunc(reshape);
       glutKeyboardFunc(keyboard);
       glutMainLoop();
       return 0;
    }