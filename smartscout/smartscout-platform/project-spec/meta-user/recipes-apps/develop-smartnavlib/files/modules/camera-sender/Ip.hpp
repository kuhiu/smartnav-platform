#ifndef A4AB82B7_3F09_424B_AF84_739D7E3FFDA5
#define A4AB82B7_3F09_424B_AF84_739D7E3FFDA5

#include <stdio.h>
#include <unistd.h>
#include <string.h> 

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

#include <string> 

namespace Ip {
  /**
   * @brief Get the interface ip
   * 
   * @param interface 
   * @return std::string 
   */
  std::string getIP(const char* interface);
}

#endif /* A4AB82B7_3F09_424B_AF84_739D7E3FFDA5 */
