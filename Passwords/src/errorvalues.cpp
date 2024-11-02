#include "errorvalues.h"

ErrorValues::ErrorValues(string msg) noexcept : msg(msg) {}

ErrorValues::ErrorValues(const ErrorValues& obj) noexcept : msg(obj.msg) {}

ErrorValues::~ErrorValues() {}

const char* ErrorValues::what() const noexcept { return msg.c_str(); }