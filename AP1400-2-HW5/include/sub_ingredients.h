#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H

#include "Ingredient.h"  // Assuming Ingredient base class exists

#define DEFINE_INGREDIENT(ClassName, Price, IngredientName) \
class ClassName : public Ingredient { \
public: \
    explicit ClassName(size_t units) : Ingredient(Price, units, IngredientName) {} \
};

// Define ingredients
DEFINE_INGREDIENT(Cinnamon, 5, "Cinnamon")
DEFINE_INGREDIENT(Chocolate, 5, "Chocolate")
DEFINE_INGREDIENT(Sugar, 1, "Sugar")
DEFINE_INGREDIENT(Cookie, 10, "Cookie")
DEFINE_INGREDIENT(Espresso, 15, "Espresso")
DEFINE_INGREDIENT(Milk, 10, "Milk")
DEFINE_INGREDIENT(MilkFoam, 5, "MilkFoam")
DEFINE_INGREDIENT(Water, 1, "Water")

#undef DEFINE_INGREDIENT  // Clean up macro after use

#endif // SUB_INGREDIENTS_H
