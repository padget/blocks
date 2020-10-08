#include "base64.hpp"
#include <array>
namespace
{
   using uchar_t = unsigned char;

   std::array<uchar_t, 4>
   tob64(const std::array<uchar_t, 3> &s)
   {
      std::array<uchar_t, 4> t;
      t[0] = s[0] >> 2;
      t[1] = ((s[0] & 0b00000011) << 4) +
             ((s[1] >> 4) & 0b00001111);
      t[2] = ((s[1] & 0b00001111) << 2) +
             ((s[2] & 0b11000000) >> 6);
      t[3] = s[2] & 0b00111111;
      return t;
   }

   std::string b64table()
   {
      return "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";
   }

   unsigned int
   rtable(
       const unsigned char c)
   {
      if (c >= 'A' && c <= 'Z')
         return c - 'A';
      else if (c >= 'a' && c <= 'z')
         return c - 'a' + ('Z' - 'A') + 1;
      else if (c >= '0' && c <= '9')
         return c - '0' + ('Z' - 'A') + ('z' - 'a') + 2;
      else if (c == '+')
         return 62;
      else if (c == '/')
         return 63;
      throw "If input is correct, this line should never be reached.";
   }
} // namespace

std::string
libs::base64::encode(
    std::string_view bytes)
{
   using uchar_t = unsigned char;

   std::string table = b64table();

   std::size_t len_encoded = (bytes.size() + 2) / 3 * 4;

   std::string encoded;
   encoded.reserve(len_encoded);

   std::size_t pos = 0;
   std::size_t length = bytes.size();

   while (pos < length)
   {
      bool succ1 = pos + 1 < length;
      bool succ2 = pos + 2 < length;

      std::array<uchar_t, 3> ctrio;

      ctrio[0] = bytes[pos + 0];
      ctrio[1] = succ1 ? bytes[pos + 1] : '\0';
      ctrio[2] = succ2 ? bytes[pos + 2] : '\0';

      std::array<uchar_t, 4> idx = tob64(ctrio);

      encoded.push_back(table[idx[0]]);
      encoded.push_back(table[idx[1]]);
      encoded.push_back(succ1 ? table[idx[2]] : '=');
      encoded.push_back(succ2 ? table[idx[3]] : '=');

      pos += 3;
   }

   return encoded;
}

std::string
libs::base64::decode(
    std::string_view enc)
{

   if (enc.empty())
      return "";

   std::size_t encsize = enc.size();
   std::size_t pos = 0;
   std::size_t approx_size = encsize / 4 * 3;
   std::string decoded;

   decoded.reserve(approx_size);

   while (pos < encsize)
   {
      uchar_t e0 = enc[pos + 0];
      uchar_t e1 = enc[pos + 1];
      uchar_t e2 = enc[pos + 2];
      uchar_t e3 = enc[pos + 3];

      uchar_t i0 = rtable(e0);
      uchar_t i1 = rtable(e1);

      uchar_t dec1 = ((i0) << 2) + ((i1 & 0x30) >> 4);

      decoded.push_back(dec1);

      if (e2 != '=')
      {
         uchar_t i2 = rtable(e2);
         uchar_t dec2 = ((i1 & 0x0f) << 4) + ((i2 & 0x3c) >> 2);
         decoded.push_back(dec2);

         if (e3 != '=')
         {
            uchar_t i3 = rtable(e3);
            uchar_t dec3 = ((i2 & 0x03) << 6) + i3;
            decoded.push_back(dec3);
         }
      }

      pos += 4;
   }

   return decoded;
}