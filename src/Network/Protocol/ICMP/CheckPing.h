#ifndef CHECLPING_H
#define CHECLPING_H

#include "../RawSocket.h"

#include <stdint.h>

struct PingRes
{
  char* ip;
  int errorCode;
  int sent = 0;
  int received = 0;
  float acgMs = -1;
  float minMs = -1;
  float maxMs = -1;
};

class CheckPing : public RawSocket
{
public:
  CheckPing();
  ~CheckPing();

  PingRes process(char* ip);

private:
  struct icmphdr* createPacket(char* packet);

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
