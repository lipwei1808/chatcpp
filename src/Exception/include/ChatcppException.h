#ifndef _CHATCPP_EXCEPTION_H_
#define _CHATCPP_EXCEPTION_H_
#include <string>
#include <cstring>
#include <exception>

class ChatcppException: public std::exception {
private:
  std::string errorPrefix = "[CHATCPP ERROR]";
protected:
  char* msg = nullptr;
  void setMsg(std::string s) {
    std::string tmp = errorPrefix + s;
    msg = &(tmp[0]);
    msg = new char[tmp.size() + 1];
    std::strcpy(msg, tmp.c_str());
  }
public:
  ChatcppException() {
    setMsg("an error occured");
  }
  virtual const char* what() {
    return msg;
  }
  ~ChatcppException() {
    delete msg;
  }
};

#endif // _CHATCPP_EXCEPTION_H_