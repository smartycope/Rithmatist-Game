// #include "Gui.hpp"
#include "Nuklear.hpp"
//TODO This is very, very nasty. Please learn how inheritance works better so you can fix this.
#define Gui Nuklear

int main(){
    Gui gui("Hello World!", 485 * 1.5, 300 * 1.5);

    return 0;
}
