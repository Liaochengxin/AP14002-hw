#ifndef ESPRESSO_BASED_H
#define ESPRESSO_BASED_H
#include "ingredient.h"

class EspressoBased
{
public:
    //
    virtual std::string get_name() = 0;
    virtual double price() = 0;

    virtual void brew() = 0;

    std::vector<Ingredient*>& get_ingredients() {return ingredients;};
    //if define in protected, it only can be used in derived class
    ~EspressoBased();

protected:
    EspressoBased();
    EspressoBased(const EspressoBased& esp);
    void operator=(const EspressoBased& esp)=delete;

    std::vector<Ingredient*> ingredients;
    std::string name;

};
#endif // ESPRESSO_BASED_H
