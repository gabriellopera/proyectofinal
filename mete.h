#ifndef METE_H
#define METE_H


class mete
{
private:
    float PX; //pos en x
    float PY; //pos en y
    float mass; // masa del cuerpo
    float R; //radio del cuerpo
    float VX; //vel en x
    float VY; //vel en y
    float angulo; //angulo en el que va el cuerpo
    float AX; //acel en x
    float AY; //acel en y
    float G; //gravedad
    float K; //Resistencia del aire
    float e; //Coeficiente de restitucion
    float V; //vector de velocidad
    float dt; //delta tiempo
public:
    mete(float posX_,float posY_,float velX_,float velY_,float masa_,float radio_,float K_,float e_);
    ~mete();
    void actualizar();

    float getPX() const;

    float getPY() const;

    float getMass() const;
    float getR() const;
    float getVX() const;
    ;
    float getVY() const;

    float getE() const;
    void set_vel(float vx, float vy, float px, float py);

};

#endif // METE_H
