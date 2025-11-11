#ifndef ARP_PING_H
#define ARP_PING_H

#include <net/if_arp.h>

#include "../RawSocket.h"

struct ArpPingRes
{
  char* ip;
  char mac[18];
};

class ARP_Ping : public RawSocket
{
public:
  ARP_Ping();

  ArpPingRes process(const char* ip, struct NetAdapter& adapter);

private:
  struct arpPacker
  {
    struct arphdr header;
    uint8_t sender_mac[6];
    uint8_t sender_ip[4];
    uint8_t target_mac[6];
    uint8_t target_ip[4];
  } __attribute__((packed));


};

#endif // ARP_PING_H


// /*            32 bits   (char = 8 bytes,  32bits = 4 bytes);
// =============================================
// =     Hardare Type    =    Rtotocol Type    =
// =============================================
// = Hardware = Protocol =       Operation     =
// = Lenghth  =  Length  = 1:Request   2:Reply =
// =============================================
// =          Sender Hardware Address          =
// =============================================
// =          Sender Protocol Address          =
// =============================================
// =          Target Hardware Address          =
// =============================================
// =          Target Protocol Address          =
// =============================================
//   Hardware Type - 16-битное поле, определяющее “тип канальной среды”. Наиболее часто
// используемые типы представлены ниже
//   1	Ethernet
//   15	Frame Relay
//   17	HDLC
//   18	Fiber Channel
//   20	Serial Link

//   Protocol Type - 16-битное поле, определяющее протокол сетевого уровня, который отправитель
// связывает с идентификатором канала передачи данных. Для протокола IP версии 4
// значение данного поля равно 0x0800

//   Hardware Address Length - 8-битное поле, определяющее длину идентификатора канальной
// среды в байтах. MAC-адреса имеет длину 48 бит или 6 байт.

//   Protocol Address Length - 8-битное поле, определяющее длину адреса сетевого уровня в байтах.
// IP-адреса имеет длину 32 бита или 4 байта.

// Operation - 16-битное поле, которое определяет какой тип пакета ARP используется:
//   ARP Request - 1
//   ARP Reply - 2
//   Reverse ARP Request - 3
//   Reverse ARP Reply - 4
//   Inverse ARP Request - 8
//   Inverse ARP Reply - 9



//  */
