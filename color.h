#ifndef COLOR_H_
#define COLOR_H_

#define ESC "\e"
#define COLOR(code) ESC "[" #code "m"

struct fg {
  static constexpr auto reset = COLOR(0);
  static constexpr auto black = COLOR(30);
  static constexpr auto red = COLOR(31);
  static constexpr auto green = COLOR(32);
  static constexpr auto yellow = COLOR(33);
  static constexpr auto blue = COLOR(34);
  static constexpr auto magenta = COLOR(35);
  static constexpr auto cyan = COLOR(36);
  static constexpr auto white = COLOR(37);
  static constexpr auto bright_black = COLOR(90);
  static constexpr auto bright_red = COLOR(91);
  static constexpr auto bright_green = COLOR(92);
  static constexpr auto bright_yellow = COLOR(93);
  static constexpr auto bright_blue = COLOR(94);
  static constexpr auto bright_magenta = COLOR(95);
  static constexpr auto bright_cyan = COLOR(96);
  static constexpr auto bright_white = COLOR(97);
};

struct bg {
  static constexpr auto reset = COLOR(0);
  static constexpr auto black = COLOR(40);
  static constexpr auto red = COLOR(41);
  static constexpr auto green = COLOR(42);
  static constexpr auto yellow = COLOR(43);
  static constexpr auto blue = COLOR(44);
  static constexpr auto magenta = COLOR(45);
  static constexpr auto cyan = COLOR(46);
  static constexpr auto white = COLOR(47);
  static constexpr auto bright_black = COLOR(100);
  static constexpr auto bright_red = COLOR(101);
  static constexpr auto bright_green = COLOR(102);
  static constexpr auto bright_yellow = COLOR(103);
  static constexpr auto bright_blue = COLOR(104);
  static constexpr auto bright_magenta = COLOR(105);
  static constexpr auto bright_cyan = COLOR(106);
  static constexpr auto bright_white = COLOR(107);
};

#undef ESC
#undef COLOR

#endif