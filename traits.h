#ifndef TRAITS_H_
#define TRAITS_H_

#include <ostream>
#include <type_traits>

namespace details {

template <typename T, typename = void>
struct has_print : std::false_type {};

template <typename T>
struct has_print<T, std::void_t<decltype(std::declval<const T&>().print(
                        std::declval<std::ostream&>()))>> : std::true_type {};

template <typename T, typename = void>
struct has_enum_str : std::false_type {};

template <typename T>
struct has_enum_str<T, std::void_t<decltype(enumStr(std::declval<const T&>()))>>
    : std::true_type {};

template <typename T, typename = void>
struct is_iterable : std::false_type {};

template <typename T>
struct is_iterable<T,
                   std::void_t<decltype(std::begin(std::declval<const T&>()) !=
                                        std::end(std::declval<const T&>()))>>
    : std::true_type {};

template <typename T, typename = void>
struct has_key_type : std::false_type {};

template <typename T>
struct has_key_type<T, std::void_t<typename T::key_type>> : std::true_type {};

template <typename T, typename = void>
struct has_mapped_type : std::false_type {};

template <typename T>
struct has_mapped_type<T, std::void_t<typename T::mapped_type>>
    : std::true_type {};

template <typename T>
struct is_map {
  static constexpr bool value =
      has_key_type<T>::value && has_mapped_type<T>::value;
};

template <typename T>
struct is_set {
  static constexpr bool value =
      has_key_type<T>::value && !has_mapped_type<T>::value;
};

template <typename T, typename = void>
struct ostream_defined : std::false_type {};

template <typename T>
struct ostream_defined<
    T, std::void_t<decltype(std::declval<std::ostream>() << std::declval<T>())>>
    : std::true_type {};

}  // namespace details

template <typename T>
constexpr bool has_print_v = details::has_print<T>::value;

template <typename T>
constexpr bool has_enum_str = details::has_enum_str<T>::value;

template <typename T>
constexpr bool is_iterable_v = details::is_iterable<T>::value;

template <typename T>
constexpr bool is_map_v = details::is_map<T>::value;
template <typename T>
constexpr bool is_set_v = details::is_set<T>::value;

template <typename T>
constexpr bool ostream_defined_v = details::ostream_defined<T>::value;

#endif