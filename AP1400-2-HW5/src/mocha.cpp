#include "mocha.h"
#include <string>
#include <vector>
#include "sub_ingredients.h"
#include "espresso_based.h"

Mocha::Mocha() : espresso_based() {
  name = "Mocha";
  ingredient.push_back(new Espresso(2));
  ingredient.push_back(new Milk(2));
  ingredient.push_back(new MilkFoam(1));
  ingredient.push_back(new Chocolate(1));
}

Mocha::Mocha(const Mocha& mocha) : espresso_based(mocha){
  name = "mocha";
  for (const Ingredient& i : mocha.side_items){
    side_items.push_back(i->clone());
  }
}

Mocha::~Mocha(){
  for (Ingredient& i : mocha.side_items){
    delete i; 
  }
  side_items.clear();
}

void Mocha::operator=(const Mocha& mocha){
  if (&mocha != this){
    for (auto* ptr : ingredients){
      delete ptr;
    }
    for (auto* ptr : side_items){
      delete ptr;
    }
    
    ingredients.clear();
    side_items.clear();

    for (auto* ptr : mocha.ingredients){  
        ingredients.push_back(ptr->clone());
    }
    for (auto* ptr : mocha.side_items){  
        side_items.push_back(ptr->clone());
    }
  }
}

std::string Mocha::get_name(){
  return name;
}

double Mocha::price(){
  double p = 0;
  for (const Ingredient& i : ingredients){
    p += i->price();
  }
  for (const Ingredient& i : side_items){
    p += i->price()
  }

  return p;
}

void Mocha::brew(){
    std::cout << "making mocha..." << std::endl;
    for (const auto& i : ingredients) {
        std::cout << "adding " << i->get_name() << "..." << std::endl;
    }
    for (const auto& i : side_items) {
        std::cout << "adding " << i->get_name() << "..." << std::endl;
    }
    std::cout << "mocha finished" << std::endl;
}

void Mocha::add_side_item(Ingredient* side){
  side_items.push_back(side);
}

void Mocha::get_side_items(){
  return side_items;
}
