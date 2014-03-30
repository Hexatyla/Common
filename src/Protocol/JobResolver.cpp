//
// Resolver.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <geoffrey@epitech.net>
// 
// Started on  Thu Feb 27 17:00:52 2014 geoffrey bauduin
// Last update Mon Mar 24 14:45:16 2014 geoffrey bauduin
//

#include	"Protocol/JobResolver.hpp"

Protocol::JobResolver::JobResolver(void) {

}

Protocol::JobResolver::~JobResolver(void) {

}

Protocol::JobResolver::Exception::Exception(const std::string &what) throw():
  _what(what) {

}

Protocol::JobResolver::Exception::~Exception(void) throw() {

}

const char	*Protocol::JobResolver::Exception::what(void) const throw() {
  return (this->_what.c_str());
}

void	Protocol::JobResolver::checkJobCommand(const Protocol::Job *job, ::Command::Command command) const {
  if (job->getCommand() != command) {
    throw new Protocol::JobResolver::Exception(std::string("Command ") + ::Command::CommandToString(job->getCommand()) + "does not match " + ::Command::CommandToString(command));
  }
}

void	Protocol::JobResolver::playerInformation(const Protocol::Job *job, Kernel::ID::id_t &playerID,
						 unsigned int &teamID, Kernel::Serial &race) const {
  this->checkJobCommand(job, Command::PLAYER);
  const Protocol::Argument *args = job->getArguments();
  playerID = args[0].kid;
  teamID = args[1].id;
  race = args[2].serial;
}

void	Protocol::JobResolver::youAre(const Protocol::Job *job, Kernel::ID::id_t &playerID) const {
  this->checkJobCommand(job, Command::YOUARE);
  const Protocol::Argument *args = job->getArguments();
  playerID = args[0].kid;
}

void	Protocol::JobResolver::createItem(const Protocol::Job *job, Kernel::Serial &serial, Kernel::ID::id_t &id,
					  double &x, double &y, double &z, int &orientation,
					  Kernel::ID::id_t &playerID) const {
  this->checkJobCommand(job, ::Command::OCREATE);
  const Protocol::Argument *args = job->getArguments();
  serial = args[0].serial;
  id = args[1].kid;
  x = args[2].pos;
  y = args[3].pos;
  z = args[4].pos;
  orientation = args[5].pos;
  playerID = args[6].kid;
}

void	Protocol::JobResolver::deleteItem(const Protocol::Job *job, Kernel::ID::id_t &id) const {
  this->checkJobCommand(job, ::Command::ODESTROY);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
}

void	Protocol::JobResolver::updateItem(const Protocol::Job *job, Kernel::ID::id_t &id, double &x, double &y,
					  double &z, int &orientation, unsigned int &currentLife,
					  unsigned int &currentRessources,
					  unsigned int &xp, unsigned int &level) const {
  this->checkJobCommand(job, ::Command::OMAJ);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
  x = args[1].position[0];
  y = args[1].position[1];
  z = args[1].position[2];
  orientation = args[2].orientation;
  currentLife = args[3].currentLife;
  currentRessources = args[4].currentRess;
  xp = args[5].currentRess;
  level = args[6].currentRess;
}

void	Protocol::JobResolver::itemWaypoint(const Protocol::Job *job, Kernel::ID::id_t &id, unsigned int &wpID,
					    double &x, double &y, double &z, double &speed) const {
  this->checkJobCommand(job, ::Command::OWP);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
  wpID = args[1].wpID;
  x = args[2].pos;
  y = args[3].pos;
  z = args[4].pos;
  speed = args[5].speed;
}

void	Protocol::JobResolver::itemStopAction(const Protocol::Job *job, Kernel::ID::id_t &id) const {
  this->checkJobCommand(job, ::Command::OSTOP);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
}

void	Protocol::JobResolver::itemAction(const Protocol::Job *job, Kernel::ID::id_t &id,
					  Game::eAction &action) const {
  this->checkJobCommand(job, ::Command::OACT);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
  action = args[1].action;
}

