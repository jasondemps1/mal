#ifndef __DEBUG_HPP__
#define __DEBUG_HPP__

#define DEBUG 0

#if DEBUG
#include <iostream>

#define FUNC_OUT std::cout << __FUNCTION__ << std::endl
#else
#define FUNC_OUT 0
#endif

#endif
