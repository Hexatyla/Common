//
// Argument.hpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Fri Jan 10 17:30:07 2014 gautier lefebvre
// Last update Fri Mar 21 23:24:55 2014 geoffrey bauduin
//

#ifndef		__PROTOCOL_ARGUMENT_HPP__
#define		__PROTOCOL_ARGUMENT_HPP__

#include	"Protocol/Error.hpp"
#include	"Protocol/Command.hpp"
#include	"Room/Type.hpp"
#include	"Protocol/Color.hpp"
#include	"Protocol/Difficulty.hpp"
#include	"Protocol/Race.hpp"
#include	"Protocol/User.hpp"
#include	"Kernel/ID.hpp"
#include	"Game/Action.hpp"
#include	"Game/Stance.hpp"
#include	"Game/Ressources.hpp"


#define GRP_SIZE	64
#define SERIALS_SIZE	8

namespace	Protocol {
  union		Argument {
    Error::Code			error;
    Command::Command		command;
    Color::Color		color;
    Race::Race			race;
    Difficulty::Difficulty	difficulty;
    Room::Type			roomType;
    ::User::Status		userStatus;
    char			pseudo[256];
    char			serial[33];
    char			password[33];
    char			msg[256];
    char			mail[256];
    char			avatar[256];
    char			filename[256];
    char			filechunk[256];
    bool			yes;
    unsigned int		stat;
    unsigned int		nb_chunk;
    unsigned int		id_chunk;
    unsigned long long		filesize;
    int				size_chunk;
    int				id;
    int				slot;
    int				team;
    Kernel::ID::id_t		kid;
    unsigned int		wpID;
    unsigned int		currentLife;
    unsigned int		currentRess;
    double			pos;
    double			speed;
    int				orientation;
    Game::eAction		action;
    Kernel::ID::id_t		grp[GRP_SIZE];
    bool			adapt;
    Game::Stance::Type		stance;
    bool			day;
    unsigned int		amount;
    unsigned int		queue_id;
    bool			activated;
    bool			automatic;
    char			serials[SERIALS_SIZE][32];
    Game::Ressources::Type	ressourceType;
    double			percentage;
    double			position[3];
  };

  enum ArgType {
    ERROR,
    KID,
    DOUBLE,
    RESSTYPE,
    UINT,
    COMMAND,
    COLOR,
    RACE,
    DIFFICULTY,
    ROOM,
    USERSTATUS,
    STRING33,
    STRING256,
    BOOL,
    ULL,
    INT,
    EACTION,
    STANCE,
    CHAR32TAB,
    DOUBLE3,
    KID64,
    NONE
  };

}

#endif
