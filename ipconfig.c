/* https://code.woboq.org/userspace/glibc/inet/ifaddrs.h.html  <ifaadrs.h> 헤더 참조 */
/* https://pubs.opengroup.org/onlinepubs/7908799/xns/netinetin.h.html <netinet/in.h> 헤더 참조 */
#include "ipconfig.h"

#define REQ_CNT 20

void convrt_mac( const char *data, char *cvrt_str, int sz );
/* MAC address를 보기 좋게 변환하는 함수 */

int ipconfig()
{
  struct ifaddrs *interfaceArray = NULL, *tempIfAddr = NULL;
  void *tempAddrPtr = NULL;
  char addressOutputBuffer[INET6_ADDRSTRLEN];
  int rc = 0;

  rc = getifaddrs(&interfaceArray);  /* 현재 인터페이스 검색 */
  if (rc == 0)
  {    
    for(tempIfAddr = interfaceArray; tempIfAddr != NULL; tempIfAddr = tempIfAddr->ifa_next)
	/* ifa_next 필드에는 목록의 다음 구조에 대한 포인터가 포함되어 있습니다. 이 필드는 목록의 마지막 구조에서 NULL입니다. */
    {
      if(tempIfAddr->ifa_addr->sa_family == AF_INET)
	  /* ifa_addr 필드는 인터페이스의 주소 또는 링크 수준 주소를 참조합니다. 그렇지 않으면 NULL입니다. (ifa_addr 필드의 sa_family 필드는 ifa_addr 주소의 형식을 결정해야 합니다.) */
        tempAddrPtr = &((struct sockaddr_in *)tempIfAddr->ifa_addr)->sin_addr;
      else
        tempAddrPtr = &((struct sockaddr_in6 *)tempIfAddr->ifa_addr)->sin6_addr;
      
      printf("Internet Address:  %s \n",
             inet_ntop(tempIfAddr->ifa_addr->sa_family,
                       tempAddrPtr,
                       addressOutputBuffer,
                       sizeof(addressOutputBuffer)));

      printf("LineDescription :  %s \n", tempIfAddr->ifa_name);
	  /*ifa_name 필드에 인터페이스(라인 설명) 이름이 포함되어 있습니다.*/
      if(tempIfAddr->ifa_netmask != NULL)
	  /* ifa_netmask 필드는 ifa_addr와 연결된 넷마스크를 참조합니다. 이 넷마스크가 설정되어 있으면 해당 넷마스크는 NULL입니다. */
      {
        if(tempIfAddr->ifa_netmask->sa_family == AF_INET)
          tempAddrPtr = &((struct sockaddr_in *)tempIfAddr->ifa_netmask)->sin_addr;
        else
          tempAddrPtr = &((struct sockaddr_in6 *)tempIfAddr->ifa_netmask)->sin6_addr;

        printf("Netmask         :  %s \n",
               inet_ntop(tempIfAddr->ifa_netmask->sa_family,
                         tempAddrPtr,
                         addressOutputBuffer,
                         sizeof(addressOutputBuffer)));
      }

      if(tempIfAddr->ifa_ifu.ifu_broadaddr != NULL)
      {
        /* ifa_flags 필드가 P2P 인터페이스임을 나타내는 경우 */
		/* ifa_flags 필드에는 인터페이스에 대한 일부 정보를 제공하는 플래그가 포함되어 있습니다. */
        if(tempIfAddr->ifa_flags & IFF_POINTOPOINT)
        {
          printf("Destination Addr:  ");
          if(tempIfAddr->ifa_ifu.ifu_dstaddr->sa_family == AF_INET)
		  /* ifa_ifu 필드는 다음과 같은 조합입니다. */
		  /* ifu_broadadaddr는 점 대 점 인터페이스에 대해서만 참조되어야 하며, ifa_addr이 존재하면 연결된 브로드캐스트 주소를 참조하고, 그렇지 않으면 NULL입니다. */
		  /* ifu_dstadr는 지점 간 인터페이스에서 대상 주소를 참조합니다(있는 경우). 그렇지 않으면 NULL입니다. */
            tempAddrPtr = &((struct sockaddr_in *)tempIfAddr->ifa_ifu.ifu_dstaddr)->sin_addr;
          else
            tempAddrPtr = &((struct sockaddr_in6 *)tempIfAddr->ifa_ifu.ifu_dstaddr)->sin6_addr;
        }
        else
        {
          printf("Broadcast Addr  :  ");
          if(tempIfAddr->ifa_ifu.ifu_broadaddr->sa_family == AF_INET)
            tempAddrPtr = &((struct sockaddr_in *)tempIfAddr->ifa_ifu.ifu_broadaddr)->sin_addr;
          else
            tempAddrPtr = &((struct sockaddr_in6 *)tempIfAddr->ifa_ifu.ifu_broadaddr)->sin6_addr;
        }
          
        printf("%s \n",
               inet_ntop(tempIfAddr->ifa_ifu.ifu_broadaddr->sa_family,
                         tempAddrPtr,
                         addressOutputBuffer,
                         sizeof(addressOutputBuffer)));
      }
      printf("\n");
    }

    freeifaddrs(interfaceArray);             /* 동적 메모리 해제 */
    interfaceArray = NULL;                   /* 해제 후 사용 방지  */
  }
  else
  {
     printf("getifaddrs() failed with errno =  %d %s \n",
            errno, strerror(errno));
     return rc;
  }
}
