#ifndef INPUT_H
#define INPUT_H
#include "string"
namespace Input {
struct interrupt {};
struct invalidColorFormat {};
struct invalidColor {
    std::string str;
};
} // namespace Input
#endif
