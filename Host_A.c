#include "Sim_Engine.h"
#include "queue.h"
#include "Host_A.h"
#include "utils.h"

static qnode* Q;
static int seq_num;
static int sending;

static void SendToB()
{
    if(!IsEmpty(Q) && !sending){
        sending = 1;
        starttimer(A, TIMEOUT);
        tolayer3(A, CheckQ(Q));
    }
}

/* Called from layer 5, passed the data to be sent to other side */
void A_output( struct msg message)
{
    struct pkt packet;

    //Filling the package
    packet.seqnum = seq_num;
    packet.acknum = 0;
    memcpy(packet.payload, message.data, sizeof(message));
    packet.checksum = GenChecksum(packet);

    enQ(&Q, packet);
    SendToB();
    seq_num = seq_num ^ 1;
}

/* Called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet) 
{
    sending = 0;
    stoptimer(A);
    deQ(&Q);
    SendToB();
}

/* Called when A's timer goes off */
void A_timerinterrupt() 
{
    sending = 0;
    SendToB();
}  

/* The following routine will be called once (only) before any other */
/* Host A routines are called. You can use it to do any initialization */
void A_init() 
{
    Q = NULL;
    seq_num = 0;
    sending = 0;
}