void	Protocol::JobResolver::fillIDArray(const Protocol::Argument *args, std::vector<Kernel::ID::id_t> &units,
					   unsigned int amount, unsigned int j) const {
  unsigned int i = 0;
  for (unsigned int act = 0 ; act < amount && j < 7 ; ++act) {
    units.push_back(args[j].grp[i++]);
    if (i % GRP_SIZE == 0) {
      ++j;
      i = 0;
    }
  }
}

void	Protocol::JobResolver::askMoveItemGroup(const Protocol::Job *job, std::vector<Kernel::ID::id_t> &units,
						double &x, double &y, double &z, bool &adapt) const {
  this->checkJobCommand(job, ::Command::OGRPMOVE);
  const Protocol::Argument *args = job->getArguments();
  x = args[0].pos;
  y = args[1].pos;
  z = args[2].pos;
  adapt = args[3].adapt;
  this->fillIDArray(args, units, args[4].amount, 5);
}

void	Protocol::JobResolver::ping(const Protocol::Job *job, Kernel::ID::id_t &playerID,
				    double &x, double &y) const {
  this->checkJobCommand(job, ::Command::PING);
  const Protocol::Argument *args = job->getArguments();
  playerID = args[0].kid;
  x = args[1].pos;
  y = args[2].pos;
}

void	Protocol::JobResolver::unitStance(const Protocol::Job *job, Kernel::ID::id_t &id,
					  Game::Stance::Type &stance) const {
  this->checkJobCommand(job, ::Command::USTANCE);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
  stance = args[1].stance;
}

void	Protocol::JobResolver::askChangeUnitStance(const Protocol::Job *job, Kernel::ID::id_t &id,
						   Game::Stance::Type &stance) const {
  this->checkJobCommand(job, ::Command::UCHGSTANCE);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
  stance = args[1].stance;
}

void	Protocol::JobResolver::unitGroupStance(const Protocol::Job *job, std::vector<Kernel::ID::id_t> &units,
					       Game::Stance::Type &stance) const {
  this->checkJobCommand(job, ::Command::UCHGGRPSTANCE);
  const Protocol::Argument *args = job->getArguments();
  stance = args[0].stance;
  this->fillIDArray(args, units, args[1].amount, 2);
}

void	Protocol::JobResolver::unitAskStance(const Protocol::Job *job, Kernel::ID::id_t &id) const {
  this->checkJobCommand(job, ::Command::UASKSTANCE);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
}

void	Protocol::JobResolver::askItemInfo(const Protocol::Job *job, Kernel::ID::id_t &id) const {
  this->checkJobCommand(job, ::Command::OASKINFO);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
}

void	Protocol::JobResolver::askMoveItem(const Protocol::Job *job, Kernel::ID::id_t &id, double &x, double &y,
					   double &z) const {
  this->checkJobCommand(job, ::Command::OASKMOVE);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
  x = args[1].pos;
  y = args[2].pos;
  z = args[3].pos;
}

void	Protocol::JobResolver::dayNightSwitch(const Protocol::Job *job, bool &day) const {
  this->checkJobCommand(job, ::Command::DAYNIGHT);
  const Protocol::Argument *args = job->getArguments();
  day = args[0].day;
}

void	Protocol::JobResolver::playerRessources(const Protocol::Job *job, Kernel::ID::id_t &id, unsigned int &gold,
						unsigned int &wood, unsigned int &food) const {
  this->checkJobCommand(job, ::Command::PRESS);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
  gold = args[1].amount;
  wood = args[2].amount;
  food = args[3].amount;
}

void	Protocol::JobResolver::askPlayerRessources(const Protocol::Job *job, Kernel::ID::id_t &id) const {
  this->checkJobCommand(job, ::Command::ASKPRESS);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
}

void	Protocol::JobResolver::itemMove(const Protocol::Job *job, Kernel::ID::id_t &id, double &x, 
					double &y, double &z) const {
  this->checkJobCommand(job, ::Command::OMOVE);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
  x = args[1].pos;
  y = args[2].pos;
  z = args[3].pos;
}

void	Protocol::JobResolver::askItemAction(const Protocol::Job *job, Kernel::ID::id_t &id) const {
  this->checkJobCommand(job, ::Command::OASKACT);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
}

