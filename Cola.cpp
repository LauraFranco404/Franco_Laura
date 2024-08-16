#include "Cola.h"
void Cola::dibujarCola(float angulo, int n, float x, float y, float z)
{


	glPushMatrix();
	glTranslatef(x, y, z);

	glTranslatef(-0.5, 0.0, 0.0);

	glRotatef((GLfloat)angulo, 0.0, 0.0, 1.0);

	glTranslatef(0.5, 0.0, 0.0); glPushMatrix();

	glScalef(1.0, 0.4, 1.0);

	glutWireCube(1.0);

	glPopMatrix();

	for (int i = 0; i < n; i++) {
		glTranslatef(0.5, 0.0, 0.0);

		glRotatef((GLfloat)angulo, 0.0, 0.0, 1.0);

		glTranslatef(0.5, 0.0, 0.0);

		glPushMatrix();

		glScalef(1.0, 0.4, 1.0);

		if (i % 2 == 0) {
			glutSolidCube(1.0);

		}
		else {
			glutWireCube(1.0);
		}
		glPopMatrix();

	}

		for (int i = 0; i < n + 3; i++) {
			glTranslatef(0.5, 0.0, 0.0);

			glRotatef(-(GLfloat)angulo, 0.0, 0.0, 1.0);

			glTranslatef(0.5, 0.0, 0.0);

			glPushMatrix();

			glScalef(1.0, 0.4, 1.0);

			if (i % 2 == 0) {
				glutSolidCube(1.0);

			}
			else {
				glutWireCube(1.0);

			}
			glPopMatrix();

		}
		for (int i = 0; i < 4; i++) {
			glTranslatef(0.5, 0.0, 0.0);

			glRotatef(-(GLfloat)angulo - 10, 0.0, 0.0, 1.0);

			glTranslatef(0.5, 0.0, 0.0);

			glPushMatrix();

			glScalef(1.0, 0.4, 1.0);
			if (i % 2 == 0) {
				glutSolidCube(1.0);

			}
			else {
				glutWireCube(1.0);

			}
			glPopMatrix();
		}
	glPopMatrix();

};