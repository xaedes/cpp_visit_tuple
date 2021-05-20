#pragma once

#include <tuple>
#include <type_traits>

namespace detail
{
    template <class ReturnType, int Idx, class Tuple, class Visitor, std::enable_if_t<(Idx >= std::tuple_size<Tuple>::value) , bool> = true, std::enable_if_t<!std::is_void<ReturnType>::value, bool> = true>
    ReturnType visit_tuple_impl(Tuple& tuple, int idx, const Visitor& visitor)
    {
        ReturnType default_value;
        return default_value;
    }
    
    template <class ReturnType, int Idx, class Tuple, class Visitor, std::enable_if_t<(Idx < std::tuple_size<Tuple>::value) , bool> = true, std::enable_if_t<!std::is_void<ReturnType>::value, bool> = true>
    ReturnType visit_tuple_impl(Tuple& tuple, int idx, const Visitor& visitor)
    {
        if (Idx == idx)
        {
            return visitor(std::get<Idx>(tuple));
        }
        return visit_tuple_impl<ReturnType, Idx+1>(tuple, idx, visitor);
    }

    template <class ReturnType, int Idx, class Tuple, class Visitor, std::enable_if_t<(Idx >= std::tuple_size<Tuple>::value) , bool> = true, std::enable_if_t<std::is_void<ReturnType>::value, bool> = true>
    ReturnType visit_tuple_impl(Tuple& tuple, int idx, const Visitor& visitor)
    {
    }
    
    template <class ReturnType, int Idx, class Tuple, class Visitor, std::enable_if_t<(Idx < std::tuple_size<Tuple>::value) , bool> = true, std::enable_if_t<std::is_void<ReturnType>::value, bool> = true>
    ReturnType visit_tuple_impl(Tuple& tuple, int idx, const Visitor& visitor)
    {
        if (Idx == idx)
        {
            visitor(std::get<Idx>(tuple));
        }
        visit_tuple_impl<ReturnType, Idx+1>(tuple, idx, visitor);
    }


    template <int Idx, class Tuple, class AccumType, class Visitor, std::enable_if_t<(Idx >= std::tuple_size<Tuple>::value) , bool> = true>
    AccumType&& foldl_tuple_impl(Tuple& tuple, AccumType&& accum, const Visitor& visitor)
    {
        return std::forward<AccumType>(accum);
    }
    
    template <int Idx, class Tuple, class AccumType, class Visitor, std::enable_if_t<(Idx < std::tuple_size<Tuple>::value) , bool> = true>
    AccumType&& foldl_tuple_impl(Tuple& tuple, AccumType&& accum, const Visitor& visitor)
    {
        return std::forward<AccumType>(
            foldl_tuple_impl<Idx+1>(
                tuple, 
                std::forward<AccumType>(
                    visitor(
                        std::forward<AccumType>(accum), 
                        std::get<Idx>(tuple)
                    )
                ), visitor
            )
        );
    }
}

template <class ReturnType, class Tuple, class Visitor, std::enable_if_t<!std::is_void<ReturnType>::value, bool> = true>
ReturnType visit_tuple(Tuple& tuple, int idx, const Visitor& visitor)
{
    return detail::visit_tuple_impl<ReturnType, 0>(tuple, idx, visitor);
}

template <class ReturnType, class Tuple, class Visitor, std::enable_if_t<std::is_void<ReturnType>::value, bool> = true>
ReturnType visit_tuple(Tuple& tuple, int idx, const Visitor& visitor)
{
    detail::visit_tuple_impl<ReturnType, 0>(tuple, idx, visitor);
}

template <class Tuple, class AccumType, class Visitor>
AccumType&& foldl_tuple(Tuple& tuple, AccumType&& accum, const Visitor& visitor)
{
    return std::forward<AccumType>(
        detail::foldl_tuple_impl<0>(
            tuple, 
            std::forward<AccumType>(accum), 
            visitor
        )
    );
}