void	Protocol::JobResolver::unitCreateBuilding(const Protocol::Job *job, Kernel::ID::id_t &unitID,
						  Kernel::ID::id_t &buildingID) const {
  this->checkJobCommand(job, ::Command::UBUILD);
  const Protocol::Argument *args = job->getArguments();
  unitID = args[0].kid;
  buildingID = args[1].kid;
}

void	Protocol::JobResolver::askUnitProd(const Protocol::Job *job, Kernel::ID::id_t &building,
					   Kernel::Serial &serial) const {
  this->checkJobCommand(job, ::Command::UASKPROD);
  const Protocol::Argument *args = job->getArguments();
  building = args[0].kid;
  serial = args[1].serial;
}

void	Protocol::JobResolver::unitProduction(const Protocol::Job *job, Kernel::ID::id_t &building,
					      unsigned int &qID, Kernel::Serial &serial) const {
  this->checkJobCommand(job, ::Command::UPROD);
  const Protocol::Argument *args = job->getArguments();
  building = args[0].kid;
  qID = args[1].queue_id;
  serial = args[2].serial;
}

void	Protocol::JobResolver::activateCapacity(const Protocol::Job *job, Kernel::ID::id_t &id,
						Kernel::Serial &serial, bool &activated) const {
  this->checkJobCommand(job, ::Command::OACTCAPA);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
  serial = args[1].serial;
  activated = args[2].activated;
}

void	Protocol::JobResolver::unitPickingUpRessources(const Protocol::Job *job, Kernel::ID::id_t &id,
						       unsigned int &gold, unsigned int &wood,
						       unsigned int &food) const {
  this->checkJobCommand(job, ::Command::UPURESS);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
  gold = args[1].amount;
  wood = args[2].amount;
  food = args[3].amount;
}

void	Protocol::JobResolver::askUnitPickedUpRessources(const Protocol::Job *job, Kernel::ID::id_t &id) const {
  this->checkJobCommand(job, ::Command::ASKUPURESS);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
}

void	Protocol::JobResolver::askItemEffects(const Protocol::Job *job, Kernel::ID::id_t &id) const {
  this->checkJobCommand(job, ::Command::ASKOEFFECT);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
}

void	Protocol::JobResolver::stopItemEffect(const Protocol::Job *job, Kernel::ID::id_t &id,
					      Kernel::Serial &serial) const {
  this->checkJobCommand(job, ::Command::OSTOPEFFECT);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
  serial = args[1].serial;
}

void	Protocol::JobResolver::itemEffect(const Protocol::Job *job, Kernel::ID::id_t &id, Kernel::Serial &serial,
					  double &percentage) const {
  this->checkJobCommand(job, ::Command::OEFFECT);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
  serial = args[1].serial;
  percentage = args[2].percentage;
}

void	Protocol::JobResolver::askSetItemAction(const Protocol::Job *job, Kernel::ID::id_t &id,
						Game::eAction &action) const {
  this->checkJobCommand(job, ::Command::OSETACTION);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
  action = args[1].action;
}

void	Protocol::JobResolver::askSetItemsAction(const Protocol::Job *job, std::vector<Kernel::ID::id_t> &items,
						 Game::eAction &action) const {
  this->checkJobCommand(job, ::Command::OSETACTIONS);
  const Protocol::Argument *args = job->getArguments();
  action = args[0].action;
  this->fillIDArray(args, items, args[1].amount, 2);
}

void	Protocol::JobResolver::unitHasBeenProduced(const Protocol::Job *job, Kernel::ID::id_t &id,
						   Kernel::Serial &serial) const {
  this->checkJobCommand(job, ::Command::BPRODF);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
  serial = args[1].serial;
}

void	Protocol::JobResolver::askRemoveUnitFromProduction(const Protocol::Job *job, Kernel::ID::id_t &id,
							   Kernel::Serial &serial) const {
  this->checkJobCommand(job, ::Command::UASKDPROD);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
  serial = args[1].serial;
}

void	Protocol::JobResolver::removeUnitFromProduction(const Protocol::Job *job, Kernel::ID::id_t &id,
							   Kernel::Serial &serial) const {
  this->checkJobCommand(job, ::Command::UDPROD);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
  serial = args[1].serial;
}

