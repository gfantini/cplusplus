#pragma once
#include "animal.hh"

/* access level
 * public:    public, protected of base class accessible, with same rights
 * protected: public, protected of base class become protected
 * private:   public, protected of base class become private, cannot be further inherited
 */
class Dog : public Animal{
public:
  Dog(std::string name);
  // overrides Animal::Speak()
  void Speak() override;
};
