#ifndef LOG_H
#define LOG_H

#include <QLoggingCategory>

bool initLog(const std::string& appName);
void finishgLog(int signal);

void setOutputMode(const std::string& mode);

#endif // LOG_H
