/*
 * MIT License
 *
 * Copyright (c) 2022 Vasily Davydov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#include "command_wrapper.h"

cmd_tokens get_cmd_tokens(const char * first_line, ...)
{
    cmd_tokens command = {0};
    if(first_line == NULL) return command;

    va_list params;
    va_start(params, first_line);
    for(const char* buffer = va_arg(params, const char*);
        buffer != NULL;
        buffer = va_arg(params, const char*))
    {
        command.amount += 1;
    }
    va_end(params);

    command.lines = calloc(sizeof(first_line), command.amount);
    if (command.lines == NULL)
    {
        LEAKTRACER_ERROR("%s", "Could not allocate memory.")
        return command;
    }
    command.amount = 0;
    command.lines[command.amount] = first_line;
    command.amount += 1;

    va_start(params, first_line);
    for(const char* buffer = va_arg(params, const char*);
        buffer != NULL;
        buffer = va_arg(params, const char*))
    {
        command.lines[command.amount] = calloc(sizeof(char), strlen(buffer));
        if (command.lines[command.amount] == NULL)
        {
            LEAKTRACER_ERROR("%s", "Could not allocate memory.")
            return command;
        }
        command.lines[command.amount] = buffer;
        command.amount += 1;
    }
    va_end(params);


    return command;
}

char* tokens_to_str(cmd_tokens tokens)
{
    if(tokens.lines[0] == NULL) return NULL;
    
    size_t string_total_length = 0;
    for(size_t i = 0; i < tokens.amount; i++)
    {
        string_total_length += strlen(tokens.lines[i]);
        if (i > 0) string_total_length++; // for spaces
    }

    char* final_string = (char*) calloc(sizeof(char), string_total_length + 1);
    if (final_string == NULL)
    {
        LEAKTRACER_ERROR("%s", "Could not allocate memory.")
        return final_string;
    }
    string_total_length = 0;
    for(size_t i = 0; i < tokens.amount; i++)
    {
        if(i > 0)
        {
            memcpy(final_string + string_total_length, " ", 1);
            string_total_length += strlen(" ");
        }
        size_t current_token_length = strlen(tokens.lines[i]);
        memcpy(final_string + string_total_length, 
               tokens.lines[i], current_token_length);
        string_total_length += current_token_length;
    }
    return final_string;
}

void free_tokens(cmd_tokens tokens)
{
    if(tokens.lines[0] == NULL) return;

    for(size_t i = 0; i < tokens.amount; i++)
    {
        free((void*)tokens.lines[i]);
    }

    free((void*)tokens.lines);
}

cmd tokens_to_cmd(cmd_tokens tokens)
{
    cmd command = {0};
    if (tokens.lines[0] == NULL) return command;

    command.bin = tokens.lines[0];
    command.args = tokens.lines;

    return command;
}
