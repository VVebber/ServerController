#ifndef REQUEST_H
#define REQUEST_H

#include <QString>
#include <QJsonObject>
#include <functional>

struct Request
{
  enum RequestType
  {
    GET = 0,
    POST = 1,
    PUT = 2,
  };

  RequestType type = GET;

  QString url;
  QJsonObject data;

  std::function<void(const QString&)> callback;
};

using RequstType = Request::RequestType;

class RequestSender : public QObject
{
    Q_OBJECT

public:
    static RequestSender& instance()
    {
        static RequestSender inst;
        return inst;
    }

    void addRequest(const Request& req)
    {
        emit sendRequest(req);
    }

signals:
    void sendRequest(Request req);
};

#endif // REQUEST_H
