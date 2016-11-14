#ifndef UTILS_H_
#define UTILS_H_

#define ArrayCount(a) sizeof(a) / sizeof(a[0])

namespace utils
{
inline float lerp(float start, float end, float t)
{
    return (1 - t) * start + t * end;
}

inline bool float_eq(float a, float b)
{
    return std::fabs(a - b) <= std::numeric_limits<float>::epsilon();
}

template <typename T>
inline float clamp(T v, T min, T max)
{
    return (v < min) ? min : (v > max ? max : v);
}
}

#endif
