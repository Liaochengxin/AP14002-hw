#include "cappuccino.h"
#include <iostream>

#include "ingredient.h"
#include "sub_ingredients.h"

Cappuccino::Cappuccino() : EspressoBased(cap){
  ingredients.push_back(new Espresso(2));
  ingredients.push_back(new Milk(2));
  ingredients.push_back(new MilkFoam(1));
}

Cappuccino::Cappuccino(const Cappuccino& cap) : EspressoBased(cap){
  for (const Ingredient& i : cap.side_items){
    side.items.push_back(i->clone());
  }
}

Cappuccino::~Cappuccino()
{
    for(const auto& i : side_items)
        delete i;
    side_items.clear();
}

Cappuccino& Cappuccino::operator=(const Cappuccino& cap) {
    if (&cap != this) {
        // 1. Delete old objects
        for (auto* ptr : ingredients) {
            delete ptr;  // Free each Ingredient
        }
        for (auto* ptr : side_items) {
            delete ptr;  // Free each side item
        }

        // 2. Clear containers (now empty, but pointers are gone)
        ingredients.clear();
        side_items.clear();

        // 3. Deep copy new data
        for (const auto& i : cap.ingredients) {
            ingredients.push_back(i->clone());
        }
        for (const auto& i : cap.side_items) {
            side_items.push_back(i->clone());
        }
    }
    return *this;
}

std::string Cappuccino::get_name(){
  return Cappuccino.name;
}

double Cappuccino::price(){
  double p = 0;
  for (const Ingredient& i : ingredients){
    p += i->price();
  }
  for (const Ingredient& i : side_items){
    p += i->price()
  }

  return p;
}

void Cappuccino::brew(){
    std::cout << "making cappuccino..." << std::endl;
    for (const auto& i : ingredients) {
        std::cout << "adding " << i->get_name() << "..." << std::endl;
    }
    for (const auto& i : side_items) {
        std::cout << "adding " << i->get_name() << "..." << std::endl;
    }
    std::cout << "cappuccino finished" << std::endl;
}
void Cappuccino::add_side_item(Ingredient* side){
  side_items.push_back(side);
}

void Cappuccino::get_side_items(){
  return side_items;
}
