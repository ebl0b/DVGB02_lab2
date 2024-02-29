#include "Sim_Engine.h"
#include "queue.h"
#include "Host_A.h"
#include <string.h>

static qnode* Q;
static int seq_num;
static int serv_seq_num;

static int GenChecksum(struct msg message){
    int checksum = 0;
    int msglen = sizeof(message);
    for(int i = 0; i<msglen; i++){
        checksum += message.data[i];
    }
    return checksum;
}

static void SendToB(){
    if(!IsEmpty(Q)){
        starttimer(A, 10);
        tolayer3(A, CheckQ(Q));
    }
}

/* Called from layer 5, passed the data to be sent to other side */
void A_output( struct msg message) {
    struct pkt packet;
    packet.seqnum = seq_num;
    packet.acknum = 0;
    memcpy(packet.payload, message.data, sizeof(message));
    packet.checksum = GenChecksum(message);
    enQ(&Q, packet);
    serv_seq_num = CheckQ(Q).seqnum;
    if(serv_seq_num == seq_num){
        printf("\n\ntest: %d\n\n", Qsize(Q));
        SendToB();
    }
    seq_num++;
}

/* Called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet) {
    stoptimer(A);
    printf("\n\ntest input\n\n");
    if(!IsEmpty(Q)){
        deQ(&Q);
        serv_seq_num++;
    }
    SendToB();
}

/* Called when A's timer goes off */
void A_timerinterrupt() {
    SendToB();
}  

/* The following routine will be called once (only) before any other */
/* Host A routines are called. You can use it to do any initialization */
void A_init() {
    Q = NULL;
    seq_num = 0;
    serv_seq_num = 0;
}
