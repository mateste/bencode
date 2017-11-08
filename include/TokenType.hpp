#pragma once

namespace Bencode
{
enum class TokenType
{
    Integer,
    Bytes,
    Dict,
    List,
    DictListEnd,
    Invalid
};
}
