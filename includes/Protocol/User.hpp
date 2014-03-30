//
// User.hpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Sun Feb  9 16:44:13 2014 gautier lefebvre
// Last update Sun Feb  9 17:07:26 2014 gautier lefebvre
//

#ifndef		__PROTOCOL_USER_HPP__
#define		__PROTOCOL_USER_HPP__

#include	<string>

namespace	User {
  enum	Status {
    CONNECTED,
    DISCONNECTED,
    BUSY,
    AFK
  };

  const std::string &StatusToString(::User::Status);

  struct UserStatusString {
    ::User::Status	status;
    std::string		string;
  };

  static const int	NB_STATUS = 4;

  static const UserStatusString UserStatusStringTab[::User::NB_STATUS]={
    {::User::CONNECTED, "Connected"},
    {::User::DISCONNECTED, "Disconnected"},
    {::User::BUSY, "Busy"},
    {::User::AFK, "AFK"}
  };
}

#endif
