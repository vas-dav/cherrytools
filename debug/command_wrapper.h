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
#ifndef COMMAND_WRAPPER_H
#define COMMAND_WRAPPER_H

#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "leaktracer_log.h"

typedef struct
{
 const char** lines;
 size_t amount;
} cmd_tokens;

typedef struct
{
    const char* bin;
    const char** args;
} cmd;

#define command_wrapper(...)                                                \
do                                                            \
{                                                             \
   cmd_tokens tokens = get_cmd_tokens(__VA_ARGS__, NULL);     \
   LEAKTRACER_INFO("Executing: %s\n", tokens_to_str(tokens));                   \
   execvp(tokens.lines[0], (char * const*)tokens.lines); \
   free_tokens(tokens); \
\
}while(0)                                                     \

cmd_tokens get_cmd_tokens(const char *, ...);
char* tokens_to_str(cmd_tokens);
cmd tokens_to_cmd(cmd_tokens);
void free_tokens(cmd_tokens);
#endif /* COMMAND_WRAPPER_H */
