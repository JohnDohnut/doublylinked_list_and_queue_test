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
int dlist_check_consistency(dlist_t* dlist){https://github.com/JohnDohnut/doublylinked_list_and_queue_test
	if(dlist == NULL)
		return PARAM_NULL;
	if(dlist->head == NULL || dlist-> tail ==NULL){
		return DLIST_INCONSISTENT;	 
	}
	node_t* prev_node = NULL;
	node_t* curr_node = dlist->head;
	while(curr_node!=dlist->tail ){
	
		if(curr_node -> next == NULL){
			printf("dlist is consistent, next of none tail node is NULL, node ptr : %p\n",curr_node);
			return DLIST_INCONSISTENT;
		}
		if(curr_node -> prev != prev_node){
			printf("dlist is consistent, prev node not match, node ptr : %p \n",curr_node);
			return DLIST_INCONSISTENT;
		}
		if(curr_node->next->prev != curr_node){
			printf("dlist is consistent, prev of next node is not current node, node ptr : %p, node data : %d\n",curr_node, curr_node->data);
			return DLIST_INCONSISTENT;
		}
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

	dlist->tail-> prev = dlist->head;
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
		return NULL;
	return dlist->head;
}
node_t* dlist_get_tail(dlist_t* dlist){
	if(dlist == NULL)
		return NULL;
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
int dlist_delete_node(dlist_t* dlist, node_t*node){
	if(dlist == NULL)
		return PARAM_NULL;
	if(dlist_check_consistency != NO_ERR)
		return DLIST_INCONSISTENT;
	node_t* curr_node = dlist->head;
	while(curr_node!=NULL){
		if(curr_node == node)
			break;	
		curr_node = curr_node -> next;
	}
	if(curr_node == node){
		curr_node = node->prev;
		curr_node -> next = node -> next;
		node -> next -> prev = curr_node;
		free(node);
		return NO_ERR;
	}
	else{
		return NO_NODE_FOUND;	
	}
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
		return DLIST_INCONSISTENT;
	node->prev = dlist->head;
	node->next = dlist->head->next;
	
	(dlist->head->next)->prev = node;
	dlist->head->next = node;		
	return 0;
}	
/**
*@fn int dlist_insert_node_to_tail(dlist_t* dlist, node_t* node)
*@brief delete node from dlist
*@param dlist_t* dlist
*@param node_t* node
*@return int
*/
int dlist_insert_node_to_tail(dlist_t* dlist, node_t* node){
	if(dlist == NULL || node == NULL ){
		return PARAM_NULL;	
	}	
	if(dlist_check_consistency(dlist) !=0)
		return DLIST_INCONSISTENT;
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
	dlist_t* return_dlist = dlist_init();
	if(return_dlist == NULL)
		return NULL;
	if(dlist_check_consistency(headlist)!=NO_ERR || dlist_check_consistency(taillist) !=NO_ERR)
		return NULL;

	return_dlist->head = headlist->head;
	return_dlist->tail = taillist->tail;

	node_t* new_headlist_tail = headlist->tail->prev;
	node_t* new_taillist_head = taillist->head->next;
	
	new_headlist_tail -> next = new_taillist_head;
	new_taillist_head -> prev = new_headlist_tail;
	
	free(headlist->tail);
	free(taillist->head);
	free(headlist);
	free(taillist);
	return return_dlist;
}
/**
*@fn node_t* dlist_search_node_by_data_from_head(dlist_t* dlist, int data)
*@brief search node from dlist by name, starts from head.
*@param dlist_t* dlist
*@param int data
*@return node_t*
*/
node_t* dlist_search_node_by_data_from_head(dlist_t* dlist, int data){
	if(dlist == NULL)
		return NULL;
	node_t* curr_node = dlist->head;
	while(curr_node != dlist->tail){
		if(curr_node->data == data)
			return curr_node;
		curr_node = curr_node -> next;
	}
	return NULL;
}
/**
*@fn node_t* dlist_search_node_by_data_from_tail(dlist_t* dlist, int data)
*@brief search node from dlist by name, starts from tail
*@param dlist_t* dlist
*@param int data
*@return node_t*
*/
node_t* dlist_search_node_by_data_from_tail(dlist_t* dlist, int data){
	if(dlist == NULL)
		return NULL;
	node_t* curr_node = dlist->tail;
	while(curr_node != dlist->head){
		if(curr_node->data == data)
			return curr_node;
		curr_node = curr_node -> prev;
	}
	return NULL;
}
/**
*@fn int dlist_is_node_in_dlist(dlist_t* dlist, node_t* node)
*@brief check if node is in dlist
*@param dlist_t* dlist
*@param node_t* node
*@return int
*/
int dlist_is_node_in_dlist(dlist_t* dlist, node_t* node){
	if(dlist==NULL || node == NULL)
		return PARAM_NULL;
	node_t* curr_node = dlist->head;
	while(curr_node != dlist->tail){
		if(curr_node == node)
			return NO_ERR;
		curr_node = curr_node -> next;
	}
	return NODE_NOT_IN_DLIST;
}
/**
*@fn int dlist_swap_node(dlist_t* dlist, node_t* first, node_t* second)
*@brief swap two nodes
*@param dlist_t* dlist
*@param node_t* first
*@param node_t* second
*@return int
*/
int dlist_swap_node(dlist_t* dlist, node_t* first, node_t* second){
	if(dlist == NULL || first == NULL || second == NULL)
		return PARAM_NULL;
	if(dlist_check_consistency != NO_ERR)
		return DLIST_INCONSISTENT;
	if(first == dlist->head || second == dlist-> head || first == dlist->tail || second == dlist->tail)
		return MODIFY_HEAD;
	if(first == second)
		return SWAP_SAME_NODE;
	if(dlist_is_node_in_dlist(dlist, first) != NO_ERR || dlist_is_node_in_dlist(dlist, second) != NO_ERR)
		return NODE_NOT_IN_DLIST;
	node_t* first_prev = first->prev;
	node_t* first_next = first->next;

	first->next = second -> next;
	first->prev = second -> prev;
	
	second->prev = first_prev;
	second->next = first_next;

	first->next->prev = first;
	first->prev->next = first;
	
	second->next->prev = second;
	second->prev->next = second;

	return NO_ERR;
	
}

dlist_t* dlist_add_50_test_nodes(dlist_t* dlist, int add){
	if(dlist == NULL)
		return dlist;
	node_t* new_node;
	int i=add;
	for(i=add+1;i<add+50;i++){
		new_node = node_init();
		new_node->data = i;
		dlist_insert_node_to_tail(dlist,new_node);
	}
	return dlist;
}

dlist_t* dlist_add_test_node(dlist_t* dlist){
	if(dlist == NULL){
		return NULL;
	}
	node_t* new_node;
	int i=0;
	for(i=1;i<101;i++){
		new_node = node_init();
		new_node->data = i;
		if(i%2 == 0){
			
			dlist_insert_node_to_head(dlist,new_node);
		}
		else{	
			dlist_insert_node_to_tail(dlist,new_node);
		}
	}
	return dlist;
}
/**
*@fn void dlist_print_dlist(dlist_t* dlist)
*@brief print dlist
*@param dlist_t* dlist
*/
void dlist_print_dlist(dlist_t* dlist){
	
	node_t* node = dlist->head;
	while(node != NULL){
		if(node == dlist->head){
			printf("head => ");
		}
		else if(node == dlist->tail){
			printf("tail\n",node->data);
		}
		else{
			printf("%d => ",node->data);
		}
		node = node->next;
 	}
	printf("\n");

}
/**
*@section dlist Doubly Linked List
*test code for init => add node => merge dlist => destroy
*Head and tail nodes are dummy node, which is indicated by is_dummy member variable of struct node_s.
*/
int main(int argc, char* argv[]){
	dlist_t* dlist = dlist_init();
	dlist_t* dlist_50 = dlist_init();
	dlist_t* dlist_100 = dlist_init();

	dlist_add_test_node(dlist);
	dlist_add_50_test_nodes(dlist_50, 0);
	dlist_add_50_test_nodes(dlist_100,50);

	dlist_print_dlist(dlist);
	dlist_print_dlist(dlist_50);
	dlist_print_dlist(dlist_100);
	
	dlist_t* merged_dlist = dlist_merge_dlist(dlist_50,dlist_100);

	
	dlist_destroy(dlist);
	dlist_destroy(merged_dlist);
	
	return 0;
 	}





