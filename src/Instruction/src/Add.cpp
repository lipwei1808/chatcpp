#include <memory>
#include "Add.h"
#include "Tasks.h"

Add::Add(std::shared_ptr<Task> toAdd): toAdd(toAdd) {}

void Add::execute(Tasks &tasks) {
  tasks.add(toAdd);
  tasks.save();
  std::cout << "    added: " << toAdd->getName() << std::endl;
}
