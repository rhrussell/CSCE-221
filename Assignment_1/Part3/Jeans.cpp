#include <iostream>
#include <cstdlib>
#include "Jeans.h"
using namespace std;

Jeans::Jeans()
{
    color = Jeans_colors(rand() % 4);
    size = Jeans_sizes(rand() % 4);
}

Jeans::Jeans(Jeans_colors c, Jeans_sizes s)
{
    color = c;
    size = s;
}

bool Jeans::operator==(const Jeans& j) const
{
    if((j.color == this->color) && (j.size == this->size))
    {
        return true;
    }
}

ostream& operator<<(ostream& o, const Jeans& j)
{
    int num;
    num = int(j.get_color());
    o << "(";

    switch(num)
    {
        case 0:
            o << "white";
            break;

        case 1:
            o << "blue";
            break;

        case 2:
            o << "brown";
            break;

        case 3:
            o << "black";
            break;
    }

    o << ", ";
    num = int(j.get_size());
    switch(num)
    {
        case 0:
            o << "small";
            break;

        case 1:
            o << "medium";
            break;
                
        case 2:
            o << "large";
            break;

        case 3:
            o << "xlarge";
            break;
    }

    o << ")";

    return o;
}