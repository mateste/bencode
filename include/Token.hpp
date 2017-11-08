#pragma once

#include <vector>
#include "TokenType.hpp"

namespace Bencode
{
struct Token
{
    TokenType type;
    std::vector<unsigned char> content;
};

inline bool operator==(const Token & t1, const Token & t2)
{
    return t1.type == t2.type && t1.content == t2.content;
}
}

