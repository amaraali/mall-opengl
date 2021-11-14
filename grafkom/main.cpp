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

    //KACA KIRI KOLAM RENANG
    for (int i = -50; i < -30; i += 4)
    {
        for (int j = -20; j < 70; j += 10)
        {
            int x = i + 4;
            int y = j + 10;
            int z = -50;
            glBegin(GL_QUADS);
            glColor4f(255 / 255.f, 251 / 255.f, 231 / 255.f, 0.5);
            glVertex3f(i, y, z);
            glVertex3f(x, y, z);
            glVertex3f(x, j, z);
            glVertex3f(i, j, z);
            glEnd();

            glBegin(GL_LINE_STRIP);
            glColor4f(0 / 255.f, 0 / 255.f, 0 / 255.f, 0.1);
            glVertex3f(i, y, z);
            glVertex3f(i, j, z);
            glVertex3f(x, j, z);
            glVertex3f(x, y, z);
            glEnd();
        }
    }

    //KACA KANAN KOLAM RENANG
    for (int i = -190; i < -170; i += 4)
    {
        for (int j = -20; j < 70; j += 10)
        {
            int x = i + 4;
            int y = j + 10;
            int z = -60;
            glBegin(GL_QUADS);
            glColor4f(255 / 255.f, 251 / 255.f, 231 / 255.f, 0.5);
            glVertex3f(i, y, z);
            glVertex3f(x, y, z);
            glVertex3f(x, j, z);
            glVertex3f(i, j, z);
            glEnd();

            glBegin(GL_LINE_STRIP);
            glColor4f(0 / 255.f, 0 / 255.f, 0 / 255.f, 0.1);
            glVertex3f(i, y, z);
            glVertex3f(i, j, z);
            glVertex3f(x, j, z);
            glVertex3f(x, y, z);
            glEnd();
        }
    }

    //KACA KANAN
    for (int i = -50; i < -30; i += 4)
    {
        for (int j = -20; j < 70; j += 10)
        {
            int x = i + 4;
            int y = j + 10;
            int z = 55;
            glBegin(GL_QUADS);
            glColor4f(255 / 255.f, 251 / 255.f, 231 / 255.f, 0.5);
            glVertex3f(i, y, z);
            glVertex3f(x, y, z);
            glVertex3f(x, j, z);
            glVertex3f(i, j, z);
            glEnd();

            glBegin(GL_LINE_STRIP);
            glColor4f(0 / 255.f, 0 / 255.f, 0 / 255.f, 0.1);
            glVertex3f(i, y, z);
            glVertex3f(i, j, z);
            glVertex3f(x, j, z);
            glVertex3f(x, y, z);
            glEnd();
        }
    }

    //KACA KIRI
    for (int i = -200; i < -180; i += 4)
    {
        for (int j = -20; j < 70; j += 10)
        {
            int x = i + 4;
            int y = j + 10;
            int z = 55;
            glBegin(GL_QUADS);
            glColor4f(255 / 255.f, 251 / 255.f, 231 / 255.f, 0.5);
            glVertex3f(i, y, z);
            glVertex3f(x, y, z);
            glVertex3f(x, j, z);
            glVertex3f(i, j, z);
            glEnd();

            glBegin(GL_LINE_STRIP);
            glColor4f(0 / 255.f, 0 / 255.f, 0 / 255.f, 0.1);
            glVertex3f(i, y, z);
            glVertex3f(i, j, z);
            glVertex3f(x, j, z);
            glVertex3f(x, y, z);
            glEnd();
        }
    }

    //matahari
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslated(0, 300, 0);
    glutSolidSphere(15, 20, 20);
    glPopMatrix();

    //papan iklan
    for (int i = 0; i < 2; i++) {
        glColor3f(221 / 255.f, 208 / 255.f, 141 / 255.f);
        glBegin(GL_QUADS); // banner
        glVertex3f(20 + (i * 40), -30, 55);
        glColor3f(214 / 255.f, 21 / 255.f, 15 / 255.f);
        glVertex3f(50 + (i * 40), -30, 55);
        glColor3f(21 / 255.f, 24 / 255.f, 0 / 255.f);
        glVertex3f(50 + (i * 40), 40, 55);
        glColor3f(231 / 255.f, 24 / 255.f, 536 / 255.f);
        glVertex3f(20 + (i * 40), 40, 55);
        glEnd();
        glColor3f(255 / 255.f, 255 / 255.f, 255 / 255.f);
        glBegin(GL_QUADS); // banner
        glVertex3f(20 + (i * 40), -30, 55);
        glVertex3f(20 + (i * 40), -30, 53);
        glVertex3f(20 + (i * 40), 40, 53);
        glVertex3f(20 + (i * 40), 40, 55);
        glEnd();
        glBegin(GL_QUADS); // banner
        glVertex3f(50 + (i * 40), -30, 55);
        glVertex3f(50 + (i * 40), -30, 53);
        glVertex3f(50 + (i * 40), 40, 53);
        glVertex3f(50 + (i * 40), 40, 55);
        glEnd();
        glBegin(GL_QUADS); // banner
        glVertex3f(20 + (i * 40), 40, 55);
        glVertex3f(20 + (i * 40), 40, 53);
        glVertex3f(50 + (i * 40), 40, 53);
        glVertex3f(50 + (i * 40), 40, 55);
        glEnd();
        glBegin(GL_QUADS); // banner
        glVertex3f(20 + (i * 40), -30, 55);
        glVertex3f(20 + (i * 40), -30, 53);
        glVertex3f(50 + (i * 40), -30, 53);
        glVertex3f(50 + (i * 40), -30, 55);
        glEnd();
    }
    for (int i = 0; i < 3; i++) {
        glColor3f(221 / 255.f, 208 / 255.f, 141 / 255.f);
        glBegin(GL_QUADS); // banner
        glVertex3f(-170 + (i * 40), -30, 58);
        glColor3f(25 / 255.f, 21 / 255.f, 15 / 255.f);
        glVertex3f(-140 + (i * 40), -30, 58);
        glColor3f(21 / 255.f, 24 / 255.f, 0 / 255.f);
        glVertex3f(-140 + (i * 40), 40, 58);
        glColor3f(341 / 255.f, 24 / 255.f, 12 / 255.f);
        glVertex3f(-170 + (i * 40), 40, 58);
        glEnd();
        glColor3f(255 / 255.f, 255 / 255.f, 255 / 255.f);
        glBegin(GL_QUADS); // banner
        glVertex3f(-170 + (i * 40), -30, 58);
        glVertex3f(-170 + (i * 40), -30, 56);
        glVertex3f(-170 + (i * 40), 40, 58);
        glVertex3f(-170 + (i * 40), 40, 56);
        glEnd();
        glBegin(GL_QUADS); // banner
        glVertex3f(-140 + (i * 40), -30, 58);
        glVertex3f(-140 + (i * 40), -30, 56);
        glVertex3f(-140 + (i * 40), 40, 56);
        glVertex3f(-140 + (i * 40), 40, 58);
        glEnd();
        glBegin(GL_QUADS); // banner
        glVertex3f(-170 + (i * 40), 40, 58);
        glVertex3f(-170 + (i * 40), 40, 56);
        glVertex3f(-140 + (i * 40), 40, 56);
        glVertex3f(-140 + (i * 40), 40, 58);
        glEnd();
        glBegin(GL_QUADS); // banner
        glVertex3f(-170 + (i * 40), -30, 58);
        glVertex3f(-170 + (i * 40), -30, 56);
        glVertex3f(-140 + (i * 40), -30, 56);
        glVertex3f(-140 + (i * 40), -30, 58);
        glEnd();
    }
    //pagar lantai 2 1
    glColor4f(215 / 255.f, 255 / 255.f, 253 / 255.f, 0.3);
    glBegin(GL_QUADS); // kaca
    glVertex3f(209, -10, 10);
    glVertex3f(160, -10, 10);
    glVertex3f(160, 0, 10);
    glVertex3f(209, 0, 10);
    glEnd();
    glColor3f(228 / 255.f, 228 / 255.f, 228 / 255.f);
    glBegin(GL_QUADS); // tiang pagar
    glVertex3f(159, -10, 10);
    glVertex3f(160, -10, 10);
    glVertex3f(160, 0, 10);
    glVertex3f(159, 0, 10);
    glVertex3f(210, -10, 10);
    glVertex3f(209, -10, 10);
    glVertex3f(209, 0, 10);
    glVertex3f(210, 0, 10);
    glEnd();

    //pagar lantai 2 2
    glColor4f(215 / 255.f, 255 / 255.f, 253 / 255.f, 0.3);
    glBegin(GL_QUADS); // kaca
    glVertex3f(160, -10, 10);
    glVertex3f(100, -10, 30);
    glVertex3f(100, 0, 30);
    glVertex3f(160, 0, 10);
    glVertex3f(90, 0, 30);
    glVertex3f(90, -10, 30);
    glVertex3f(100, -10, 30);
    glVertex3f(100, 0, 30);
    glEnd();
    glColor3f(228 / 255.f, 228 / 255.f, 228 / 255.f);
    glBegin(GL_QUADS); // tiang pagar
    glVertex3f(90, -10, 30);
    glVertex3f(89, -10, 30);
    glVertex3f(89, 0, 30);
    glVertex3f(90, 0, 30);
    glEnd();

    //pagar lantai 2 3
    glColor4f(215 / 255.f, 255 / 255.f, 253 / 255.f, 0.3);
    glBegin(GL_QUADS); // kaca
    glVertex3f(89, -10, 30);
    glVertex3f(10, -10, 10);
    glVertex3f(10, 0, 10);
    glVertex3f(89, 0, 30);
    glEnd();
    glColor3f(228 / 255.f, 228 / 255.f, 228 / 255.f);
    glBegin(GL_QUADS); // tiang pagar
    glVertex3f(10, -10, 10);
    glVertex3f(9, -10, 10);
    glVertex3f(9, 0, 10);
    glVertex3f(10, 0, 10);
    glEnd();

    //pagar lantai 2 4
    glColor4f(215 / 255.f, 255 / 255.f, 253 / 255.f, 0.3);
    glBegin(GL_QUADS); // kaca
    glVertex3f(9, -10, 10);
    glVertex3f(-100, -10, 30);
    glVertex3f(-100, 0, 30);
    glVertex3f(9, 0, 10);
    glEnd();
    glColor3f(228 / 255.f, 228 / 255.f, 228 / 255.f);
    glBegin(GL_QUADS); // tiang pagar
    glVertex3f(-100, -10, 30);
    glVertex3f(-101, -10, 30);
    glVertex3f(-101, 0, 30);
    glVertex3f(-100, 0, 30);
    glEnd();

    //pagar lantai 2 5
    glColor4f(215 / 255.f, 255 / 255.f, 253 / 255.f, 0.3);
    glBegin(GL_QUADS); // kaca
    glVertex3f(-101, -10, 30);
    glVertex3f(-160, -10, 20);
    glVertex3f(-160, 0, 20);
    glVertex3f(-101, 0, 30);
    glVertex3f(-160, -10, 20);
    glVertex3f(-160, 0, 20);
    glVertex3f(-189, 0, 20);
    glVertex3f(-189, -10, 20);
    glEnd();
    glColor3f(228 / 255.f, 228 / 255.f, 228 / 255.f);
    glBegin(GL_QUADS); // tiang pagar
    glVertex3f(-189, -10, 20);
    glVertex3f(-190, -10, 20);
    glVertex3f(-190, 0, 20);
    glVertex3f(-189, 0, 20);
    glEnd();

    //pagar lantai 2 6,7
    glColor4f(215 / 255.f, 255 / 255.f, 253 / 255.f, 0.3);
    glBegin(GL_QUADS); // kaca
    glVertex3f(-190, -10, 20);
    glVertex3f(-190, -10, -20);
    glVertex3f(-190, 0, -20);
    glVertex3f(-190, 0, 20);
    glEnd();
    glColor3f(228 / 255.f, 228 / 255.f, 228 / 255.f);
    glBegin(GL_QUADS); // tiang pagar
    glVertex3f(-189, -10, -20);
    glVertex3f(-190, -10, -20);
    glVertex3f(-190, 0, -20);
    glVertex3f(-189, 0, -20);

    //pagar lantai 2 8
    glColor4f(215 / 255.f, 255 / 255.f, 253 / 255.f, 0.3);
    glBegin(GL_QUADS); // kaca
    glVertex3f(-189, -10, -20);
    glVertex3f(-140, -10, -20);
    glVertex3f(-140, 0, -20);
    glVertex3f(-189, 0, -20);
    glVertex3f(-140, -10, -20);
    glVertex3f(-115, -10, -25);
    glVertex3f(-115, 0, -25);
    glVertex3f(-140, 0, -20);
    glVertex3f(-114, -10, -25);
    glVertex3f(-50, -10, -30);
    glVertex3f(-50, 0, -30);
    glVertex3f(-114, 0, -25);
    glEnd();
    glColor3f(228 / 255.f, 228 / 255.f, 228 / 255.f);
    glBegin(GL_QUADS); // tiang pagar
    glVertex3f(-50, -10, -30);
    glVertex3f(-49, -10, -30);
    glVertex3f(-49, 0, -30);
    glVertex3f(-50, 0, -30);
    glVertex3f(-140, -10, -20);
    glVertex3f(-139, -10, -20);
    glVertex3f(-139, 0, -20);
    glVertex3f(-140, 0, -20);
    glVertex3f(-115, -10, -25);
    glVertex3f(-114, -10, -25);
    glVertex3f(-114, 0, -25);
    glVertex3f(-115, 0, -25);
    glEnd();

    //pagar lantai 2 9
    glColor4f(215 / 255.f, 255 / 255.f, 253 / 255.f, 0.3);
    glBegin(GL_QUADS); // kaca
    glVertex3f(-49, -10, -30);
    glVertex3f(10, -10, -10);
    glVertex3f(10, 0, -10);
    glVertex3f(-49, 0, -30);
    glVertex3f(10, -10, -10);
    glVertex3f(75, -10, -25);
    glVertex3f(75, 0, -25);
    glVertex3f(10, 0, -10);
    glVertex3f(75, -10, -25);
    glVertex3f(119, -10, -25);
    glVertex3f(119, 0, -25);
    glVertex3f(75, 0, -25);
    glEnd();
    glColor3f(228 / 255.f, 228 / 255.f, 228 / 255.f);
    glBegin(GL_QUADS); // tiang pagar
    glVertex3f(10, -10, -10);
    glVertex3f(9, -10, -10);
    glVertex3f(9, 0, -10);
    glVertex3f(10, 0, -10);
    glVertex3f(75, -10, -25);
    glVertex3f(76, -10, -25);
    glVertex3f(76, 0, -25);
    glVertex3f(75, 0, -25);
    glVertex3f(119, -10, -25);
    glVertex3f(120, -10, -25);
    glVertex3f(120, 0, -25);
    glVertex3f(119, 0, -25);
    glEnd();

    //pagar lantai 2 10
    glColor4f(215 / 255.f, 255 / 255.f, 253 / 255.f, 0.3);
    glBegin(GL_QUADS); // kaca
    glVertex3f(120, -10, -25);
    glVertex3f(170, -10, -10);
    glVertex3f(170, 0, -10);
    glVertex3f(120, 0, -25);
    glVertex3f(170, -10, -10);
    glVertex3f(199, -10, -10);
    glVertex3f(199, 0, -10);
    glVertex3f(170, 0, -10);
    glEnd();
    glColor3f(228 / 255.f, 228 / 255.f, 228 / 255.f);
    glBegin(GL_QUADS); // tiang pagar
    glVertex3f(170, -10, -10);
    glVertex3f(171, -10, -10);
    glVertex3f(171, 0, -10);
    glVertex3f(170, 0, -10);
    glVertex3f(199, -10, -10);
    glVertex3f(200, -10, -10);
    glVertex3f(200, 0, -10);
    glVertex3f(199, 0, -10);
    glEnd();

    //pagar lantai 3 1
    glColor4f(215 / 255.f, 255 / 255.f, 253 / 255.f, 0.3);
    glBegin(GL_QUADS); // kaca
    glVertex3f(209, 30, 10);
    glVertex3f(160, 30, 10);
    glVertex3f(160, 40, 10);
    glVertex3f(209, 40, 10);
    glEnd();
    glColor3f(228 / 255.f, 228 / 255.f, 228 / 255.f);
    glBegin(GL_QUADS); // tiang pagar
    glVertex3f(159, 30, 10);
    glVertex3f(160, 30, 10);
    glVertex3f(160, 40, 10);
    glVertex3f(159, 40, 10);
    glVertex3f(210, 30, 10);
    glVertex3f(209, 30, 10);
    glVertex3f(209, 40, 10);
    glVertex3f(210, 40, 10);
    glEnd();

    //pagar lantai 3 2
    glColor4f(215 / 255.f, 255 / 255.f, 253 / 255.f, 0.3);
    glBegin(GL_QUADS); // kaca
    glVertex3f(160, 30, 10);
    glVertex3f(100, 30, 30);
    glVertex3f(100, 40, 30);
    glVertex3f(160, 40, 10);
    glVertex3f(90, 40, 30);
    glVertex3f(90, 30, 30);
    glVertex3f(100, 30, 30);
    glVertex3f(100, 40, 30);
    glEnd();
    glColor3f(228 / 255.f, 228 / 255.f, 228 / 255.f);
    glBegin(GL_QUADS); // tiang pagar
    glVertex3f(90, 30, 30);
    glVertex3f(89, 30, 30);
    glVertex3f(89, 40, 30);
    glVertex3f(90, 40, 30);
    glEnd();

    //pagar lantai 3 3
    glColor4f(215 / 255.f, 255 / 255.f, 253 / 255.f, 0.3);
    glBegin(GL_QUADS); // kaca
    glVertex3f(89, 30, 30);
    glVertex3f(10, 30, 10);
    glVertex3f(10, 40, 10);
    glVertex3f(89, 40, 30);
    glEnd();
    glColor3f(228 / 255.f, 228 / 255.f, 228 / 255.f);
    glBegin(GL_QUADS); // tiang pagar
    glVertex3f(10, 30, 10);
    glVertex3f(9, 30, 10);
    glVertex3f(9, 40, 10);
    glVertex3f(10, 40, 10);
    glEnd();

    //pagar lantai 3 4
    glColor4f(215 / 255.f, 255 / 255.f, 253 / 255.f, 0.3);
    glBegin(GL_QUADS); // kaca
    glVertex3f(9, 30, 10);
    glVertex3f(-100, 30, 30);
    glVertex3f(-100, 40, 30);
    glVertex3f(9, 40, 10);
    glEnd();
    glColor3f(228 / 255.f, 228 / 255.f, 228 / 255.f);
    glBegin(GL_QUADS); // tiang pagar
    glVertex3f(-100, 30, 30);
    glVertex3f(-101, 30, 30);
    glVertex3f(-101, 40, 30);
    glVertex3f(-100, 40, 30);
    glEnd();

    //pagar lantai 3 5
    glColor4f(215 / 255.f, 255 / 255.f, 253 / 255.f, 0.3);
    glBegin(GL_QUADS); // kaca
    glVertex3f(-101, 30, 30);
    glVertex3f(-160, 30, 20);
    glVertex3f(-160, 40, 20);
    glVertex3f(-101, 40, 30);
    glVertex3f(-160, 30, 20);
    glVertex3f(-160, 40, 20);
    glVertex3f(-189, 40, 20);
    glVertex3f(-189, 30, 20);
    glEnd();
    glColor3f(228 / 255.f, 228 / 255.f, 228 / 255.f);
    glBegin(GL_QUADS); // tiang pagar
    glVertex3f(-189, 30, 20);
    glVertex3f(-190, 30, 20);
    glVertex3f(-190, 40, 20);
    glVertex3f(-189, 40, 20);
    glEnd();

    //pagar lantai 3 6,7
    glColor4f(215 / 255.f, 255 / 255.f, 253 / 255.f, 0.3);
    glBegin(GL_QUADS); // kaca
    glVertex3f(-190, 30, 20);
    glVertex3f(-190, 30, -20);
    glVertex3f(-190, 40, -20);
    glVertex3f(-190, 40, 20);
    glEnd();
    glColor3f(228 / 255.f, 228 / 255.f, 228 / 255.f);
    glBegin(GL_QUADS); // tiang pagar
    glVertex3f(-189, 30, -20);
    glVertex3f(-190, 30, -20);
    glVertex3f(-190, 40, -20);
    glVertex3f(-189, 40, -20);

    //pagar lantai 3 8
    glColor4f(215 / 255.f, 255 / 255.f, 253 / 255.f, 0.3);
    glBegin(GL_QUADS); // kaca
    glVertex3f(-189, 30, -20);
    glVertex3f(-140, 30, -20);
    glVertex3f(-140, 40, -20);
    glVertex3f(-189, 40, -20);
    glVertex3f(-140, 30, -20);
    glVertex3f(-115, 30, -25);
    glVertex3f(-115, 40, -25);
    glVertex3f(-140, 40, -20);
    glVertex3f(-114, 30, -25);
    glVertex3f(-50, 30, -30);
    glVertex3f(-50, 40, -30);
    glVertex3f(-114, 40, -25);
    glEnd();
    glColor3f(228 / 255.f, 228 / 255.f, 228 / 255.f);
    glBegin(GL_QUADS); // tiang pagar
    glVertex3f(-50, 30, -30);
    glVertex3f(-49, 30, -30);
    glVertex3f(-49, 40, -30);
    glVertex3f(-50, 40, -30);
    glVertex3f(-140, 30, -20);
    glVertex3f(-139, 30, -20);
    glVertex3f(-139, 40, -20);
    glVertex3f(-140, 40, -20);
    glVertex3f(-115, 30, -25);
    glVertex3f(-114, 30, -25);
    glVertex3f(-114, 40, -25);
    glVertex3f(-115, 40, -25);
    glEnd();

    //pagar lantai 3 9
    glColor4f(215 / 255.f, 255 / 255.f, 253 / 255.f, 0.3);
    glBegin(GL_QUADS); // kaca
    glVertex3f(-49, 30, -30);
    glVertex3f(10, 30, -10);
    glVertex3f(10, 40, -10);
    glVertex3f(-49, 40, -30);
    glVertex3f(10, 30, -10);
    glVertex3f(75, 30, -25);
    glVertex3f(75, 40, -25);
    glVertex3f(10, 40, -10);
    glVertex3f(75, 30, -25);
    glVertex3f(119, 30, -25);
    glVertex3f(119, 40, -25);
    glVertex3f(75, 40, -25);
    glEnd();
    glColor3f(228 / 255.f, 228 / 255.f, 228 / 255.f);
    glBegin(GL_QUADS); // tiang pagar
    glVertex3f(10, 30, -10);
    glVertex3f(9, 30, -10);
    glVertex3f(9, 40, -10);
    glVertex3f(10, 40, -10);
    glVertex3f(75, 30, -25);
    glVertex3f(76, 30, -25);
    glVertex3f(76, 40, -25);
    glVertex3f(75, 40, -25);
    glVertex3f(119, 30, -25);
    glVertex3f(120, 30, -25);
    glVertex3f(120, 40, -25);
    glVertex3f(119, 40, -25);
    glEnd();

    //pagar lantai 3 10
    glColor4f(215 / 255.f, 255 / 255.f, 253 / 255.f, 0.3);
    glBegin(GL_QUADS); // kaca
    glVertex3f(120, 30, -25);
    glVertex3f(170, 30, -10);
    glVertex3f(170, 40, -10);
    glVertex3f(120, 40, -25);
    glVertex3f(170, 30, -10);
    glVertex3f(199, 30, -10);
    glVertex3f(199, 40, -10);
    glVertex3f(170, 40, -10);
    glEnd();
    glColor3f(228 / 255.f, 228 / 255.f, 228 / 255.f);
    glBegin(GL_QUADS); // tiang pagar
    glVertex3f(170, 30, -10);
    glVertex3f(171, 30, -10);
    glVertex3f(171, 40, -10);
    glVertex3f(170, 40, -10);
    glVertex3f(199, 30, -10);
    glVertex3f(200, 30, -10);
    glVertex3f(200, 40, -10);
    glVertex3f(199, 40, -10);
    glEnd();


    //LANTAI 2 DEKET deva
    //LANTAI 2 1
    glColor3f(255 / 255.f, 251 / 255.f, 231 / 255.f);
    glBegin(GL_POLYGON);
    glVertex3f(210, -10, 27);
    glVertex3f(210, -10, 10);
    glVertex3f(160, -10, 10);
    glVertex3f(160, -10, 40);
    glEnd();

    //LANTAI 2 2
    glColor3f(255 / 255.f, 251 / 255.f, 231 / 255.f);
    glBegin(GL_POLYGON);
    glVertex3f(160, -10, 40);
    glVertex3f(160, -10, 10);
    glVertex3f(100, -10, 30);
    glVertex3f(90, -10, 30);
    glVertex3f(90, -10, 50);
    glEnd();

    //LANTAI 2 3
    glColor3f(255 / 255.f, 251 / 255.f, 231 / 255.f);
    glBegin(GL_POLYGON);
    glVertex3f(90, -10, 50);
    glVertex3f(90, -10, 30);
    glVertex3f(10, -10, 10);
    glVertex3f(10, -10, 50);
    glEnd();

    //LANTAI 2 4
    glColor3f(255 / 255.f, 251 / 255.f, 231 / 255.f);
    glBegin(GL_POLYGON);
    glVertex3f(10, -10, 50);
    glVertex3f(10, -10, 10);
    glVertex3f(-100, -10, 30);
    glVertex3f(-100, -10, 55);
    glVertex3f(-50, -10, 55);
    glVertex3f(-30, -10, 50);
    glEnd();

    //LANTAI 2 5
    glColor3f(255 / 255.f, 251 / 255.f, 231 / 255.f);
    glBegin(GL_POLYGON);
    glVertex3f(-100, -10, 55);
    glVertex3f(-100, -10, 30);
    glVertex3f(-160, -10, 20);
    glVertex3f(-190, -10, 20);
    glVertex3f(-190, -10, 50);
    glEnd();

    //LANTAI 2 6
    glColor3f(255 / 255.f, 251 / 255.f, 231 / 255.f);
    glBegin(GL_POLYGON);
    glVertex3f(-190, -10, 50);
    glVertex3f(-190, -10, 0);
    glVertex3f(-280, -10, 0);
    glVertex3f(-280, -10, 40);
    glEnd();

    //LANTAI 2 JAUH
    //LANTAI 2 7
    glColor3f(255 / 255.f, 251 / 255.f, 231 / 255.f);
    glBegin(GL_POLYGON);
    glVertex3f(-280, -10, 0);
    glVertex3f(-190, -10, 0);
    glVertex3f(-190, -10, -60);
    glVertex3f(-280, -10, -60);
    glEnd();

    //LANTAI 2 8
    glColor3f(255 / 255.f, 251 / 255.f, 231 / 255.f);
    glBegin(GL_POLYGON);
    glVertex3f(-190, -10, -20);
    glVertex3f(-140, -10, -20);
    glVertex3f(-90, -10, -30);
    glVertex3f(-50, -10, -30);
    glVertex3f(-50, -10, -50);
    glVertex3f(-130, -10, -60);
    glVertex3f(-190, -10, -60);
    glEnd();

    //LANTAI 2 9
    glColor3f(255 / 255.f, 251 / 255.f, 231 / 255.f);
    glBegin(GL_POLYGON);
    glVertex3f(-50, -10, -30);
    glVertex3f(10, -10, -10);
    glVertex3f(90, -10, -30);
    glVertex3f(100, -10, -30);
    glVertex3f(120, -10, -25);
    glVertex3f(120, -10, -50);
    glVertex3f(-50, -10, -50);
    glEnd();

    //LANTAI 2 10
    glColor3f(255 / 255.f, 251 / 255.f, 231 / 255.f);
    glBegin(GL_POLYGON);
    glVertex3f(120, -10, -25);
    glVertex3f(170, -10, -10);
    glVertex3f(200, -10, -10);
    glVertex3f(200, -10, -30);
    glVertex3f(120, -10, -50);
    glEnd();

    //LANTAI 3 DEKET
    //LANTAI 3 1
    glColor3f(255 / 255.f, 251 / 255.f, 231 / 255.f);
    glBegin(GL_POLYGON);
    glVertex3f(210, 30, 27);
    glVertex3f(210, 30, 10);
    glVertex3f(160, 30, 10);
    glVertex3f(160, 30, 40);
    glEnd();

    //LANTAI 3 2
    glColor3f(255 / 255.f, 251 / 255.f, 231 / 255.f);
    glBegin(GL_POLYGON);
    glVertex3f(160, 30, 40);
    glVertex3f(160, 30, 10);
    glVertex3f(100, 30, 30);
    glVertex3f(90, 30, 30);
    glVertex3f(90, 30, 50);
    glEnd();

    //LANTAI 3 3
    glColor3f(255 / 255.f, 251 / 255.f, 231 / 255.f);
    glBegin(GL_POLYGON);
    glVertex3f(90, 30, 50);
    glVertex3f(90, 30, 30);
    glVertex3f(10, 30, 10);
    glVertex3f(10, 30, 50);
    glEnd();

    //LANTAI 3 4
    glColor3f(255 / 255.f, 251 / 255.f, 231 / 255.f);
    glBegin(GL_POLYGON);
    glVertex3f(10, 30, 50);
    glVertex3f(10, 30, 10);
    glVertex3f(-100, 30, 30);
    glVertex3f(-100, 30, 55);
    glVertex3f(-50, 30, 55);
    glVertex3f(-30, 30, 50);
    glEnd();

    //LANTAI 3 5
    glColor3f(255 / 255.f, 251 / 255.f, 231 / 255.f);
    glBegin(GL_POLYGON);
    glVertex3f(-100, 30, 55);
    glVertex3f(-100, 30, 30);
    glVertex3f(-160, 30, 20);
    glVertex3f(-190, 30, 20);
    glVertex3f(-190, 30, 50);
    glEnd();

    //LANTAI 3 6
    glColor3f(255 / 255.f, 251 / 255.f, 231 / 255.f);
    glBegin(GL_POLYGON);
    glVertex3f(-190, 30, 50);
    glVertex3f(-190, 30, 0);
    glVertex3f(-280, 30, 0);
    glVertex3f(-280, 30, 40);
    glEnd();

    //LANTAI 3 JAUH
    //LANTAI 3 7
    glColor3f(255 / 255.f, 251 / 255.f, 231 / 255.f);
    glBegin(GL_POLYGON);
    glVertex3f(-280, 30, 0);
    glVertex3f(-190, 30, 0);
    glVertex3f(-190, 30, -60);
    glVertex3f(-280, 30, -60);
    glEnd();

    //LANTAI 3 8
    glColor3f(255 / 255.f, 251 / 255.f, 231 / 255.f);
    glBegin(GL_POLYGON);
    glVertex3f(-190, 30, -20);
    glVertex3f(-140, 30, -20);
    glVertex3f(-90, 30, -30);
    glVertex3f(-50, 30, -30);
    glVertex3f(-50, 30, -50);
    glVertex3f(-130, 30, -60);
    glVertex3f(-190, 30, -60);
    glEnd();

    //LANTAI 3 9
    glColor3f(255 / 255.f, 251 / 255.f, 231 / 255.f);
    glBegin(GL_POLYGON);
    glVertex3f(-50, 30, -30);
    glVertex3f(10, 30, -10);
    glVertex3f(90, 30, -30);
    glVertex3f(100, 30, -30);
    glVertex3f(120, 30, -25);
    glVertex3f(120, 30, -50);
    glVertex3f(-50, 30, -50);
    glEnd();

    //LANTAI 3 10
    glColor3f(255 / 255.f, 251 / 255.f, 231 / 255.f);
    glBegin(GL_POLYGON);
    glVertex3f(120, 30, -25);
    glVertex3f(170, 30, -10);
    glVertex3f(200, 30, -10);
    glVertex3f(200, 30, -30);
    glVertex3f(120, 30, -50);
    glEnd();

    // jalan raya
    glColor3f(100 / 255.f, 100 / 255.f, 100 / 255.f);
    glBegin(GL_QUADS);
    glVertex3d(-350, -49.9, 75);
    glVertex3d(350, -49.9, 75);
    glVertex3d(350, -49.9, 150);
    glVertex3d(-350, -49.9, 150);
    glEnd();
    // bahu jalan
    glColor3f(210 / 255.f, 210 / 255.f, 210 / 255.f);
    glBegin(GL_QUADS);
    glVertex3d(-350, -45, 105);
    glVertex3d(350, -45, 105);
    glVertex3d(350, -45, 120);
    glVertex3d(-350, -45, 120);
    glEnd();
    glColor3f(58 / 255.f, 58 / 255.f, 58 / 255.f);
    glBegin(GL_QUADS);
    glVertex3d(-350, -49.9, 120);
    glVertex3d(350, -49.9, 120);
    glVertex3d(350, -45, 120);
    glVertex3d(-350, -45, 120);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3d(-350, -49.9, 105);
    glVertex3d(350, -49.9, 105);
    glVertex3d(350, -45, 105);
    glVertex3d(-350, -45, 105);
    glEnd();
    glColor3f(0.95, 0.95, 0.95);
    for (int i = 0; i < 70; i++) {
        glBegin(GL_QUADS);
        glVertex3d(-350 + (i * 10), -49.9, 120.1);
        glVertex3d(-345 + (i * 10), -49.9, 120.1);
        glVertex3d(-345 + (i * 10), -45, 120.1);
        glVertex3d(-350 + (i * 10), -45, 120.1);
        glEnd();
        glBegin(GL_QUADS);
        glVertex3d(-350 + (i * 10), -49.9, 104.9);
        glVertex3d(-345 + (i * 10), -49.9, 104.9);
        glVertex3d(-345 + (i * 10), -45, 104.9);
        glVertex3d(-350 + (i * 10), -45, 104.9);
        glEnd();
    }
    glColor3f(1, 1, 1);
    for (int i = 0; i < 35; i++) {
        glBegin(GL_QUADS);
        glVertex3d(-350 + (i * 20), -49.8, 135.5);
        glVertex3d(-340 + (i * 20), -49.8, 135.5);
        glVertex3d(-340 + (i * 20), -49.8, 134.5);
        glVertex3d(-350 + (i * 20), -49.8, 134.5);
        glEnd();
        glBegin(GL_QUADS);
        glVertex3d(-350 + (i * 20), -49.8, 90.5);
        glVertex3d(-340 + (i * 20), -49.8, 90.5);
        glVertex3d(-340 + (i * 20), -49.8, 89.5);
        glVertex3d(-350 + (i * 20), -49.8, 89.5);
        glEnd();
    }


    // PARKIRAN
    glColor3f(100 / 255.f, 100 / 255.f, 100 / 255.f);
    glBegin(GL_QUADS);
    glVertex3f(-350, -49.9, -140);
    glVertex3f(-280, -49.9, -140);
    glVertex3f(-280, -49.9, 75);
    glVertex3f(-350, -49.9, 75);
    glEnd();
    // GARIS PUTIH
    glColor3f(1, 1, 1);
    for (int i = 0; i < 2; i++) {
        glBegin(GL_QUADS); // kanan dan kiri
        glVertex3f(-349 + (i * 67), -49.8, -139);
        glVertex3f(-348 + (i * 67), -49.8, -139);
        glVertex3f(-348 + (i * 67), -49.8, 41);
        glVertex3f(-349 + (i * 67), -49.8, 41);
        glEnd();
    }
    glBegin(GL_QUADS); // belakang
    glVertex3f(-348, -49.8, -139);
    glVertex3f(-282, -49.8, -139);
    glVertex3f(-282, -49.8, -138);
    glVertex3f(-348, -49.8, -138);
    glEnd();
    glBegin(GL_QUADS); // depan
    glVertex3f(-348, -49.8, 40);
    glVertex3f(-302, -49.8, 40);
    glVertex3f(-302, -49.8, 41);
    glVertex3f(-348, -49.8, 41);
    glEnd();
    int jarak_parkir = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 11; j++) {
            glBegin(GL_QUADS); // garis parkir
            glVertex3f(-348 + (i * 26), -49.8, -124 + jarak_parkir);
            glVertex3f(-333 + (i * 26), -49.8, -124 + jarak_parkir);
            glVertex3f(-333 + (i * 26), -49.8, -123 + jarak_parkir);
            glVertex3f(-348 + (i * 26), -49.8, -123 + jarak_parkir);
            glEnd();
            jarak_parkir += 14;
        }
        jarak_parkir = 0;
    }

    // trotoar
    glColor3f(229 / 255.f, 148 / 255.f, 148 / 255.f);
    glBegin(GL_POLYGON);
    glVertex3f(-350, -49.8, 42);
    glVertex3f(-302, -49.8, 42);
    glVertex3f(-302, -49.8, 75);
    glVertex3f(-350, -49.8, 75);
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
