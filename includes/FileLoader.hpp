//
// FileLoader.hpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Wed Feb 12 16:33:04 2014 gautier lefebvre
// Last update Fri Mar  7 14:47:57 2014 gautier lefebvre
//

#ifndef		__FILELOADER_HPP__
#define		__FILELOADER_HPP__

#include	<vector>
#include	<string>
#include	"Singleton.hpp"
#include	"Threading/Mutex.hpp"

class		FileLoader:
  public Singleton<FileLoader> {
  friend class Singleton<FileLoader>;

private:
  bool	fileHasExtension(const std::string &, const std::string &);

  FileLoader();
  ~FileLoader();

public:
  void		loadFileByExtension(const std::string &, const std::string &, std::vector<std::string>&);
  void		loadFileByName(const std::string &, std::vector<std::string>&);

  static std::string	get_filename(const std::string &, bool ext = false);

};

#endif
