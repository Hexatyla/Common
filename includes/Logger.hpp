//
// Logger.hpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Sat Jan 18 16:00:00 2014 geoffrey bauduin
// Last update Fri Mar 21 14:14:08 2014 geoffrey bauduin
//

#ifndef LOGGER_HPP_
# define LOGGER_HPP_

#include	<fstream>
#include	<vector>
#include	<map>
#include	<string>
#include	<stdarg.h>
#include	"Singleton.hpp"
#include	"Threading/Mutex.hpp"
#include	"ThreadData.hpp"

class Logger: public Singleton<Logger> {

  friend class Singleton;

public:
  enum	Level {
    NONE,
    INFORMATION,
    WARNING,
    FATAL,
    DEBUG
  };

private:
  std::map<Logger::Level, std::string>	_colors;
  std::map<const char, std::string (Logger::*)(va_list &)>	_f;
  Mutex					*_mutex;
  unsigned int				_decal;
  std::string				_strDecal;
  bool					_inserted;
  bool					_force;
  std::ofstream				_out;
  bool					_writeFile;

  Logger(void);
  ~Logger(void);

  std::string	_double(va_list &);
  std::string	_string(va_list &);
  std::string	_int(va_list &);
  std::string	_uint(va_list &);
  std::string	_job(va_list &);

  void	writeToFile(const std::string &);

public:
  void		log(const std::string &, Logger::Level level = NONE);
  void		logf(const std::string &, Logger::Level level, ...);
  void		addDecalage(unsigned int amount = 1);
  void		removeDecalage(unsigned int amount = 1);
  void		dumpThread(const Clock *, const std::vector<ThreadData> &, unsigned int);
  void		force(void);

};

#endif
