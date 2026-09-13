#pragma once

#include <stdexcept>

using namespace std;

struct ValidationError : runtime_error
{
    using runtime_error::runtime_error;
};

struct SerializationError : runtime_error
{
    using runtime_error::runtime_error;
};