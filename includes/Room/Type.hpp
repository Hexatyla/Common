//
// Type.hpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Mon Jan 13 16:13:23 2014 gautier lefebvre
// Last update Fri Jan 24 17:05:01 2014 gautier lefebvre
//

#ifndef		__ROOM_TYPE_HPP__
#define		__ROOM_TYPE_HPP__

#include	<string>

namespace	Room {
  enum		Type {
    CUSTOM,
    ONEVSONE,
    TWOVSTWO,
    THREEVSTHREE
  };

  const std::string &RoomTypeToString(Room::Type t);

  struct RoomTypeString {
    Room::Type	type;
    std::string	string;
  };

  static const int	NB_ROOMTYPE = 4;

  static const RoomTypeString RoomTypeStringTab[Room::NB_ROOMTYPE]={
    {Room::CUSTOM, "Custom"},
    {Room::ONEVSONE, "OneVersusOne"},
    {Room::TWOVSTWO, "TwoVersusTwo"},
    {Room::THREEVSTHREE, "ThreeVersusThree"}
  };
}

#endif
