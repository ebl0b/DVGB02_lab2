#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

#define END     "\033[0m"
#define RED     "\033[31m"

static qnode* CreateNode(){
	qnode* tmp = (qnode*)malloc(sizeof(qnode));
	if(tmp==NULL)
		printf(RED "MEM ERROR" END);
	return tmp;
}

void enQ(qnode** Q, struct pkt packet){
	qnode* new_node = CreateNode();
	qnode* curr_node = *Q;
	new_node->nx_pkt = NULL;
	new_node->qpkt = packet;
	if(IsEmpty(curr_node)){
		*Q = new_node;
	}else{
		for(; !IsEmpty(curr_node->nx_pkt); curr_node = curr_node->nx_pkt);
		curr_node->nx_pkt = new_node;
	}
}

void deQ(qnode** Q){
	qnode* curr_node = *Q;
	*Q = curr_node->nx_pkt;
	free(curr_node);
}

struct pkt CheckQ(qnode* Q){
	return Q->qpkt;
}

int IsEmpty(qnode* Q){
	return Q==NULL ? 1 : 0;
}

int Qsize(qnode* Q){
	int i = 0;
	while(Q!=NULL){
		i++;
		Q = Q->nx_pkt;
	}
	return i;
}