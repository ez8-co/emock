
#ifndef __TESTNGPP_CONSOLE_STATE_H
#define __TESTNGPP_CONSOLE_STATE_H

#include <ostream>

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct ConsoleState
{
protected:
   ConsoleState(bool c)
      : colorful(c)
   {}
      
public:
   bool isColorful() const
   {
      return colorful;
   }
      
private:
      bool colorful;
};
   
////////////////////////////////////////////////////////
struct SuccState : public ConsoleState
{
   SuccState(bool colorful) : ConsoleState(colorful)
   {}
};
   
////////////////////////////////////////////////////////
struct FailState : public ConsoleState
{
   FailState(bool colorful) : ConsoleState(colorful)
   {}
};
   
////////////////////////////////////////////////////////
struct NormalState : public ConsoleState
{
   NormalState(bool colorful) : ConsoleState(colorful)
   {}
};
   
////////////////////////////////////////////////////////
struct InfoState : public ConsoleState
{
   InfoState(bool colorful) : ConsoleState(colorful)
   {}
};
   
////////////////////////////////////////////////////////
struct WarnState : public ConsoleState
{
   WarnState(bool colorful) : ConsoleState(colorful)
   {}
};

////////////////////////////////////////////////////////
struct DebugState : public ConsoleState
{
   DebugState(bool colorful) : ConsoleState(colorful)
   {}
};
   
////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const SuccState& succ);
std::ostream& operator<<(std::ostream& os, const FailState& fail);
std::ostream& operator<<(std::ostream& os, const NormalState& norm);
std::ostream& operator<<(std::ostream& os, const InfoState& info);
std::ostream& operator<<(std::ostream& os, const WarnState& warn);
std::ostream& operator<<(std::ostream& os, const DebugState& debug);

////////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif

