#include "Parser.hpp"
#include <array>
#include <vector>


namespace
{
Bencode::Parser::iterator::value_type makeInteger(std::istream & istr)
{
    std::array<char, 64> buf;
    istr.getline(buf.data(), buf.size(), 'e');
    return {Bencode::TokenType::Integer, {std::begin(buf), std::begin(buf) + istr.gcount() - 1}};
}

Bencode::Parser::iterator::value_type makeBytes(std::istream & istr)
{
    std::array<char, 64> sizeStr;
    istr.getline(sizeStr.data(), static_cast<std::streamsize>(sizeStr.size()), ':');
    std::vector<char> buf;
    buf.resize(std::stoul(sizeStr.data()), 0);
    istr.read(buf.data(), static_cast<std::streamsize>(buf.size()));
    return {Bencode::TokenType::Bytes, {std::begin(buf), std::end(buf)}};
}


Bencode::Parser::iterator::value_type getEntity(std::istream& istr)
{
    auto c = istr.peek();
    while(c != std::istream::traits_type::eof())
    {
        switch(c)
        {
        case 'i':
            istr.get();
            return makeInteger(istr);
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return makeBytes(istr);
        case 'l':
            istr.get();
            return {Bencode::TokenType::List, {}};
        case 'd':
            istr.get();
            return {Bencode::TokenType::Dict, {}};
        case 'e':
            istr.get();
            return {Bencode::TokenType::DictListEnd, {}};
        default:
            return {Bencode::TokenType::Invalid, {}};
        }
    }
    return {Bencode::TokenType::Invalid, {}};
}
}

namespace Bencode
{

Parser::iterator::iterator(Parser & parser, bool isEnd)
    : m_parser(parser)
    , m_content(isEnd ? value_type{TokenType::Invalid, {}} : parser.current())
{
}
Parser::iterator::reference Parser::iterator::operator*()
{
    return m_content;
}

Parser::iterator Parser::iterator::operator++()
{
    m_content = m_parser.next();
    return *this;
}

bool Parser::iterator::operator!=(const iterator & other)
{
    return m_content.content != other.m_content.content || m_content.type != other.m_content.type;
}


Parser::Parser(std::istream & str)
    : m_stream(str)
    , m_currentToken(getEntity(m_stream))
{

}

Parser::iterator Parser::begin()
{
    m_stream.seekg(0);
    next();
    return Parser::iterator(*this, false);
}

Parser::iterator Parser::end()
{
    return Parser::iterator(*this, true);
}

Parser::iterator::value_type Parser::current()
{
    return m_currentToken;
}

Parser::iterator::value_type Parser::next()
{
    m_currentToken = getEntity(m_stream);
    return current();
}
}
