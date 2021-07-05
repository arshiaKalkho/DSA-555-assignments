selectBiggestToLoc(iterator loc); {  // sentinal
	iterator begin;
	iterator biggest;
	
	while (begin != loc) {
		
		if (begin->current->data > biggest->current->data) {
			biggest = begin;

		}
		begin++;  

	}
	biggest->prev->next = biggest->next;      //deleting
	biggest->next->prev = biggest->prev;


	begin--; //this is now where we wante it to be
	Node node = new Node(*biggest, begin->next, begin);
	
	begin->next->prev = node;
    begin->next = node;
}

bool DList::eraseNthNode(unsigned int n) {//sentinal
	
	iterator begin = begin();
	
	
	for (int i = 0; i <= list.end(); i++) {
		if (i = n) {
			begin->prev->next = begin->next;
			begin->next->prev = begin->prev;
		
			return true;
		
		}
		begin++;
	
	}

	return false


}


int countNumBigger(int number, const int arr[], int size) {//checking array one by one back to front abusing size argument

	
	if (array[size-1] > number && size != 0) {    //if last element is bigger and arr not empty
		return countNumBigger(number, arr,size-1) + 1;


	}
	else if(size == 0) {                          //when array is empty 
	
		return 0;                     //this means that the final element wasn't bigger so start from zero
	
	}
	else {
	
		return countNumBigger(number, arr, size - 1);  //when it isn't bigger than number
	
	}



}



















