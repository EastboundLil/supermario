#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#define LOG(msg) std::cout << __FILE__ << " (" << __LINE__ << "):       " << msg << std::endl

#endif // LOGGER_H
