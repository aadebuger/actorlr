#include <string>
#include <iostream>

#include "caf/all.hpp"

using std::endl;
using std::string;
using std::cout;

using namespace caf;

behavior adder() { return {
    [](int x, int y) { return x + y;
       
    },
    [](double x, double y) {
        return x + y; }
}; }

int main()
{ actor_system_config cfg;
    actor_system sys{cfg};
// Create (spawn) our actor.
    auto a = sys.spawn(adder);
    // Send it a message.
    scoped_actor self{sys};
    self->send(a, 40, 2);
// Block and wait for reply.
    self->receive(
[](int result) {
cout << result << endl; // prints “42”
} );
}
