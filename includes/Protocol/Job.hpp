//
// Job.hpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Mon Jan 13 16:27:35 2014 gautier lefebvre
// Last update Wed Mar 26 11:07:21 2014 Gautier Lefebvre
//

#ifndef		__PROTOCOL_JOB_HPP__
#define		__PROTOCOL_JOB_HPP__

#include	<vector>
#include	<iostream>
#include	"Protocol/Argument.hpp"
#include	"Kernel/Serial.hpp"
#include	"IFromFactory.hpp"
#include	"IClonable.hpp"

namespace	Protocol {
  class		Job: public IFromFactory, public IClonable<Protocol::Job> {
  public:
    struct nJob {
      Command::Command	_command;
      Protocol::Argument	_args[7];
    };

  private:
    nJob	_data;

    unsigned int	createIDArray(const std::vector<Kernel::ID::id_t> &, unsigned int);

  public:
    Job();
    virtual ~Job();

    nJob	*getData(void);

    Command::Command	getCommand() const;
    const Protocol::Argument* getArguments() const;

    Protocol::Job	*clone(void) const;
    void	clone(const Protocol::Job *);

    void	reset();
    virtual void destroy(void);

    void	playerInformation(Kernel::ID::id_t, unsigned int, const Kernel::Serial &);
    void	youAre(Kernel::ID::id_t);

    void	askCreateBuilding(const Kernel::Serial &, double, double, double, int);

    void	exit();
    void	connection(const std::string &, const std::string &);
    void	registration(const std::string &, const std::string&, const std::string &);

