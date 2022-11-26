
#include <algorithm>

#include "rgbled.hpp"

void RGBColor::ap_lim() {
  for_each(colors.begin(), colors.end(), [this](float& f){ f = min(f, this->cap); });
}

RGBColor::RGBColor(rgb_t colors, float cap)
  // More elegant in C++17
  : red{colors[0]}, green{colors[1]}, blue{colors[2]},
    cap{cap} { ap_lim(); }
RGBColor::RGBColor(rgb_t colors) : RGBColor(colors, 1.0f) {}

float RGBColor::operator[](size_t n) const { return colors[n]; }

RGBColor& RGBColor::operator*=(const float& f) {
  for_each(colors.begin(), colors.end(), [f](float& g){ g *= f; });
  ap_lim();
  return *this;
}

RGBColor RGBColor::operator*(float f) {
  RGBColor result{*this};
  result *= f;
  return result;
}

RGBLed::RGBLed (RGBLed::rgb_pwm pins)
    : pins{pins} {
  // 50Hz PWM clock default a bit too low, go to 2000Hz (less flicker)
  for_each(begin(pins), end(pins), [](PwmOut& p){ p.period(0.0005); });
}
 
void RGBLed::write(const RGBColor& color) {
  // I really want to do "pins = color" or "pins = color.items()" but C++ isn't
  // smart enough to delegate the assignment. (at least <array> isn't)
  for (size_t i = 0; i < pins.size(); i++) {
    pins[i] = color[i];
  }
}

RGBLed RGBLed::operator=(const RGBColor& color) {
  write(color);
  return *this;
}
