#include "NetWorker.h"

#include <QUrl>
#include <QTimer>
#include <QEventLoop>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

NetWorker::NetWorker(const QString& url) : m_url(url)
{

}

QString NetWorker::postRequest(QString& data)
{
  qDebug()<<Q_FUNC_INFO;
  QUrl url = m_url;
  QString res = "";

  QEventLoop loop;

  QNetworkReply* reply = nullptr;
  QNetworkRequest request(url);    //Объект запроса
  QNetworkAccessManager manager;

  QTimer timer;
  timer.setInterval(2000);
  timer.setSingleShot(true);

  request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

  bool isConnected = connect(&manager, &QNetworkAccessManager::finished,
                             &loop, [&loop](QNetworkReply*) { loop.quit(); });

  if(isConnected)
    isConnected = connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);

  if(isConnected)
  {
    reply = manager.post(request, data.toUtf8());  //Запрос
    loop.exec();

    if(!timer.isActive())
    {
      isConnected = false;
    } else timer.stop();
  }

  if(isConnected)
  {
    if(reply->error() == QNetworkReply::NoError)
    {
     res = reply->readAll();
    }
  }

  if(reply != nullptr)
  {
    if(!isConnected)
      reply->abort();
    reply->deleteLater();
  }
  return res;
}

QString NetWorker::getRequest()
{
  QUrl url = m_url;
  QEventLoop getLoop;

  QNetworkAccessManager manager;
  QNetworkRequest request(url);
  QNetworkReply *reply = nullptr;

  bool isConnected = connect(&manager, &QNetworkAccessManager::finished,
                             &getLoop, [&getLoop](QNetworkReply*) { getLoop.quit(); });

  QString res;
  if(isConnected)
  {

    reply = manager.get(request);
    getLoop.exec();

    if(reply->error() == QNetworkReply::NoError)
    {
      res = QString::fromUtf8(reply->readAll());
    }
    else
    {
      qDebug()<<"error:"<< reply->error();
    }
  }

  if(reply != nullptr)
    reply->deleteLater();

  return res;
}
