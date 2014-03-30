//
// Player.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Fri Jan 10 18:48:31 2014 geoffrey bauduin
// Last update Wed Mar 19 16:20:26 2014 geoffrey bauduin
//

#ifndef GAME_PLAYER_HPP_
# define GAME_PLAYER_HPP_

namespace Game { class Team; }

#include	<list>
#include	<map>
#include	<vector>
#include	"Game/Race.hpp"
#include	"Game/Amelioration.hpp"
#include	"HasID.hpp"
#include	"Threading/Mutex.hpp"
#include	"Game/ProductionQueue.hpp"
#include	"IFromFactory.hpp"

namespace	Game {

  class	Player: public HasID, virtual public IFromFactory {

  private:
    mutable Mutex					*_dataMutex;
    mutable Mutex					*_ressourcesMutex;
    mutable Mutex					*_queuesMutex;

  protected:
    std::map<Kernel::Serial, std::vector<Game::Amelioration *> >	_ameliorations;
    unsigned int						_nbrUnits;
    unsigned int						_nbrBuildings;
    unsigned int						_nbrHeroes;
    const Game::Race						*_race;
    Game::Ressources						_ressources;
    const Game::Team						*_team;
    std::map<Kernel::Serial, Game::ProductionQueue *>		_productionQueues;
    std::list<Kernel::Serial>					_buildings;

  public:
    Player(void);
    virtual ~Player(void);

    virtual void	init(Kernel::ID::id_t, const Game::Race *, const Game::Team *);
    virtual void	destroy(void);

    void		setTeam(const Game::Team *);
    const Game::Race	*getRace(void) const;
    const Game::Team	*getTeam(void) const;

    void		setRessources(Game::Ressources::Type, unsigned int);

    const std::vector<Game::Amelioration *>	getAmeliorations(void) const;
    const std::vector<Game::Amelioration *>	&getAmeliorations(const Kernel::Serial &) const;

    virtual void	addToQueue(const Kernel::Serial &, const Kernel::Serial &);
    virtual void	insertInQueue(const Kernel::Serial &, const Kernel::Serial &, unsigned int);
    virtual bool	removeFromQueue(const Kernel::Serial &, const Kernel::Serial &);
    virtual const Kernel::Serial	popQueue(const Kernel::Serial &);

    const Kernel::Serial	&frontQueue(const Kernel::Serial &) const;
    const Kernel::Serial	&backQueue(const Kernel::Serial &) const;

    bool		isAlliedWith(const Game::Player *) const;

    bool		hasAmelioration(const Kernel::Serial &, const Kernel::Serial &) const;
    bool		hasAmelioration(const Kernel::Serial &) const;
    bool		hasBuilding(const Kernel::Serial &) const;

    void		addBuilding(const Kernel::Serial &);
    void		removeBuilding(const Kernel::Serial &);

    bool		isInQueue(const Kernel::Serial &, const Kernel::Serial &) const;

    virtual void	addUnit(unsigned int amount = 1);
    virtual void	removeUnit(unsigned int amount = 1);
    virtual void	addHero(unsigned int amount = 1);
    virtual void	removeHero(unsigned int amount = 1);
    virtual void	addBuilding(unsigned int amount = 1);
    virtual void	removeBuilding(unsigned int amount = 1);

    unsigned int	getNbrUnits(void) const;
    unsigned int	getNbrHeroes(void) const;
    unsigned int	getNbrBuildings(void) const;

    virtual void	addRessources(const Game::Ressources &);
    virtual void	addRessources(Game::Ressources::Type, unsigned int);

    virtual void	removeRessources(const Game::Ressources &);
    virtual void	removeRessources(Game::Ressources::Type, unsigned int);

    const Game::Ressources &getRessources(void) const;
    unsigned int	getRessources(Game::Ressources::Type) const;

    virtual bool	hasEnoughRessources(const Game::Ressources &) const;

    bool	hasLost(void) const;

    void		addAmelioration(const Kernel::Serial &, const Kernel::Serial &);

  };

}

#endif
