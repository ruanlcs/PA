#ifndef NOH_H
#define NOH_H

#include "coord.h"


class Noh
{
private:
    Coord pos,ant;
    double g,h;

public:
    Noh();
    ~Noh();

    double custoPassado() const;
    double custoFuturo() const;
    double f() const;

    bool operator==(const Noh& N) const;
    bool operator==(const Coord& C) const;
    bool operator!=(const Noh& N) const;
    bool operator!=(const Coord& C) const;
    bool operator<(const Noh& N) const;
    Coord operator+(const Coord& C)const;

    Coord getPos()const;
    Coord getAnt()const;

    void setG(const double& G);
    void setH(const double& H);
    void setPos(const Coord& C);
    void setAnt(const Coord& C);
    void setAntNoh(const Noh& N);

    void heuristica(const Coord& Dest);

};


#endif // NOH_H
