//
// Protocol.cpp for ex in /home/deleme/pfa
// 
// Made by anthony delemer
// Login   <deleme_a@epitech.net>
// 
// Started on  Mon Jan 13 17:02:04 2014 anthony delemer
// Last update Wed Mar 26 15:57:31 2014 geoffrey bauduin
//

#include	<cstring>
#include	<iostream>
#include	"Protocol/Job.hpp"
#include	"Converter.hpp"
#include	"Protocol/Error.hpp"
#include	"Factory/Protocol.hpp"

#define		MAX(x, y)	((x) > (y) ? (x) : (y))

Protocol::Job::Job() : _data()
{
  _data._command = Command::ERR;
}

Protocol::Job::~Job() {}

Protocol::Job::nJob *Protocol::Job::getData(void) {
  return (&this->_data);
}

Command::Command	Protocol::Job::getCommand() const {
  return (this->_data._command);
}

const Protocol::Argument* Protocol::Job::getArguments() const {
  return (this->_data._args);
}

void	Protocol::Job::reset() {
  // for (unsigned int i = 0 ; i < 7 ; ++i) {
  //   memset(&this->_data._args[i], 0, sizeof(Protocol::Argument));
  // }
}

void	Protocol::Job::destroy(void) {
}

Protocol::Job	*Protocol::Job::clone(void) const {
  Protocol::Job *job = Factory::Protocol::Job::create();
  job->_data._command = this->_data._command;
  unsigned int i = 0;
  for (auto it : this->_data._args) {
    job->_data._args[i++] = it;
  }
  return (job);
}

void	Protocol::Job::clone(const Protocol::Job *job) {
  this->_data._command = job->_data._command;
  unsigned int i = 0;
  for (auto it : job->_data._args) {
    this->_data._args[i++] = it;
  }
}

void	Protocol::Job::askCreateBuilding(const Kernel::Serial &serial, double x, double y, double z, int o) {
  this->_data._command = Command::ASKCBUILDING;
  strncpy(this->_data._args[0].serial, serial.c_str(), 32);
  this->_data._args[1].pos = x;
  this->_data._args[2].pos = y;
  this->_data._args[3].pos = z;
  this->_data._args[4].orientation = o;
}

void	Protocol::Job::playerInformation(Kernel::ID::id_t id, unsigned int teamID, const Kernel::Serial &serial) {
  this->_data._command = Command::PLAYER;
  this->_data._args[0].kid = id;
  this->_data._args[1].id = teamID;
  strncpy(this->_data._args[2].serial, serial.c_str(), 32);
}

void	Protocol::Job::youAre(Kernel::ID::id_t id) {
  this->_data._command = Command::YOUARE;
  this->_data._args[0].kid = id;
}

void	Protocol::Job::exit() {
  this->_data._command = Command::EXIT;
}

void	Protocol::Job::success(Command::Command c) {
  this->_data._command = Command::SUCCESS;
  this->_data._args[0].command = c;
}

void	Protocol::Job::fail(Command::Command c,Error::Code e) {
  this->_data._command = Command::FAIL;
  this->_data._args[0].command = c;
  this->_data._args[1].error = e;
}

void	Protocol::Job::connection(const std::string &nick, const std::string &pass)
{
  this->_data._command = Command::CO;
  strncpy(this->_data._args[0].pseudo, nick.c_str(), 255);
  strncpy(this->_data._args[1].password, pass.c_str(), 32);
}

void	Protocol::Job::registration(const std::string &nick, const std::string &mail, const std::string &pass)
{
  this->_data._command = Command::REG;
  strncpy(this->_data._args[0].pseudo, nick.c_str(), 255);
  strncpy(this->_data._args[1].mail, mail.c_str(), 255);
  strncpy(this->_data._args[2].password, pass.c_str(), 32);
}

void	Protocol::Job::playerInfos(const std::string& nick, const std::string& mail, const std::string& avatar, ::User::Status s) {
  this->_data._command = Command::PINFOS;
  strncpy(this->_data._args[0].pseudo, nick.c_str(), 255);
  strncpy(this->_data._args[1].mail, mail.c_str(), 255);
  strncpy(this->_data._args[2].avatar, avatar.c_str(), 255);
  this->_data._args[3].userStatus = s;
}

void	Protocol::Job::playerStats(unsigned int wx, unsigned int lx, unsigned int wy, unsigned int ly, unsigned int wz, unsigned int lz) {
  this->_data._command = Command::PSTATS;
  this->_data._args[0].stat = wx;
  this->_data._args[1].stat = lx;
  this->_data._args[2].stat = wy;
  this->_data._args[3].stat = ly;
  this->_data._args[4].stat = wz;
  this->_data._args[5].stat = lz;
}

void	Protocol::Job::setStatus(::User::Status s) {
  this->_data._command = Command::SETSTATUS;
  this->_data._args[0].userStatus = s;
}

void	Protocol::Job::setRace(Race::Race r) {
  this->_data._command = Command::SETRACE;
  this->_data._args[0].race = r;
}

void	Protocol::Job::newFriendRequest(const std::string& nick)
{
  this->reset();

  this->_data._command = Command::NEWFRIENDREQUEST;
  strncpy(this->_data._args[0].pseudo, nick.c_str(), 255);
}

void	Protocol::Job::friendRequest(const std::string &nick)
{
  this->_data._command = Command::AFD;
  strncpy(this->_data._args[0].pseudo, nick.c_str(), 255);
}

void	Protocol::Job::removeFriend(const std::string &nick)
{
  this->_data._command = Command::DFD;
  strncpy(this->_data._args[0].pseudo, nick.c_str(), 255);
}

void	Protocol::Job::answerFriendRequest(const std::string &nick, bool answer)
{
  this->_data._command = Command::AIFD;
  strncpy(this->_data._args[0].pseudo, nick.c_str(), 255);
  this->_data._args[1].yes = answer;
}

void	Protocol::Job::sendWhisp(const std::string &nick, const std::string &msg) {
  this->_data._command = Command::SWH;
  strncpy(this->_data._args[0].pseudo, nick.c_str(), 255);
  strncpy(this->_data._args[1].msg, msg.c_str(), 255);
}

void	Protocol::Job::sendMsgGroup(const std::string &msg) {
  this->_data._command = Command::SMSGGRP;
  strncpy(this->_data._args[0].msg, msg.c_str(), 255);
}

void	Protocol::Job::sendMsgGlob(const std::string &msg) {
  this->_data._command = Command::SMSGGLB;
  strncpy(this->_data._args[0].msg, msg.c_str(), 255);
}

