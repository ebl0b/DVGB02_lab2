#include "utils.h"

int GenChecksum(struct pkt packet){
	unsigned char* ptr = (unsigned char*)&packet;
	int sum = 0;
	for(int i = 0; i<2*sizeof(int); i++)
		sum += ptr[i];
	ptr += 3*sizeof(int);
	for(int i = 0; i<20; i++)
		sum += ptr[i];
	return sum;
}

int CmpChecksum(int cs1, int cs2){
	return cs1 == cs2;
}
int CmpSeqnum(int ss1, int ss2){
	return ss1 == ss2;
}