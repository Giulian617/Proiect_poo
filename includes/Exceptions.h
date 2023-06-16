#ifndef EXCEPTIONS
#define EXCEPTIONS

#include <stdexcept>

class app_error : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

class value_error : public app_error
{
    using app_error::app_error;
};

class not_a_valid_color_error : public app_error
{
    using app_error::app_error;
};

#endif