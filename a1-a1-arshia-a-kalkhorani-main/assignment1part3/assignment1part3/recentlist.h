/*******************************************************************/
/*                                                                 */
/*  A1 Part 2: RecentList starter file                             */
/*                                                                 */
/*  Author1 Name: <Arshia A Kalkhorani>		 					   */
/*      - class/function list/main author or main checker          */
/*  Author2 Name: <name here>		 							   */
/*      - class/function list/main author or main checker          */
/*                                                                 */
/*******************************************************************/

template <typename T>

class RecentList{
	
	struct Node{// sentinal model
		T data;
		Node* next;
		Node* prev;
		Node(const T& fdata=T{}, Node* pr = nullptr, Node* nx=nullptr){ //constructor i flipped them it makes more sense previous and then next
			data = fdata;
			next = nx;
			prev = pr;
		}
	};

	Node* front;
	Node* back;


public:
	
	
	
	class const_iterator{
		friend class RecentList<T>;
	protected: //constructor protected so that iterator class can access it in its constructor below
		
		
		Node* current;
		
		
		const_iterator(Node* n) {
			this->current = n;
		}

	public:
		const_iterator(){								 //constructor
			current = nullptr;
		}
		const_iterator operator++(){					//++
			current = current->next;
			return *this;
		}
		
		
		const_iterator operator++(int){					//++ int
			const_iterator old = *this;
			current = current->next;
			
			
			return old;
		}
		
		
		
		const_iterator operator--(){					//--
			current = current->prev;
			return *this;
		}
		
		
		
		const_iterator operator--(int){					//-- int
			const_iterator old = *this;
			current = current->prev;
			return old;
		}
		
		
		bool operator==(const_iterator rhs) {        //       ==
			return (current == rhs.current); 
		}  
		
		
		
		bool operator!=(const_iterator rhs){          //        !=
			return (current != rhs.current);
		}
		
		
		
		const T& operator*()const{ return this->current->data; }
	};
	class iterator:public const_iterator{
		friend class RecentList<T>;
	protected:	
		
		//iterator(Node* n) :const_iterator(n) {}       //constructor
		iterator(Node* n) {
			this->current = n;
		}

	public:
		
		iterator() {}//:const_iterator(){}
		
		iterator operator++(){                                             //++
			if (this->current) {
				this->current = this->current->next;
			}
			
			return *this;
		}
		
		
		iterator operator++(int){                                          //++ int
			iterator old = *this;
			if (this->current) {
				this->current = this->current->next;
			}
			
			return old;
		}
		
		
		iterator operator--(){                                             //-- 
		
			if (this->current) {
				this->current = this->current->prev;
			}
			
		    return *this;
		}
		iterator operator--(int){                                          //-- int
			iterator old = *this;
			if (this->current) {
				this->current = this->current->prev;
			}
			

			return old;
		}
		
		
		T& operator*() { return this->current->data; }                     //*
		
		
		const T& operator*()const{ return this->current->data; }            //*
	};
	
	
	
	RecentList();
	~RecentList();                                                   //assignment opperators
	RecentList(const RecentList& rhs);
	RecentList& operator=(const RecentList& rhs);
	RecentList(RecentList&& rhs);
	RecentList& operator=(RecentList&& rhs);
	void push_front(const T& data);
	void push_back(const T& data);
	void pop_front();
	void pop_back();
	
	
	iterator begin() { return iterator(front->next); }                                           //BEGIN
	iterator end() { return iterator(back); }                                                    //END
	
	
	const_iterator cbegin() const { return const_iterator(front->next); }                        //CBEGIN
	const_iterator cend() const { return const_iterator(back); }   //                            //CEND
	
	
	iterator search(const T& data);
	
	iterator erase(iterator it);
	iterator erase(iterator first, iterator last);
	bool empty() const;
	int size() const;
	T& getFront();
	T& getBack();

};

template <typename T>
RecentList<T>::RecentList(){                               //putting the sentinals in place                  //NO ARG CONSTRUCTOR
	front = new Node();                                    
	back = new Node();

	front->next = back;
	back->prev = front;
}
template <typename T>
RecentList<T>::~RecentList(){                                                                                //DESTRUCTOR
	
	Node* curr = front;                                    //setting the current to the first element
	
	while (curr) {                                         //as long as current is not nullptr go to next element and delete the old one
		Node* temp = curr; 
		curr = curr->next;
		delete temp;
	}
}
template <typename T>
RecentList<T>::RecentList(const RecentList& rhs){                                                   // COPY
	

	front = new Node();                                    //making centinals 
	back = new Node();

	front->next = back;
	back->prev = front;

	                                                       //making a replica of the list

	for (const_iterator it = rhs.cbegin(); it != rhs.cend(); it++) {
	
		Node* node = new Node(*it, back->prev,back);
		back->prev->next = node;
		back->prev = node;
	
	}


}
template <typename T>
RecentList<T>& RecentList<T>::operator=(const RecentList& rhs){                                     // = COPY
	                                                          //we can erase the data first since the object is already initianilized

	this->erase(this->begin(), this->end());
	
	front = new Node();                                    //making centinals 
	back = new Node();

	front->next = back;
	back->prev = front;

	                                                           //making a replica of the list

	for (const_iterator it = rhs.cbegin(); it != rhs.cend(); it++) {

		Node* node = new Node(*it, back->prev,back);
		back->prev->next = node;
		back->prev = node;

	}
	return *this;


}
template <typename T>
RecentList<T>::RecentList(RecentList&& rhs){                                                        // MOVE 
	                                                     //tranfaring ownership to this object
	front = rhs.front;
	back = rhs.back;     
	                                                     //reseting the rhs to a safe empty state
	rhs.front = new Node();
	rhs.back = new Node();
	                                                     //pointing the sentinals together
	rhs.front->next = rhs.back;
	rhs.back->prev = rhs.front;
}

