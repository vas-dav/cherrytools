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

#define C_INFO "\x1b[34mINFO\x1b[0m"
#define C_WARN "\x1b[33mWARNING\x1b[0m"
#define C_ERROR "\x1b[31mERROR\x1b[0m"

#define CHERRY_BUFFER_MAX_CAP 500
#define CHERRY_MESSAGE_MAX_CAP 150

#define _CHERRY_STREAMOUT(message, message_length)              \
    INT_ASSERT(message_length > 0);                             \
    fwrite(message, sizeof(char), message_length, stdout);      \
    fflush(stdout);                                             \

void construct_log(const char * _status,
                   const char * _location,
                   const size_t _line,
                   const char * _fmt, ...)
{
    va_list args;
    va_start(args, _fmt);
    char message [CHERRY_BUFFER_MAX_CAP] = {0};
    int message_len = vsnprintf(message, CHERRY_BUFFER_MAX_CAP, _fmt, args);
    va_end(args);
    char buffer [CHERRY_BUFFER_MAX_CAP] = {0};
    int buffer_len = snprintf(buffer, CHERRY_BUFFER_MAX_CAP,
                             "[%s] [File: %s] [Line: %d] %.*s\n",
                             _status,
                             _location,
                             _line,
                             message_len,
                             message);
    _CHERRY_STREAMOUT(buffer, buffer_len)
    
}

#define CHERRY_INFO(fmt, ...)                                        \
    construct_log(C_INFO, __FILE__, __LINE__, fmt, ##__VA_ARGS__);  \

#define CHERRY_WARNING(fmt, ...)                                        \
    construct_log(C_WARN, __FILE__, __LINE__, fmt, ##__VA_ARGS__);  \

#define CHERRY_ERROR(fmt, ...)                                       \
    construct_log(C_ERROR, __FILE__, __LINE__, fmt, ##__VA_ARGS__);  \

//TODO: CHERRY_DEBUG

#endif
