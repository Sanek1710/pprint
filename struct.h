#ifndef STRUCT_H_
#define STRUCT_H_

#include "color.h"
#include "indentos.h"
#include "macro.h"

#define ENUM_MAP_MEMBER(Enum, member) Enum::member
#define ENUM_MAP_MEMBER_CASE(Enum, member) \
  case ENUM_MAP_MEMBER(Enum, member):      \
    return PP_STR(member);
#define ENUM_MAP_MEMBER_CASES(Enum, members...) \
  PP_FOREACH(PP_BIND(ENUM_MAP_MEMBER_CASE, Enum), members)
#define ENUM_STR(Enum, members...)          \
  auto enumStr(Enum e) {                    \
    switch (e) {                            \
      ENUM_MAP_MEMBER_CASES(Enum, members); \
      default:                              \
        return "";                          \
    }                                       \
  }

#define OS_MAP_INLINE_MEMBER(os, member) \
  << "." << fg::cyan << PP_STR(member) << fg::reset << ": " << member << "\n"
#define OS_MAP_INLINE_MEMBERS(os, members...) \
  os PP_FOREACH(PP_BIND(OS_MAP_INLINE_MEMBER, os), members)
#define INLINE_PRINT(Type, members...)                     \
  inline void print(std::ostream& os) const {              \
    os << fg::green << PP_STR(Type) << fg::reset << "{\n"; \
    {                                                      \
      indentos indos{os, true};                            \
      OS_MAP_INLINE_MEMBERS(os, members);                  \
    }                                                      \
    os << "}";                                             \
  }

#endif