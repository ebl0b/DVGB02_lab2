#include "Sim_Engine.h"
#include "Host_B.h"
#include <string.h>

static int prev_seq_num;

static int GenChecksum(struct msg message){
    int checksum = 0;
    int msglen = sizeof(message);
    for(int i = 0; i<msglen; i++){
        checksum += message.data[i];
    }
    return checksum;
}

/* Called from layer 5, passed the data to be sent to other side */
void B_output( struct msg message) {
  /* DON'T IMPLEMENT */
}

/* Called from layer 3, when a packet arrives for layer 4 */
void B_input(struct pkt packet) {
    struct msg message;
    memcpy(message.data, packet.payload, sizeof(message));
    int cmp = GenChecksum(message);
    if(cmp == packet.checksum && prev_seq_num != packet.seqnum){
        tolayer3(B, packet);
        tolayer5(B, message.data);
    }
    else if(cmp == packet.checksum && prev_seq_num == packet.seqnum){
        tolayer3(B, packet);
    }
}

/* Called when B's timer goes off */
void B_timerinterrupt() {
  /* TODO */
}  

/* The following routine will be called once (only) before any other */
/* Host B routines are called. You can use it to do any initialization */
void B_init() {
  prev_seq_num = 0;
}