void	Protocol::JobResolver::heroPickedUpAnObject(const Protocol::Job *job, Kernel::ID::id_t &hero,
						    Kernel::ID::id_t &object) const {
  this->checkJobCommand(job, ::Command::HPUOBJ);
  const Protocol::Argument *args = job->getArguments();
  hero = args[0].kid;
  object = args[1].kid;
}

void	Protocol::JobResolver::askHeroObjects(const Protocol::Job *job, Kernel::ID::id_t &hero) const {
  this->checkJobCommand(job, ::Command::ASKHOBJ);
  const Protocol::Argument *args = job->getArguments();
  hero = args[0].kid;
}

void	Protocol::JobResolver::heroObjectsList(const Protocol::Job *job, Kernel::ID::id_t &id,
					       std::vector<Kernel::ID::id_t> &objects) const {
  this->checkJobCommand(job, ::Command::HPUOBJS);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
  this->fillIDArray(args, objects, args[1].amount, 2);
}

void	Protocol::JobResolver::heroReleasedObject(const Protocol::Job *job, Kernel::ID::id_t &hero,
						 Kernel::ID::id_t &object) const {
  this->checkJobCommand(job, ::Command::HROBJ);
  const Protocol::Argument *args = job->getArguments();
  hero = args[0].kid;
  object = args[1].kid;
}

void	Protocol::JobResolver::askHeroToTakeObject(const Protocol::Job *job, Kernel::ID::id_t &hero,
						   Kernel::ID::id_t &object) const {
  this->checkJobCommand(job, ::Command::ASKHPUOBJ);
  const Protocol::Argument *args = job->getArguments();
  hero = args[0].kid;
  object = args[1].kid;
}

void	Protocol::JobResolver::askHeroToReleaseObject(const Protocol::Job *job, Kernel::ID::id_t &hero,
						      Kernel::ID::id_t &object, double &x,
						      double &y, double &z) const {
  this->checkJobCommand(job, ::Command::ASKHROBJ);
  const Protocol::Argument *args = job->getArguments();
  hero = args[0].kid;
  object = args[1].kid;
  x = args[2].pos;
  y = args[3].pos;
  z = args[4].pos;
}

void	Protocol::JobResolver::playerHasAmelioration(const Protocol::Job *job, Kernel::ID::id_t &player,
						     Kernel::Serial &item, Kernel::Serial &amelioration) const {
  this->checkJobCommand(job, ::Command::PAMELIO);
  const Protocol::Argument *args = job->getArguments();
  player = args[0].kid;
  item = args[1].serial;
  amelioration = args[2].serial;
}

void	Protocol::JobResolver::playerHasJustProducedAmelioration(const Protocol::Job *job, Kernel::ID::id_t &player,
								 Kernel::Serial &item,
								 Kernel::Serial &amelioration) const {
  this->checkJobCommand(job, ::Command::PPRODAMELIO);
  const Protocol::Argument *args = job->getArguments();
  player = args[0].kid;
  item = args[1].serial;
  amelioration = args[2].serial;
}

void	Protocol::JobResolver::askPlayerAmeliorations(const Protocol::Job *job, Kernel::ID::id_t &player) const {
  this->checkJobCommand(job, ::Command::ASKPAMELIO);
  const Protocol::Argument *args = job->getArguments();
  player = args[0].kid;
}

void	Protocol::JobResolver::askProduceAmelioration(const Protocol::Job *job, Kernel::Serial &item,
						      Kernel::Serial &amelioration) const {
  this->checkJobCommand(job, ::Command::ASKPRODAMELIO);
  const Protocol::Argument *args = job->getArguments();
  item = args[0].serial;
  amelioration = args[1].serial;
}

void	Protocol::JobResolver::removeAmeliorationFromProductionQueue(const Protocol::Job *job,
								     Kernel::ID::id_t &player,
								     Kernel::Serial &item,
								     Kernel::Serial &amelioration) const {
  this->checkJobCommand(job, ::Command::DAMELIO);
  const Protocol::Argument *args = job->getArguments();
  player = args[0].kid;
  item = args[1].serial;
  amelioration = args[2].serial;
}