void	Protocol::Job::newFriend(const std::string &nick, ::User::Status s)
{
  this->_data._command = Command::NFD;
  strncpy(this->_data._args[0].pseudo, nick.c_str(), 255);
  this->_data._args[1].userStatus = s;
}

void	Protocol::Job::loseFriend(const std::string &nick)
{
  this->_data._command = Command::LFD;
  strncpy(this->_data._args[0].pseudo, nick.c_str(), 255);
}

void	Protocol::Job::friendStatus(const std::string &nick, ::User::Status status)
{
  this->_data._command = Command::SFD;
  strncpy(this->_data._args[0].pseudo, nick.c_str(), 255);
  this->_data._args[1].userStatus = status;
}

void	Protocol::Job::recvWhisp(const std::string &from, const std::string &to, const std::string &msg)
{
  this->_data._command = Command::RWH;
  strncpy(this->_data._args[0].pseudo, from.c_str(), 255);
  strncpy(this->_data._args[1].pseudo, to.c_str(), 255);
  strncpy(this->_data._args[2].msg, msg.c_str(), 255);
}

void	Protocol::Job::recvMsgGroup(const std::string &nick, const std::string &msg) {
  this->_data._command = Command::RMSGGRP;
  strncpy(this->_data._args[0].pseudo, nick.c_str(), 255);
  strncpy(this->_data._args[1].msg, msg.c_str(), 255);
}

void	Protocol::Job::recvMsgGlob(const std::string &nick, const std::string &msg) {
  this->_data._command = Command::RMSGGLB;
  strncpy(this->_data._args[0].pseudo, nick.c_str(), 255);
  strncpy(this->_data._args[1].msg, msg.c_str(), 255);
}

void	Protocol::Job::addPlayerInGroup(const std::string& nick)
{
  this->_data._command = Command::APIG;
  strncpy(this->_data._args[0].pseudo, nick.c_str(), 32);
}

void	Protocol::Job::answerGroupRequest(const std::string& nick, bool answer)
{
  this->_data._command = Command::AGR;
  strncpy(this->_data._args[0].pseudo, nick.c_str(), 32);
  this->_data._args[1].yes = answer;
}

void	Protocol::Job::kickPlayerGroup(const std::string& nick)
{
  this->_data._command = Command::KPG;
  strncpy(this->_data._args[0].pseudo, nick.c_str(), 32);
}

void	Protocol::Job::leaveGroup() {
  this->_data._command = Command::LVGP;
}

void	Protocol::Job::deleteGroup() {
  this->_data._command = Command::DELGRP;
}

void	Protocol::Job::groupRequest(const std::string& nick)
{
  this->_data._command = Command::GR;
  strncpy(this->_data._args[0].pseudo, nick.c_str(), 32);
}

void	Protocol::Job::newPlayerInGroup(const std::string& nick, Race::Race r)
{
  this->_data._command = Command::NPIG;
  strncpy(this->_data._args[0].pseudo, nick.c_str(), 32);
  this->_data._args[1].race = r;
}

void	Protocol::Job::playerLeftGroup(const std::string& nick)
{
  this->_data._command = Command::PLG;
  strncpy(this->_data._args[0].pseudo, nick.c_str(), 32);
}

void	Protocol::Job::groupLeader(const std::string &nick) {
  this->_data._command = Command::GPLD;
  strncpy(this->_data._args[0].pseudo, nick.c_str(), 32);
}

void	Protocol::Job::groupKicked() {
  this->_data._command = Command::GRPKICKED;
}

void	Protocol::Job::groupDeleted() {
  this->_data._command = Command::GRPDELETED;
}

void	Protocol::Job::groupMemberChangedRace(const std::string &nick, Race::Race r) {
  this->_data._command = Command::GRPMBRCHGRACE;
  strncpy(this->_data._args[0].pseudo, nick.c_str(), 255);
  this->_data._args[1].race = r;
}

void	Protocol::Job::quicklaunch(Room::Type t) {
  this->_data._command = Command::QUICKLAUNCH;
  this->_data._args[0].roomType = t;
}

void	Protocol::Job::leaveGameSearch() {
  this->_data._command = Command::LEAVEGAMESEARCH;
}

void	Protocol::Job::gameSearching() {
  this->_data._command = Command::GAMESEARCHING;
}

void	Protocol::Job::endGameSearching() {
  this->_data._command = Command::ENDGAMESEARCHING;
}

void	Protocol::Job::gameLoading() {
  this->_data._command = Command::GAMELOADING;
}

void	Protocol::Job::gameLaunch() {
  this->_data._command = Command::GAMELAUNCH;
}

void	Protocol::Job::playerInRoom(const std::string &nick, Race::Race r, int team, bool rdy) {
  this->_data._command = Command::PLAYERINROOM;
  strncpy(this->_data._args[0].pseudo, nick.c_str(), 255);
  this->_data._args[1].race = r;
  this->_data._args[2].team = team;
  this->_data._args[3].yes = rdy;
}

void	Protocol::Job::playerReady(const std::string &nick) {
  this->_data._command = Command::PLAYERREADY;
  strncpy(this->_data._args[0].pseudo, nick.c_str(), 255);
}

void	Protocol::Job::iAmReady() {
  this->_data._command = Command::IAMREADY;
}

void	Protocol::Job::fileInfos(const std::string &filename,  unsigned long long size, unsigned int nb_chunk) {
  this->_data._command = Command::FINFOS;
  strncpy(this->_data._args[0].filename, filename.c_str(), 255);
  this->_data._args[1].filesize = size;
  this->_data._args[2].nb_chunk = nb_chunk;
}

void	Protocol::Job::askFileExists(const std::string &filename) {
  this->_data._command = Command::ASKFILEEXISTS;
  strncpy(this->_data._args[0].filename, filename.c_str(), 255);
}

void	Protocol::Job::fileExists(const std::string &filename, bool answer) {
  this->_data._command = Command::FILEEXISTS;
  strncpy(this->_data._args[0].filename, filename.c_str(), 255);
  this->_data._args[1].yes = answer;
}

void	Protocol::Job::fileChunk(const std::string &filename, unsigned int id, const char *chunk, int size_chunk) {
  this->_data._command = Command::FILECHUNK;
  strncpy(this->_data._args[0].filename, filename.c_str(), 255);
  this->_data._args[1].id_chunk = id;
  this->_data._args[2].size_chunk = size_chunk;
  memcpy(this->_data._args[3].filechunk, chunk, size_chunk);
}

void	Protocol::Job::joinSpectator(const std::string &target) {
  this->_data._command = Command::JOINSPECTATOR;
  strncpy(this->_data._args[0].pseudo, target.c_str(), 255);
}

