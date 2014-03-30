//
// Map.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Feb 14 22:50:36 2014 geoffrey bauduin
// Last update Tue Mar 11 15:54:50 2014 geoffrey bauduin
//

#ifndef PARSER_MAP_HPP_
# define PARSER_MAP_HPP_

#include	<map>
#include	"Singleton.hpp"
#include	"Game/Map.hpp"
#include	"Parser/JSON.hpp"
#include	"Game/Ressources.hpp"
#ifdef __SERVER__
# include "Server/Map.hpp"
#endif

namespace	Parser {

  class	Map: public Singleton<Parser::Map> {

    friend class Singleton<Parser::Map>;

  private:
    enum	Token {
      X, Y, Z, RESSOURCE
    };

    enum TokenRessource {
      TYPE, XR, YR, VALUE
    };

    enum TokenStart {
      ST_X, ST_Y
    };

    std::map<Token, std::string>			_tokens;
    std::map<TokenRessource, std::string>		_tokensRessource;
    std::map<std::string, Game::Ressources::Type>	_hashtabRessourcesType;

    std::map<TokenStart, std::string>			_tokensStart;

    Map(void);
    virtual ~Map(void);

    bool	check(const Json::Value &);
    bool	parseMap(const Json::Value &, std::vector<unsigned int> &, unsigned int &, unsigned int &);

#ifdef __SERVER__
    bool	parseSpots(const Json::Value &, std::vector<Server::Map::Spot> &);
    bool	parseStart(const Json::Value &, std::vector<std::pair<double, double> > &);
#endif

  public:
    Game::Map	*parse(const std::string &);

  };

}

#endif
