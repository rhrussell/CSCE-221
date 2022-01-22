#include <iostream>
using namespace std;

#ifndef Stress_ball_H
#define Stress_ball_H

enum Stress_ball_colors {red, blue, yellow, green};
enum Stress_ball_sizes {small, medium, large};

struct Stress_ball
{
    public:
        Stress_ball(); //default constructor: creates stress ball from random color and size
        Stress_ball(Stress_ball_colors c, Stress_ball_sizes s); //parameterized constructor: creates stress ball with given color and size
        Stress_ball_colors get_color() const { return color; } //getter function: returns color of stress ball
        Stress_ball_sizes get_size() const { return size; } //getter function: returns size of stress ball
        bool operator==(const Stress_ball& b) const; //overloaded operator: returns true if sb's color and size are the same as the stress ball this
    private:
        Stress_ball_colors color;
        Stress_ball_sizes size;
};

ostream& operator<<(ostream& o, const Stress_ball& sb); //overloaded operator: prints the stress ball as a pair of color and size, Ex. (red, small)

#endif