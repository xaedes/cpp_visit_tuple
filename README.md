# cpp_visit_tuple
Access tuple element with index specified at runtime by visiting it, for example with an auto lambda.

Example usage:
```cpp
auto tpl = std::make_tuple(1.0, std::string("foobar"), true);
std::cout << std::boolalpha;
for (int i=0; i<std::tuple_size<decltype(tpl)>::value; ++i)
{
    visit_tuple(tpl, i, [](auto& item){
        std::cout << item << std::endl;
    });
}
```

Will output:
```
1
foobar
true
```
