#include <iostream>
#include "visit_tuple.h"

int main() {
    
    auto tpl = std::make_tuple(1.0, std::string("foobar"), true);
    std::cout << std::boolalpha;
    for (int i=0; i<std::tuple_size<decltype(tpl)>::value; ++i)
    {
        visit_tuple(tpl, i, [](auto& item){
            std::cout << item << std::endl;
        });
    }
}
