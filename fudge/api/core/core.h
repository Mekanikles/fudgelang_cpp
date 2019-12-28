#pragma once

#define FUDGE_API __attribute__ ((visibility("default")))

#include <string>
#include <vector>
#include <utility>
#include <memory>

#define interface struct

using string = std::string;

template<typename T>
using vector = std::vector<T>;
