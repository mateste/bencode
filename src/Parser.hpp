#pragma once
#include <fstream>
#include <vector>
#include "Token.hpp"

namespace Bencode
{
class Parser
{
public:
    class iterator
    {
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = Token;
        using difference_type = std::ptrdiff_t;
        using pointer = const value_type*;
        using reference = const value_type&;

        iterator(Parser & parser, bool isEnd);

        reference operator*();
        iterator operator++();
        bool operator!=(const iterator & other);

    private:
        Parser & m_parser;
        value_type m_content;
    };

    explicit Parser(std::istream & str);

    iterator begin();
    iterator end();

    iterator::value_type current();
    iterator::value_type next();

private:
    std::istream & m_stream;
    iterator::value_type m_currentToken;
};

}
