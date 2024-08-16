#include "Player.h"


void Player::Move(float amount_x, float amount_y)
{
	posX += amount_x* PLAYER_SPEED;
	posY += amount_y* PLAYER_SPEED;
    printPos();
}


void Player::Dibujar()
{
    glPushMatrix(); 
    glTranslatef(posX, posY, Z_POS);
    glutSolidSphere(0.5, 20, 20);
    glPopMatrix();

}

void Player::printPos()
{
    std::cout << "Pos x: " << posX << " Pos y: " << posY << std::endl;
}
