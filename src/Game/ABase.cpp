//
// ABase.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <geoffrey@epitech.net>
// 
// Started on  Wed Feb 12 13:03:04 2014 geoffrey bauduin
// Last update Wed Mar 26 11:06:08 2014 geoffrey bauduin
//

#include	<limits>
#include	<cstddef>
#include	"Game/ABase.hpp"
#include	"Game/Player.hpp"
#include	"Threading/ScopeLock.hpp"

#define	CONVERT(data, ptr)	(reinterpret_cast<void *>(reinterpret_cast<unsigned long long>(ptr) - reinterpret_cast<unsigned long long>(data)))

Game::ABase::ABase(void):
  HasInfos(), HasSerial(),
  _mutex(new Mutex),
  _player(NULL) {
}

Game::ABase::~ABase(void) {
  delete this->_mutex;
}

const Game::Race	*Game::ABase::getRace(void) const {
  return (this->_race);
}

Game::Type	Game::ABase::getType(void) const {
  return (this->_type);
}

const Game::Team	*Game::ABase::getTeam(void) const {
  if (this->_player) {
    return (this->_player->getTeam());
  }
  return (NULL);
}

void	Game::ABase::init(const Kernel::Serial &serial, Game::Type type, const Game::Player *player) {
  HasInfos::init(serial, type);
  HasSerial::init(serial);
  this->_player = player;
  this->_race = player ? player->getRace() : NULL;
  this->_type = type;
}

void	Game::ABase::destroy(void) {
  HasInfos::destroy();
  HasSerial::destroy();
}

const Game::Player *Game::ABase::getPlayer(void) const {
  return (this->_player);
}

template<typename T>
static T	getFromData(const Game::ABase *element, void *addr) {
  T val = *GET_VAL(element->getInfos().data, addr, T);
  if (element->getPlayer()) {
    for (auto it : element->getPlayer()->getAmeliorations(element->serial())) {
      val += *GET_VAL(it->getInfos().data, addr, T);
    }
  }
  const Game::AElement *aelement = dynamic_cast<const Game::AElement *>(element);
  if (aelement) {
    const Game::AElement::EffectContainer effects = aelement->getEffects();
    for (auto it : effects) {
      for (auto effect : it.second) {
	val += *GET_VAL(effect->getInfos().data, addr, T);
      }
    }
    const std::list<const Game::Effect *> tmpEffects = aelement->getTemporaryEffects();
    for (auto it : tmpEffects) {
      T n = *GET_VAL(it->getInfos().data, addr, T);
      if (element->getPlayer()->isAlliedWith(it->getPlayer())) {
	val += n;
      }
      else {
	if (std::numeric_limits<T>::is_signed == false && val < n) {
	  val = 0;
	}
	else {
	  val -= n;
	}
      }
    }
  }
  return (val);
}

unsigned int	Game::ABase::getUIntFromData(void *addr) const {
  return (getFromData<unsigned int>(this, addr));
}

double	Game::ABase::getDoubleFromData(void *addr) const {
  return (getFromData<double>(this, addr));
}

unsigned int	Game::ABase::getMaxLife(void) const {
  ScopeLock s(this->_mutex);
  const HasInfos::infos &infos = this->getInfos();
  return (this->getUIntFromData(CONVERT(infos.data, &infos.data->maxHP)));
}

unsigned int	Game::ABase::getMaxRessources(void) const {
  ScopeLock s(this->_mutex);
  const HasInfos::infos &infos = this->getInfos();
  return (this->getUIntFromData(CONVERT(infos.data, &infos.data->maxRessources)));
}

unsigned int	Game::ABase::getAttack(void) const {
  ScopeLock s(this->_mutex);
  const HasInfos::infos &infos = this->getInfos();
  return (this->getUIntFromData(CONVERT(infos.data, &infos.data->attack)));
}

unsigned int	Game::ABase::getDefense(void) const {
  ScopeLock s(this->_mutex);
  const HasInfos::infos &infos = this->getInfos();
  return (this->getUIntFromData(CONVERT(infos.data, &infos.data->defense)));
}

unsigned int	Game::ABase::getHpRegen(void) const {
  ScopeLock s(this->_mutex);
  const HasInfos::infos &infos = this->getInfos();
  return (this->getUIntFromData(CONVERT(infos.data, &infos.data->hpRegen)));
}

unsigned int	Game::ABase::getSpeed(void) const {
  ScopeLock s(this->_mutex);
  const HasInfos::infos &infos = this->getInfos();
  return (this->getUIntFromData(CONVERT(infos.data, &infos.data->speed)));
}

double	Game::ABase::getHitbox(void) const {
  ScopeLock s(this->_mutex);
  const HasInfos::infos &infos = this->getInfos();
  return (this->getDoubleFromData(CONVERT(infos.data, &infos.data->hitbox)));
}

double	Game::ABase::getCritChance(void) const {
  ScopeLock s(this->_mutex);
  const HasInfos::infos &infos = this->getInfos();
  double v = this->getDoubleFromData(CONVERT(infos.data, &infos.data->critChance));
  return (v > 1.0 ? 1.0 : v);
}

double	Game::ABase::getAttackRange(void) const {
  ScopeLock s(this->_mutex);
  const HasInfos::infos &infos = this->getInfos();
  return (this->getDoubleFromData(CONVERT(infos.data, &infos.data->attackRange)));
}

unsigned int	Game::ABase::getRessourcesRegen(void) const {
  ScopeLock s(this->_mutex);
  const HasInfos::infos &infos = this->getInfos();
  return (this->getUIntFromData(CONVERT(infos.data, &infos.data->ressourcesRegen)));
}

double	Game::ABase::getDaySight(void) const {
  ScopeLock s(this->_mutex);
  const HasInfos::infos &infos = this->getInfos();
  return (this->getDoubleFromData(CONVERT(infos.data, &infos.data->daySight)));
}

double	Game::ABase::getNightSight(void) const {
  ScopeLock s(this->_mutex);
  const HasInfos::infos &infos = this->getInfos();
  return (this->getDoubleFromData(CONVERT(infos.data, &infos.data->nightSight)));
}

