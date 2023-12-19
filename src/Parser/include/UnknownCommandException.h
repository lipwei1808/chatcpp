#ifndef _UNKNOWN_COMMAND_EXCEPTION_H_
#define _UNKNOWN_COMMAND_EXCEPTION_H_
#include "ChatcppException.h"

class UnknownCommandException: public ChatcppException {
public:
  virtual char* what() {
    setMsg("Unknown command");
    return msg;
  }
};

#endif  // _UNKNOWN_COMMAND_EXCEPTION_H_