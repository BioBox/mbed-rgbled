
#include <array>

#include <mbed.h>

// We can't use a valarray because it's inheritly dynamic (can't enforce a
// length), but array isn't desirable either because it doesn't support the
// numerics.
//
// Aggregate types cannot have base classes in C++, so I no other choice but to
// make my own class from scratch.
class RGBColor {
  public:
    using rgb_t = array<float, 3>;
    const float &red, &green, &blue;
    const float cap;
    RGBColor(rgb_t colors);
    RGBColor(rgb_t colors, float cap);
    float operator[](size_t n) const;
    RGBColor& operator*=(const float& f);
    RGBColor operator*(float f);
    // We want this class to be iterable, but iterating over user-defined
    // classes pre C++20 requires about 50 lines of abstruse boilerplate code.
    // Besides, we don't actually want to make a new iterator; we simply want
    // to wrap around our array.
    rgb_t::iterator begin() noexcept { return colors.begin(); }
    rgb_t::const_iterator cbegin() const noexcept { return colors.cbegin(); }
    rgb_t::iterator end() noexcept { return colors.end(); }
    rgb_t::const_iterator cend() const noexcept { return colors.cend(); }
  private:
    rgb_t colors;
    void ap_lim();
};

class RGBLed {
  using rgb_pwm = array<PwmOut, 3>;
  public:
    RGBLed(rgb_pwm pins);
    void write(const RGBColor& color);
    RGBLed operator=(const RGBColor& color);
  private:
    rgb_pwm pins;
};
 
