#include "gtest/gtest.h"
#include "Parser.hpp"

namespace Bencode
{
::std::ostream& operator<<(::std::ostream& os, TokenType bar)
{
    os << "TokenType::";
    switch(bar)
    {
    case TokenType::Bytes:
        return os << "Bytes";
    case TokenType::Dict:
        return os << "Dict";
    case TokenType::DictListEnd:
        return os << "DictListEnd";
    case TokenType::Integer:
        return os << "Integer";
    case TokenType::Invalid:
        return os << "Invalid";
    case TokenType::List:
        return os << "List";
    }
    return os;
}

}
namespace
{

class ParserTest : public ::testing::Test
{
public:
    void verify(std::string str, const std::vector<Bencode::Token> & tokens)
    {
        std::stringstream istr{str};
        Bencode::Parser p{istr};
        std::vector<Bencode::Token> result{std::begin(p), std::end(p)};
        ASSERT_EQ(tokens.size(), result.size());
        for(auto i = 0u; i < tokens.size(); i++)
        {
            EXPECT_EQ(tokens[i].type, result[i].type) << "at index: " << i;
            EXPECT_EQ(tokens[i].content, result[i].content) << "at index: " << i;
        }
    }
};

TEST_F(ParserTest, Integer)
{
    verify("i42e",
    {
        {Bencode::TokenType::Integer, {'4', '2'}}
    });
}
TEST_F(ParserTest, Bytes)
{
    verify("3:elo",
    {
        {Bencode::TokenType::Bytes, {'e', 'l', 'o'}}
    });
}
TEST_F(ParserTest, List)
{
    verify("l3:eloe",
    {
        {Bencode::TokenType::List, {}},
        {Bencode::TokenType::Bytes, {'e', 'l', 'o'}},
        {Bencode::TokenType::DictListEnd, {}},
    });
}
TEST_F(ParserTest, Dict)
{
    verify("d3:key5:valuee",
    {
        {Bencode::TokenType::Dict, {}},
        {Bencode::TokenType::Bytes, {'k', 'e', 'y'}},
        {Bencode::TokenType::Bytes, {'v', 'a', 'l', 'u', 'e'}},
        {Bencode::TokenType::DictListEnd, {}},
    });
}
TEST_F(ParserTest, Invalid)
{
    verify("_invalid", {});
}
TEST_F(ParserTest, Complex)
{
    verify("d3:keyl6:value1i423eee",
    {
        {Bencode::TokenType::Dict, {}},
        {Bencode::TokenType::Bytes, {'k', 'e', 'y'}},
        {Bencode::TokenType::List, {}},
        {Bencode::TokenType::Bytes, {'v', 'a', 'l', 'u', 'e', '1'}},
        {Bencode::TokenType::Integer, {'4', '2', '3'}},
        {Bencode::TokenType::DictListEnd, {}},
        {Bencode::TokenType::DictListEnd, {}},
    });
}
}