template <typename T>
RecentList<T>& RecentList<T>::operator=(RecentList&& rhs){											// = MOVE
	
	                                                    //create new nodes
	Node* tmpFront = front;
	Node* tmpBack = back;
	                                                    //make them point to right spot
	front = rhs.front;
	back = rhs.back;
	rhs.front = tmpFront;
	rhs.back = tmpBack;

	return *this;
}


template <typename T>
void RecentList<T>::push_front(const T& data){															 //INSERT
	
	Node* newNode = new Node(data, front, front->next); //make new node at the front of the list
	front->next->prev = newNode;
	front->next = newNode;
}
template <typename T>
void RecentList<T>::push_back(const T& data) {															 //push_back

	Node* newNode = new Node(data, back->prev,back);  //make new node at the end of the list
	back->prev->next = newNode;
	back->prev = newNode;

}

template <typename T>
void RecentList<T>::pop_front() {


	RecentList<T>::iterator it = this->begin();
	if (it.begin() && it != end()) {                //if iterator is pointing to something && not the nullptr at the end of the list
		
		Node* remove = it;                  //creating a copy (remove)


		it.current->prev->next = it.current->next;  //placing 
		it.current->next->prev = it.current->prev;

		
	}

}

template <typename T>
void RecentList<T>::pop_back() {


	RecentList<T>::iterator it = this->end();
	if (it.begin() && it != end()) {                //if iterator is pointing to something && not the nullptr at the end of the list
		
		Node* remove = it;                  //creating a copy (remove)


		it.current->prev->next = it.current->next;  //placing 
		it.current->next->prev = it.current->prev;


	}

}


template <typename T>
typename RecentList<T>::iterator RecentList<T>::search(const T& data){                                //SEARCH
	                                                    //search for the node and move it to front then return the iterator 
	iterator beg = this->begin();
	iterator end = this->end();

	while (beg != end) {                                //till the end of the list
		
		if (beg.current->data == data) {                //see if the data matches
			

			  
			beg.current->prev->next = beg.current->next;//removing the found node from the list 
			beg.current->next->prev = beg.current->prev;

			
			beg.current->next = front->next;            //replacing
			beg.current->prev = front;
			front->next->prev = beg.current;
			front->next = beg.current;

			return beg;
		}
		++beg; //next
	}

	return this->end();
}

template <typename T>
 T& RecentList<T>::getFront() {
	
	
	 RecentList<T>::iterator it = this->front;
	return *it;
}
template <typename T>
 T& RecentList<T>::getBack() {
	 RecentList<T>::iterator it = this->back;
    return *it;
}

template <typename T>
typename RecentList<T>::iterator RecentList<T>::erase(iterator it){									 //ERASE 1ARG
	if (it.current && it != end()) {                //if iterator is pointing to something && not the nullptr at the end of the list
		Node* remove = it.current;                  //creating a copy (remove)
		
		
		it.current->prev->next = it.current->next;  //placing 
		it.current->next->prev = it.current->prev;

		//delete remove;                              //deleting would cause this not to work i could't spend more time
		//return ++it; 
	}
	
	return ++it;
	                                  	

	
}

template <typename T>
typename RecentList<T>::iterator RecentList<T>::erase(iterator first, iterator last){                 //ERASE 2ARG
	Node* temp;

	
	first.current->prev->next = last.current;
	last.current->prev = first.current->prev;

	
	if (first != last) {                             //if not empty
		temp = first.current;						 //make current next
		
		delete temp;                                 //say goodbye to temp
	
		++first;                                     //go next
	}
	return last;
}
template <typename T>                                                                              
bool RecentList<T>::empty() const{                                                                    //EMPTY
	return front->next == back;                       //check to see if front == back
}
template <typename T>
int RecentList<T>::size() const{                                                                      //SIZE
	int size = 0;
	for (const_iterator it = this->cbegin(); it != this->cend(); it++) {//simple for loop for counting each element
		size++;
	}
	return size;
	
}