    void	playerInfos(const std::string&, const std::string&, const std::string&, ::User::Status s);
    void	playerStats(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

    void	setStatus(::User::Status s);
    void	setRace(Race::Race r);

    void	friendRequest(const std::string &);
    void	removeFriend(const std::string &);
    void	answerFriendRequest(const std::string &, bool);

    void	lockTeams(bool);
    void	cheats(bool);
    void	chat(bool);
    void	ready(bool);

    void	sendWhisp(const std::string &, const std::string&);
    void	sendMsgGroup(const std::string &);
    void	sendMsgGlob(const std::string &);

    void	newFriend(const std::string &, ::User::Status s);
    void	loseFriend(const std::string &);
    void	friendStatus(const std::string &, ::User::Status s);

    void	addPlayerInGroup(const std::string&);
    void	answerGroupRequest(const std::string&, bool);
    void	kickPlayerGroup(const std::string&);
    void	leaveGroup();
    void	deleteGroup();

    void	groupRequest(const std::string&);
    void	newPlayerInGroup(const std::string&, Race::Race r);
    void	playerLeftGroup(const std::string&);
    void	groupLeader(const std::string&);
    void	groupKicked();
    void	groupDeleted();
    void	groupMemberChangedRace(const std::string&, Race::Race);

    void	recvWhisp(const std::string &, const std::string&, const std::string &);
    void	recvMsgGroup(const std::string &, const std::string &);
    void	recvMsgGlob(const std::string &, const std::string &);

    void	success(Command::Command c);
    void	fail(Command::Command c, Error::Code e);

    void	quicklaunch(Room::Type t);
    void	leaveGameSearch();
    void	gameSearching();
    void	endGameSearching();

    void	gameLoading();
    void	gameLaunch();
    void	playerReady(const std::string &);
    void	playerInRoom(const std::string &, Race::Race r, int team, bool rdy);
    void	iAmReady();

    void	fileInfos(const std::string &, unsigned long long, unsigned int);
    void	askFileExists(const std::string &);
    void	fileExists(const std::string &, bool);
    void	fileChunk(const std::string&, unsigned int, const char *, int);

    void	joinSpectator(const std::string &);
    void	leaveSpectator();

    void	createItem(const std::string &, Kernel::ID::id_t, double, double, double, int, Kernel::ID::id_t);
    void	deleteItem(Kernel::ID::id_t);
    void	updateItem(Kernel::ID::id_t, double, double, double, int, unsigned int,
			   unsigned int, unsigned int, unsigned int);
    void	askItemInfo(Kernel::ID::id_t);

    void	heroPickedUpAnObject(Kernel::ID::id_t, Kernel::ID::id_t);
    void	askHeroObjects(Kernel::ID::id_t);
    void	heroObjectsList(Kernel::ID::id_t, const std::vector<Kernel::ID::id_t> &);
    void	heroReleasedObject(Kernel::ID::id_t, Kernel::ID::id_t);
    void	askHeroToTakeObject(Kernel::ID::id_t, Kernel::ID::id_t);
    void	askHeroToReleaseObject(Kernel::ID::id_t, Kernel::ID::id_t, double, double, double);

    void	itemWaypoint(Kernel::ID::id_t, unsigned int, double, double, double, double);
    void	itemMove(Kernel::ID::id_t, double, double, double);
    void	itemStopAction(Kernel::ID::id_t);
    void	itemAction(Kernel::ID::id_t, Game::eAction);
    void	askItemAction(Kernel::ID::id_t);
    void	askSetItemAction(Kernel::ID::id_t, Game::eAction);
    void	askSetItemsAction(Game::eAction, const std::vector<Kernel::ID::id_t> &);
    void	moveItemGroup(double, double, double, bool, const std::vector<Kernel::ID::id_t> &);
    void	askMoveItem(Kernel::ID::id_t, double, double, double);
    void	askActivateCapacity(Kernel::ID::id_t, const Kernel::Serial &);
    void	activateCapacity(Kernel::ID::id_t, const Kernel::Serial &, bool);
    void	askAutomaticCapacity(Kernel::ID::id_t, const Kernel::Serial &, bool);
    void	unitPickingUpRessources(Kernel::ID::id_t, unsigned int, unsigned int, unsigned int);
    void	askUnitPickedUpRessources(Kernel::ID::id_t);
    void	askItemEffects(Kernel::ID::id_t);
    void	stopItemEffect(Kernel::ID::id_t, const Kernel::Serial &);
    void	itemEffect(Kernel::ID::id_t, const Kernel::Serial &, double);
    void	temporaryEffect(Kernel::ID::id_t, const Kernel::Serial &, Kernel::ID::id_t);
    void	removeTemporaryEffect(Kernel::ID::id_t, const Kernel::Serial &, Kernel::ID::id_t);

    void	unitStance(Kernel::ID::id_t, Game::Stance::Type);
    void	unitChangeStance(Kernel::ID::id_t, Game::Stance::Type);
    void	unitGrpStance(const std::vector<Kernel::ID::id_t> &, Game::Stance::Type);
    void	unitAskStance(Kernel::ID::id_t);

    void	dayNightSwitch(bool);
    void	askDayOrNight(void);

    void	ping(Kernel::ID::id_t, double, double);
    void	askPlayerRessources(Kernel::ID::id_t);
    void	playerRessources(Kernel::ID::id_t, unsigned int, unsigned int, unsigned int);

    void	unitCreateBuilding(Kernel::ID::id_t, Kernel::ID::id_t);
    void	unitStopBuildingBuilding(Kernel::ID::id_t, Kernel::ID::id_t);
    void	buildingHasBeenBuilt(Kernel::ID::id_t);
    void	askUnitToBuild(Kernel::ID::id_t, Kernel::ID::id_t);
    void	askUnitsToBuild(Kernel::ID::id_t, const std::vector<Kernel::ID::id_t> &);
    void	askUnitProd(Kernel::ID::id_t, const Kernel::Serial&);
    void	unitProduction(Kernel::ID::id_t, unsigned int, const Kernel::Serial&);
    void	unitHasBeenProduced(Kernel::ID::id_t, const Kernel::Serial &);
    void	askRemoveUnitFromProduction(Kernel::ID::id_t, const Kernel::Serial &);
    void	removeUnitFromProduction(Kernel::ID::id_t, const Kernel::Serial &);

    void	newFriendRequest(const std::string&);
    void	removeFriendRequest(const std::string&);

    void	playerHasAmelioration(Kernel::ID::id_t, const Kernel::Serial &, const Kernel::Serial &);
    void	playerHasJustProducedAmelioration(Kernel::ID::id_t, const Kernel::Serial &, const Kernel::Serial &);
    void	askPlayerAmeliorations(Kernel::ID::id_t);
    void	askProduceAmelioration(const Kernel::Serial &, const Kernel::Serial &);
    void	askRemoveAmeliorationFromProductionQueue(const Kernel::Serial &, const Kernel::Serial &);
    void	removeAmeliorationFromProductionQueue(Kernel::ID::id_t, const Kernel::Serial &, const Kernel::Serial &);
    void	ameliorationProduction(Kernel::ID::id_t, const Kernel::Serial &, const Kernel::Serial &, unsigned int);
    void	askElementAmeliorations(Kernel::ID::id_t, const Kernel::Serial &);

    void	unitHarvest(Kernel::ID::id_t, Kernel::ID::id_t);
    void	unitDeposit(Kernel::ID::id_t, Kernel::ID::id_t);
    void	askUnitHarvest(Kernel::ID::id_t, Kernel::ID::id_t);
    void	askUnitsHarvest(Kernel::ID::id_t, const std::vector<Kernel::ID::id_t> &);
    void	unitStopHarvest(Kernel::ID::id_t);
    void	unitWaitHarvest(Kernel::ID::id_t);
    void	unitStopWaitHarvest(Kernel::ID::id_t);

    void	askSpotID(double, double, double);
    void	ressourceSpot(Kernel::ID::id_t, double, double, double, Game::Ressources::Type, unsigned int);
    void	updateSpot(Kernel::ID::id_t, unsigned int);

    void	itemAttack(Kernel::ID::id_t, Kernel::ID::id_t);
    void	askItemAttack(Kernel::ID::id_t, Kernel::ID::id_t);
    void	askItemsAttack(Kernel::ID::id_t, const std::vector<Kernel::ID::id_t> &);
    void	askItemAttackZone(Kernel::ID::id_t, double, double, double);
    void	askItemsAttackZone(const std::vector<Kernel::ID::id_t> &, double, double, double);
    void	itemAttackZone(Kernel::ID::id_t, double, double, double);

    void	askUnitPatrol(Kernel::ID::id_t, double, double);
    void	askUnitsPatrol(const std::vector<Kernel::ID::id_t> &, double, double, bool);
    // void	unitPatrol(Kernel::ID::id_t, double, double, double);

    void	itemUseCapacity(Kernel::ID::id_t, Kernel::ID::id_t, const Kernel::Serial &);
    void	askItemUseCapacity(Kernel::ID::id_t, Kernel::ID::id_t, const Kernel::Serial &);
    void	itemUseZoneCapacity(Kernel::ID::id_t, const Kernel::Serial &, double, double, double);
    void	askItemUseZoneCapacity(Kernel::ID::id_t, const Kernel::Serial &, double, double, double);

    void	itemUseCapacity(Kernel::ID::id_t, const Kernel::Serial &);

  };

}

std::ostream&	operator<<(std::ostream& os, const Protocol::Job &);

#endif
