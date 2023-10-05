#include "Denizen.h"

void Denizen::addInput(float InputX, float InputY)
{
    if (this->InputX != InputX)
        this->InputX += InputX;
    if (this->InputY != InputY)
        this->InputY += InputY;
}
void Denizen::move()
{
    this->sprite.move(InputX * currentSpeed, InputY * currentSpeed);
}