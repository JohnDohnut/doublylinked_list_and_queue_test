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
	if( (queue->front == NULL && queue->rear != NULL) || (queue->front != NULL && queue->rear == NULL) ){
		return QUEUE_INCONSISTENT;
	}
	if(queue->front == queue->rear){
		return NO_ERR;
	}
	node_t* curr_node = queue->front;
	while(curr_node != queue->rear){
		if(curr_node -> next != curr_node->next->prev->next){
			return QUEUE_INCONSISTENT;		
		}
		if(curr_node -> next == curr_node || curr_node -> prev == curr_node){
			return QUEUE_INCONSISTENT;
		}
		if(curr_node != queue->rear && curr_node -> next == NULL){
			return QUEUE_INCONSISTENT;
		}
		if(curr_node == queue->rear && curr_node -> next != NULL){
			printf("Queue inconsistent, rear has next\n");
			return QUEUE_INCONSISTENT;
		}
		curr_node = curr_node -> next;
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
	queue -> rear = NULL;
	queue -> front = NULL;
}

/**
*@fn queue_enqueue(queue_t* queue, node_t* node)
*@brief push node to queue
*@param queue_t* queue
*@param node_t* node
*@return int
*/
int queue_enqueue(queue_t* queue, node_t* node){
	if(queue == NULL || node == NULL){
		return PARAM_NULL;
	}
	if(queue_check_consistency(queue) != NO_ERR){
		printf("incon push\n");
		return QUEUE_INCONSISTENT;
	}
	if((queue->front == queue->rear)  && (queue -> front == NULL)){
		queue->front = node;
		queue->rear = node;
		return NO_ERR;
		
	}
	else{
		node_t* temp = queue->rear;
		queue->rear = node;
		temp->next = queue->rear;
		queue->rear->prev = temp;
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
node_t* queue_dequeue(queue_t* queue){
	if(queue == NULL)
		return NULL;
	if(queue_check_consistency(queue) != NO_ERR){
		return NULL;
	}
	node_t* node = queue->front;
	if(queue->rear == queue->front){
		queue->rear = NULL;
		queue->front = NULL;
		return node;
	}
	queue->front = node->next;
	queue->front->prev = NULL;
	node->next = NULL;
	node->prev = NULL;
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
	if(queue->front == queue->rear){
		node_destroy(queue->front);
		free(queue);	
	}
	int count = 0;
	node_t* curr_node = queue->front;
	node_t* next_node = curr_node->next; 
	curr_node = queue->front;
	while(next_node != NULL){
		node_destroy(curr_node);
		curr_node = next_node;
		next_node = curr_node->next;
		
	}
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
		node->data = (void *)(i);
		if(queue_enqueue(queue,node)<NO_ERR){
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
	node_t* curr_node = queue->front;
	while(curr_node != NULL){
		if(curr_node == queue->front){
			printf("\nfront | %d ",curr_node->data);
		}
		
		else{
			printf(" => %d ",curr_node->data);		
		}
		curr_node  = curr_node ->next;
	}
	printf(" | rear\n");
}
/**
*@fn queue_t* queue_merge_queue(queue_t* front_queue, queue_t* rear_queue)
*@brief merge two queues
*@param queue_t*
*@param queue_t* 
*@return queue_t*
*/
queue_t* queue_merge_queue(queue_t* front_queue, queue_t* rear_queue){
	if(front_queue == NULL || rear_queue == NULL){
		return NULL;
	}
	if(queue_check_consistency(front_queue) != NO_ERR || queue_check_consistency(rear_queue) != NO_ERR){
		printf("	! merge queue inconsistent\n");
		return NULL;
	}
	if(front_queue->front == NULL && front_queue->rear ==NULL){
		free(front_queue);
		return rear_queue;	
	}
	else if(rear_queue->front == NULL && rear_queue->rear == NULL){
		free(rear_queue);
		return front_queue;
	}
	queue_t* new_queue = queue_init();
	new_queue->front = front_queue->front;
	new_queue->rear = rear_queue->rear;
	front_queue->rear->next = rear_queue->front;
	rear_queue->front->prev = front_queue->rear;
	free(front_queue);
	free(rear_queue);
	return new_queue;
	
}







