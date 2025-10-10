#ifndef NETWORKER_H
#define NETWORKER_H

#include <QObject>

class NetWorker : public QObject
{
public:
  NetWorker(const QString& url = "");

  QString getRequest();
  QString postRequest(QString& data);
private:
  QString m_url;
};

#endif // NETWORKER_H
