#include <iostream>
#include <cstdlib>
#include "Stress_ball.h"
using namespace std;

Stress_ball::Stress_ball()
{
    color = Stress_ball_colors(rand() % 4);
    size = Stress_ball_sizes(rand() % 3);
}

Stress_ball::Stress_ball(Stress_ball_colors c, Stress_ball_sizes s)
{
    color = c;
    size = s;
}

bool Stress_ball::operator==(const Stress_ball& b) const
{
    if((b.color == this->color) && (b.size == this->size))
    {
        return true;
    }
}

ostream& operator<<(ostream& o, const Stress_ball& sb)
{
    int num;
    num = int(sb.get_color());
    o << "(";

    switch(num)
    {
        case 0:
            o << "red";
            break;

        case 1:
            o << "blue";
            break;

        case 2:
            o << "yellow";
            break;

        case 3:
            o << "green";
            break;
    }

    o << ", ";
    num = int(sb.get_size());
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
    }

    o << ")";

    return o;
}
