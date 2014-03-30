//
// Controller.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Mon Feb  3 16:34:21 2014 geoffrey bauduin
// Last update Mon Mar 17 17:17:43 2014 geoffrey bauduin
//

#ifndef GAME_CONTROLLER_HPP_
# define GAME_CONTROLLER_HPP_

#include	<map>
#include	"Singleton.hpp"
#include	"Threading/Mutex.hpp"
#include	"Game/Race.hpp"
#include	"Game/Player.hpp"
#include	"Game/Building.hpp"
#include	"Game/Unit.hpp"
#include	"Game/Object.hpp"
#include	"Game/RessourcesSpot.hpp"
#include	"Protocol/Error.hpp"
#include	"Game/Map.hpp"

namespace	Game {

  class	Controller: public Singleton<Game::Controller> {

    friend class Singleton<Game::Controller>;

  public:
    typedef std::map<Kernel::Serial, Game::Race *> Container;

    class	Error {

    public:
      enum Type {
	NONE,
	UNDEFINED,
	NOT_ENOUGH_RESSOURCES,
	NOT_ENOUGH_SELF_RESSOURCES,
	REQUIREMENTS_NOT_FULLFILLED,
	BUILDING_CANNOT_BUILD_THIS_UNIT,
	ITEM_NOT_IN_RACE,
	UNKNOWN_ITEM,
	ITEM_IS_NOT_OWNED_BY_PLAYER,
	CAPACITY_IS_NOT_IN_LIST,
	CAPACITY_CANNOT_BE_USED,
	ITEM_IS_NOT_OWNED_BY_TEAM,
	UNKNOWN_PLAYER,
	PLAYER_IS_NOT_IN_THE_SAME_TEAM,
	ITEM_IS_NOT_CORRECT,
	ITEM_CANNOT_BE_REMOVED_FROM_PRODUCTION_LIST,
	HERO_CANNOT_CARRY_MORE_OBJECTS,
	HERO_IS_NOT_CARRYING_THIS_ITEM,
	OBJECT_IS_ALREADY_BEING_CARRIED,
	PLAYER_DOES_NOT_EXIST,
	PLAYER_IS_ALREADY_PRODUCING_AMELIORATION,
	PLAYER_ALREADY_HAS_AMELIORATION,
	ITEM_HASNT_GOT_CAPACITY,
	BUILDING_IS_ALREADY_BUILT,
	ITEM_CANNOT_MOVE,
	BUILDING_IS_NOT_BUILT,
	ITEM_CANNOT_ATTACK,
	CAPACITY_CANNOT_BE_AUTOMATIC
      };

    };

  private:
    Mutex		*_mutex;
    std::map<std::string, std::list<Kernel::Serial> >	_fRaces;
    Container		_races;
    std::map<Error::Type, ::Error::Code>	_hashtab;
    std::vector< ::Game::Type>	_objectTypes;

    Controller(void);
    ~Controller(void);

