//----------------Interia.h------------------//
//  Author: Excilious
//  Date: 23/06/24
//  Abstraction: Header for inverse script.
//
//----------------------------------------------//

#ifndef INERTIA_HEADER
#define INERTIA_HEADER

class Intertia
{    
    public:
        Intertia();
        void PrecalculateIntertia();

    private:
        float Velocity = 0.0f;
};

#endif