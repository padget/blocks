//
//  base64 encoding and decoding with C++.
//  Version: 2.rc.04 (release candidate)
//

#ifndef __libs_base64_hpp__
#define __libs_base64_hpp__

#include <string>
#include <string_view>

std::string base64_encode(
    std::string_view s,
    bool url = false);

std::string
base64_encode_pem(
    std::string_view s);

std::string
base64_encode_mime(
    std::string_view s);

std::string
base64_decode(
    std::string_view s,
    bool remove_linebreaks = false);

#endif