void	Protocol::Job::leaveSpectator() {
  this->_data._command = Command::LEAVESPECTATOR;
}

void	Protocol::Job::createItem(const std::string &serial, Kernel::ID::id_t id, double x, double y, double z, int orientation, Kernel::ID::id_t playerID) {
  this->_data._command = Command::OCREATE;
  strncpy(this->_data._args[0].serial, serial.c_str(), 32);
  this->_data._args[1].kid = id;
  this->_data._args[2].pos = x;
  this->_data._args[3].pos = y;
  this->_data._args[4].pos = z;
  this->_data._args[5].orientation = orientation;
  this->_data._args[6].kid = playerID;
}

void	Protocol::Job::deleteItem(Kernel::ID::id_t id) {
  this->_data._command = Command::ODESTROY;
  this->_data._args[0].kid = id;
}

void	Protocol::Job::updateItem(Kernel::ID::id_t id, double x, double y, double z, int orientation,
				  unsigned int currentLife, unsigned int currentRess, unsigned int xp,
				  unsigned int level) {
  this->_data._command = Command::OMAJ;
  this->_data._args[0].kid = id;
  this->_data._args[1].position[0] = x;
  this->_data._args[1].position[1] = y;
  this->_data._args[1].position[2] = z;
  this->_data._args[2].orientation = orientation;
  this->_data._args[3].currentLife = currentLife;
  this->_data._args[4].currentRess = currentRess;
  this->_data._args[5].amount = xp;
  this->_data._args[6].amount = level;
}

void	Protocol::Job::itemWaypoint(Kernel::ID::id_t id, unsigned int wpID, double x, double y, double z, double speed) {
  this->_data._command = Command::OWP;
  this->_data._args[0].kid = id;
  this->_data._args[1].wpID = wpID;
  this->_data._args[2].pos = x;
  this->_data._args[3].pos = y;
  this->_data._args[4].pos = z;
  this->_data._args[5].speed = speed;
}

void	Protocol::Job::itemStopAction(Kernel::ID::id_t id) {
  this->_data._command = Command::OSTOP;
  this->_data._args[0].kid = id;
}

void	Protocol::Job::itemAction(Kernel::ID::id_t id, Game::eAction action) {
  this->_data._command = Command::OACT;
  this->_data._args[0].kid = id;
  this->_data._args[1].action = action;
}

unsigned int	Protocol::Job::createIDArray(const std::vector<Kernel::ID::id_t> &vector, unsigned int j) {
  unsigned int i = 0;
  unsigned int amount = 0;
  for (auto it : vector) {
    this->_data._args[j].grp[i++] = it;
    ++amount;
    if (i % GRP_SIZE == 0) {
      ++j;
      if (j >= 7) {
	break;
      }
      i = 0;
    }
  }
  return (amount);
}

void	Protocol::Job::moveItemGroup(double x, double y, double z, bool adapt, const std::vector<Kernel::ID::id_t> &units) {
  this->_data._command = Command::OGRPMOVE;
  this->_data._args[0].pos = x;
  this->_data._args[1].pos = y;
  this->_data._args[2].pos = z;
  this->_data._args[3].adapt = adapt;
  this->_data._args[4].amount = this->createIDArray(units, 5);
}

void	Protocol::Job::ping(Kernel::ID::id_t playerID, double x, double y) {
  this->_data._command = Command::PING;
  this->_data._args[0].kid = playerID;
  this->_data._args[1].pos = x;
  this->_data._args[2].pos = y;
}

void	Protocol::Job::unitStance(Kernel::ID::id_t id, Game::Stance::Type stance) {
  this->_data._command = Command::USTANCE;
  this->_data._args[0].kid = id;
  this->_data._args[1].stance = stance;
}

void	Protocol::Job::unitChangeStance(Kernel::ID::id_t id, Game::Stance::Type stance) {
  this->_data._command = Command::UCHGSTANCE;
  this->_data._args[0].kid = id;
  this->_data._args[1].stance = stance;
}

void	Protocol::Job::unitGrpStance(const std::vector<Kernel::ID::id_t> &units, Game::Stance::Type stance) {
  this->_data._command = Command::UCHGGRPSTANCE;
  this->_data._args[0].stance = stance;
  this->_data._args[1].amount = this->createIDArray(units, 2);;
}

void	Protocol::Job::unitAskStance(Kernel::ID::id_t id) {
  this->_data._command = Command::UASKSTANCE;
  this->_data._args[0].kid = id;
}

void	Protocol::Job::askItemInfo(Kernel::ID::id_t id) {
  this->_data._command = Command::OASKINFO;
  this->_data._args[0].kid = id;
}

void	Protocol::Job::askMoveItem(Kernel::ID::id_t id, double x, double y, double z) {
  this->_data._command = Command::OASKMOVE;
  this->_data._args[0].kid = id;
  this->_data._args[1].pos = x;
  this->_data._args[2].pos = y;
  this->_data._args[3].pos = z;
}

void	Protocol::Job::dayNightSwitch(bool day) {
  this->_data._command = Command::DAYNIGHT;
  this->_data._args[0].day = day;
}

void	Protocol::Job::askDayOrNight(void) {
  this->_data._command = Command::ASKDAYNIGHT;
}

void	Protocol::Job::playerRessources(Kernel::ID::id_t id, unsigned int ress1, unsigned int ress2, unsigned int ress3) {
  this->_data._command = Command::PRESS;
  this->_data._args[0].kid = id;
  this->_data._args[1].amount = ress1;
  this->_data._args[2].amount = ress2;
  this->_data._args[3].amount = ress3;
}

void	Protocol::Job::askPlayerRessources(Kernel::ID::id_t id) {
  this->_data._command = Command::ASKPRESS;
  this->_data._args[0].kid = id;
}

void	Protocol::Job::itemMove(Kernel::ID::id_t id, double x, double y, double z) {
  this->_data._command = Command::OMOVE;
  this->_data._args[0].kid = id;
  this->_data._args[1].pos = x;
  this->_data._args[2].pos = y;
  this->_data._args[3].pos = z;
}

void	Protocol::Job::askItemAction(Kernel::ID::id_t id) {
  this->_data._command = Command::OASKACT;
  this->_data._args[0].kid = id;
}

void	Protocol::Job::askActivateCapacity(Kernel::ID::id_t id, const Kernel::Serial &serial) {
  this->_data._command = Command::OASKACTCAPA;
  this->_data._args[0].kid = id;
  strncpy(this->_data._args[1].serial, serial.c_str(), 32);
}

