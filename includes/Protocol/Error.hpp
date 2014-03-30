//
// Error.hpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Fri Jan 10 17:01:22 2014 gautier lefebvre
// Last update Tue Mar  4 15:16:30 2014 geoffrey bauduin
//

#ifndef		__PROTOCOL_ERROR_HPP__
#define		__PROTOCOL_ERROR_HPP__

#include	<string>

#define		NB_ERROR	54

namespace	Error {
  enum		Code {
    NONE,
    UNDEF,
    FORBIDDENOPERATION,
    NICKALREADYTAKEN,
    INVALIDMAILADDRESS,
    INVALIDPASSWORD,
    NOSUCHNICK,
    WRONGPASSWORD,
    YOUARECONNECTED,
    ERRORREGISTRATION,
    NOTCONNECTED,
    ALREADYCONNECTED,
    PLAYERNOTCONNECTED,
    FRIENDALREADYEXIST,
    FRIENDREQUESTALREADYSENT,
    FRIENDDONOTEXIST,
    FRIENDNOTINREQUEST,
    USERINGROUP,
    USERDIDNOTREQUESTGROUP,
    NOTGROUPLEADER,
    NOTINGROUP,
    NOTSAMEGROUP,
    GROUPFULL,
    NOTWAITING,
    ALREADYWAITING,
    YOUAREINVITEDINAGROUP,
    CURRENTLYWAITING,
    NOTLOADINGGAME,
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
    BUILDING_NOT_BUILT,
    ITEM_CANNOT_ATTACK,
    CAPACITY_CANNOT_BE_AUTOMATIC
  };

  const	std::string &CodeToString(Error::Code code);

  struct	CodeString {
    Error::Code	code;
    std::string	string;
  };

  static const CodeString       CodeStringTab[NB_ERROR]={
    {Error::NONE, "none"},
    {Error::UNDEF, "undefined"},
    {Error::FORBIDDENOPERATION, "Forbidden operation"},
    {Error::NICKALREADYTAKEN, "This nick is already taken"},
    {Error::INVALIDMAILADDRESS, "Invalid mail address"},
    {Error::INVALIDPASSWORD, "Invalid password"},
    {Error::NOSUCHNICK, "There is no player with this nick"},
    {Error::WRONGPASSWORD, "Wrong password"},
    {Error::ALREADYCONNECTED, "This user is already connected"},
    {Error::ERRORREGISTRATION, "An error occurred while registrating"},
    {Error::NOTCONNECTED, "You are not connected"},
    {Error::YOUARECONNECTED, "You are already connected"},
    {Error::PLAYERNOTCONNECTED, "This player is not connected"},
    {Error::FRIENDALREADYEXIST, "This user is already your friend"},
    {Error::FRIENDREQUESTALREADYSENT, "You have already sent a request to this friend"},
    {Error::FRIENDNOTINREQUEST, "This user did not send you a friend request"},
    {Error::FRIENDDONOTEXIST, "This user is not your friend"},
    {Error::USERINGROUP, "This user is already in a group"},
    {Error::USERDIDNOTREQUESTGROUP, "This user did not ask you to join his group"},
    {Error::NOTGROUPLEADER, "You cannot do that since you are not the leader of the group"},
    {Error::NOTINGROUP, "You are not in a group"},
    {Error::NOTSAMEGROUP, "You are not in the same group"},
    {Error::GROUPFULL, "The group is full"},
    {Error::NOTWAITING, "You are not waiting"},
    {Error::ALREADYWAITING, "You are already waiting"},
    {Error::YOUAREINVITEDINAGROUP, "You are already invited in a group"},
    {Error::CURRENTLYWAITING, "You are currently waiting to start a game"},
    {Error::NOTLOADINGGAME, "You are not currently loading a game"},
    {Error::NOT_ENOUGH_RESSOURCES, "You don't have enough ressources"},
    {Error::NOT_ENOUGH_SELF_RESSOURCES, "You don't have enough personnal ressources"},
    {Error::REQUIREMENTS_NOT_FULLFILLED, "You can't do that yet because you need to fullfill the requirements"},
    {Error::BUILDING_CANNOT_BUILD_THIS_UNIT, "This building cannot produce this unit"},
    {Error::ITEM_NOT_IN_RACE, "This item is not in your race"},
    {Error::UNKNOWN_ITEM, "This item is unknown"},
    {Error::ITEM_IS_NOT_OWNED_BY_PLAYER, "You don't own this item"},
    {Error::CAPACITY_IS_NOT_IN_LIST, "This capacity isn't in the list"},
    {Error::CAPACITY_CANNOT_BE_USED, "This capacity cannot be used"},
    {Error::ITEM_IS_NOT_OWNED_BY_TEAM, "This item is not owned by your team"},
    {Error::UNKNOWN_PLAYER, "This player doesn't exists"},
    {Error::PLAYER_IS_NOT_IN_THE_SAME_TEAM, "This player is not in your team"},
    {Error::ITEM_IS_NOT_CORRECT, "This item is not correct"},
    {Error::ITEM_CANNOT_BE_REMOVED_FROM_PRODUCTION_LIST, "This item cannot be removed from the production queue"},
    {Error::HERO_CANNOT_CARRY_MORE_OBJECTS, "This hero cannot carry more objects"},
    {Error::HERO_IS_NOT_CARRYING_THIS_ITEM, "This hero isn't carrying this itm"},
    {Error::OBJECT_IS_ALREADY_BEING_CARRIED, "This object is already being carried"},
    {Error::PLAYER_DOES_NOT_EXIST, "This player doesn't exists"},
    {Error::PLAYER_IS_ALREADY_PRODUCING_AMELIORATION, "You are already producing the amelioration"},
    {Error::PLAYER_ALREADY_HAS_AMELIORATION, "You already have this amelioration"},
    {Error::ITEM_HASNT_GOT_CAPACITY, "This item hasn't got the capacity"},
    {Error::BUILDING_IS_ALREADY_BUILT, "This building is already built"},
    {Error::ITEM_CANNOT_MOVE, "This item cannot move"},
    {Error::BUILDING_NOT_BUILT, "This building has not been built yet."},
    {Error::ITEM_CANNOT_ATTACK, "This item cannot attack."},
    {Error::CAPACITY_CANNOT_BE_AUTOMATIC, "This capacity cannot be automatic."}
  };
}

#endif
