#ifndef _INSTRUCTION_EXCEPTION_H_
#define _INSTRUCTION_EXCEPTION_H_
#include <string>
#include "ChatcppException.h"

class InstructionException: public ChatcppException {
public:
  InstructionException(): message("instruction error") {}
  InstructionException(std::string message): message(message) {}
  virtual char* what() {
    setMsg(message);
    return msg;
  }
public:
  std::string message;
};

#endif // _INSTRUCTION_EXCEPTION_H_