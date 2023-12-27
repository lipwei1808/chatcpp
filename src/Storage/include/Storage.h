#ifndef _STORAGE_H_
#define _STORAGE_H_
#include <fstream>
#include <memory>
#include <string>
#include <memory>
#include "Tasks.h"
#include "Task.h"

class Storage {
public:
  void save(Saveable &items) const;
  Tasks load() const;
  std::string getFilepath() const ;
  static std::shared_ptr<Storage> getInstance(std::string filepath);

private: 
  Storage(std::string filepath);
  std::vector<std::shared_ptr<Task>> parseToTasks(std::vector<std::string> lines) const;
  static bool checkFilepath(std::string filepath);
private:
  std::string filepath;
};

#endif // _STORAGE_H_