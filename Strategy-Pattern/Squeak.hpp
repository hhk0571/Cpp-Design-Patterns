#ifndef SQUEAK_HPP
#define SQUEAK_HPP

#include "QuackBehavior.hpp"

#include <iostream>

class Squeak : public QuackBehavior {
public:
    void quack() override {
        std::cout << "Squeak" << std::endl;
    }
};

#endif