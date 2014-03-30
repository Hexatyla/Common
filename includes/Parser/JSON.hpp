//
// JSONParser.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Tue Jan 21 11:04:41 2014 geoffrey bauduin
// Last update Fri Feb 14 23:00:47 2014 geoffrey bauduin
//

#ifndef PARSER_JSON_HPP_
# define PARSER_JSON_HPP_

#include	"Json/json.h"
#include	"Singleton.hpp"
#include	"Utils/FileReader.hpp"

namespace	Parser {

  class	JSON: public Singleton<Parser::JSON> {

    friend class Singleton;

  private:

    JSON(void);
    ~JSON(void);

  public:
    bool		parse(const std::string &, Json::Value &);

  };

}

#endif
