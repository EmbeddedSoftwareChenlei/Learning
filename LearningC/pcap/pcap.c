#include <stdio.h>
#include <pcap.h>
#include <time.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <hiredis/hiredis.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/if_ether.h>
#include <net/if.h>
#include <linux/sockios.h>

#define IP "127.0.0.1" // ip address
#define PORT 6379      // visit port
#define DEV "eth0"     // device

unsigned char macaddr[ETH_ALEN];

void getMacAddr()
{
    memset(macaddr, 0, ETH_ALEN);
    char *device = DEV;
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    struct ifreq req;
    int err;
    strcpy(req.ifr_name, device);
    err = ioctl(s, SIOCGIFHWADDR, &req);
    printf("err value is %d\n", err);
    close(s);
    if (err != -1) {
        memcpy(macaddr, req.ifr_hwaddr.sa_data, ETH_ALEN);
    }
}

void doSaveData(const u_char **packet)
{
    getMacAddr();
    char *mac = (char *)malloc(sizeof(char *));
    int i;
    for (i = 0; i < ETH_ALEN; i++) {
        mac[i] = macaddr[i];
        printf("macAddr: %p, mac: %p\n", macaddr,mac);
    }
    printf("macAddr: %s, mac: %s\n", macaddr, *(&mac));
    printf("packet1 value is %02x\n", (*packet)[1]);
   // redisContext* c = redisConnect(IP, PORT);
   // if (c == NULL || c->err)
   // {
   //     if (c) {
   //         printf("Error: %s\n", c->errstr);
   //         redisFree(c);
   //     } else {
   //         printf("Can't allocate redis contex\n");
   //     }
   //     return;
   // }
   // printf("Connect to redisServer Success\n");

   // const char *command = "incr count";
   // redisReply *r = redisCommand(c, command);
   // if (NULL == r) {
   //     printf("Execute command failure\n");
   //     redisFree(c);
   //     return;
   // }
   // freeReplyObject(r);
   // printf("Succeed to execute command[%s]\n", command);
   // 
   // const char *command1 = "get count";
   // r = (redisReply*)redisCommand(c, command1);
   // if (NULL == r) {
   //     printf("Execute command1 failure\n");
   //     redisFree(c);
   //     return;
   // }
   // char* value = r->str;
   // freeReplyObject(r);
   // printf("Succeed to excute command[%s]\n", command1);

   // char index[20] = " packet";
   // strcat(index, value);
   // printf("index is %s\n", index);
   // char order[50] = " ";
   // printf("packet is %s\n", (char*)packet);
   // strcat(order, (char*)packet);
   // printf("order is %s\n", order);
   // strcat(index, order);
   // printf("content is %s\n", order);
   // char command2[50] = "set";
   // strcat(command2, order);

   // printf("command2 is [%s]\n", command2);
   // r = redisCommand(c, command2);
   // if (NULL == r) {
   //     printf("Execute command2 failure\n");
   //     redisFree(c);
   //     return;
   // }
   // freeReplyObject(r);
   // printf("Succeed to excute command[%s]\n", command2);

   // char command3[50] = "get";
   // strcat(command3, index);
   // r = redisCommand(c, command3);
   // if (NULL == r) {
   //     printf("Execute command3 failure\n");
   //     redisFree(c);
   //     return;
   // }
   // char *packetValue = r->str;
   // printf("packet value is %s\n", packetValue);
   // freeReplyObject(r);
   // redisFree(c);
}

void GetPacket(u_char* arg, const struct pcap_pkthdr* pkthdr, const u_char *packet)
{
    int *id = (int *)arg;
    
    doSaveData(&packet);
    printf("id: %d\n", ++(*id));
    printf("Packet length: %d\n", pkthdr->len);
    printf("Number of bytes: %d\n", pkthdr->caplen);
    printf("Recived time: %s\n", ctime((const time_t *)&pkthdr->ts.tv_sec)); 

    int i; 
    for (i = 0; i < pkthdr->len; i++) {
        printf(" %02x", packet[i]);
        if ((i+1)%16 == 0) {
            printf("\n"); 
        }
    }
    printf("\n\n");
    
    printf("temp value is %02x\n", packet[1]);
}

int main(int argc, char* argv[])
{
    char *dev, errbuf[PCAP_ERRBUF_SIZE];

	dev = pcap_lookupdev(errbuf);

    if (dev) { 
	    printf("success: Device: %s\n", dev);
    } else {
        printf("error: %s\n", errbuf);
        exit(1);
    }

    // open a device
    pcap_t *device = pcap_open_live(dev, 65535, 1, 0, errbuf);
    
    // link layer type
    int link_type = pcap_datalink(device);
    printf("link layer type=%d\n", link_type);

    if (!device) {
        printf("error: pcap_open_live(): %s\n", errbuf);
        exit(1);
    }

    /*
    // wait a packet to arrive
    struct pcap_pkthdr packet;
    const u_char *pkStr = pcap_next(device, &packet);

    if (!pkStr) {
        printf("did not capture a packet!\n");
        exit(1);
    }
    */

    //construct a filter
    struct bpf_program filter;
    pcap_compile(device, &filter, "src host 192.168.2.141", 1, 0);
    pcap_setfilter(device, &filter);

    // wait packet forever
    int id = 0;
    pcap_loop(device, -1, GetPacket, (u_char *)&id);
    //pcap_dispatch(device, -1, GetPacket, (u_char *)&id);
    /*
    printf("Packet length:%d\n", packet.len);
    printf("Number of bytes:%d\n", packet.caplen);
    printf("Recieved time: %s\n", ctime((const time_t *)&packet.ts.tv_sec));
    */

    pcap_close(device);
    return 0;
}