void	Protocol::Job::unitCreateBuilding(Kernel::ID::id_t item_id, Kernel::ID::id_t item_id2) {
  this->_data._command = Command::UBUILD;
  this->_data._args[0].kid = item_id;
  this->_data._args[1].kid = item_id2;
}

void	Protocol::Job::askUnitProd(Kernel::ID::id_t item_id, const Kernel::Serial& serial) {
  this->_data._command = Command::UASKPROD;
  this->_data._args[0].kid = item_id;
  strncpy(this->_data._args[1].serial, serial.c_str(), 32);
}

void	Protocol::Job::unitProduction(Kernel::ID::id_t item_id, unsigned int queue_id, const Kernel::Serial& serial) {
  this->_data._command = Command::UPROD;
  this->_data._args[0].kid = item_id;
  this->_data._args[1].queue_id = queue_id;
  strncpy(this->_data._args[2].serial, serial.c_str(), 32);
}

void	Protocol::Job::activateCapacity(Kernel::ID::id_t id, const Kernel::Serial &serial, bool act) {
  this->_data._command = Command::OACTCAPA;
  this->_data._args[0].kid = id;
  strncpy(this->_data._args[1].serial, serial.c_str(), 32);
  this->_data._args[2].activated = act;
}

void	Protocol::Job::unitPickingUpRessources(Kernel::ID::id_t id, unsigned int ress1, unsigned int ress2, unsigned int ress3) {
  this->_data._command = Command::UPURESS;
  this->_data._args[0].kid = id;
  this->_data._args[1].amount = ress1;
  this->_data._args[2].amount = ress2;
  this->_data._args[3].amount = ress3;
}

void	Protocol::Job::askUnitPickedUpRessources(Kernel::ID::id_t id) {
  this->_data._command = Command::ASKUPURESS;
  this->_data._args[0].kid = id;
}

void	Protocol::Job::askItemEffects(Kernel::ID::id_t id) {
  this->_data._command = Command::ASKOEFFECT;
  this->_data._args[0].kid = id;
}

void	Protocol::Job::stopItemEffect(Kernel::ID::id_t id, const Kernel::Serial &serial) {
  this->_data._command = Command::OSTOPEFFECT;
  this->_data._args[0].kid = id;
  strncpy(this->_data._args[1].serial, serial.c_str(), 32);
}

void	Protocol::Job::itemEffect(Kernel::ID::id_t id, const Kernel::Serial &serial, double percentage) {
  this->_data._command = Command::OEFFECT;
  this->_data._args[0].kid = id;
  strncpy(this->_data._args[1].serial, serial.c_str(), 32);
  this->_data._args[2].percentage = percentage;
}

void	Protocol::Job::askSetItemAction(Kernel::ID::id_t id, Game::eAction action) {
  this->_data._command = Command::OSETACTION;
  this->_data._args[0].kid = id;
  this->_data._args[1].action = action;
}

void	Protocol::Job::askSetItemsAction(Game::eAction action, const std::vector<Kernel::ID::id_t> &items) {
  this->_data._command = Command::OSETACTIONS;
  this->_data._args[0].action = action;
  this->_data._args[1].amount = this->createIDArray(items, 2);
}

void	Protocol::Job::unitHasBeenProduced(Kernel::ID::id_t id, const Kernel::Serial &serial) {
  this->_data._command = Command::BPRODF;
  this->_data._args[0].kid = id;
  strncpy(this->_data._args[1].serial, serial.c_str(), 32);
}

void	Protocol::Job::askRemoveUnitFromProduction(Kernel::ID::id_t id, const Kernel::Serial &serial) {
  this->_data._command = Command::UASKDPROD;
  this->_data._args[0].kid = id;
  strncpy(this->_data._args[1].serial, serial.c_str(), 32);
}

void	Protocol::Job::removeUnitFromProduction(Kernel::ID::id_t id, const Kernel::Serial &serial) {
  this->_data._command = Command::UDPROD;
  this->_data._args[0].kid = id;
  strncpy(this->_data._args[1].serial, serial.c_str(), 32);
}

void	Protocol::Job::heroPickedUpAnObject(Kernel::ID::id_t hero, Kernel::ID::id_t object) {
  this->_data._command = Command::HPUOBJ;
  this->_data._args[0].kid = hero;
  this->_data._args[1].kid = object;
}

void	Protocol::Job::askHeroObjects(Kernel::ID::id_t hero) {
  this->_data._command = Command::ASKHOBJ;
  this->_data._args[0].kid = hero;
}

void	Protocol::Job::heroObjectsList(Kernel::ID::id_t hero, const std::vector<Kernel::ID::id_t> &objects) {
  this->_data._command = Command::HPUOBJS;
  this->_data._args[0].kid = hero;
  this->_data._args[1].amount = this->createIDArray(objects, 2);
}

void	Protocol::Job::heroReleasedObject(Kernel::ID::id_t hero, Kernel::ID::id_t object) {
  this->_data._command = Command::HROBJ;
  this->_data._args[0].kid = hero;
  this->_data._args[1].kid = object;
}

void	Protocol::Job::askHeroToTakeObject(Kernel::ID::id_t hero, Kernel::ID::id_t object) {
  this->_data._command = Command::ASKHPUOBJ;
  this->_data._args[0].kid = hero;
  this->_data._args[1].kid = object;
}

void	Protocol::Job::askHeroToReleaseObject(Kernel::ID::id_t hero, Kernel::ID::id_t object, double x, double y, double z) {
  this->_data._command = Command::ASKHROBJ;
  this->_data._args[0].kid = hero;
  this->_data._args[1].kid = object;
  this->_data._args[2].pos = x;
  this->_data._args[3].pos = y;
  this->_data._args[4].pos = z;
}

void	Protocol::Job::playerHasAmelioration(Kernel::ID::id_t playerID, const Kernel::Serial &unit, const Kernel::Serial &amelioration) {
  this->_data._command = Command::PAMELIO;
  this->_data._args[0].kid = playerID;
  strncpy(this->_data._args[1].serial, unit.c_str(), 32);
  strncpy(this->_data._args[2].serial, amelioration.c_str(), 32);
}

void	Protocol::Job::playerHasJustProducedAmelioration(Kernel::ID::id_t playerID, const Kernel::Serial &unit, const Kernel::Serial &amelioration) {
  this->_data._command = Command::PPRODAMELIO;
  this->_data._args[0].kid = playerID;
  strncpy(this->_data._args[1].serial, unit.c_str(), 32);
  strncpy(this->_data._args[2].serial, amelioration.c_str(), 32);
}