    bool		checkRessources(const Game::Player *, const Kernel::Serial &, Error::Type &) const;
    bool		checkRequirements(const Game::Player *, const Game::Requirements *, Error::Type &) const;
    bool		checkIfBuildingCanBuildUnit(const Game::AElement *, const Kernel::Serial &, Error::Type &) const;
    bool		checkIfItemExists(const Kernel::Serial &serial, Error::Type &) const;
    bool		checkIfUnitIsInRace(const Game::Race *, const Kernel::Serial &, Error::Type &) const;
    bool		checkIfItemIsInRace(const Game::Race *, const Kernel::Serial &, Error::Type &) const;
    bool		checkIfItemIsOwnedByPlayer(const Game::Player *, const Game::AElement *, Error::Type &) const;
    bool		checkIfBuildingIsInRace(const Game::Race *, const Kernel::Serial &, Error::Type &) const;
    bool		checkIfCapacityIsInList(const Kernel::Serial &, const Kernel::Serial &, Error::Type &) const;
    bool		checkIfItemHasEnoughSelfRessources(const Game::AElement *, const Kernel::Serial &, Error::Type &) const;
    bool		checkIfCapacityIsNotPassive(const Kernel::Serial &, Error::Type &) const;
    bool		checkIfItemIsOwnedByTeam(const Game::Player *, const Game::AElement *, Error::Type &) const;
    bool		checkIfPlayersAreAllied(const Game::Player *, const Game::Player *, Error::Type &) const;
    bool		checkIfItemIs(const Game::AElement *, ::Game::Type, Error::Type &) const;
    bool		checkIfItemIsLast(const Game::Building *, const Kernel::Serial &, Error::Type &) const;
    bool		checkIfHeroCanCarryMoreObjects(const Game::Hero *, Error::Type &) const;
    bool		checkIfHeroIsCarryingThisObject(const Game::Hero *, const Game::AElement *, Error::Type &) const;
    bool		checkIfObjectCanBePickedUp(const Game::Object *, Error::Type &) const;
    bool		checkIfAmeliorationIsLastInQueue(const Game::Player *, const Kernel::Serial &, const Kernel::Serial &, Error::Type &) const;
    bool		checkIfPlayerHasNotAmelioration(const Game::Player *, const Kernel::Serial &,
							const Kernel::Serial &, Error::Type &) const;
    bool		checkIfPlayerIsNotProducingAmelioration(const Game::Player *, const Kernel::Serial &,
								const Kernel::Serial &, Error::Type &) const;
    bool		checkIfItemHasCapacity(const Game::AElement *, const Kernel::Serial &, Error::Type &) const;
    bool		checkIfBuildingIsNotBuilt(const Game::Building *, Error::Type &) const;
    bool		checkIfItemIsOneOfThese(const Game::AElement *, int, Error::Type &) const;
    bool		checkIfItemCanAttack(const Game::AElement *, Error::Type &) const;
    bool		checkIfItemCanBeAttacked(const Game::AElement *, Error::Type &) const;
    bool		checkIfBuildingCanBeBuilt(const Game::Building *, Error::Type &) const;
    bool		checkIfBuildingIsBuilt(const Game::Building *, Error::Type &) const;
    bool		checkIfItemCanAttackZone(const Game::AElement *, Error::Type &) const;
    bool		checkIfCapacityCanBeAutomatic(const Kernel::Serial &, Error::Type &) const;

    bool		checkHandRange(const Game::AElement *, double, double, double) const;
    bool		checkHandRange(const Game::AElement *, double, double, double, double, double, double) const;
    bool		checkHitboxesCollision(const Game::AElement *, const Game::AElement *) const;
    bool		checkAttackRange(const Game::AElement *, double, double, double) const;

  public:
    const Container	flushRaces(void);
    ::Error::Code	translate(Error::Type) const;
    Error::Type		translate(::Error::Code) const;
    const Game::Race	*getRace(const Kernel::Serial &) const;
    const Game::Race	*getRaceNamed(const std::string &, const std::string &) const;
    const Container	&getRaces(void) const;
    void		addRace(const std::string &, Game::Race *);
    void		removeRace(Game::Race *);
    void		removeRace(const Kernel::Serial &);

