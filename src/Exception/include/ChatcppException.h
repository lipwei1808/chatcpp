#ifndef _CHATCPP_EXCEPTION_H_
#define _CHATCPP_EXCEPTION_H_
#include <string>
#include <exception>

class ChatcppException: public std::exception {
private:
  std::string errorPrefix = "[CHATCPP ERROR]";
protected:
  char* generateChatcppError(std::string s) {
    return &(errorPrefix + s)[0];
  }
public:
  char* what() {
    return generateChatcppError(" an error occured");
  }
};

#endif // _CHATCPP_EXCEPTION_H_