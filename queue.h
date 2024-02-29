#include "sim_engine.h"

#ifndef QUEUE
#define QUEUE

struct qnode{
	struct pkt qpkt;
	struct qnode* nx_pkt;
};
typedef struct qnode qnode;

void 		enQ		(qnode** Q, struct pkt packet);
void		deQ		(qnode** Q);
struct pkt	CheckQ	(qnode* Q);
int			IsEmpty	(qnode* Q);

#endif