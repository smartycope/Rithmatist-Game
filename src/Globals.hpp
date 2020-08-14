#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <ctime>

//  Regular
//! Warning
//? Blue
//* Bold
//TODO Remember...
//todo remember...
/** @param parameter*/
//// Nevermind

#define RAD2DEG 56.54866776;
#ifndef PI
#define PI 3.14159265358979323846
#endif
#define verbose 4
#define TOO_MUCH 50 * 6
#define FILE_NAME_LENGTH 45

#define appendVector(main, append)                                        \
    switch(append.size()){                                                \
        case 0:                                                           \
            break;                                                        \
        case 1:                                                           \
            main.push_back(append[0]); break;                             \
        default:                                                          \
            main.insert(main.end(), append.begin(), append.end()); break; \
    }

#define appendHeapVector(main, append)                                        \
    switch(append->size()){                                                   \
        case 0:                                                               \
            break;                                                            \
        case 1:                                                               \
            main->push_back((*append)[0]); break;                             \
        default:                                                              \
            main->insert(main->end(), append->begin(), append->end()); break; \
    }

#define logVal(var) std::cout << g::getDebugCount() << ": " << #var << " = " << var << std::endl;

#define _print(message) std::cout << g::getDebugCount() << ": " << #message << std::endl;
#define _endl std::cout << std::endl;
#define _rawprint(message) std::cout << ": " << #message;
#define _log g::log

#define START_TIME time_t _start, _finish; \
                   time(&_start);

#define LOG_TIME time(&_finish); \
                 std::string file = __FILE__; \
                 std::cout << g::getDebugCount() << "\b\b\b\b: " << file.substr(FILE_NAME_LENGTH) << "::" << __func__ << " took " \
                 << difftime(_finish, _start) << " seconds to run.\n";

#define START_CLOCK clock_t _how_long; \
                    _how_long = clock();


#define LOG_CLOCK _how_long = clock() - _how_long; \
                  std::string file = __FILE__; \
                  std::cout << g::getDebugCount() << "\b\b\b\b: " << file.substr(FILE_NAME_LENGTH) << "::" << __func__ << " took " \
                  << float(_how_long) << " cycles to run.\n"; // this is not necisarriy "cycles"


/*
0: No debug info
5: All debug info
*/

namespace g{

unsigned long getDebugCount();

void log(std::string message = "", unsigned int verbosity = verbose);

void printVector(const std::vector<float>& v, int itemsPerLine = -1, int spacing = 11);

void printVector(const std::vector<int>& v, int itemsPerLine = -1, int spacing = 11);

float round(float var, int digits = 1);


// static int set_at(SDL_Surface *surf, int x, int y, Uint32 color, int *drawn_area);

// void printVector(const std::vector<Point>& v, int itemsPerLine = -1, int spacing = 11);
} // namespace g
