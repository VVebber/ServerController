#ifndef CHECLPING_H
#define CHECLPING_H

#include "../RawSocket.h"

#include <stdint.h>
#include <QtGlobal>

struct PingRes
{
  char* ip = nullptr;
  int errorCode = 0;
  int sent = 0;
  int received = 0;
  float acgMs = -1;
  float minMs = -1;
  float maxMs = -1;

  ~PingRes() {
    delete[] ip;
    ip = nullptr;
  }

  PingRes() = default;
  PingRes(const PingRes&) = delete;
  PingRes& operator=(const PingRes&) = delete;

  PingRes(PingRes&& other) noexcept {
      *this = std::move(other);
  }

  PingRes& operator=(PingRes&& other) noexcept {
      if (this != &other) {
          delete[] ip;
          ip = other.ip;
          errorCode = other.errorCode;
          sent = other.sent;
          received = other.received;
          acgMs = other.acgMs;
          minMs = other.minMs;
          maxMs = other.maxMs;

          other.ip = nullptr;
      }
      return *this;
  }
};

class CheckPing : public RawSocket
{
public:
  CheckPing();
  ~CheckPing();

  PingRes process(const char* ip);

private:
#if defined(Q_OS_LINUX)
  struct icmphdr* createPacket(char* packet);
#elif defined(Q_OS_MACOS)
  struct icmp* createPacket(char* packet);
#endif

private:
  uint16_t checksum(void *data, int len);
};


/*

struct PingResult {
    std::string ip;
    int sent = 0;
    int received = 0;
    int lost() const { return sent - received; }
    double avgMs = 0.0;
    double minMs = 0.0;
    double maxMs = 0.0;
    double lossPct() const { return sent ? (100.0 * lost() / sent) : 0.0; }
    std::string error; // пусто, если всё ок
    std::vector<int> rtts; // опционально
};


Для результата ping'а обычно полезны такие поля:

std::string ip; — адрес, который пинговали.

int sent; — сколько пакетов отправлено.

int received; — сколько ответов получено.

int lost; — потерянные пакеты (или процент lossPct).

double avgMs; — средняя задержка (RTT) в мс.

double minMs, maxMs; — мин/макс RTT (полезно для статистики).

int lastErrno; / std::string error; — описание ошибки, если не удалось.

опционально std::vector<int> rtts — отдельные измерения (если нужно деталями).
  */
#endif // CHECLPING_H
