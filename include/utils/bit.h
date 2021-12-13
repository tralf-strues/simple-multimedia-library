/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file bit.h
 * @date 2021-10-23
 * 
 * @copyright Copyright (c) 2021
 */

#pragma once

#define BIT(x) (1 << x)
#define GET_BIT(number, i) ((number >> i) & 1)
