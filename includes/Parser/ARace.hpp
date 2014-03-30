//
// ARace.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <geoffrey@epitech.net>
// 
// Started on  Mon Mar 10 15:45:03 2014 geoffrey bauduin
// Last update Sat Mar 15 14:52:32 2014 geoffrey bauduin
//

#ifndef PARSER_ARACE_HPP_
# define PARSER_ARACE_HPP_

#include	<vector>
#include	<map>
#include	"Parser/JSON.hpp"
#include	"Game/Race.hpp"
#include	"Kernel/Data.hpp"
#include	"Game/Type.hpp"
#include	"Threading/Mutex.hpp"
#include	"Kernel/Manager.hpp"

namespace	Parser {

  class ARace {

  public:
    typedef std::map<std::string, Game::Race *>	Container;

  protected:
    Mutex	*_mutex;
    bool	_verbose;

    enum Token {
      RACES, ELEMENTS
    };
    enum TokenType {
      UNIT, BUILDING, HERO, OBJECT, PROJECTILE, CAPACITY, EFFECT, AMELIORATION, SPELL
    };

    enum Field { TYPE, NAME, DESCRIPTION, HITBOX, RANGE, PASSTHROUGH, ATTACK, DEFENSE,
		 HP, REGENHP, TYPERESSOURCE, RESSOURCE, REGENRESSOURCE,
		 ATTACKSPEED, CRITICALSTRIKE, SPEED, SIGHT_N, SIGHT_D,
		 COST_R1, COST_R2, COST_R3, COST_TYPE_RESS, COST_RESS, COST_LIFE,
		 CAN_AUTO, IS_AUTO,
		 CANALISATION, CANALISATION_WHEN, COOLDOWN, CREATION, DURATION,
		 ELEM_TYPE_RESS, ELEM_LIFE_ACT, ELEM_RESS, RACE, LINK_ELEMENTS, REQUIREMENTS,
		 EFFECT_TYPE, EFFECT_EQUIP, EFFECT_CIBLE, EFFECT_LINK, CAPACITY_TARGET };

    enum	TokenLEList {
      LE_UNITS, LE_BUILDINGS, LE_HEROS, LE_OBJECTS, LE_PROJECTILES,
      LE_AMELIORATIONS, LE_SPELLS, LE_CAPACITY, LE_EFFECT
    };

    std::map<Field, std::string>	_tokens;
    std::map<Token, std::string>	_categories;
    std::vector<std::string>		_reqCategories;
    std::vector<std::string>		_dataFields;
    std::vector<std::string>		_costFields;
    std::vector<std::string>		_timerFields;
    std::vector<std::string>		_effectsFields;
    std::vector<std::string>		_capacityFields;
    std::map<TokenType, std::string>	_tokensTypes;
    std::vector<std::string>		_parseOrder;
    std::vector<std::string>		_linkedElements;
    std::vector<std::string>		_linkedElementsList;
    std::vector<std::string>		_requirementsList;
    std::map<TokenLEList, std::string>	_tokenLEList;
    std::vector<std::string>		_defaultCapacities;

    std::map<std::string, Kernel::Effect::Type>		_effectTypeHashtab;
    std::map<std::string, Kernel::Effect::TargetSide>	_effectSideHashtab;
    std::map<std::string, Game::Type>			_gameTypeHashtab;
    std::map<std::string, Game::Capacity::Target>	_capacityTargetHashtab;

  private:
    bool	checkCategories(const Json::Value &);
  protected:
    virtual void	emptyContainer(bool rm);
    bool	check(const Json::Value &, const std::vector<std::string> &, const std::string &);

  private:

    enum	Checks {
      C_DATA =  0b0000001,
      C_COST =  0b0000010,
      C_TIMER = 0b0000100,
      C_LE =    0b0001000,
      C_RACE =  0b0010000,
      C_CAPA =  0b0100000,
      C_EFFE =  0b1000000
    };

    std::map<TokenLEList, ::Game::Type>	_leListToType;

    bool	doChecks(const Json::Value &, int);

    bool	parseUnit(const Kernel::Serial &, const Json::Value &);
    bool	parseBuilding(const Kernel::Serial &, const Json::Value &);
    bool	parseHero(const Kernel::Serial &, const Json::Value &);
    bool	parseObject(const Kernel::Serial &, const Json::Value &);
    bool	parseProjectile(const Kernel::Serial &, const Json::Value &);
    bool	parseCapacity(const Kernel::Serial &, const Json::Value &);
    bool	parseEffect(const Kernel::Serial &, const Json::Value &);
    bool	parseAmelioration(const Kernel::Serial &, const Json::Value &);

