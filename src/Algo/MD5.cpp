//
// MD5.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Thu Jan 16 15:47:11 2014 geoffrey bauduin
// Last update Wed Feb 26 14:13:22 2014 geoffrey bauduin
//

#include	<openssl/md5.h>
#include	<iomanip>
#include	<sstream>
#include	"Algo/MD5.hpp"

Algo::MD5::MD5(void) {
}

Algo::MD5::~MD5(void) {
}

const std::string	Algo::MD5::digest(const std::string &string) {
  std::ostringstream stream;
  unsigned char	result[MD5_DIGEST_LENGTH];
  for (unsigned int i = 0 ; i < MD5_DIGEST_LENGTH ; ++i) {
    result[i] = 0;
  }
  stream.str("");
  ::MD5(reinterpret_cast<const unsigned char *>(string.c_str()), string.size(), result);
  for (int i = 0 ; i < MD5_DIGEST_LENGTH ; ++i) {
    stream << std::hex << std::setfill('0') << std::setw(2) << static_cast<unsigned int>(result[i]);
  }
  return (stream.str());
}
