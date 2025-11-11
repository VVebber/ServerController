#ifndef NETWORKER_H
#define NETWORKER_H

#include "./Request.h"

#include <QQueue>
#include <QObject>

class NetWorker : public QObject
{
public:
  NetWorker();
  ~NetWorker();

public slots:
  void addRequest(Request requst);

private slots:
  void onReplyFinished(class QNetworkReply* reply, Request req);

private:
  void processNext();

  void getRequest(class QNetworkRequest& request, Request req);
  void postRequest(class QNetworkRequest& request, Request req);

private:
  class QNetworkAccessManager* m_manager;

  QQueue<Request> m_requests;

  bool m_isBusy;
};

#endif // NETWORKER_H
