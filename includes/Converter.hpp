//
// Converter.hpp for pfa in /home/gautier/MyGame
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Wed Jul 17 15:11:07 2013 gautier lefebvre
// Last update Sat Mar 22 17:44:56 2014 Gautier Lefebvre
//

#ifndef			__CONVERTER_HPP__
#define			__CONVERTER_HPP__

#include		<string>
#include		<sstream>
#include		<iostream>
#include		<iomanip>

class			Converter {
public:
  template<typename T>
  static std::string StringOf(const T& val)
  {
    std::stringstream stream;

    stream << std::fixed << std::setprecision(1) << val;
    return (stream.str());
  }

  template<typename T>
  static T		StringTo(const std::string &val)
  {
    std::stringstream	stream;
    T			ret;

    stream << val;
    stream >> ret;
    return (ret);
  }

  template<typename T, typename U>
  static U		convert(const T& val)
  {
    U			ret;
    std::stringstream	stream;

    stream << val;
    stream >> ret;
    return (ret);
  }
};

#define	StringOfInt(x)		Converter::StringOf<int>(x)
#define	StringToInt(x)		Converter::StringTo<int>(x)

#define	StringOfUInt(x)		Converter::StringOf<unsigned int>(x)
#define	StringToUInt(x)		Converter::StringTo<unsigned int>(x)

#define	StringOfLLUInt(x)	Converter::StringOf<long long unsigned int>(x)
#define	StringToLLUInt(x)	Converter::StringTo<long long unsigned int>(x)

#define	StringOfDouble(x)	Converter::StringOf<double>(x)
#define	StringToDouble(x)	Converter::StringTo<double>(x)

#endif
