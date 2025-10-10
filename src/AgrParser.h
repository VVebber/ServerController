#ifndef AGRPARSER_H
#define AGRPARSER_H

class AgrParser
{
public:
  AgrParser(int argc, char* argv[]);
  bool parse();

private:
  char** m_argv;
  int m_argc;
};

#endif // AGRPARSER_H
