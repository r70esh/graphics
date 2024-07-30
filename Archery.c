#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int windowWidth = 800;
int windowHeight = 600;
int arrows = 0;
double score = 0;

void display();
void drawDartboard();
void drawDart(float x, float y);
void keyboard(unsigned char key, int x, int y);
void throwDart(float angle);
void gameover();

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawDartboard();
    glFlush();
}

void drawDartboard() {
    int i;
    float radius[] = {150, 130, 110, 90, 70};
    float colors[][3] = {{1.0, 0.0, 0.0}, {1.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 1.0, 1.0}};

    for (i = 0; i < 5; i++) {
        glColor3fv(colors[i]);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0, 0);
        for (int j = 0; j <= 360; j++) {
            float angle = j * M_PI / 180.0f;
            glVertex2f(radius[i] * cos(angle), radius[i] * sin(angle));
        }
        glEnd();
    }
}

void drawDart(float x, float y) {
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x + 10, y + 10);
    glEnd();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
            break;
        case 32:
            if (arrows < 10) {
                throwDart(rand() % 360);
            } else {
                gameover();
            }
            break;
    }
}

void throwDart(float angle) {
    float x = 150 * cos(angle * M_PI / 180.0f);
    float y = 150 * sin(angle * M_PI / 180.0f);
    float dist = sqrt(x * x + y * y);

    if (dist <= 70) {
        score += 100;
    } else if (dist <= 90) {
        score += 70;
    } else if (dist <= 110) {
        score += 50;
    } else if (dist <= 130) {
        score += 40;
    } else if (dist <= 150) {
        score += 35;
    }

    arrows++;
    glClear(GL_COLOR_BUFFER_BIT);
    drawDartboard();
    drawDart(x, y);
    glFlush();
}

void gameover() {
    printf("Game Over!\nYour score is: %.0f\n", score);
    arrows = 0;
    score = 0;
    glClear(GL_COLOR_BUFFER_BIT);
    drawDartboard();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Dartboard Game");
    gluOrtho2D(-windowWidth / 2, windowWidth / 2, -windowHeight / 2, windowHeight / 2);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
