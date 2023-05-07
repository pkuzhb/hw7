#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include <string>
#include "./parser.h"
#include "../includes/rjsjai.h"

AI *Parser::parse(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cerr << "Error: argc < 3\n";
        std::exit(EXIT_FAILURE);
    }
    else
    {
        if (strcmp(argv[1], "--chat") == 0)
        {
            // no exist "-"!
            for (int i = 2; i < argc; ++i)
            {
                if (argv[i][0] == '-')
                {
                    std::cerr << "Error: too many options\n";
                    std::exit(EXIT_FAILURE);
                }
            }
            std::string input = "";
            for (int i = 2; i < argc; ++i)
            {
                input = input + argv[i] + " ";
            }
            input.pop_back();
            // normal case!
            AI *tem = new Chat(input);
            return tem;
        }

        else if (strcmp(argv[1], "--draw") == 0 || strcmp(argv[1], "--math") == 0)
        {
            // next option must be "--output" or "-o"!
            int i;
            std::string input = "";
            for (i = 2; i < argc - 1 && argv[i][0] != '-'; ++i)
            {
                input = input + argv[i] + " ";
            }
            input.pop_back();

            if (i == argc - 1)
            {
                std::cerr << "Error: too few options\n";
                std::exit(EXIT_FAILURE);
            }

            std::string output = "";
            if (strcmp(argv[i], "--output") == 0 || strcmp(argv[i], "-o") == 0)
            {
                ++i;
                for (; i < argc; ++i)
                {
                    output = output + argv[i] + " ";
                }
                output.pop_back();
                // normal case!
                if (strcmp(argv[1], "--draw") == 0)
                {
                    AI *tem = new Draw(input, output);
                    return tem;
                }
                else
                {
                    AI *tem = new Math(input, output);
                    return tem;
                }
            }
            else
            {
                std::cerr << "Error: invalid option\n";
                std::exit(EXIT_FAILURE);
            }
        }

        else if (strcmp(argv[1], "--output") == 0 || strcmp(argv[1], "-o") == 0)
        {
            // next option must be "--draw" or "--math"!
            int i;
            std::string output = "";
            for (i = 2; i < argc - 1 && argv[i][0] != '-'; ++i)
            {
                output = output + argv[i] + " ";
            }
            output.pop_back();

            if (i == argc - 1)
            {
                std::cerr << "Error: too few options\n";
                std::exit(EXIT_FAILURE);
            }

            std::string input = "";
            if (strcmp(argv[i], "--draw") == 0 || strcmp(argv[i], "--math") == 0)
            {
                int rem_i = i;
                ++i;
                for (; i < argc; ++i)
                {
                    input = input + argv[i] + " ";
                }
                input.pop_back();
                // normal case!
                if (strcmp(argv[rem_i], "--draw") == 0)
                {
                    AI *tem = new Draw(input, output);
                    return tem;
                }
                else
                {
                    AI *tem = new Math(input, output);
                    return tem;
                }
            }
            else
            {
                std::exit(EXIT_FAILURE);
            }
        }
        else
        {
            std::cerr << "Error: invalid option\n";
            std::exit(EXIT_FAILURE);
        }
    }
}

void Chat::sendRequest()
{
    RJSJAI *obj = ai_create("e08e6cef-df76-4536-9cfb-2ac7d09021f2");
    int errcode = ai_send(obj, AI_TYPE_CHAT, this->input.c_str());
    if (errcode)
    {
        std::cerr << "Failed to call AI interface, Error code: " << errcode << std::endl;
        std::exit(errcode);
    }

    errcode = ai_status(obj);
    if (errcode)
    {
        std::cerr << "Failed to call AI interface, Error code: " << errcode << std::endl;
        std::exit(errcode);
    }

    this->dest = nullptr;
    int size = ai_result(obj, this->dest);
    this->dest = new char[size + 1];
    memset(this->dest, 0, size + 1);
    ai_result(obj, this->dest);
    ai_free(obj);
}

void Chat::showResponse()
{
    std::cout << this->dest;
    delete[] this->dest;
}

void Draw::sendRequest()
{
    RJSJAI *obj = ai_create("e08e6cef-df76-4536-9cfb-2ac7d09021f2");
    int errcode = ai_send(obj, AI_TYPE_DRAW, this->input.c_str());
    if (errcode)
    {
        std::cerr << "Failed to call AI interface, Error code: " << errcode << std::endl;
        std::exit(errcode);
    }

    errcode = ai_status(obj);
    if (errcode)
    {
        std::cerr << "Failed to call AI interface, Error code: " << errcode << std::endl;
        std::exit(errcode);
    }

    this->dest = nullptr;
    this->size = ai_result(obj, this->dest);
    this->dest = new char[this->size];
    memset(this->dest, 0, this->size);
    ai_result(obj, this->dest);
    ai_free(obj);
}

void Draw::showResponse()
{
    std::ofstream outFile(this->output, std::ios::out | std::ios::binary);
    outFile.write(this->dest, this->size);
    delete[] this->dest;
}

void Math::sendRequest()
{
    RJSJAI *obj = ai_create("e08e6cef-df76-4536-9cfb-2ac7d09021f2");
    int errcode = ai_send(obj, AI_TYPE_WOLFRAM, this->input.c_str());
    if (errcode)
    {
        std::cerr << "Failed to call AI interface, Error code: " << errcode << std::endl;
        std::exit(errcode);
    }

    errcode = ai_status(obj);
    if (errcode)
    {
        std::cerr << "Failed to call AI interface, Error code: " << errcode << std::endl;
        std::exit(errcode);
    }

    this->dest = nullptr;
    this->size = ai_result(obj, this->dest);
    this->dest = new char[this->size];
    memset(this->dest, 0, this->size);
    ai_result(obj, this->dest);
    ai_free(obj);
}

void Math::showResponse()
{
    std::ofstream outFile(this->output, std::ios::out | std::ios::binary);
    outFile.write(this->dest, this->size);
    delete[] this->dest;
}