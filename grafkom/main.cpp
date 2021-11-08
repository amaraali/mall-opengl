// Kelompok 10 GRAFKOM Senin

// AMARA NUR ALI 4611419089
// GHAMAL FEBRYANTO 4611419074
// BHARAKA ZULFA M 4611419062

#include <windows.h>
#include <stdlib.h>
#include <gl/glut.h>
#include <vector>
#include <cmath>

void init(void);
void tampil(void);
void ukuran(int, int);

// mouse
void mouse(int button, int state, int x, int y);
void mouseMotion(int x, int y);

// keyboard
void keyboard(unsigned char, int, int);

float xrot = 0.0f;
float yrot = 0.0f;
float xdiff = 0.0f;
float ydiff = 0.0f;
bool mouseDown = false;
int is_depth;

// variabel untuk animasi
float y_pos = 0.0f;
float x_pos = 0.0f;
float x_awan = 0.0f;

// delta : perubahan per frame
float delta = 0.5f;
float delta_awan = 1.5f;

bool is_naik = true;
bool is_kiri = true;
bool is_kanan = true;

void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 30, timer, 0);

    // awan
    if (x_awan < 160 && is_kanan) x_awan += delta_awan;
    else is_kanan = false;

    if (x_awan > -160 && !is_kanan) x_awan -= delta_awan;
    else is_kanan = true;
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 700);
    glutInitWindowPosition(250, 80);
    glutCreateWindow("KELOMPOK 10");
    init();

    // animasi
    glutTimerFunc(0, timer, 0);

    // transparan
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutDisplayFunc(tampil);
    glutReshapeFunc(ukuran);

    glutKeyboardFunc(keyboard);

    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);

    glutMainLoop();
    return 0;
}

void init(void) {
    glClearColor(62 / 255.f, 185 / 255.f, 255 / 255.f, 1.0);
    glMatrixMode(GL_PROJECTION);

    // lighting
    // glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);

    glEnable(GL_DEPTH_TEST);
    is_depth = 1;

    glLineWidth(6.0);

    glMatrixMode(GL_MODELVIEW);
}

void awan(float x1, float x2, float y1, float y2, float z) {
    float batas = x1 + 20;
    for (float i = x1; i <= batas; i += 10) {
        glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslated(i, y1, z);
        glutSolidSphere(10, 20, 20);
        glPopMatrix();
    }
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslated(x2, y2, z);
    glutSolidSphere(10, 20, 20);
    glPopMatrix();
}

