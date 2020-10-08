

#ifndef __libs_base64_hpp__
#define __libs_base64_hpp__

#include <string>
#include <string_view>

namespace libs::base64
{
    std::string
    encode(
        std::string_view s);

    std::string
    decode(
        std::string_view s);

} // namespace libs::base64
#endif
