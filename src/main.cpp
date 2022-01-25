#include <iostream>

#include "state/state.hpp"

int main() {
    State<X, Y, Z> position(1, 2, 3);
    std::cout << "State with dimensions " << position.getDimension() << ": ";
    std::cout << position << std::endl;

    State<Roll, Pitch, Yaw> orientation(2.5 * M_PI, 2 * M_PI, 1.5 * M_PI);
    std::cout << "State with dimensions " << position.getDimension() << ": ";
    std::cout << orientation << std::endl;
}