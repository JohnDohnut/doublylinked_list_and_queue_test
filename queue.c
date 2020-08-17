#include "queue.h"
/**
*@fn int queue_check_consistency(queue_t* queue)
*@brief check consistency of queue
*@param queue_t* queue
*@return int
*/
int queue_check_consistency(queue_t* queue){
	if(queue == NULL){
		printf("param null\n");
		return PARAM_NULL;
	}
	if(queue->front == NULL){

		printf("front null\n");
		return QUEUE_INCONSISTENT;
	}
	if(queue->rear->is_dummy == 0){
		printf("rear is not dummy");
		return QUEUE_INCONSISTENT;
	}
	return NO_ERR;
}
/**
*@fn queue_init()
*@brief initialize queue
*@return queue_t* 
*/
queue_t* queue_init(){
	
	queue_t* queue = malloc(sizeof(queue_t));
	if(queue == NULL){
		return NULL;
	}
	queue->rear = node_init();
	if(queue->rear == NULL){
		return NULL;
	}
	queue->rear->next == queue->rear;
	queue->rear->prev == NULL;
	queue->front = queue->rear;	
		
	queue->rear->is_dummy = 1;
	return queue;
}
/**
*@fn queue_push(queue_t* queue, node_t* node)
*@brief push node to queue
*@param queue_t* queue
*@param node_t* node
*@return int
*/
int queue_push(queue_t* queue, node_t* node){
	if(queue == NULL || node == NULL){
		return PARAM_NULL;
	}
	if(queue_check_consistency(queue) != NO_ERR){
		printf("incon push\n");
		return QUEUE_INCONSISTENT;
	}
	if(queue->front == queue->rear){
		queue->front = node;
		queue->rear->next =node;
		node->next = NULL;
		node->prev = queue->rear;
	}
	else{
		node_t* temp = queue->rear->next;
		queue->rear->next = node;
		temp -> prev = node;
		node -> next = temp;
		node -> prev = queue->rear;
	}
	
	return NO_ERR;
}
/**
*@fn node_t* queue_peek(queue_t* queue)
*@brief peek queue
*@param queue_t* queue
*@return node_t*
*/
node_t* queue_peek(queue_t* queue){
	if(queue == NULL)
		return NULL;
	if(queue_check_consistency(queue) != NO_ERR){
		return NULL;
	}
	return queue->front;

}

/**
*@fn node_t* queue_pop(queue_t* queue)
*@brief pop node from queue
*@param queue_t* queue
*@return node_t*
*/
node_t* queue_pop(queue_t* queue){
	if(queue == NULL)
		return NULL;
	if(queue_check_consistency(queue) != NO_ERR){
		return NULL;
	}
	if(queue->rear == queue->front){
		return NULL;
	}
	queue->front = queue->front->prev;
	node_t* node = queue->front->next;
	node -> prev = NULL;
	node -> next = NULL;
	queue->front == NULL;
	
	return node;
}
/**
*@fn int queue_destroy(queue_t* queue)
*@brief destroy queue and all its nodes
*@param queue_t* queue
*@return int
*/
int queue_destroy(queue_t* queue){
	if(queue == NULL){
		return PARAM_NULL;
	}
	if(queue_check_consistency(queue) != NO_ERR){

		return QUEUE_INCONSISTENT;
	}
	int count = 0;
	node_t* temp = queue->front;
	node_t* curr_node = queue->front;
	while(curr_node != NULL){
		temp = curr_node->prev;
		free(curr_node);
		count++;
		curr_node = temp;
	}
	printf("count : %d \n",count);
	free(queue);
	return NO_ERR;
}


queue_t* queue_add_test_node(queue_t* queue,int add){
	if(queue == NULL)
		return NULL;
	if(queue_check_consistency(queue) != NO_ERR)
		return NULL;
	int i=1;
	node_t* node;
	for(i=1;i<add+1;i++){
		node = node_init();
		node->data = i;
		if(queue_push(queue,node)<NO_ERR){
			printf("push err\n");
			break;
		}
	}
	return queue;
}
/**
*@fn void queue_print_queue(queue_t* queue)
*@brief print queue
*@param queue_t* queue
*/
void queue_print_queue(queue_t* queue){
	node_t* curr_node = queue->rear;
	while(curr_node != NULL){
		if(curr_node == queue->rear){
			printf("rear => ");
		}
		else if(curr_node == queue->front){
			printf("%d => pop\n",curr_node->data);
			break;
		}
		else{
			printf("%d => ",curr_node->data);		
		}
		curr_node  = curr_node ->next;
	}
	printf("done\n");
}


/**
*@mainpapge C doubly linked list and queue test
*@section queue_section Queue
*test code for init => push => pop => destroy
*/
int main(){

	queue_t* queue = queue_init();
	queue_add_test_node(queue,50);
	queue_print_queue(queue);
	queue_pop(queue);
	printf("%d	\n", queue->front->data);
	queue_print_queue(queue);

	queue_destroy(queue);
	return 0;
}






