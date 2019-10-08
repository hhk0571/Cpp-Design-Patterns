#include "MallardDuck.hpp"
#include "RedHeadDuck.hpp"
#include "DecoyDuck.hpp"
#include "RubberDuck.hpp"
#include "Duck.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class DuckFactory
{
public:
    DuckFactory()  = default;
    ~DuckFactory() = default;

    unique_ptr<Duck> newDuck(string&& duckName)
    {
        unique_ptr<Duck> duck = nullptr;

        if (duckName == "MallardDuck") {
            duck = make_unique<MallardDuck>();
        } else if (duckName == "RedHeadDuck") {
            duck = make_unique<RedHeadDuck>();
        } else if (duckName == "DecoyDuck") {
            duck = make_unique<DecoyDuck>();
        } else if (duckName == "RubberDuck") {
            duck = make_unique<RubberDuck>();
        }
        return duck;
    }
};



int main() {
    DuckFactory duckFactory;

    vector<unique_ptr<Duck>> ducks;
    ducks.push_back(duckFactory.newDuck("MallardDuck"));
    ducks.push_back(duckFactory.newDuck("RedHeadDuck"));
    ducks.push_back(duckFactory.newDuck("DecoyDuck"));
    ducks.push_back(duckFactory.newDuck("RubberDuck"));

    for (auto& duck:ducks) {
        duck->display();
        duck->swim();
        duck->performQuack();
        duck->performFly();
        std::cout << std::endl;
    }

    return 0;
}

