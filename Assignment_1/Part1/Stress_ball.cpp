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
    o << "(";

    switch(sb.get_color())
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

    switch(sb.get_size())
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

/*
enum Stress_ball_colors {red, blue, yellow, green};
enum Stress_ball_sizes {small, medium, large};
class Stress_ball
{
    public:
        Stress_ball()
        {
            color = Stress_ball_colors(rand() % 4);
            size = Stress_ball_sizes(rand() % 3);
        }

        Stress_ball(Stress_ball_colors c, Stress_ball_sizes s)
        {
            color = c;
            size = s;
        }

        Stress_ball_colors get_color() const
        {
            return color;
        }

        Stress_ball_sizes get_size() const
        {
            return size;
        }

        bool operator==(const Stress_ball& b) const
        {
            if((b.color == this->color) && (b.size == this->size))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

    private:
        Stress_ball_colors color;
        Stress_ball_sizes size;
};

ostream& operator<<(ostream& o, const Stress_ball& sb)
{
    o << "(";

    switch(sb.get_color())
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

    switch(sb.get_size())
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
}*/
