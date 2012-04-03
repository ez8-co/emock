
#if defined(_MSC_VER)
#include <windows.h>
#endif

#include <testngpp/utils/ConsoleState.h>

TESTNGPP_NS_START

///////////////////////////////////////////////////////////
#if defined(_MSC_VER)

///////////////////////////////////////////////////////////
#define C_RED     (FOREGROUND_RED   | FOREGROUND_INTENSITY)
#define C_BLUE    (FOREGROUND_BLUE  | FOREGROUND_INTENSITY)
#define C_GREEN   (FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define C_YELLOW  (FOREGROUND_RED   | FOREGROUND_GREEN |FOREGROUND_INTENSITY)
#define C_MAGENTA (FOREGROUND_RED   | FOREGROUND_BLUE  |FOREGROUND_INTENSITY)
#define C_CYAN    (FOREGROUND_GREEN | FOREGROUND_BLUE  |FOREGROUND_INTENSITY)
#define C_WHITE   (FOREGROUND_RED   | FOREGROUND_BLUE  |FOREGROUND_GREEN )

///////////////////////////////////////////////////////////
namespace 
{
   struct Color
   {
      Color(unsigned int c)
         : color(c)
	  {}

      void operator()(void) const
      {
         ::SetConsoleTextAttribute
            ( ::GetStdHandle(STD_OUTPUT_HANDLE)
            , color);
      }

   private:
      unsigned int color;
   };
}

///////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const Color color)
{
   color();
   return os;
}

///////////////////////////////////////////////////////////

#endif


///////////////////////////////////////////////////////////
#if defined(_MSC_VER)

#define RED     Color(C_RED)
#define GREEN   Color(C_GREEN)
#define YELLOW  Color(C_YELLOW)
#define BLUE    Color(C_BLUE)
#define MAGENTA Color(C_MAGENTA)
#define CYAN    Color(C_CYAN)
#define WHITE   Color(C_WHITE)

#else

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[0m"

#endif

///////////////////////////////////////////////////////////
#define DEF_STATE_COLOR_MAPPING(S,C) \
std::ostream& operator<<(std::ostream& os, const S& state) \
{ \
   if(state.isColorful()) os << C; \
   return os; \
}

///////////////////////////////////////////////////////////
DEF_STATE_COLOR_MAPPING(SuccState,   GREEN)
DEF_STATE_COLOR_MAPPING(InfoState,   CYAN)
DEF_STATE_COLOR_MAPPING(WarnState,   YELLOW)
DEF_STATE_COLOR_MAPPING(DebugState,  BLUE)
DEF_STATE_COLOR_MAPPING(FailState,   RED)
DEF_STATE_COLOR_MAPPING(NormalState, WHITE)

///////////////////////////////////////////////////////////

TESTNGPP_NS_END
