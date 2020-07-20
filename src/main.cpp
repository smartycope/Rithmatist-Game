// #include "Debug.hpp"
// Debug d;
// #include "Globals.cpp"
#include "Gui.hpp"

int main(){
    Gui gui("Hello World!", 485, 300);

    return 0;
}


// apparently
// _ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c@@GLIBCXX_3.4
// demangled means
// std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char)@GLIBCXX_3.4 (2)