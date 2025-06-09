#include "espresso_based.h"

EspressoBased::EspressoBased() : name("") {}

//copy
EspressoBased::EspressoBased(const EspressoBased& esp) : name(esp.name){
  for (const auto& ingredient : esp.ingredients){
    ingredients.push_back(ingredient->clone());
}
 
EspressoBased::~EspressoBased(){
  for (auto& ingredient : esp.ingredients){
    //here ingredient is a copy not the pointer itself
    delete ingredient;
  }
  ingredients.clear();
}

