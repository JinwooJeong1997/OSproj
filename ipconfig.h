#include <sys/types.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ether.h>
#include <net/if.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void convrt_mac( const char *data, char *cvrt_str, int sz );
/* MAC address를 보기 좋게 변환하는 함수 */

int ipconfig();