#include "Sim_Engine.h"
#include <string.h>

int 	GenChecksum	(struct pkt packet);
int 	CmpChecksum	(int cs1, int cs2);
int 	CmpSeqnum	(int ss1, int ss2);