//
// FileLoader.cpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Wed Feb 12 16:36:12 2014 gautier lefebvre
// Last update Fri Mar  7 14:48:22 2014 gautier lefebvre
//

#include	<stdexcept>
#include	<functional>
#include	<unistd.h>
#include	<cstring>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<dirent.h>
#include	"FileLoader.hpp"
#include	"Threading/ScopeLock.hpp"

FileLoader::FileLoader() {}

FileLoader::~FileLoader() {
}

bool		FileLoader::fileHasExtension(const std::string &file, const std::string &extension) {
  return (file.size() > extension.size() && file.substr(file.size() - extension.size(), extension.size()) == extension);
}

void		FileLoader::loadFileByExtension(const std::string &directory, const std::string &extension, std::vector<std::string>& files) {
  DIR		*dir = opendir(directory.c_str());
  if (dir == NULL) { return ; }
  struct dirent *file;
  while ((file = readdir(dir)) != NULL) {
    if (this->fileHasExtension(std::string(file->d_name), extension)) {
      if (directory.back() != '/') {
        files.push_back(directory + "/" + file->d_name);
      }
      else {
	files.push_back(directory + file->d_name);
      }
    }
  }
  closedir(dir);
}

void		FileLoader::loadFileByName(const std::string &file, std::vector<std::string>& files) {
  struct stat	f;
  if (stat(file.c_str(), &f) == -1) {
    return ;
  }
  files.push_back(file);
}

std::string	FileLoader::get_filename(const std::string &path, bool ext) {
  size_t	last = path.find_last_of("/\\");
  size_t	p = ext ? path.size() - 1 : path.find_last_of(".");

  if (last == std::string::npos) {
    last = -1;
  }
  if (p == std::string::npos) {
    p = path.size() - 1;
  }
  try {
    return (path.substr(last + 1, p - last - 1));
  }
  catch (const std::out_of_range &) {
    return (path);
  }
}