    bool		playerCanCreateUnit(const Game::Player *, const Game::AElement *,
					   const Kernel::Serial &, Error::Type &) const;
    bool		playerCanBuildBuilding(const Game::Player *, const Kernel::Serial &,
					       Error::Type &) const;
    bool		itemCanUseCapacity(const Game::AElement *, const Kernel::Serial &, Error::Type &) const;
    bool		playerCanChangeUnitStance(const Game::Player *, const Game::AElement *, Error::Type &) const;
    bool		playerCanAskUnitStance(const Game::Player *, const Game::AElement *, Error::Type &) const;
    bool		playerCanAskItemInformations(const Game::Player *, const Game::AElement *, Error::Type &) const;
    bool		playerCanStopItemAction(const Game::Player *, const Game::AElement *, Error::Type &) const;
    bool		playerCanAskItemAction(const Game::Player *, const Game::AElement *, Error::Type &) const;
    bool		playerCanAskPlayerRessources(const Game::Player *, const Game::Player *, Error::Type &) const;
    bool		playerCanSetItemAction(const Game::Player *, const Game::AElement *, Error::Type &) const;
    bool		playerCanRemoveUnitFromProductionList(const Game::Player *, const Game::AElement *,
							      const Kernel::Serial &, Error::Type &) const;
    bool		playerCanAskHeroObjects(const Game::Player *, const Game::AElement *, Error::Type &) const;
    bool		playerCanAskHeroToPickUpObject(const Game::Player *, const Game::Hero *,
						       const Game::Object *, Error::Type &) const;
    bool		playerCanAskHeroToReleaseObject(const Game::Player *, const Game::Hero *,
							const Game::Object *, Error::Type &) const;
    bool		playerCanAskAmeliorations(const Game::Player *, const Game::Player *, Error::Type &) const;
    bool		playerCanAskAmeliorations(const Game::Player *, const Game::Player *,
						  const Kernel::Serial &, Error::Type &) const;
    bool		playerCanRemoveAmeliorationFromProductionQueue(const Game::Player *,
								       const Kernel::Serial &,
								       const Kernel::Serial &,
								       Error::Type &) const;
    bool		playerCanProduceAmelioration(const Game::Player *, const Kernel::Serial &,
						     const Kernel::Serial &, Error::Type &) const;
    bool		playerCanAskUnitToBuild(const Game::Player *, const Game::Unit *, const Game::Building *,
						Error::Type &) const;
    bool		playerCanAskUnitToHarvestRessourcesSpot(const Game::Player *, const Game::AElement *,
								const Game::AElement *, Error::Type &) const;
    bool		playerCanAskUnitPickedUpRessources(const Game::Player *, const Game::AElement *, Error::Type &) const;
    bool		playerCanAskItemEffects(const Game::Player *, const Game::AElement *, Error::Type &) const;
    bool		playerCanMoveItem(const Game::Player *, const Game::AElement *, Error::Type &) const;
    bool		playerCanAskItemToAttackItem(const Game::Player *, const Game::AElement *,
						     const Game::AElement *, Error::Type &) const;
    bool		playerCanAskUnitToPatrol(const Game::Player *, const Game::AElement *, Error::Type &) const;
    bool		playerCanAskItemToAttackZone(const Game::Player *, const Game::AElement *,
						     Error::Type &) const;
    bool		playerCanAskItemToUseCapacity(const Game::Player *, const Game::AElement *,
						      const Kernel::Serial &, Error::Type &) const;
    bool		playerCanAskItemToSetCapacityAutomatic(const Game::Player *, const Game::AElement *,
							       const Kernel::Serial &, Error::Type &) const;
    bool		playerCanCreateBuilding(const Game::Player *, const Kernel::Serial &, Error::Type &) const;

    bool		unitCanDepositInBuilding(const Game::AElement *, const Game::AElement *, ::Game::Ressources::Type) const;
    bool		itemIsInRangeOfPoint(const Game::AElement *, double, double, double, double, double, double) const;
    bool		itemIsInRangeOfPoint(const Game::AElement *, double, double, double) const;
    bool		itemIsInRangeOfItem(const Game::AElement *, const Game::AElement *) const;
    bool		itemHasAttackRangeOnItem(const Game::AElement *, const Game::AElement *) const;
    bool		itemHasAttackRangeOnPoint(const Game::AElement *, double, double, double) const;
    bool		itemHasVisionOnItem(const Game::Map *, const Game::AElement *, const Game::AElement *) const;
    bool		itemHasVisionOnPoint(const Game::Map *, const Game::AElement *, double, double, double) const;
    bool		unitCanBuildBuilding(const Game::Unit *, const Game::Building *, Error::Type &) const;
    bool		itemCanMove(const Game::AElement *, Error::Type &) const;

  };

}

#endif
