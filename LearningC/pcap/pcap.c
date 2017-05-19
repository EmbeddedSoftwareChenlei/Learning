#include <stdio.h>
#include <pcap.h>
#include <time.h>
#include <stdlib.h>

void GetPacket(u_char* arg, const struct pcap_pkthdr* pkthdr, const u_char *packet)
{
    int *id = (int *)arg;
    
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