void	Protocol::JobResolver::askRemoveAmeliorationFromProductionQueue(const Protocol::Job *job,
									Kernel::Serial &item,
									Kernel::Serial &amelioration) const {
  this->checkJobCommand(job, ::Command::ASKDAMELIO);
  const Protocol::Argument *args = job->getArguments();
  item = args[0].serial;
  amelioration = args[1].serial;
}

void	Protocol::JobResolver::ameliorationProduction(const Protocol::Job *job, Kernel::ID::id_t &playerID,
						      Kernel::Serial &item, Kernel::Serial &amelioration,
						      unsigned int &qID) const {
  this->checkJobCommand(job, ::Command::PRODAMELIO);
  const Protocol::Argument *args = job->getArguments();
  playerID = args[0].kid;
  item = args[1].serial;
  amelioration = args[2].serial;
  qID = args[3].queue_id;
}

void	Protocol::JobResolver::askElementAmeliorations(const Protocol::Job *job, Kernel::ID::id_t &playerID,
						       Kernel::Serial &item) const {
  this->checkJobCommand(job, ::Command::ASKPSAMELIO);
  const Protocol::Argument *args = job->getArguments();
  playerID = args[0].kid;
  item = args[1].serial;
}

void	Protocol::JobResolver::askUnitToBuild(const Protocol::Job *job, Kernel::ID::id_t &unit,
					      Kernel::ID::id_t &building) const {
  this->checkJobCommand(job, ::Command::UASKBUILD);
  const Protocol::Argument *args = job->getArguments();
  unit = args[0].kid;
  building = args[1].kid;
}

void	Protocol::JobResolver::unitStopBuildingBuilding(const Protocol::Job *job, Kernel::ID::id_t &unit,
							Kernel::ID::id_t &building) const {
  this->checkJobCommand(job, ::Command::USTOPBUILD);
  const Protocol::Argument *args = job->getArguments();
  unit = args[0].kid;
  building = args[1].kid;
}

void	Protocol::JobResolver::buildingHasBeenBuilt(const Protocol::Job *job, Kernel::ID::id_t &id) const {
  this->checkJobCommand(job, ::Command::BBUILT);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
}

void	Protocol::JobResolver::unitHarvest(const Protocol::Job *job, Kernel::ID::id_t &unit,
					   Kernel::ID::id_t &spot) const {
  this->checkJobCommand(job, ::Command::UHARVEST);
  const Protocol::Argument *args = job->getArguments();
  unit = args[0].kid;
  spot = args[1].kid;
}

void	Protocol::JobResolver::askUnitHarvest(const Protocol::Job *job, Kernel::ID::id_t &unit,
					   Kernel::ID::id_t &spot) const {
  this->checkJobCommand(job, ::Command::UASKHARVEST);
  const Protocol::Argument *args = job->getArguments();
  unit = args[0].kid;
  spot = args[1].kid;
}

void	Protocol::JobResolver::unitDeposit(const Protocol::Job *job, Kernel::ID::id_t &unit,
					   Kernel::ID::id_t &building) const {
  this->checkJobCommand(job, ::Command::UDEPOSIT);
  const Protocol::Argument *args = job->getArguments();
  unit = args[0].kid;
  building = args[1].kid;
}

void	Protocol::JobResolver::askUnitsHarvest(const Protocol::Job *job, std::vector<Kernel::ID::id_t> &units,
					       Kernel::ID::id_t &spot) const {
  this->checkJobCommand(job, ::Command::USASKHARVEST);
  const Protocol::Argument *args = job->getArguments();
  spot = args[0].kid;
  this->fillIDArray(args, units, args[1].kid, 2);
}

void	Protocol::JobResolver::askSpotID(const Protocol::Job *job, double &x, double &y, double &z) const {
  this->checkJobCommand(job, ::Command::ASKRESSSPOTID);
  const Protocol::Argument *args = job->getArguments();
  x = args[0].pos;
  y = args[1].pos;
  z = args[2].pos;
}