void	Protocol::Job::askPlayerAmeliorations(Kernel::ID::id_t playerID) {
  this->_data._command = Command::ASKPAMELIO;
  this->_data._args[0].kid = playerID;
}

void	Protocol::Job::askProduceAmelioration(const Kernel::Serial &type, const Kernel::Serial &amelioration) {
  this->_data._command = Command::ASKPRODAMELIO;
  strncpy(this->_data._args[0].serial, type.c_str(), 32);
  strncpy(this->_data._args[1].serial, amelioration.c_str(), 32);
}

void	Protocol::Job::askRemoveAmeliorationFromProductionQueue(const Kernel::Serial &type, const Kernel::Serial &amelioration) {
  this->_data._command = Command::ASKDAMELIO;
  strncpy(this->_data._args[0].serial, type.c_str(), 32);
  strncpy(this->_data._args[1].serial, amelioration.c_str(), 32);
}

void	Protocol::Job::removeAmeliorationFromProductionQueue(Kernel::ID::id_t playerID, const Kernel::Serial &type, const Kernel::Serial &amelioration) {
  this->_data._command = Command::DAMELIO;
  this->_data._args[0].kid = playerID;
  strncpy(this->_data._args[1].serial, type.c_str(), 32);
  strncpy(this->_data._args[2].serial, amelioration.c_str(), 32);
}

void	Protocol::Job::ameliorationProduction(Kernel::ID::id_t playerID, const Kernel::Serial &type, const Kernel::Serial &amelioration, unsigned int queue_id) {
  this->_data._command = Command::PRODAMELIO;
  this->_data._args[0].kid = playerID;
  strncpy(this->_data._args[1].serial, type.c_str(), 32);
  strncpy(this->_data._args[2].serial, amelioration.c_str(), 32);
  this->_data._args[3].queue_id = queue_id;
}

void	Protocol::Job::askElementAmeliorations(Kernel::ID::id_t playerID, const Kernel::Serial &type) {
  this->_data._command = Command::ASKPSAMELIO;
  this->_data._args[0].kid = playerID;
  strncpy(this->_data._args[1].serial, type.c_str(), 32);
}

void	Protocol::Job::askUnitToBuild(Kernel::ID::id_t unitID, Kernel::ID::id_t buildingID) {
  this->_data._command = Command::UASKBUILD;
  this->_data._args[0].kid = unitID;
  this->_data._args[1].kid = buildingID;
}

void	Protocol::Job::unitStopBuildingBuilding(Kernel::ID::id_t unitID, Kernel::ID::id_t buildingID) {
  this->_data._command = Command::USTOPBUILD;
  this->_data._args[0].kid = unitID;
  this->_data._args[1].kid = buildingID;
}

void	Protocol::Job::buildingHasBeenBuilt(Kernel::ID::id_t id) {
  this->_data._command = Command::BBUILT;
  this->_data._args[0].kid = id;
}

void	Protocol::Job::unitHarvest(Kernel::ID::id_t unit, Kernel::ID::id_t spot) {
  this->_data._command = Command::UHARVEST;
  this->_data._args[0].kid = unit;
  this->_data._args[1].kid = spot;
}

void	Protocol::Job::unitDeposit(Kernel::ID::id_t unit, Kernel::ID::id_t building) {
  this->_data._command = Command::UDEPOSIT;
  this->_data._args[0].kid = unit;
  this->_data._args[1].kid = building;
}

void	Protocol::Job::askUnitHarvest(Kernel::ID::id_t unit, Kernel::ID::id_t spot) {
  this->_data._command = Command::UASKHARVEST;
  this->_data._args[0].kid = unit;
  this->_data._args[1].kid = spot;
}

void	Protocol::Job::askUnitsHarvest(Kernel::ID::id_t spot, const std::vector<Kernel::ID::id_t> &units) {
  this->_data._command = Command::USASKHARVEST;
  this->_data._args[0].kid = spot;
  this->_data._args[1].amount = this->createIDArray(units, 2);
}

void	Protocol::Job::askSpotID(double x, double y, double z) {
  this->_data._command = Command::ASKRESSSPOTID;
  this->_data._args[0].pos = x;
  this->_data._args[1].pos = y;
  this->_data._args[2].pos = z;
}

void	Protocol::Job::ressourceSpot(Kernel::ID::id_t id, double x, double y, double z, Game::Ressources::Type type, unsigned int amount) {
  this->_data._command = Command::RESSSPOT;
  this->_data._args[0].kid = id;
  this->_data._args[1].pos = x;
  this->_data._args[2].pos = y;
  this->_data._args[3].pos = z;
  this->_data._args[4].ressourceType = type;
  this->_data._args[5].amount = amount;
}

void	Protocol::Job::updateSpot(Kernel::ID::id_t id, unsigned int amount) {
  this->_data._command = Command::UPDSPOT;
  this->_data._args[0].kid = id;
  this->_data._args[1].amount = amount;
}

void	Protocol::Job::unitStopHarvest(Kernel::ID::id_t id) {
  this->_data._command = Command::USTOPHARVEST;
  this->_data._args[0].kid = id;
}

void	Protocol::Job::unitWaitHarvest(Kernel::ID::id_t id) {
  this->_data._command = Command::UWAITHARVEST;
  this->_data._args[0].kid = id;
}

void	Protocol::Job::unitStopWaitHarvest(Kernel::ID::id_t id) {
  this->_data._command = Command::USTOPWAITHARVEST;
  this->_data._args[0].kid = id;
}

void	Protocol::Job::temporaryEffect(Kernel::ID::id_t itemID, const Kernel::Serial &serial, Kernel::ID::id_t fromID) {
  this->_data._command = Command::OTMPEFFECT;
  this->_data._args[0].kid = itemID;
  strncpy(this->_data._args[1].serial, serial.c_str(), 32);
  this->_data._args[2].kid = fromID;
}

void	Protocol::Job::removeTemporaryEffect(Kernel::ID::id_t itemID, const Kernel::Serial &serial, Kernel::ID::id_t fromID) {
  this->_data._command = Command::OSTOPTMPEFFECT;
  this->_data._args[0].kid = itemID;
  strncpy(this->_data._args[1].serial, serial.c_str(), 32);
  this->_data._args[2].kid = fromID;
}

void	Protocol::Job::askAutomaticCapacity(Kernel::ID::id_t itemID, const Kernel::Serial &serial, bool automatic) {
  this->_data._command = Command::OASKAUTOCAPA;
  this->_data._args[0].kid = itemID;
  strncpy(this->_data._args[1].serial, serial.c_str(), 32);
  this->_data._args[2].automatic = automatic;
}

