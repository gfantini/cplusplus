#pragma once
#include "animal.hh"

/* access level
 * public:    public, protected of base class accessible, with same rights
 * protected: public, protected of base class become protected
 * private:   public, protected of base class become private, cannot be further inherited
 */
class Dog : public Animal{
public:
  // this syntax is an initializer list, and calls the base class ctor
  Dog(std::string name);
  // overrides Animal::Speak()
  void Speak() override;
};
