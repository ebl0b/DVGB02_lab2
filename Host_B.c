#include "Sim_Engine.h"
#include "Host_B.h"
#include <string.h>

static int prev_seq_num;

static int make_checksum(struct pkt packet) {
    int sum = 0;
    for (int i = 0; packet.payload[i] != '\0'; i++)
        sum += packet.payload[i];
    sum += packet.acknum;
    sum += packet.seqnum;
    return sum;
}

/* Called from layer 5, passed the data to be sent to other side */
void B_output( struct msg message) {
  /* DON'T IMPLEMENT */
}

/* Called from layer 3, when a packet arrives for layer 4 */
void B_input(struct pkt packet) {
    struct msg message;
    memcpy(message.data, packet.payload, sizeof(message));
    int cmp = make_checksum(packet);
    printf("\n\nseqnum: %d\nprev_seqnum: %d\n\n", packet.seqnum, prev_seq_num);
    if(cmp == packet.checksum && prev_seq_num != packet.seqnum){
        printf("\n\ntest B input\n\n");
        tolayer3(B, packet);
        tolayer5(B, message.data);
        prev_seq_num = packet.seqnum;
    }
    else if(cmp == packet.checksum && prev_seq_num == packet.seqnum){
        tolayer3(B, packet);
        //prev_seq_num = packet.seqnum;
    }
}

/* Called when B's timer goes off */
void B_timerinterrupt() {
  /* TODO */
}  

/* The following routine will be called once (only) before any other */
/* Host B routines are called. You can use it to do any initialization */
void B_init() {
  prev_seq_num = -1;
}
