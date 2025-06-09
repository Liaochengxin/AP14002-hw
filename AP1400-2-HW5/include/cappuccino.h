#ifndef CAPPUCCINO
#define CAPPUCCINO

#include <string>
#include <vector>
#include "sub_ingredients.h"
#include "espresso_based.h"

class cappuccino : public espressobased
{
public:
    Cappuccino();
    Cappuccino(const Cappuccino& cap);

	  ~Cappuccino() override;
    void operator=(const Cappuccino& cap);

    std::string get_name() override;
    double price() override;
    void brew() override;

    void add_side_item(Ingredient* side);
    std::vector<Ingredient*>& get_side_items();

private:
    std::vector<Ingredient*> side_items;

};
#endif // CAPPUCCINO
