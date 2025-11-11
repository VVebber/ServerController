#include "NetWorker.h"

#include <QUrl>
#include <QTimer>
#include <QEventLoop>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

NetWorker::NetWorker()
{
  qDebug()<<Q_FUNC_INFO;
  m_isBusy = false;
  m_manager = new QNetworkAccessManager(this);
}

NetWorker::~NetWorker()
{
  qDebug()<<Q_FUNC_INFO;
  delete m_manager;
}

void NetWorker::addRequest(Request requst)
{
  m_requests.push_back(requst);

  if(!m_isBusy)
    processNext();
}

void NetWorker::processNext()
{
  if(m_requests.isEmpty()) return;

  m_isBusy = true;
  Request req = m_requests.dequeue();

  QNetworkRequest request(req.url);
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

  switch (req.type) {
    case Request::GET:
      getRequest(request, req);
      break;
    case Request::POST:
      postRequest(request, req);
      break;

    default:
      break;
  }
}

void NetWorker::getRequest(QNetworkRequest& request, Request req)
{
  qDebug()<<Q_FUNC_INFO;
  QNetworkReply *reply = nullptr;

  connect(m_manager, &QNetworkAccessManager::finished, this,
          [this, req](QNetworkReply* reply)
  {
    onReplyFinished(reply, req);
  });

  m_manager->get(request);
}


void NetWorker::postRequest(QNetworkRequest& request, Request req)
{
  qDebug()<<Q_FUNC_INFO;
  QNetworkReply* reply = nullptr;

  QJsonDocument doc(req.data);
  reply = m_manager->post(request, doc.toJson());

  connect(reply, &QNetworkReply::finished, this, [this, reply, req]() {
      onReplyFinished(reply, req);
  });
}


void NetWorker::onReplyFinished(QNetworkReply* reply, Request req)
{
  QString response = "";

  if(reply->error() == QNetworkReply::NoError)
  {
    response = QString::fromUtf8(reply->readAll());
  }
  else
  {
    qDebug()<<"error:"<< reply->readAll();
  }

  if(reply->isRunning())
    reply->abort();

  reply->deleteLater();


  m_isBusy = false;
  if(req.callback)
    req.callback(response);

  processNext();
}
