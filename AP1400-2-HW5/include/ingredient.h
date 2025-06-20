#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <cstddef>  // For size_t
#include <string>   // For std::string
class Ingredient
{
public:
    virtual double get_price_unit()=0;
    virtual size_t get_units()=0;
    virtual std::string get_name()=0;

    virtual double price()=0;
    

protected:
    Ingredient(double price_unit, size_t units, std::string name);

    double price_unit;
    size_t units;
    std::string name;
};

#endif // INGREDIENT_H
