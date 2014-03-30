//
// Logger.cpp for  in /home/geoffrey/Projects/pfa
// 
// Made by geoffrey bauduin
// Login   <baudui_g@epitech.net>
// 
// Started on  Sat Jan 18 16:01:26 2014 geoffrey bauduin
// Last update Fri Mar 21 14:19:10 2014 geoffrey bauduin
//

#include	<iomanip>
#include	<iostream>
#include	"Date.hpp"
#include	"Logger.hpp"
#include	"Threading/ScopeLock.hpp"
#include	"Converter.hpp"
#include	"Protocol/Job.hpp"

Logger::Logger(void):
  _colors(), _f(), _mutex(new Mutex), _decal(0), _strDecal(""), _inserted(true), _force(false), _out() {
  this->_colors[Logger::NONE] = "\033[0m";
  this->_colors[Logger::INFORMATION] = "\033[0;33m";
  this->_colors[Logger::WARNING] = "\033[0;35m";
  this->_colors[Logger::FATAL] = "\033[0;31m";
  this->_colors[Logger::DEBUG] = "\033[0;32m";
  this->_f['f'] = &Logger::_double;
  this->_f['s'] = &Logger::_string;
  this->_f['d'] = &Logger::_int;
  this->_f['u'] = &Logger::_uint;
  this->_f['j'] = &Logger::_job;
  this->_out.open(std::string("/tmp/") + Date::getFilenameDateTime());
  this->_writeFile = !this->_out.fail();
}

Logger::~Logger(void) {
  delete this->_mutex;
}

void	Logger::force(void) {
  this->_force = true;
  this->_inserted = false;
}

std::string	Logger::_job(va_list &ap) {
  const Protocol::Job *job = va_arg(ap, const Protocol::Job *);
  std::stringstream stream;
  stream << *job;
  return (stream.str());
}

std::string	Logger::_double(va_list &ap) {
  double v = va_arg(ap, double);
  return (Converter::StringOf<double>(v));
}

std::string	Logger::_string(va_list &ap) {
  return (*(va_arg(ap, std::string *)));
}

std::string	Logger::_int(va_list &ap) {
  int v = va_arg(ap, int);
  return (Converter::StringOf<int>(v));
}

std::string	Logger::_uint(va_list &ap) {
  unsigned int v = va_arg(ap, unsigned int);
  return (Converter::StringOf<unsigned int>(v));
}

void	Logger::writeToFile(const std::string &string) {
  if (this->_writeFile) {
    this->_out << string;
  }
}

void	Logger::log(const std::string &string, Logger::Level level) {
  std::stringstream	stream;
  if (!this->_force) {
    this->_mutex->lock();
  }
  if (!this->_inserted) {
    stream << std::endl;
  }
  this->_inserted = true;
  stream << Date::getTime(true) << " -- " << this->_strDecal << this->_colors[level] << string << this->_colors[NONE] << std::endl;
  const std::string str = stream.str();
  std::cerr << str;
  this->writeToFile(str);
  if (!this->_force) {
    this->_mutex->unlock();
  }
}

void	Logger::logf(const std::string &format, Logger::Level level, ...) {
  std::stringstream stream;
  if (!this->_force) {
    this->_mutex->lock();
  }
  if (!this->_inserted) {
    stream << std::endl;
  }
  this->_inserted = true;
  stream << Date::getTime(true) << " -- " << this->_strDecal << this->_colors[level];
  va_list ap;
  va_start(ap, level);
  bool f = false;
  for (auto it : format) {
    if (f && it != '%') {
      stream << (this->*_f[it])(ap);
      f = false;
    }
    else if (!f && it != '%') {
      stream << it;
    }
    if (it == '%') {
      if (f == true) {
	stream << '%';
      }
      f = !f;
    }
  }
  stream << this->_colors[NONE] << std::endl;
  va_end(ap);
  const std::string str = stream.str();
  std::cerr << str;
  this->writeToFile(str);
  if (!this->_force) {
    this->_mutex->unlock();
  }
}

void	Logger::addDecalage(unsigned int amount) {
  ScopeLock s(this->_mutex);
  for (unsigned int i = 0 ; i < amount ; ++i) {
    this->_decal++;
    this->_strDecal += "\t";
  }
}

void	Logger::removeDecalage(unsigned int amount) {
  ScopeLock s(this->_mutex);
  for (unsigned int i = 0 ; i < amount && this->_decal > 0 ; ++i) {
    this->_decal--;
    this->_strDecal.erase(0, 1);
  }
}

void	Logger::dumpThread(const Clock *current, const std::vector<ThreadData> &th, unsigned int size) {
  ScopeLock s(this->_mutex);
  this->_inserted = false;
  std::cerr << "\r" << size << " - ";
  Logger::Level imp = Logger::NONE;
  for (auto it : th) {
    if (it.status == SLEEPING) {
      imp = Logger::NONE;
    }
    else if (it.status == WORKING) {
      imp = current->getElapsedTimeSince(it.clock) > 3.0 ? FATAL : INFORMATION;
    }
    std::cerr << this->_colors[imp] << "#" << it.id + 1 << " ";
    if (imp == FATAL) {
      std::cerr << "(" << std::setprecision(3) << current->getElapsedTimeSince(it.clock) << "s in Event >" << it.event << "<) ";
    }
    std::cerr << this->_colors[NONE];
  }
}
