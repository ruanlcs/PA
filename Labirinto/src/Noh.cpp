#include <cmath>
#include "Noh.h"
#include "coord.h"
#include <algorithm>

using namespace std;

Noh::Noh(){}

Noh::~Noh()
{
    //dtor
}

double Noh::custoPassado() const
{
    return g;
}

double Noh::custoFuturo() const
{
    return h;
}

double Noh::f() const
{
    return h + g;
}

bool Noh::operator==(const Noh& N) const
{
    return getPos() == N.getPos();
}

bool Noh::operator==(const Coord& C) const
{
    return getPos() == C;
}

bool Noh::operator!=(const Noh& N) const
{
    return !operator==(N);
}

bool Noh::operator!=(const Coord& C) const
{
    return !operator==(C);
}

bool Noh::operator<(const Noh& N) const
{
    return f() < N.f();
}

Coord Noh::operator+(const Coord& C)const
{
    return pos+ C;
}

Coord Noh::getPos()const
{
    return pos;
}

Coord Noh::getAnt()const
{
    return ant;
}

void Noh::setAntNoh(const Noh& N)
{
    ant = N.getPos();
}
void Noh::setG(const double& G)
{
    g = G;
}

void Noh::setH(const double& H)
{
    h = H;
}

void Noh::setPos(const Coord& C)
{
    pos = C;
}

void Noh::setAnt(const Coord& C)
{
    ant = C;
}

void Noh::heuristica(const Coord& Dest)
{
    double delta_x = abs(Dest.lin - pos.lin);
    double delta_y = abs(Dest.col - pos.col);

    h = sqrt(2) * min(delta_x, delta_y) + abs(delta_x - delta_y);

}
