#include "espresso_based.h"

EspressoBased::EspressoBased() : name("") {}

//copy
EspressoBased::EspressoBased(const EspressoBased& esp) : name(esp.name), ingredients(esp.ingredients){
}
 
EspressoBased::~EspressoBased() {
  for (auto& ingredient : ingredients){
    //here ingredient is a copy not the pointer itself
    delete ingredient;
  }
  ingredients.clear();
}

