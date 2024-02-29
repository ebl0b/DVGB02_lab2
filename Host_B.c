#include "Sim_Engine.h"
#include "Host_B.h"
#include "utils.h"

static int prev_seq_num;

/* Called from layer 5, passed the data to be sent to other side */
void B_output( struct msg message) {
  /* DON'T IMPLEMENT */
}

/* Called from layer 3, when a packet arrives for layer 4 */
void B_input(struct pkt packet) 
{
    struct msg message;

    memcpy(message.data, packet.payload, sizeof(message));
    int cmp = GenChecksum(packet);  

    if(CmpChecksum(cmp, packet.checksum) && !CmpSeqnum(prev_seq_num, packet.seqnum)){
        //Packet is intact and IS NOT a duplicate
        tolayer3(B, packet);
        tolayer5(B, message.data);
        prev_seq_num = packet.seqnum;
    }

    else if(CmpChecksum(cmp, packet.checksum) && CmpSeqnum(prev_seq_num, packet.seqnum)){
        //Packet is intact and IS a duplicate
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
  prev_seq_num = 1;
}
