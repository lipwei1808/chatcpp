#ifndef _PARSER_EXCEPTION_H_
#define _PARSER_EXCEPTION_H_
#include <string>
#include <exception>
#include "ChatcppException.h"

class ParserException: public ChatcppException {
private:
  std::string message = "";
public:
  ParserException() = default;
  ParserException(std::string message) {
    setMsg(message);
  }
  virtual const char* what() {
    return msg;
  }
};

#endif // _PARSER_EXCEPTION_H_