#ifndef INPUT_H
#define INPUT_H
#include "string"
namespace Input {
struct interrupt {};
struct invalidColorFormat {};
struct invalidNumberFormat {};
struct invalidColor {
    std::string str;
};
struct numberOutOfBounds {};
struct fullColumn {};
} // namespace Input
#endif
