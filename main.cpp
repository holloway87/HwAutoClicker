/**
 * @author Thomas Rudolph <me@holloway-web.de>
 * @since 2017.03.19
 */

#include <iostream>

#include "AutoClicker.hpp"

using namespace std;

int main() {
    AutoClicker program;

    if (0 != program.init()) {
        cerr << "could not open display" << endl;

        return 1;
    }
    program.loop();
    program.shutdown();

    return 0;
}
