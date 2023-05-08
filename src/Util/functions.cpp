#include <cmath>

float wave(float time, float from, float to, float duration) {
    float amplitude = (to - from) / 2.0f;
    float frequency = 1.0f / duration;
    float phase = from + amplitude;
    return amplitude * sin(2 * M_PI * frequency * time) + phase;
}