#include "wall.h"
#include "maze.h"


/*******************************************************************/
/*                                                                 */
/*  A1 Part 3: runMaze() function                                  */
/*                                                                 */
/*  Author1 Name:Arshia A Kalkhorani     		 			       */
/*      - class/function list/main author or main checker          */
/*  Author2 Name: <name here>		 							   */
/*      - class/function list/main author or main checker          */
/*                                                                 */
/*******************************************************************/



template <typename T>

class RecentList {

	struct Node {// sentinal model
		T data;
		Node* next;
		Node* prev;
		Node(const T& fdata = T{}, Node* pr = nullptr, Node* nx = nullptr) { //constructor i flipped them it makes more sense previous and then next
			data = fdata;
			next = nx;
			prev = pr;
		}
	};

	Node* front;
	Node* back;

	int size = 0;
public:


	class const_iterator {
		friend class RecentList<T>;
	protected: //constructor protected so that iterator class can access it in its constructor below


		Node* current;


		const_iterator(Node* n) {
			this->current = n;
		}

	public:
		const_iterator() {								 //constructor
			current = nullptr;
		}
		const_iterator operator++() {					//++
			current = current->next;
			return *this;
		}


		const_iterator operator++(int) {					//++ int
			const_iterator old = *this;
			current = current->next;


			return old;
		}



		const_iterator operator--() {					//--
			current = current->prev;
			return *this;
		}



		const_iterator operator--(int) {					//-- int
			const_iterator old = *this;
			current = current->prev;
			return old;
		}


		bool operator==(const_iterator rhs) {        //       ==
			return (current == rhs.current);
		}



		bool operator!=(const_iterator rhs) {          //        !=
			return (current != rhs.current);
		}



		const T& operator*()const { return this->current->data; }
	};
	class iterator :public const_iterator {
		friend class RecentList<T>;
	protected:

		//iterator(Node* n) :const_iterator(n) {}       //constructor
		iterator(Node* n) {
			this->current = n;
		}

	public:

		iterator() {}//:const_iterator(){}

		iterator operator++() {                                             //++
			if (this->current) {
				this->current = this->current->next;
			}

			return *this;
		}


		iterator operator++(int) {                                          //++ int
			iterator old = *this;
			if (this->current) {
				this->current = this->current->next;
			}

			return old;
		}


		iterator operator--() {                                             //-- 

			if (this->current) {
				this->current = this->current->prev;
			}

			return *this;
		}
		iterator operator--(int) {                                          //-- int
			iterator old = *this;
			if (this->current) {
				this->current = this->current->prev;
			}


			return old;
		}


		T& operator*() { return this->current->data; }                     //*


		const T& operator*()const { return this->current->data; }            //*
	};



	RecentList();
	~RecentList();                                                   //assignment opperators
	RecentList(const RecentList& rhs);
	RecentList& operator=(const RecentList& rhs);
	RecentList(RecentList&& rhs);
	RecentList& operator=(RecentList&& rhs);
	iterator begin() { return iterator(front->next); }                                           //BEGIN
	iterator end() { return iterator(back); }                                                    //END


	const_iterator cbegin() const { return const_iterator(front->next); }                        //CBEGIN
	const_iterator cend() const { return const_iterator(back); }   //                            //CEND

	void insert(const T& data);
	iterator search(const T& data);
	iterator erase(iterator it);
	iterator erase(iterator first, iterator last);
	bool empty() const;
	int getSize() const;

	void push_front(const T& data) {
		
		front->next = front->next->prev = new Node(data, front, front->next);
		++size;
	}
	void push_back(const T& data) {
		
		back->prev = back->prev->next = new Node(data, back->prev,back) ;
		++size;
	}
	void pop_front() {
		
		if (front->next != back) {
			front->next = front->next->next;
			delete front->next->prev;
			front->next->prev = front;
			--size;
		}
	}
	void pop_back() {
		
		if (back->prev != front) {
			back->prev = back->prev->prev;
			delete back->prev->next;
			back->prev->next = back;
			--size;
		}
	}
	
};

