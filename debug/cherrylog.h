/*
 * FILE: CHERRYLOG.H
 *
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
 */

#ifndef _CHERRYLOG_H_
#define _CHERRYLOG_H_

// minimal includes
#include <stdio.h>
#include <stdarg.h>

// internal debug defines
#ifdef HIGH_PRIORITY_DEBUG
#include <assert.h>
#define INT_ASSERT(statement) assert(statement)
#else
#define INT_ASSERT(statement) 
#endif

#define C_INFO "\x1b[33mINFO\x1b[0m"

#define _CHERRY_STREAMOUT(message, message_length)              \
    INT_ASSERT(message_length > 0);                             \
    fwrite(message, sizeof(char), message_length, stdout);      \

#define _GENERATE_MESSAGE(status, location, line, log_args)

#define CHERRY_INFO(...)                                        \
    _GENERATE_MESSAGE(C_INFO, __FILE__, __LINE__, __VA_ARGS__)  \

#define CHERRY_WARN(...)                                        \
    //TODO

#define CHERRY_ERROR(...)                                       \
    //TODO

//TODO: CHERRY_DEBUG

#endif
