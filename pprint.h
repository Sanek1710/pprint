#ifndef PPRINT_H_
#define PPRINT_H_

#include <optional>
#include <tuple>

#include "struct.h"
#include "traits.h"

template <typename T>
std::enable_if_t<has_print_v<T> && !ostream_defined_v<T>, std::ostream&>
operator<<(std::ostream& os, const T& t) {
  t.print(os);
  return os;
}

template <typename T>
std::enable_if_t<std::is_enum_v<T> && has_enum_str<T>, std::ostream&>
operator<<(std::ostream& os, const T& t) {
  return os << enumStr(t);
}

template <typename Value>
struct value_wrap {
  const Value& val;
};
template <typename KeyValue>
struct key_value_wrap {
  const KeyValue& val;
};
template <typename Value>
std::ostream& operator<<(std::ostream& os, const value_wrap<Value>& v) {
  return os << v.val;
}
template <typename KeyValue>
std::ostream& operator<<(std::ostream& os, const key_value_wrap<KeyValue>& kv) {
  const auto& [k, v] = kv.val;
  return os << k << ": " << v;
}

template <typename Range, template <typename Value> typename ValueWrapper>
struct range_wrap {
  const Range& range;
  const char* start = "[";
  const char* end = "]";
  const char* sep = ", ";
};

template <typename Range, template <typename Value> typename ValueWrapper>
std::ostream& operator<<(std::ostream& os,
                         const range_wrap<Range, ValueWrapper>& r) {
  auto it = std::begin(r.range);
  using ValueWrapperT = ValueWrapper<decltype(*it)>;
  const auto end = std::end(r.range);

  if (it == end) return os << r.start << r.end;
  os << r.start << "\n";
  {
    indentos indos{os, true};
    os << ValueWrapperT{*it};
    for (++it; it != end; ++it) {
      os << r.sep << ValueWrapperT{*it};
    }
  }
  return os << "\n" << r.end;
}

template <typename T>
std::enable_if_t<!has_print_v<T> && is_iterable_v<T> && is_map_v<T> &&
                     !ostream_defined_v<T>,
                 std::ostream&>
operator<<(std::ostream& os, const T& t) {
  return os << range_wrap<T, key_value_wrap>{t, "{", "}", ",\n"};
}

template <typename T>
std::enable_if_t<!has_print_v<T> && is_iterable_v<T> && is_set_v<T> &&
                     !ostream_defined_v<T>,
                 std::ostream&>
operator<<(std::ostream& os, const T& t) {
  return os << range_wrap<T, value_wrap>{t, "{", "}", ", "};
}

template <typename T>
std::enable_if_t<!has_print_v<T> && is_iterable_v<T> && !is_map_v<T> &&
                     !is_set_v<T> && !ostream_defined_v<T>,
                 std::ostream&>
operator<<(std::ostream& os, const T& t) {
  return os << range_wrap<T, value_wrap>{t, "[", "]", ", "};
}

template <typename T1, typename T2>
std::enable_if_t<!ostream_defined_v<std::pair<T1, T2>>, std::ostream&>
operator<<(std::ostream& os, const std::pair<T1, T2>& t) {
  return os << "(" << t.first << ", " << t.second << ")";
}

template <typename... TS>
std::enable_if_t<!ostream_defined_v<std::tuple<TS...>>, std::ostream&>
operator<<(std::ostream& os, const std::tuple<TS...>& t) {
  os << "(";
  std::apply(
      [&](const auto&... args) {
        bool first = true;
        ((os << (first ? "" : ", ") << args, first = false), ...);
      },
      t);
  return os << ")";
}

template <typename T>
std::enable_if_t<!ostream_defined_v<std::optional<T>>, std::ostream&>
operator<<(std::ostream& os, const std::optional<T>& t) {
  if (t) return os << *t;
  return os << "<nullopt>";
}

#endif