    bool	canAddElementToElement(const Game::Race *, const std::string &,
				       const Kernel::Serial &, ::Game::Type) const;
    void	addElementsToElement(const Kernel::Serial &, ::Game::Type, ::Game::Type,
				     const std::vector<std::string> &);
    Game::Race	*getRaceContainingItem(const Kernel::Serial &, ::Game::Type);

  protected:
    virtual void	createData(const Kernel::Serial &, const Json::Value &, ::Game::Type);
    virtual void	createCost(const Kernel::Serial &, const Json::Value &);
    virtual void	createTimer(const Kernel::Serial &, const Json::Value &);
    virtual void	createCapacityList(const Kernel::Serial &, const std::vector<std::string> &);
    virtual void	createCapacityData(const Kernel::Serial &, const Json::Value &);
    virtual void	createBuildingData(const Kernel::Serial &, const std::vector<std::string> &);
    virtual void	createAmeliorationData(const Kernel::Serial &, const std::vector<std::string> &);
    virtual void	createEffectData(const Kernel::Serial &, const Json::Value &);
    virtual void	addEffectEffects(const Kernel::Serial &, const std::vector<std::string> &);
    virtual void	addCapacityEffects(const Kernel::Serial &, const std::vector<std::string> &);
    virtual void	addCapacityProjectiles(const Kernel::Serial &, const std::vector<std::string> &);

    virtual void	createRequirements(Game::Race *, const Kernel::Serial &,
					   const std::map<Game::Type, std::vector<Kernel::Serial> > &);

    virtual bool	resolve(void);

    virtual bool	linkElements(void);
    virtual bool	linkRequirements(void);

    const Kernel::Serial getSerial(const Json::Value &);

    std::map<std::string, bool (Parser::ARace::*)(const Kernel::Serial &, const Json::Value &)> _ptrFunc;

    bool	parseRace(const Json::Value &);
    bool	parseElements(const Json::Value &);
    bool	parseLinkedElements(const Kernel::Serial &, const Json::Value &);
    bool	parseRequirements(const Kernel::Serial &, const Json::Value &);


    Container		_container;

    std::map<std::string, Kernel::Serial>	_parsedUnits;
    std::map<std::string, Kernel::Serial>	_parsedBuildings;
    std::map<std::string, Kernel::Serial>	_parsedHeroes;
    std::map<std::string, Kernel::Serial>	_parsedObjects;
    std::map<std::string, Kernel::Serial>	_parsedProjectiles;
    std::map<std::string, Kernel::Serial>	_parsedCapacities;
    std::map<std::string, Kernel::Serial>	_parsedEffects;
    std::map<std::string, Kernel::Serial>	_parsedAmeliorations;

    const Kernel::Serial	getSerial(::Game::Type, const std::string &);

    std::map<Kernel::Serial, std::map<TokenLEList, std::vector<std::string> > >	_linkedElementsData;
    std::map<Kernel::Serial, std::map<TokenLEList, std::vector<std::string> > >	_requirementsData;

    std::map< ::Game::Type, std::vector<TokenLEList> >	_resolveData;
    std::vector<TokenLEList>				_resolveRequirements;

    std::map<Kernel::Serial, Kernel::Data *>		_kData;
    std::map<Kernel::Serial, Kernel::Cost *>		_kCost;
    std::map<Kernel::Serial, Kernel::Time *>		_kTimer;
    std::map<Kernel::Serial, Kernel::BuildingData *>	_kBData;
    std::map<Kernel::Serial, Kernel::CapacityData *>	_kCData;
    std::map<Kernel::Serial, Kernel::Effect *>		_kEffect;
    std::map<Kernel::Serial, Kernel::CapacityList *>	_kCList;
    std::map<Kernel::Serial, Game::Requirements *>	_itemReq;

    void		end(void);

    virtual bool	_parse(const std::string &, const Json::Value &) = 0;

    virtual ::Game::Race	*createRace(const std::string &, const Kernel::Serial &) const;
    virtual void		deleteRace(::Game::Race *) const;

  public:
    ARace(void);
    virtual ~ARace(void);

    virtual const Container	parse(const std::string &);

  };

}

#endif