void tampil(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // mouse
    glPushMatrix();
    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);

    //pondasi
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glVertex3f(-350, -50, -140);
    glVertex3f(350, -50, -140);
    glVertex3f(350, -50, 100);
    glVertex3f(-350, -50, 100);
    glEnd();

    // pondasi bawah
    glColor3f(86 / 255.f, 46 / 255.f, 0 / 255.f);
    glBegin(GL_QUADS);
    glVertex3f(-350, -70, -140);
    glVertex3f(350, -70, -140);
    glVertex3f(350, -70, 150);
    glVertex3f(-350, -70, 150);
    glEnd();

    // pondasi tepi
    glColor3f(115 / 255.f, 62 / 255.f, 0 / 255.f);
    glBegin(GL_QUADS); // depan
    glVertex3f(-350, -50, 150);
    glVertex3f(350, -50, 150);
    glVertex3f(350, -70, 150);
    glVertex3f(-350, -70, 150);
    glEnd();
    glBegin(GL_QUADS); // belakang
    glVertex3f(-350, -50, -140);
    glVertex3f(350, -50, -140);
    glVertex3f(350, -70, -140);
    glVertex3f(-350, -70, -140);
    glEnd();
    glColor3f(105 / 255.f, 55 / 255.f, 0 / 255.f);
    glBegin(GL_QUADS); // kiri
    glVertex3f(-350, -50, -140);
    glVertex3f(-350, -50, 150);
    glVertex3f(-350, -70, 150);
    glVertex3f(-350, -70, -140);
    glEnd();
    glBegin(GL_QUADS); // kanan
    glVertex3f(350, -50, -140);
    glVertex3f(350, -50, 150);
    glVertex3f(350, -70, 150);
    glVertex3f(350, -70, -140);
    glEnd();

    //dinding depans
    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_QUADS);
    glVertex3f(120, -50, 50);
    glVertex3f(220, -50, 25);
    glVertex3f(220, 70, 25);
    glVertex3f(120, 70, 50);
    glEnd();
    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_QUADS);
    glVertex3f(-30, -50, 55);
    glVertex3f(120, -50, 50);
    glVertex3f(120, 70, 50);
    glVertex3f(-30, 70, 55);
    glEnd();
    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_QUADS);
    glVertex3f(-280, -50, -60);
    glVertex3f(-190, -50, -60);
    glVertex3f(-190, 70, -60);
    glVertex3f(-280, 70, -60);
    glEnd();
    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_QUADS);
    glVertex3f(-170, -50, -60);
    glVertex3f(-130, -50, -60);
    glVertex3f(-130, 70, -60);
    glVertex3f(-170, 70, -60);
    glEnd();

    // dinding pele
    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_QUADS);
    glVertex3f(-280, -50, 40);
    glVertex3f(-200, -50, 55);
    glVertex3f(-200, 70, 55);
    glVertex3f(-280, 70, 40);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3f(-180, -50, 55);
    glVertex3f(-50, -50, 55);
    glVertex3f(-50, 70, 55);
    glVertex3f(-180, 70, 55);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3f(-280, -50, 40);
    glVertex3f(-280, -50, -60);
    glVertex3f(-280, 70, -60);
    glVertex3f(-280, 70, 40);
    glEnd();

    // dinding jek
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.8, 0.8);
    glVertex3f(220, -50, -30);
    glVertex3f(120, -50, -50);
    glVertex3f(120, 70, -50);
    glVertex3f(220, 70, -30);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.8, 0.8);
    glVertex3f(120, -50, -50);
    glVertex3f(-30, -50, -50);
    glVertex3f(-30, 70, -50);
    glVertex3f(120, 70, -50);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.8, 0.8);
    glVertex3f(-50, -50, -50);
    glVertex3f(-130, -50, -60);
    glVertex3f(-130, 70, -60);
    glVertex3f(-50, 70, -50);
    glEnd();

    // atap
    glColor3f(0.85, 0.85, 0.85);
    glBegin(GL_POLYGON);
    glVertex3d(220, 70, 25);
    glVertex3d(120, 70, 50);
    glVertex3d(-30, 70, 55);
    glVertex3d(-50, 70, 55);
    glVertex3d(-180, 70, 55);
    glVertex3d(-200, 70, 55);
    glVertex3d(-280, 70, 40);
    glVertex3d(-280, 70, -60);
    glVertex3d(-130, 70, -60);
    glVertex3d(-50, 70, -50);
    glVertex3d(120, 70, -50);
    glVertex3d(220, 70, -30);
    glEnd();

    // lantai
    glColor3f(0.85, 0.85, 0.85);
    glBegin(GL_POLYGON);
    glVertex3f(220, -49.8, 25);
    glVertex3f(120, -49.8, 50);
    glVertex3f(-30, -49.8, 55);
    glVertex3f(-50, -49.8, 55);
    glVertex3f(-180, -49.8, 55);
    glVertex3f(-200, -49.8, 55);
    glVertex3f(-280, -49.8, 40);
    glVertex3f(-280, -49.8, -60);
    glVertex3f(-130, -49.8, -60);
    glVertex3f(-50, -49.8, -50);
    glVertex3f(120, -49.8, -50);
    glVertex3f(220, -49.8, -30);
    glEnd();

    // trotoar
    glColor3f(229 / 255.f, 148 / 255.f, 148 / 255.f);
    glBegin(GL_POLYGON);
    glVertex3f(-280, -49.9, -80);
    glVertex3f(350, -49.9, -80);
    glVertex3f(350, -49.9, 75);
    glVertex3f(-280, -49.9, 75);
    glEnd();

    // rumput
    glColor3f(15 / 255.f, 154 / 255.f, 3 / 255.f);
    glBegin(GL_POLYGON);
    glVertex3f(-280, -49.9, -140);
    glVertex3f(350, -49.9, -140);
    glVertex3f(350, -49.9, -80);
    glVertex3f(-280, -49.9, -80);
    glEnd();

    // kolam
    glColor3f(22 / 255.f, 111 / 255.f, 194 / 255.f);
    glBegin(GL_POLYGON);
    glVertex3f(-120, -49.8, -110);
    glVertex3f(-75, -49.8, -125);
    glVertex3f(-30, -49.8, -130);
    glVertex3f(30, -49.8, -130);
    glVertex3f(75, -49.8, -125);
    glVertex3f(120, -49.8, -110);
    glVertex3f(75, -49.8, -95);
    glVertex3f(30, -49.8, -90);
    glVertex3f(-30, -49.8, -90);
    glVertex3f(-75, -49.8, -95);
    glEnd();



    //AWANz
    glPushMatrix();
    glTranslatef(x_awan, 0, 0);
    awan(90, 100, 110, 120, -60);
    awan(-170, -160, 130, 140, -90);
    awan(0, 10, 150, 160, -80);
    awan(-10, 0, 140, 150, 80);
    awan(-200, -190, 120, 130, 50);
    awan(150, 160, 140, 150, 0);
    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
}

void idle() {
    if (!mouseDown) {
        xrot += 0.3f;
        yrot += 0.4f;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
    case 'W':
        glTranslatef(0.0, 0.0, 3.0);
        break;
    case 'd':
    case 'D':
        glTranslatef(3.0, 0.0, 0.0);
        break;
    case 's':
    case 'S':
        glTranslatef(0.0, 0.0, -3.0);
        break;
    case 'a':
    case 'A':
        glTranslatef(-3.0, 0.0, 0.0);
        break;
    }
    tampil();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouseDown = true;
        xdiff = x - yrot;
        ydiff = -y + xrot;
    }
    else {
        mouseDown = false;
    }
}

void mouseMotion(int x, int y) {
    if (mouseDown) {
        yrot = x - xdiff;
        xrot = y + ydiff;

        glutPostRedisplay();
    }
}

void ukuran(int lebar, int tinggi) {
    if (tinggi == 0) tinggi = 1;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(130.0, lebar / tinggi, 5.0, 1000.0);
    glTranslatef(0.0, -5.0, -150.0);
    glMatrixMode(GL_MODELVIEW);
}
