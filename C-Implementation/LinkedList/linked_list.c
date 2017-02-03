









void reverse_list(List* the_list){
	Node currentNode = the_list->head->next;
	head->next=null;
	Node hold_next=currentNode->next;
	Node hold_prev = the_list->head;

	while(hold_prev!=tail){
		hold_next = currentNode->next;
		currentNode->next = hold_prev;
		hold_prev = currentNode;
		currentNode = hold;
	}

	hold_next = the_list->head;
	the_list->head = the_list->tail;
	the_list->tail = hold_next;


}
