#pragma once
#include <tuple>
#include <type_traits>

namespace detail
{
    template <int Idx, class Tuple, class Visitor, std::enable_if_t<(Idx >= std::tuple_size<Tuple>::value) , bool> = true>
    void visit_tuple_impl(Tuple& tuple, int idx, const Visitor& visitor)
    {}
    
    template <int Idx, class Tuple, class Visitor, std::enable_if_t<(Idx < std::tuple_size<Tuple>::value) , bool> = true>
    void visit_tuple_impl(Tuple& tuple, int idx, const Visitor& visitor)
    {
        if (Idx == idx)
        {
            visitor(std::get<Idx>(tuple));
        }
        else
        {
            visit_tuple_impl<Idx+1>(tuple, idx, visitor);
        }
    }
}

template <class Tuple, class Visitor>
void visit_tuple(Tuple& tuple, int idx, const Visitor& visitor)
{
    detail::visit_tuple_impl<0>(tuple, idx, visitor);
}

