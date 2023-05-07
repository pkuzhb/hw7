#ifndef PARSER_H
#define PARSER_H
#include "./ai.h"
#include <string>

class Parser
{
    Parser(int argc, char **argv);
    AI *doParse();

public:
    static AI *parse(int argc, char **argv);
};

class Chat : public AI
{
public:
    std::string input, output;
    char *dest;
    Chat(std::string in) : input{in} {}
    void sendRequest();
    void showResponse();
    ~Chat() = default;
};

class Draw : public AI
{
public:
    std::string input, output;
    char *dest;
    int size;
    Draw(std::string in, std::string out) : input{in}, output{out} {}
    void sendRequest();
    void showResponse();
    ~Draw() = default;
};

class Math : public AI
{
public:
    std::string input, output;
    char *dest;
    int size;
    Math(std::string in, std::string out) : input{in}, output{out} {}
    void sendRequest();
    void showResponse();
    ~Math() = default;
};
#endif
