#include "dlist.h"
/**
*@fn int dlist_check_consistency(dlist_t* dlist)
*@brief check consistency of dlist.
*@param dlist_t* dlist
*@return int
*@detail
*1. check if head or tail is null
*2. for every node in dlist, check if current node, previous node, and next node is linked.
*/
int dlist_check_consistency(dlist_t* dlist){
	if(dlist == NULL)
		return PARAM_NULL;
	if(dlist->HEAD == NULL || dlist-> tail ==NULL){
		return DLIST_INCONSISTENT;	 
	}
	node_t* prev_node = NULL;
	node_t* curr_node = dlist->head;
	while(curr_node!=dlist->tail ){
	
		if(curr_node -> next == NULL)
			return DLIST_INCONSISTENT;
		if(curr_node -> prev != prev_node)
			return DLIST_INCONSISTENT;
		if(curr_node->next->prev != curr_node)
			return DLIST_INCONSISTENT;
		prev_node = curr_node;
		curr_node = curr_node->next;
	}
	return NO_ERR;	
	
}

dlist_t* dlist_init(){
	
	dlist_t* dlist = malloc(sizeof(dlist_t));
	if(dlist == NULL){
		return NULL;
	}
	dlist-> head = node_init();
	dlist-> tail = node_init();
	
	dlist->head->prev = NULL;
	dlist->head->next = dlist->tail;

	dlist->tail-> prev = dlist->prev;
	dlist->tail->next = NULL;	
	return dlist;		
}
/**
*@fn int dlist_destroy(dlist_t* dlist)
*@param dlist_t* dlist
*@return int
*@brief destroy dlist_t* 
*@detail
*dlist_destroy(dlist_t* dlist) must be called after checking the consistency of target dlist_t
*to ensure that there's no left node after calling dlist_destroy(dlist_t* dlist)
*/
int dlist_destroy(dlist_t* dlist){
	///dlist check error on dlist;
	if(dlist == NULL)
		return PARAM_NULL;
	node_t* next_node = dlist->head;
	node_t* node = dlist->head;
	while(next_node != NULL){
		node = next_node;
		next_node = node->next;
		node_destroy(node);	
	}
}

node_t* dlist_get_head(dlist_t* dlist){
	if(dlist == NULL)
		return PARAM_NULL;
	return dlist->head;
}
node_t* dlist_get_tail(dlist_t* dlist){
	if(dlist == NULL)
		return PARAM_NULL;
	return dlist->tail;
}

int dlist_set_head(dlist_t* dlist, node_t* node){
	if(dlist == NULL)
		return PARAM_NULL;
	dlist->head = node;
	return 0;	
}
int dlist_set_tail(dlist_t* dlist, node_t* node){
	if(dlist ==NULL)
		return PARAM_NULL;
	dlist->tail = node;
	return 0;
}
/**
*@fn int dlist_insert_node_to_head(dlist_t* dlist, node_t* node)
*@brief 
*@param dlist_t* node_t*
*@return int
*@detail
*All modification function must be called after ensuring consistency of dlist.
*/
int dlist_insert_node_to_head(dlist_t* dlist, node_t* node){
	if(dlist == NULL || node == NULL )
		return PARAM_NULL;
	if(dlist_check_consistency(dlist) != 0)
		return DLIST_INCONSISTENCY;
	node->prev = dlist->head;
	node->next = dlist->head->next;
	
	(dlist->head->next)->prev = node;
	dlist->head->next = node;		
	return 0;
}	

int dlist_insert_node_to_tail(dlist_t* dlist, node_t* node){
	if(dlist == NULL || node == NULL ){
		return PARAM_NULL;	
	}	
	if(dlist_check_consistency(dlist) !=0)
		return DLIST_INCONSISTENCY;
	node->next = dlist->tail;
	node->prev = dlist->tail->prev;
	
	(dlist->tail->prev)->next = node;
	dlist->tail->prev = node;  
	
	return NO_ERR;

		
}
/**
*@fn dlist_t* dlist_merge_dlist(dlist_t* headlist, dlist_t* taillist)
*@brief merge two dlist and return new merged dlist.
*@param dlist_t* headlist
*@param dlist_t* taillist
*@return dlist_t*
*/
dlist_t* dlist_merge_dlist(dlist_t* headlist, dlist_t* taillist){
	if(headlist == NULL || taillist == NULL)
		return NULL;
	return_dlist = dlist_init();
	if(return_dlist == NULL)
		return NULL;
	if(dlist_check_consistency(headlist)!=NO_ERR || dlist_check_consistency(taillist) !=NO_ERR)
		return NULL;
	headlist->tail->next = taillist->head;
	taillist->head->prev = headlist->tail;
	return_dlist -> head = headlist->head;
	return_dlist -> tail = taillist->tail;
	free(headlist);
	free(taillist);
	return return_dlist;
}
int main(int argc, char* argv[]){
	dlist_t* dlist;
	dlist = dlist_init();
	node_t* node = node_init();
	node_set_data(node, 3);
	dlist_insert_node_to_head(dlist,node);
	printf("head : %d \n",dlist->head->data);
	printf("consistency : %d\n",dlist_check_error(dlist));
	free(dlist);
	return 0;
 	}





