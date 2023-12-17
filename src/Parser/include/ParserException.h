#ifndef _PARSER_EXCEPTION_H_
#define _PARSER_EXCEPTION_H_
#include <string>
#include <exception>
#include "ChatcppException.h"

class ParserException: public ChatcppException {
private:
  std::string msg = "";
public:
  ParserException() = default;
  ParserException(std::string msg): msg(msg) {}
  char* what() {
    return generateChatcppError(" PARSER EXCEPTION " + msg);
  }
};

#endif // _PARSER_EXCEPTION_H_