void	Protocol::Job::askUnitsToBuild(Kernel::ID::id_t buildingID, const std::vector<Kernel::ID::id_t> &units) {
  this->_data._command = Command::USASKBUILD;
  this->_data._args[0].kid = buildingID;
  this->_data._args[1].amount = this->createIDArray(units, 2);
}

void	Protocol::Job::itemAttack(Kernel::ID::id_t itemID, Kernel::ID::id_t otherItemID) {
  this->_data._command = Command::OATTACK;
  this->_data._args[0].kid = itemID;
  this->_data._args[1].kid = otherItemID;
}

void	Protocol::Job::askItemAttack(Kernel::ID::id_t itemID, Kernel::ID::id_t otherItemID) {
  this->_data._command = Command::ASKOATTACK;
  this->_data._args[0].kid = itemID;
  this->_data._args[1].kid = otherItemID;
}

void	Protocol::Job::itemUseCapacity(Kernel::ID::id_t itemID, Kernel::ID::id_t otherItemID,
				       const Kernel::Serial &capacity) {
  this->_data._command = Command::OUSECAP;
  this->_data._args[0].kid = itemID;
  this->_data._args[1].kid = otherItemID;
  strncpy(this->_data._args[2].serial, capacity.c_str(), 32);
}

void	Protocol::Job::askItemUseCapacity(Kernel::ID::id_t itemID, Kernel::ID::id_t otherItemID,
				       const Kernel::Serial &capacity) {
  this->_data._command = Command::ASKOUSECAP;
  this->_data._args[0].kid = itemID;
  this->_data._args[1].kid = otherItemID;
  strncpy(this->_data._args[2].serial, capacity.c_str(), 32);
}

void	Protocol::Job::askUnitPatrol(Kernel::ID::id_t unitID, double x, double y) {
  this->_data._command = Command::ASKUPATROL;
  this->_data._args[0].kid = unitID;
  this->_data._args[1].pos = x;
  this->_data._args[2].pos = y;
}

void	Protocol::Job::askUnitsPatrol(const std::vector<Kernel::ID::id_t> &units, double x, double y, bool adapt) {
  this->_data._command = Command::ASKUSPATROL;
  this->_data._args[0].pos = x;
  this->_data._args[1].pos = y;
  this->_data._args[2].adapt = adapt;
  this->_data._args[3].amount = this->createIDArray(units, 4);
}

// void	Protocol::Job::unitPatrol(Kernel::ID::id_t unitID, double x, double y, double speed) {
//   this->_data._command = Command::UPATROL;
//   this->_data._args[0].kid = unitID;
//   this->_data._args[1].pos = x;
//   this->_data._args[2].pos = y;
//   this->_data._args[3].speed = speed;
// }

void	Protocol::Job::askItemsAttack(Kernel::ID::id_t target, const std::vector<Kernel::ID::id_t> &sources) {
  this->_data._command = Command::ASKOSATTACK;
  this->_data._args[0].kid = target;
  this->_data._args[1].amount = this->createIDArray(sources, 2);
}

void	Protocol::Job::askItemAttackZone(Kernel::ID::id_t id, double x, double y, double z) {
  this->_data._command = Command::ASKOZONEATTACK;
  this->_data._args[0].kid = id;
  this->_data._args[1].pos = x;
  this->_data._args[2].pos = y;
  this->_data._args[3].pos = z;
}

void	Protocol::Job::askItemsAttackZone(const std::vector<Kernel::ID::id_t> &items, double x, double y, double z) {
  this->_data._command = Command::ASKOSZONEATTACK;
  this->_data._args[0].pos = x;
  this->_data._args[1].pos = y;
  this->_data._args[2].pos = z;
  this->_data._args[3].amount = this->createIDArray(items, 4);
}

void	Protocol::Job::itemAttackZone(Kernel::ID::id_t id, double x, double y, double z) {
  this->_data._command = Command::OZONEATTACK;
  this->_data._args[0].kid = id;
  this->_data._args[1].pos = x;
  this->_data._args[2].pos = y;
  this->_data._args[3].pos = z;
}

void	Protocol::Job::askItemUseZoneCapacity(Kernel::ID::id_t id, const Kernel::Serial &capacity,
					      double x, double y, double z) {
  this->_data._command = Command::ASKOUSEZONECAP;
  this->_data._args[0].kid = id;
  strncpy(this->_data._args[1].serial, capacity.c_str(), 32);
  this->_data._args[2].pos = x;
  this->_data._args[3].pos = y;
  this->_data._args[4].pos = z;
}

void	Protocol::Job::itemUseZoneCapacity(Kernel::ID::id_t id, const Kernel::Serial &capacity,
					      double x, double y, double z) {
  this->_data._command = Command::OUSEZONECAP;
  this->_data._args[0].kid = id;
  strncpy(this->_data._args[1].serial, capacity.c_str(), 32);
  this->_data._args[2].pos = x;
  this->_data._args[3].pos = y;
  this->_data._args[4].pos = z;
}

void	Protocol::Job::itemUseCapacity(Kernel::ID::id_t id, const Kernel::Serial &capacity) {
  this->_data._command = Command::OUSECAPA;
  this->_data._args[0].kid = id;
  strncpy(this->_data._args[1].serial, capacity.c_str(), 32);
}


struct data_map_ {
  Command::Command command;
  Protocol::ArgType data[7];
};

using namespace Protocol;

