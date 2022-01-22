#include <iostream>
using namespace std;

#ifndef Jeans_H
#define Jeans_H

enum class Jeans_colors {white, blue, brown, black};
enum class Jeans_sizes {small, medium, large, xlarge};

struct Jeans
{
    public:
        Jeans(); //default constructor: creates stress ball from random color and size
        Jeans(Jeans_colors c, Jeans_sizes s); //parameterized constructor: creates stress ball with given color and size
        Jeans_colors get_color() const { return color; } //getter function: returns color of stress ball
        Jeans_sizes get_size() const { return size; } //getter function: returns size of stress ball
        bool operator==(const Jeans& b) const; //overloaded operator: returns true if sb's color and size are the same as the stress ball this
    private:
        Jeans_colors color;
        Jeans_sizes size;
};

ostream& operator<<(ostream& o, const Jeans& sb); //overloaded operator: prints the stress ball as a pair of color and size, Ex. (red, small)

#endif