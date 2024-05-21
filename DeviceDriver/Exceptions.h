#pragma once
#include <stdexcept>

class ReadFailException : public std::exception {

};

class WriteFailException : public std::exception {

};
