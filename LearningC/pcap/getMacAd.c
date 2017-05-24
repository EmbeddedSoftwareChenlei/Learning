#include <stdio.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/if_ether.h>
#include <net/if.h>
#include <linux/sockios.h>
#include <string.h>

int main()
{
    char *device = "eth0";
    unsigned char macaddr[ETH_ALEN];
    int i, s;
    s = socket(AF_INET, SOCK_DGRAM, 0);
    struct ifreq req;
    int err;
    char *rc = strcpy(req.ifr_name, device);
    err = ioctl(s, SIOCGIFHWADDR, &req);
    printf("err value is %d\n", err);
    close(s);
    if (err != -1) {
        memcpy(macaddr, req.ifr_hwaddr.sa_data, ETH_ALEN);
        for (i = 0; i < ETH_ALEN-1; i++) {
            printf("%02x:", *(macaddr+i));
        }
        printf("%02x", macaddr[ETH_ALEN-1]);
    }
    printf("\r\n");
}