void	Protocol::JobResolver::ressourceSpot(const Protocol::Job *job, Kernel::ID::id_t &id, double &x,
					     double &y, double &z, Game::Ressources::Type &type,
					     unsigned int &amount) const {
  this->checkJobCommand(job, ::Command::RESSSPOT);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
  x = args[1].pos;
  y = args[2].pos;
  z = args[3].pos;
  type = args[4].ressourceType;
  amount = args[5].amount;
}

void	Protocol::JobResolver::updateSpot(const Protocol::Job *job, Kernel::ID::id_t &id,
					  unsigned int &amount) const {
  this->checkJobCommand(job, ::Command::UPDSPOT);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
  amount = args[1].amount;
}

void	Protocol::JobResolver::unitStopHarvest(const Protocol::Job *job, Kernel::ID::id_t &id) const {
  this->checkJobCommand(job, ::Command::USTOPHARVEST);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
}

void	Protocol::JobResolver::unitWaitHarvest(const Protocol::Job *job, Kernel::ID::id_t &id) const {
  this->checkJobCommand(job, ::Command::UWAITHARVEST);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
}

void	Protocol::JobResolver::unitStopWaitHarvest(const Protocol::Job *job, Kernel::ID::id_t &id) const {
  this->checkJobCommand(job, ::Command::USTOPWAITHARVEST);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
}

void	Protocol::JobResolver::temporaryEffect(const Protocol::Job *job, Kernel::ID::id_t &id,
					       Kernel::Serial &effect, Kernel::ID::id_t &from) const {
  this->checkJobCommand(job, ::Command::OTMPEFFECT);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
  effect = args[1].serial;
  from = args[2].kid;
}

void	Protocol::JobResolver::removeTemporaryEffect(const Protocol::Job *job, Kernel::ID::id_t &id,
						     Kernel::Serial &effect, Kernel::ID::id_t &from) const {
  this->checkJobCommand(job, ::Command::OSTOPTMPEFFECT);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
  effect = args[1].serial;
  from = args[2].kid;
}

void	Protocol::JobResolver::askAutomaticCapacity(const Protocol::Job *job, Kernel::ID::id_t &id,
						    Kernel::Serial &serial, bool &automatic) const {
  this->checkJobCommand(job, ::Command::OASKAUTOCAPA);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
  serial = args[1].serial;
  automatic = args[2].automatic;
}

void	Protocol::JobResolver::askUnitsToBuild(const Protocol::Job *job, std::vector<Kernel::ID::id_t> &units, 
					       Kernel::ID::id_t &id) const {
  this->checkJobCommand(job, ::Command::USASKBUILD);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
  this->fillIDArray(args, units, args[1].amount, 2);
}

void	Protocol::JobResolver::itemAttack(const Protocol::Job *job, Kernel::ID::id_t &source,
					  Kernel::ID::id_t &target) const {
  this->checkJobCommand(job, ::Command::OATTACK);
  const Protocol::Argument *args = job->getArguments();
  source = args[0].kid;
  target = args[1].kid;
}

void	Protocol::JobResolver::askItemAttack(const Protocol::Job *job, Kernel::ID::id_t &source,
					     Kernel::ID::id_t &target) const {
  this->checkJobCommand(job, ::Command::ASKOATTACK);
  const Protocol::Argument *args = job->getArguments();
  source = args[0].kid;
  target = args[1].kid;
}

void	Protocol::JobResolver::itemUseCapacity(const Protocol::Job *job, Kernel::ID::id_t &source,
					       Kernel::ID::id_t &target, Kernel::Serial &capacity) const {
  this->checkJobCommand(job, ::Command::OUSECAP);
  const Protocol::Argument *args = job->getArguments();
  source = args[0].kid;
  target = args[1].kid;
  capacity = args[2].serial;
}

void	Protocol::JobResolver::askItemUseCapacity(const Protocol::Job *job, Kernel::ID::id_t &source,
					       Kernel::ID::id_t &target, Kernel::Serial &capacity) const {
  this->checkJobCommand(job, ::Command::ASKOUSECAP);
  const Protocol::Argument *args = job->getArguments();
  source = args[0].kid;
  target = args[1].kid;
  capacity = args[2].serial;
}

