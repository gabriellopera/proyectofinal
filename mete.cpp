#include "mete.h"
#include <math.h>
#include <cmath>

mete::mete(float posX_, float posY_, float velX_, float velY_, float masa_, float radio_, float K_, float e_)
{
    PX = posX_; //pos en x
    PY = posY_; //pos en y
    mass = masa_; // masa del cuerpo
    R = radio_; //radio del cuerpo
    VX = velX_; //vel en x
    VY = velY_; //vel en y
    AX = 0; //acel en x
    AY = 0; //acel en y
    G = 10; //gravedad
    K = K_; //Resistencia del aire
    e = e_; //Coeficiente de restitucion
    V = 0; //vector de velocidad
    dt = 0.1; //delta tiempo


}

mete::~mete()
{

}

void mete::actualizar()
{
    //Ecuaciones del movimiento parabólico
    V = pow(((VX*VX)+(VY*VY)),(1/2)); //magnitud
    angulo = atan2(VY,VX); //angulo
    AX = -((K*(V*V)*(R*R))/mass)*cos(angulo); //acelaracion en X
    AY = (-((K*(V*V)*(R*R))/mass)*sin(angulo))-G; //acelaracion en Y
    PX = PX + ((VX*(dt)))+(((AX*(dt*dt)))/2); //posición en X
    PY = PY + ((VY*(dt)))+(((AY*(dt*dt)))/2); //posición en Y
    VX = VX + AX*dt; //velocidad en X
    VY = VY + AY*dt; //velocidad en Y
}

float mete::getPY() const
{
    return PY;
}


float mete::getMass() const
{
    return mass;
}

float mete::getR() const
{
    return R;
}

float mete::getVX() const
{
    return VX;
}

float mete::getVY() const
{
    return VY;
}


float mete::getE() const
{
    return e;
}

float mete::getPX() const
{
    return PX;
}

void mete::set_vel(float vx, float vy, float px, float py)
{
    //Con esta función se puede manipular el objeto con velocidad y posiciones nuevas
    VX = vx;
    VY = vy;
    PX = px;
    PY = py;
}
