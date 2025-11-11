#ifndef ISCANWORKER_H
#define ISCANWORKER_H

#include <QObject>

class IScanWorker : public QObject {
    Q_OBJECT
public:
    explicit IScanWorker(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~IScanWorker() = default;

    virtual void startScan() = 0;

signals:
  void finished();
};

#endif // ISCANWORKER_H
