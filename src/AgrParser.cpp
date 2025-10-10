#include "AgrParser.h"
#include "Logs/Log.h"

#include <string>

const std::string LOG_OUTPUT    = "-output";

AgrParser::AgrParser(int argc, char* argv[])
{
  m_argc = argc;
  m_argv = argv;
}

bool AgrParser::parse()
{
  char* currParam;
  char* currVal;
  for (int i = 1; i < m_argc; i+=2)
  {
    currParam = m_argv[i];
    currVal = m_argv[i+1];
    if(!strcmp(currParam, LOG_OUTPUT.c_str()))
    {
      setOutputMode(currVal);
    }
  }

  return true;
}