static const data_map_ data_map[] = {
  {Command::EXIT, {NONE, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::CO, {STRING256, STRING33, NONE, NONE, NONE, NONE, NONE}},
  {Command::REG, {STRING256, STRING256, STRING33, NONE, NONE, NONE, NONE}},
  {Command::PINFOS, {STRING256, STRING256, STRING256, NONE, NONE, NONE, NONE}},
  {Command::PSTATS, {UINT, UINT, UINT, UINT, UINT, UINT, NONE}},
  {Command::SETSTATUS, {USERSTATUS, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::SETRACE, {RACE, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::AFD, {STRING256, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::DFD, {STRING256, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::AIFD, {BOOL, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::SWH, {STRING256, STRING256, NONE, NONE, NONE, NONE, NONE}},
  {Command::SMSGGLB, {STRING256, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::RMSGGLB, {STRING256, STRING256, NONE, NONE, NONE, NONE, NONE}},
  {Command::SMSGGRP, {STRING256, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::NFD, {STRING256, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::LFD, {STRING256, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::SFD, {STRING256, USERSTATUS, NONE, NONE, NONE, NONE, NONE}},
  {Command::APIG, {STRING33, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::AGR, {STRING33, BOOL, NONE, NONE, NONE, NONE, NONE}},
  {Command::KPG, {STRING33, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::LVGP, {NONE, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::DELGRP, {NONE, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::GR, {STRING33, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::NPIG, {STRING256, RACE, NONE, NONE, NONE, NONE, NONE}},
  {Command::PLG, {STRING256, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::GPLD, {STRING33, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::GRPKICKED, {NONE, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::GRPDELETED, {NONE, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::GRPMBRCHGRACE, {STRING33, RACE, NONE, NONE, NONE, NONE, NONE}},
  {Command::RWH, {STRING256, STRING256, NONE, NONE, NONE, NONE, NONE}},
  {Command::RMSGGRP, {STRING256, STRING256, NONE, NONE, NONE, NONE, NONE}},
  {Command::SUCCESS, {COMMAND, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::FAIL, {COMMAND, ERROR, NONE, NONE, NONE, NONE, NONE}},
  {Command::QUICKLAUNCH, {ROOM, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::LEAVEGAMESEARCH, {NONE, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::GAMESEARCHING, {NONE, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::ENDGAMESEARCHING, {NONE, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::GAMELOADING, {NONE, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::GAMELAUNCH, {NONE, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::PLAYERINROOM, {STRING256, RACE, INT, BOOL, NONE, NONE, NONE}},
  {Command::PLAYERREADY, {STRING256, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::IAMREADY, {NONE, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::GAMEREADY, {NONE, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::FINFOS, {STRING256, ULL, UINT, NONE, NONE, NONE, NONE}},
  {Command::ASKFILEEXISTS, {STRING256, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::FILEEXISTS, {STRING256, BOOL, NONE, NONE, NONE, NONE, NONE}},
  {Command::FILECHUNK, {NONE, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::OCREATE, {STRING33, KID, DOUBLE, DOUBLE, DOUBLE, INT, KID}},
  {Command::ODESTROY, {KID, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::OMAJ, {KID, DOUBLE3, INT, UINT, UINT, UINT, UINT}},
  {Command::OWP, {KID, UINT, DOUBLE, DOUBLE, DOUBLE, DOUBLE, NONE}},
  {Command::OSTOP, {KID, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::OACT, {KID, EACTION, NONE, NONE, NONE, NONE, NONE}},
  {Command::OGRPMOVE, {DOUBLE, DOUBLE, DOUBLE, BOOL, UINT, KID64, KID64}},
  {Command::PING, {KID, DOUBLE, DOUBLE, NONE, NONE, NONE, NONE}},
  {Command::USTANCE, {KID, STANCE, NONE, NONE, NONE, NONE, NONE}},
  {Command::UCHGSTANCE, {KID, STANCE, NONE, NONE, NONE, NONE, NONE}},
  {Command::UCHGGRPSTANCE, {STANCE, UINT, KID64, KID64, KID64, KID64, KID64}},
  {Command::UASKSTANCE, {KID, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::OASKINFO, {KID, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::OASKMOVE, {KID, DOUBLE, DOUBLE, DOUBLE, NONE, NONE, NONE}},
  {Command::DAYNIGHT, {BOOL, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::ASKDAYNIGHT, {NONE, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::PRESS, {KID, UINT, UINT, UINT, NONE, NONE, NONE}},
  {Command::ASKPRESS, {KID, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::OMOVE, {KID, DOUBLE, DOUBLE, DOUBLE, NONE, NONE, NONE}},
  {Command::OASKACT, {KID, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::OASKACTCAPA, {KID, STRING33, NONE, NONE, NONE, NONE, NONE}},
  {Command::UBUILD, {KID, KID, NONE, NONE, NONE, NONE, NONE}},
  {Command::UASKPROD, {KID, STRING33, NONE, NONE, NONE, NONE, NONE}},
  {Command::UPROD, {KID, UINT, STRING33, NONE, NONE, NONE, NONE}},
  {Command::NEWFRIENDREQUEST, {STRING256, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::REMOVEFRIENDREQUEST, {NONE, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::OACTCAPA, {KID, STRING33, BOOL, NONE, NONE, NONE, NONE}},
  {Command::UPURESS, {KID, UINT, UINT, UINT, NONE, NONE, NONE}},
  {Command::ASKUPURESS, {KID, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::ASKOEFFECT, {KID, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::OSTOPEFFECT, {KID, STRING33, NONE, NONE, NONE, NONE, NONE}},
  {Command::OEFFECT, {KID, STRING33, DOUBLE, NONE, NONE, NONE, NONE}},
  {Command::OEFFECTS, {NONE, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::BPRODF, {NONE, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::OSETACTION, {KID, EACTION, NONE, NONE, NONE, NONE, NONE}},
  {Command::OSETACTIONS, {EACTION, UINT, KID64, KID64, KID64, KID64, KID64}},
  {Command::UASKDPROD, {KID, STRING33, NONE, NONE, NONE, NONE, NONE}},
  {Command::UDPROD, {KID, STRING33, NONE, NONE, NONE, NONE, NONE}},
  {Command::HPUOBJ, {KID, KID, NONE, NONE, NONE, NONE, NONE}},
  {Command::ASKHOBJ, {KID, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::HPUOBJS, {KID, UINT, KID64, KID64, KID64, KID64, KID64}},
  {Command::HROBJ, {KID, KID, NONE, NONE, NONE, NONE, NONE}},
  {Command::ASKHPUOBJ, {KID, KID, NONE, NONE, NONE, NONE, NONE}},
  {Command::ASKHROBJ, {KID, KID, DOUBLE, DOUBLE, DOUBLE, NONE, NONE}},
  {Command::PAMELIO, {KID, STRING33, STRING33, NONE, NONE, NONE, NONE}},
  {Command::PPRODAMELIO, {KID, STRING33, STRING33, NONE, NONE, NONE, NONE}},
  {Command::ASKPAMELIO, {KID, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::ASKPRODAMELIO, {STRING33, STRING33, NONE, NONE, NONE, NONE, NONE}},
  {Command::ASKDAMELIO, {STRING33, STRING33, NONE, NONE, NONE, NONE, NONE}},
  {Command::DAMELIO, {KID, STRING33, STRING33, NONE, NONE, NONE, NONE}},
  {Command::PRODAMELIO, {KID, STRING33, STRING33, UINT, NONE, NONE, NONE}},
  {Command::ASKPSAMELIO, {KID, STRING33, NONE, NONE, NONE, NONE, NONE}},
  {Command::UASKBUILD, {KID, KID, NONE, NONE, NONE, NONE, NONE}},
  {Command::USTOPBUILD, {KID, KID, NONE, NONE, NONE, NONE, NONE}},
  {Command::BBUILT, {KID, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::UHARVEST, {KID, KID, NONE, NONE, NONE, NONE, NONE}},
  {Command::UASKHARVEST, {KID, KID, NONE, NONE, NONE, NONE, NONE}},
  {Command::USASKHARVEST, {KID, UINT, KID64, KID64, KID64, KID64, KID64}},
  {Command::ASKRESSSPOTID, {DOUBLE, DOUBLE, DOUBLE, NONE, NONE, NONE, NONE}},
  {Command::RESSSPOT, {KID, DOUBLE, DOUBLE, DOUBLE, RESSTYPE, UINT, NONE}},
  {Command::UPDSPOT, {KID, UINT, NONE, NONE, NONE, NONE, NONE}},
  {Command::UWAITHARVEST, {KID, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::USTOPWAITHARVEST, {KID, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::USTOPHARVEST, {KID, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::OTMPEFFECT, {KID, STRING33, KID, NONE, NONE, NONE, NONE}},
  {Command::OSTOPTMPEFFECT, {KID, STRING33, KID, NONE, NONE, NONE, NONE}},
  {Command::OASKAUTOCAPA, {KID, STRING33, BOOL, NONE, NONE, NONE, NONE}},
  {Command::USASKBUILD, {KID, UINT, KID64, KID64, KID64, KID64, KID64}},
  {Command::OATTACK, {KID, KID, NONE, NONE, NONE, NONE, NONE}},
  {Command::ASKOATTACK, {KID, KID, NONE, NONE, NONE, NONE, NONE}},
  {Command::OUSECAP, {KID, KID, STRING33, NONE, NONE, NONE, NONE}},
  {Command::ASKOUSECAP, {KID, KID, STRING33, NONE, NONE, NONE, NONE}},
  {Command::ASKUPATROL, {KID, DOUBLE, DOUBLE, NONE, NONE, NONE, NONE}},
  {Command::ASKUSPATROL, {DOUBLE, DOUBLE, BOOL, UINT, KID64, KID64, KID64}},
  {Command::ASKOSATTACK, {KID, UINT, KID64, KID64, KID64, KID64, KID64}},
  {Command::ASKOZONEATTACK, {KID, DOUBLE, DOUBLE, DOUBLE, NONE, NONE, NONE}},
  {Command::ASKOSZONEATTACK, {DOUBLE, DOUBLE, DOUBLE, UINT, KID64, KID64, KID64}},
  {Command::OZONEATTACK, {KID, DOUBLE, DOUBLE, DOUBLE, NONE, NONE, NONE}},
  {Command::ASKOUSEZONECAP, {KID, STRING33, DOUBLE, DOUBLE, DOUBLE, NONE, NONE}},
  {Command::OUSEZONECAP, {KID, STRING33, DOUBLE, DOUBLE, DOUBLE, NONE, NONE}},
  {Command::OUSECAPA, {KID, STRING33, NONE, NONE, NONE, NONE, NONE}},
  {Command::PLAYER, {KID, UINT, STRING33, NONE, NONE, NONE, NONE}},
  {Command::YOUARE, {KID, NONE, NONE, NONE, NONE, NONE, NONE}},
  {Command::ASKCBUILDING, {STRING33, DOUBLE, DOUBLE, DOUBLE, INT, NONE, NONE}},
  {Command::JOINSPECTATOR, {STRING256, NONE, NONE, NONE, NONE, NONE, NONE}}
};

const std::map<Command::Command, std::vector<Protocol::ArgType> > init_jobData(void) {
  std::map<Command::Command, std::vector<Protocol::ArgType> > data;

  for (auto it : data_map) {
    data[it.command];
    for (auto it2 : it.data) {
      data[it.command].push_back(it2);
    }
  }
  return (data);
}

static const std::map<Command::Command, std::vector<Protocol::ArgType> > _jobData = init_jobData();

static const std::string printArg(const Protocol::Argument &arg, Protocol::ArgType type) {
  switch (type) {
  case Protocol::KID:
    return (Converter::StringOf<Kernel::ID::id_t>(arg.kid));
  case Protocol::DOUBLE:
    return (Converter::StringOf<double>(arg.pos));
  case Protocol::ERROR:
    return (Error::CodeToString(arg.error));
  case Protocol::RESSTYPE:
    return ("");
  case Protocol::UINT:
    return (Converter::StringOf<unsigned int>(arg.amount));
  case Protocol::COMMAND:
    return (Command::CommandToString(arg.command));
  case Protocol::COLOR:
    return ("");
  case Protocol::RACE:
    return (Race::RaceToString(arg.race));
  case Protocol::DIFFICULTY:
    return ("");
  case Protocol::ROOM:
    return ("");
  case Protocol::USERSTATUS:
    return (::User::StatusToString(arg.userStatus));
  case Protocol::STRING33:
    return (std::string("").insert(0, arg.password, 32));
  case Protocol::STRING256:
    return (std::string("").insert(0, arg.msg, 255));
  case Protocol::BOOL:
    return (arg.day == true ? "TRUE" : "FALSE");
  case Protocol::ULL:
    return (Converter::StringOf<unsigned long long>(arg.filesize));
  case Protocol::INT:
    return (Converter::StringOf<int>(arg.orientation));
  case Protocol::EACTION:
    return (Converter::StringOf<Game::eAction>(arg.action));
  case Protocol::STANCE:
    return ("");
  case Protocol::CHAR32TAB:
    return ("");
  case Protocol::DOUBLE3:
    return (Converter::StringOf<double>(arg.position[0]) + " ; " + Converter::StringOf<double>(arg.position[1]) + " ; " + Converter::StringOf<double>(arg.position[2]));
  case Protocol::KID64:
    {
      std::string str;
      for (auto it : arg.grp) {
	if (!str.empty()) {
	  str += ",";
	}
	str += Converter::StringOf<Kernel::ID::id_t>(it);
      }
      return (std::string("[") + str + std::string("]"));
    }
  default:
    return ("");
  }
}

std::ostream&	operator<<(std::ostream& os, const Protocol::Job &j) {
  if (_jobData.find(j.getCommand()) == _jobData.end()) {
    os << "undefined_job : " << Command::CommandToString(j.getCommand());
  }
  else {
    os << Command::CommandToString(j.getCommand());
    unsigned int i = 0;
    for (auto it : _jobData.at(j.getCommand())) {
      if (it == NONE) {
	break;
      }
      os << " " << printArg(j.getArguments()[i++], it);
    }
  }
  return (os);
}

/* FINDEBUG */
