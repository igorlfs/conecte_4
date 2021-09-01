#ifndef INPUT_H
#define INPUT_H
#include "string"
namespace Input {
struct interrupt {};
struct emptyLine {};
struct invalidColorFormat {
    std::string str;
};
struct invalidColor {
    std::string str;
};
} // namespace Input
#endif
