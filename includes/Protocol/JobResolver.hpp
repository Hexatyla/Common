//
// Resolver.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <geoffrey@epitech.net>
// 
// Started on  Thu Feb 27 16:58:30 2014 geoffrey bauduin
// Last update Mon Mar 17 14:54:17 2014 geoffrey bauduin
//

#ifndef PROTOCOL_JOBRESOLVER_HPP_
# define PROTOCOL_JOBRESOLVER_HPP_

#include	<string>
#include	<stdexcept>
#include	"Singleton.hpp"
#include	"Protocol/Job.hpp"

namespace	Protocol {

  class	JobResolver: public Singleton<Protocol::JobResolver> {

    friend class Singleton<Protocol::JobResolver>;

  public:
    class Exception {
    private:
      std::string	_what;
    public:
      Exception(const std::string &) throw();
      virtual ~Exception(void) throw();

      const char	*what(void) const throw();

    };

  private:
    JobResolver(void);
    virtual ~JobResolver(void);

    void	checkJobCommand(const Protocol::Job *, ::Command::Command) const;
    void	fillIDArray(const Protocol::Argument *, std::vector<Kernel::ID::id_t> &,
			    unsigned int, unsigned int) const;

  public:
    void	playerInformation(const Protocol::Job *, Kernel::ID::id_t &, unsigned int &, Kernel::Serial &) const;
    void	youAre(const Protocol::Job *, Kernel::ID::id_t &) const;
    void	createItem(const Protocol::Job *, Kernel::Serial &, Kernel::ID::id_t &,
			   double &, double &, double &, int &, Kernel::ID::id_t &) const;
    void	deleteItem(const Protocol::Job *, Kernel::ID::id_t &) const;
    void	updateItem(const Protocol::Job *, Kernel::ID::id_t &, double &, double &, double &,
			   int &, unsigned int &, unsigned int &, unsigned int &, unsigned int &) const;
    void	itemWaypoint(const Protocol::Job *, Kernel::ID::id_t &, unsigned int &,
			     double &, double &, double &, double &) const;
    void	itemStopAction(const Protocol::Job *, Kernel::ID::id_t &) const;
    void	itemAction(const Protocol::Job *, Kernel::ID::id_t &, Game::eAction &) const;
    void	askMoveItemGroup(const Protocol::Job *, std::vector<Kernel::ID::id_t> &, double &, double &, double &,
			      bool &) const;
    void	ping(const Protocol::Job *, Kernel::ID::id_t &, double &, double &) const;
    void	unitStance(const Protocol::Job *, Kernel::ID::id_t &, Game::Stance::Type &) const;
    void	askChangeUnitStance(const Protocol::Job *, Kernel::ID::id_t &, Game::Stance::Type &) const;
    void	unitGroupStance(const Protocol::Job *, std::vector<Kernel::ID::id_t> &, Game::Stance::Type &) const;
    void	unitAskStance(const Protocol::Job *, Kernel::ID::id_t &) const;
    void	askItemInfo(const Protocol::Job *, Kernel::ID::id_t &) const;
    void	askMoveItem(const Protocol::Job *, Kernel::ID::id_t &, double &, double &, double &) const;
    void	dayNightSwitch(const Protocol::Job *, bool &) const;
    void	playerRessources(const Protocol::Job *, Kernel::ID::id_t &, unsigned int &, unsigned int &,
				 unsigned int &) const;
    void	askPlayerRessources(const Protocol::Job *, Kernel::ID::id_t &) const;
    void	itemMove(const Protocol::Job *, Kernel::ID::id_t &, double &, double &, double &) const;
    void	askItemAction(const Protocol::Job *, Kernel::ID::id_t &) const;
    void	unitCreateBuilding(const Protocol::Job *job, Kernel::ID::id_t &, Kernel::ID::id_t &) const;
    void	askUnitProd(const Protocol::Job *, Kernel::ID::id_t &, Kernel::Serial &) const;
    void	unitProduction(const Protocol::Job *, Kernel::ID::id_t &, unsigned int &, Kernel::Serial &) const;
    void	activateCapacity(const Protocol::Job *, Kernel::ID::id_t &, Kernel::Serial &, bool &) const;
    void	unitPickingUpRessources(const Protocol::Job *, Kernel::ID::id_t &,
					unsigned int &, unsigned int &, unsigned int &) const;
    void	askUnitPickedUpRessources(const Protocol::Job *, Kernel::ID::id_t &) const;
    void	askItemEffects(const Protocol::Job *, Kernel::ID::id_t &) const;
    void	stopItemEffect(const Protocol::Job *, Kernel::ID::id_t &, Kernel::Serial &) const;
    void	itemEffect(const Protocol::Job *, Kernel::ID::id_t &, Kernel::Serial &, double &) const;
    void	askSetItemAction(const Protocol::Job *, Kernel::ID::id_t &, Game::eAction &) const;
    void	askSetItemsAction(const Protocol::Job *, std::vector<Kernel::ID::id_t> &, Game::eAction &) const;
    void	unitHasBeenProduced(const Protocol::Job *, Kernel::ID::id_t &, Kernel::Serial &) const;
    void	askRemoveUnitFromProduction(const Protocol::Job *, Kernel::ID::id_t &, Kernel::Serial &) const;
    void	removeUnitFromProduction(const Protocol::Job *, Kernel::ID::id_t &, Kernel::Serial &) const;
    void	heroPickedUpAnObject(const Protocol::Job *, Kernel::ID::id_t &, Kernel::ID::id_t &) const;
    void	askHeroObjects(const Protocol::Job *, Kernel::ID::id_t &) const;
    void	heroObjectsList(const Protocol::Job *, Kernel::ID::id_t &, std::vector<Kernel::ID::id_t> &) const;
    void	heroReleasedObject(const Protocol::Job *, Kernel::ID::id_t &, Kernel::ID::id_t &) const;
    void	askHeroToTakeObject(const Protocol::Job *, Kernel::ID::id_t &, Kernel::ID::id_t &) const;
    void	askHeroToReleaseObject(const Protocol::Job *, Kernel::ID::id_t &, Kernel::ID::id_t &, double &,
				       double &, double &) const;
    void	playerHasAmelioration(const Protocol::Job *, Kernel::ID::id_t &, Kernel::Serial &,
				      Kernel::Serial &) const;
    void	playerHasJustProducedAmelioration(const Protocol::Job *, Kernel::ID::id_t &, Kernel::Serial &,
						  Kernel::Serial &) const;
    void	askPlayerAmeliorations(const Protocol::Job *, Kernel::ID::id_t &) const;
    void	askProduceAmelioration(const Protocol::Job *, Kernel::Serial &, Kernel::Serial &) const;
    void	removeAmeliorationFromProductionQueue(const Protocol::Job *, Kernel::ID::id_t &,
						      Kernel::Serial &, Kernel::Serial &) const;
    void	askRemoveAmeliorationFromProductionQueue(const Protocol::Job *, Kernel::Serial &,
							 Kernel::Serial &) const;
    void	ameliorationProduction(const Protocol::Job *, Kernel::ID::id_t &, Kernel::Serial &,
				       Kernel::Serial &, unsigned int &) const;
    void	askElementAmeliorations(const Protocol::Job *, Kernel::ID::id_t &, Kernel::Serial &) const;
    void	askUnitToBuild(const Protocol::Job *, Kernel::ID::id_t &, Kernel::ID::id_t &) const;
    void	unitStopBuildingBuilding(const Protocol::Job *, Kernel::ID::id_t &, Kernel::ID::id_t &) const;
    void	buildingHasBeenBuilt(const Protocol::Job *, Kernel::ID::id_t &) const;
    void	unitHarvest(const Protocol::Job *, Kernel::ID::id_t &, Kernel::ID::id_t &) const;
    void	askUnitHarvest(const Protocol::Job *, Kernel::ID::id_t &, Kernel::ID::id_t &) const;
    void	unitDeposit(const Protocol::Job *, Kernel::ID::id_t &, Kernel::ID::id_t &) const;
    void	askUnitsHarvest(const Protocol::Job *, std::vector<Kernel::ID::id_t> &, Kernel::ID::id_t &) const;
    void	askSpotID(const Protocol::Job *, double &, double &, double &) const;
    void	ressourceSpot(const Protocol::Job *, Kernel::ID::id_t &, double &, double &, double &,
			      Game::Ressources::Type &, unsigned int &) const;
    void	updateSpot(const Protocol::Job *, Kernel::ID::id_t &, unsigned int &) const;
    void	unitStopHarvest(const Protocol::Job *, Kernel::ID::id_t &) const;
    void	unitWaitHarvest(const Protocol::Job *, Kernel::ID::id_t &) const;
    void	unitStopWaitHarvest(const Protocol::Job *, Kernel::ID::id_t &) const;
    void	temporaryEffect(const Protocol::Job *, Kernel::ID::id_t &,
				Kernel::Serial &, Kernel::ID::id_t &) const;
    void	removeTemporaryEffect(const Protocol::Job *, Kernel::ID::id_t &,
				      Kernel::Serial &, Kernel::ID::id_t &) const;
    void	askAutomaticCapacity(const Protocol::Job *, Kernel::ID::id_t &, Kernel::Serial &, bool &) const;
    void	askUnitsToBuild(const Protocol::Job *, std::vector<Kernel::ID::id_t> &, Kernel::ID::id_t &) const;
    void	itemAttack(const Protocol::Job *, Kernel::ID::id_t &, Kernel::ID::id_t &) const;
    void	askItemAttack(const Protocol::Job *, Kernel::ID::id_t &, Kernel::ID::id_t &) const;
    void	itemUseCapacity(const Protocol::Job *, Kernel::ID::id_t &,
				Kernel::ID::id_t &, Kernel::Serial &) const;
    void	askItemUseCapacity(const Protocol::Job *, Kernel::ID::id_t &,
				Kernel::ID::id_t &, Kernel::Serial &) const;
    void	askUnitPatrol(const Protocol::Job *, Kernel::ID::id_t &, double &, double &) const;
    void	askUnitsPatrol(const Protocol::Job *, std::vector<Kernel::ID::id_t> &,
			       double &, double &, bool &) const;
    void	askItemsAttack(const Protocol::Job *, std::vector<Kernel::ID::id_t> &, Kernel::ID::id_t &) const;
    void	askItemAttackZone(const Protocol::Job *, Kernel::ID::id_t &, double &, double &, double &) const;
    void	askItemsAttackZone(const Protocol::Job *, std::vector<Kernel::ID::id_t> &, double &, double &,
				   double &) const;
    void	itemAttackZone(const Protocol::Job *, Kernel::ID::id_t &, double &, double &, double &) const;
    void	askItemUseZoneCapacity(const Protocol::Job *, Kernel::ID::id_t &, Kernel::Serial &,
				       double &, double &, double &) const;
    void	itemUseZoneCapacity(const Protocol::Job *, Kernel::ID::id_t &, Kernel::Serial &,
				    double &, double &, double &) const;
    void	askActivateCapacity(const Protocol::Job *, Kernel::ID::id_t &, Kernel::Serial &) const;
    void	itemUseCapacity(const Protocol::Job *, Kernel::ID::id_t &, Kernel::Serial &) const;
    void	askCreateBuilding(const Protocol::Job *, Kernel::Serial &, double &, double &, double &, int &) const;

  };

}

#endif