template <typename T>
RecentList<T>::RecentList() {                               //putting the sentinals in place                  //NO ARG CONSTRUCTOR
	size = 0;                                         //initialize size to one
	front = new Node();
	back = new Node();

	front->next = back;
	back->prev = front;
}
template <typename T>
RecentList<T>::~RecentList() {                                                                                //DESTRUCTOR

	Node* curr = front;                                    //setting the current to the first element

	while (curr) {                                         //as long as current is not nullptr go to next element and delete the old one
		Node* temp = curr;
		curr = curr->next;
		delete temp;
	}
}
template <typename T>
RecentList<T>::RecentList(const RecentList& rhs) {                                                   // COPY


	front = new Node();                                    //making centinals 
	back = new Node();

	front->next = back;
	back->prev = front;

	//making a replica of the list

	for (const_iterator it = rhs.cbegin(); it != rhs.cend(); it++) {

		Node* node = new Node(*it, back->prev, back);
		back->prev->next = node;
		back->prev = node;

	}


}
template <typename T>
RecentList<T>& RecentList<T>::operator=(const RecentList& rhs) {                                     // = COPY
															  //we can erase the data first since the object is already initianilized

	this->erase(this->begin(), this->end());

	front = new Node();                                    //making centinals 
	back = new Node();

	front->next = back;
	back->prev = front;

	//making a replica of the list

	for (const_iterator it = rhs.cbegin(); it != rhs.cend(); it++) {

		Node* node = new Node(*it, back->prev, back);
		back->prev->next = node;
		back->prev = node;

	}
	return *this;


}
template <typename T>
RecentList<T>::RecentList(RecentList&& rhs) {                                                        // MOVE 
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
RecentList<T>& RecentList<T>::operator=(RecentList&& rhs) {											// = MOVE

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
void RecentList<T>::insert(const T& data) {															 //INSERT
	
	Node* newNode = new Node(data, front, front->next); //make new node at the front of the list
	front->next->prev = newNode;
	front->next = newNode;




}

template <typename T>
typename RecentList<T>::iterator RecentList<T>::search(const T& data) {                                //SEARCH
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
typename RecentList<T>::iterator RecentList<T>::erase(iterator it) {									 //ERASE 1ARG
	if (it.current && it != end()) {                //if iterator is pointing to something && not the nullptr at the end of the list
		Node* remove = it.current;                  //creating a copy (remove)


		it.current->prev->next = it.current->next;  //placing 
		it.current->next->prev = it.current->prev;

		//delete remove;                              //deleting would cause this not to work i could't spend more time
		//return ++it; 
	}

	return ++it;
	//return next node



}

template <typename T>
typename RecentList<T>::iterator RecentList<T>::erase(iterator first, iterator last) {                 //ERASE 2ARG
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
bool RecentList<T>::empty() const {                                                                    //EMPTY
	return front->next == back;                       //check to see if front == back
}
/*template <typename T>                               //with the new system this is not needed
int RecentList<T>::size() const {                                                                      //SIZE
	int size = 0;
	for (const_iterator it = this->cbegin(); it != this->cend(); it++) {//simple for loop for counting each element
		size++;
	}
	return size;
	
}*/
template <typename T>
int RecentList<T>::getSize() const {
	return size;
}







using namespace std;


int findPath(Maze& theMaze, RecentList<int>& path, int startCell, int endCell) {

	theMaze.mark(startCell);           //mark and push the current cell
	path.push_back(startCell);
 
	int row = theMaze.getRow(startCell);//converting from a cell to row and column so we can go differet directions
	int col = theMaze.getCol(startCell);

	bool canFindPath = false;

	
	if (startCell == endCell) {//this ends the function if the current path is the final path
		return true;
	}

	
	if (theMaze.canGo(startCell, theMaze.getCell(row, col - 1)) && !theMaze.isMarked(theMaze.getCell(row, col - 1))) {   //turn left
		
		canFindPath = findPath(theMaze, path, theMaze.getCell(row, col - 1), endCell); //recursion
		if (canFindPath) {
			return true;
		}
		else {
			path.pop_back();
		}
	}


	if (theMaze.canGo(startCell, theMaze.getCell(row, col + 1)) && !theMaze.isMarked(theMaze.getCell(row, col + 1))) {  //turn right
		
		canFindPath = findPath(theMaze, path, theMaze.getCell(row, col + 1), endCell);
		if (canFindPath) {
			return true;
		}
		else {
			path.pop_back();
		}
	}

	
	if (theMaze.canGo(startCell, theMaze.getCell(row + 1, col)) && !theMaze.isMarked(theMaze.getCell(row + 1, col))) { //turn up
		
		canFindPath = findPath(theMaze, path, theMaze.getCell(row + 1, col), endCell);
		if (canFindPath) {
			return true;
		}
		else {
			path.pop_back();
		}
	}

	
	if (theMaze.canGo(startCell, theMaze.getCell(row - 1, col)) && !theMaze.isMarked(theMaze.getCell(row - 1, col))) { // turn down
		
		canFindPath = findPath(theMaze, path, theMaze.getCell(row - 1, col), endCell);
		if (canFindPath) {
			return true;
		}
		else {
			path.pop_back();
		}
	}

	
	if (path.getSize() == 1) {  //this is so that if a path isn't available the runMaze function won't return 1 it will return zero
		path.pop_back();
	}

	
	return false;
}

int runMaze(Maze& theMaze, int path[], int startCell, int endCell) {
	RecentList<int> list;

	bool canFindPath = findPath(theMaze, list, startCell, endCell);

	RecentList<int>::iterator it = list.begin();
	int i = 0;
	while (it != list.end()) {
		path[i] = *it;
		i++;
		it++;
	}

	return list.getSize();
}