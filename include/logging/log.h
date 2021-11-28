/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file log.h
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 */

#pragma once

#include <stdio.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"

#define LOG_LIB_INFO(format, ...)  fprintf(stdout, "[LIB::INFO at %s:%d] " format "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_LIB_ERROR(format, ...) fprintf(stderr, "[LIB::ERROR at %s:%d] " format "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define LOG_APP_INFO(format, ...)  fprintf(stdout, "[APP::INFO at %s:%d] " format "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_APP_ERROR(format, ...) fprintf(stderr, "[APP::ERROR at %s:%d] " format "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#pragma GCC diagnostic pop