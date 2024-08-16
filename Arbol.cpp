#include "Arbol.h"

void Arbol::DibujarArbol(float x, float y, float z)
{
    glPushMatrix(); //esfera
        glTranslatef(x, y, z);
        glutSolidSphere(0.5, 20, 20);
        glutSolidCylinder(0.25f, 1.0f, 20, 20);
    glPopMatrix();

}
