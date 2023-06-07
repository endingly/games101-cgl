#include <string>
#include "common.h"

CGL_EXPORT std::string base64_encode(unsigned char const* , unsigned int len);
CGL_EXPORT std::string base64_decode(std::string const& s);