void	Protocol::JobResolver::askUnitPatrol(const Protocol::Job *job, Kernel::ID::id_t &unit,
					     double &x, double &y) const {
  this->checkJobCommand(job, ::Command::ASKUPATROL);
  const Protocol::Argument *args = job->getArguments();
  unit = args[0].kid;
  x = args[1].pos;
  y = args[2].pos;
}

void	Protocol::JobResolver::askUnitsPatrol(const Protocol::Job *job, std::vector<Kernel::ID::id_t> &units,
					      double &x, double &y, bool &adapt) const {
  this->checkJobCommand(job, ::Command::ASKUSPATROL);
  const Protocol::Argument *args = job->getArguments();
  x = args[0].pos;
  y = args[1].pos;
  adapt = args[2].adapt;
  this->fillIDArray(args, units, args[3].amount, 4);
}

void	Protocol::JobResolver::askItemsAttack(const Protocol::Job *job, std::vector<Kernel::ID::id_t> &units,
					      Kernel::ID::id_t &target) const {
  this->checkJobCommand(job, ::Command::ASKOSATTACK);
  const Protocol::Argument *args = job->getArguments();
  target = args[0].kid;
  this->fillIDArray(args, units, args[1].amount, 2);
}

void	Protocol::JobResolver::askItemAttackZone(const Protocol::Job *job, Kernel::ID::id_t &id, double &x,
						 double &y, double &z) const {
  this->checkJobCommand(job, ::Command::ASKOZONEATTACK);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
  x = args[1].pos;
  y = args[2].pos;
  z = args[3].pos;
}

void	Protocol::JobResolver::askItemsAttackZone(const Protocol::Job *job, std::vector<Kernel::ID::id_t> &items,
						  double &x, double &y, double &z) const {
  this->checkJobCommand(job, ::Command::ASKOSZONEATTACK);
  const Protocol::Argument *args = job->getArguments();
  x = args[0].pos;
  y = args[1].pos;
  z = args[2].pos;
  this->fillIDArray(args, items, args[3].amount, 4);
}

void	Protocol::JobResolver::itemAttackZone(const Protocol::Job *job, Kernel::ID::id_t &id, double &x,
					      double &y, double &z) const {
  this->checkJobCommand(job, ::Command::OZONEATTACK);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
  x = args[1].pos;
  y = args[2].pos;
  z = args[3].pos;
}

void	Protocol::JobResolver::askItemUseZoneCapacity(const Protocol::Job *job, Kernel::ID::id_t &id,
						      Kernel::Serial &capacity, double &x,
						      double &y, double &z) const {
  this->checkJobCommand(job, ::Command::ASKOUSEZONECAP);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
  capacity = args[1].serial;
  x = args[2].pos;
  y = args[3].pos;
  z = args[4].pos;
}

void	Protocol::JobResolver::itemUseZoneCapacity(const Protocol::Job *job, Kernel::ID::id_t &id,
						   Kernel::Serial &capacity, double &x,
						   double &y, double &z) const {
  this->checkJobCommand(job, ::Command::OUSEZONECAP);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
  capacity = args[1].serial;
  x = args[2].pos;
  y = args[3].pos;
  z = args[4].pos;
}

void	Protocol::JobResolver::askActivateCapacity(const Protocol::Job *job, Kernel::ID::id_t &id,
						   Kernel::Serial &capacity) const {
  this->checkJobCommand(job, ::Command::OASKACTCAPA);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
  capacity = args[1].serial;
}

void	Protocol::JobResolver::itemUseCapacity(const Protocol::Job *job, Kernel::ID::id_t &id,
					       Kernel::Serial &capacity) const {
  this->checkJobCommand(job, ::Command::OUSECAPA);
  const Protocol::Argument *args = job->getArguments();
  id = args[0].kid;
  capacity = args[1].serial;
}

void	Protocol::JobResolver::askCreateBuilding(const Protocol::Job *job, Kernel::Serial &serial,
						 double &x, double &y, double &z, int &orientation) const {
  this->checkJobCommand(job, ::Command::ASKCBUILDING);
  const Protocol::Argument *args = job->getArguments();
  serial = args[0].serial;
  x = args[1].pos;
  y = args[2].pos;
  z = args[3].pos;
  orientation = args[4].orientation;
}
