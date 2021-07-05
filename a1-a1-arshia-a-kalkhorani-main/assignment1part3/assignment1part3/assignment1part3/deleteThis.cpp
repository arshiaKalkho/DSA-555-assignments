#include <string>


//numRecords()

//let n be the number of elements in the list
//let T(n) be the nujmber of operations to complete the task


template <class TYPE>
int SimpleTable<TYPE>::numRecords() const {
	int rc = 0;                                       //1
	for (int i = 0; records_[i] != nullptr; i++) {    //1 + 2n
		rc++;                                         //n
	}
	return rc;                                        //1
}

// T(n) = 3+3n
//therefore T(n) = O(n)
//function is linear










//update() - if item does not exists so you need to add it as a new record, assume no grow() call is made

//let n be the number of elements in the list
//let T(n) be the nujmber of operations to complete the task


template <class TYPE>
void SimpleTable<TYPE>::update(const std::string& key, const TYPE& value) {
	int idx = -1;                                                                                 //1
	 
	for (int i = 0; i < numRecords(); i++) {                                                      //1 + 2n + n(3+3n)
		if (records_[i]->key_ == key) {                                                           //n
			idx = i;                                                                              //1
		}
	}
	if (idx == -1) {                                                                              //1
		if (numRecords() == capacity_) {                                                          //1 + 3 + 3n
			grow();                                                                               //7 + 8n
		}
		records_[numRecords()] = new Record(key, value);                                          //1 + 3 + 3n
		for (int i = numRecords() - 1; i > 0 && records_[i]->key_ < records_[i - 1]->key_; i--) { //2 + 3 + 3n + 5n
			Record* tmp = records_[i];                                                            //n
			records_[i] = records_[i - 1];                                                        //2n
			records_[i - 1] = tmp;                                                                //2n
		}

	}
	else {
		records_[idx]->data_ = value;                                                              //since grow() needs to be called this won't happen
	}
}


//T(n) = 24 + 33n + 3n^2
//T(n) = 3n^2  
//therefore T(n) = O(n^2)
//function is quadratic








					
					
					//let n be the number of elements in the list
//let T(n) be the nujmber of operations to complete the task


void grow() {
	Record** tmp = new Record * [capacity_ * 2 + 1];             //3
	for (int i = 0; i < capacity_; i++) {                        //1 + 2n
		tmp[i] = records_[i];                                    //n
	}
	for (int i = capacity_; i < capacity_ * 2 + 1; i++) {        //1 + 4n
		tmp[i] = nullptr;                                        //n
	}
	delete[] records_;
	records_ = tmp;                                              //1
	capacity_ *= 2;                                              //1
}


//T(n) = 7 + 8n
//therefore T(n) is O(n)
//function is linear











//let n be the number of elements in the list
//let T(n) be the nujmber of operations to complete the task

//update() - if item does exists and you are just modifying what is there
template <class TYPE>
void SimpleTable<TYPE>::update(const std::string& key, const TYPE& value) {
	int idx = -1;                                                                                   //1

	for (int i = 0; i < numRecords(); i++) {                                                        //1  + 2n + n(3+3n)
		if (records_[i]->key_ == key) {                                                             //n 
			idx = i;                                                                                //1
		}
	}
	if (idx == -1) {                                                                                //1
		if (numRecords() == capacity_) {                                                            //1 + 3 + 3n
			grow();
		}
		records_[numRecords()] = new Record(key, value);                                            //1 + 3n + 3
		for (int i = numRecords() - 1; i > 0 && records_[i]->key_ < records_[i - 1]->key_; i--) {   //2 + 3 + 3n + 5n
			Record* tmp = records_[i];                                                              //n
			records_[i] = records_[i - 1];                                                          //2n
			records_[i - 1] = tmp;                                                                  //2n
		}

	}
	else {
		records_[idx]->data_ = value;
	}
}

//T(n) = 17 + 26n + 3n^2
//T(n) = 3n^2
//therefore T(n) = O(n^2)
//functino is quadratic










//let n be the number of elements in the list
//let T(n) be the nujmber of operations to complete the task

//find() - if item is not there
template <class TYPE>
bool SimpleTable<TYPE>::find(const std::string& key, TYPE& value) {
	int idx = -1;                                                     //1
	for (int i = 0; i < numRecords(); i++) {                          //1 + 2n + n(3n+3)
		if (records_[i]->key_ == key) {                               //n
			idx = i;							                      
		}
	}
	if (idx == -1)                                                    //1
		return false;                                                 //1
	else {
		value = records_[idx]->data_;                                 
		return true;												  
	}
}
//T(n) = 4 + 6n + 3n^2
//T(n) = 3n^2
//therefore T(n) = O(n^2)
//function is quadratic







//let n be the number of elements in the list
//let T(n) be the nujmber of operations to complete the task

//remove() - if item is there
template <class TYPE>
bool SimpleTable<TYPE>::remove(const std::string& key) {
	int idx = -1;                                                  //1
	for (int i = 0; i < numRecords(); i++) {                       //1 + 2n + 3 + 3n
		if (records_[i]->key_ == key) {                            //n
			idx = i;                                               //1
		}
	}
	if (idx != -1) {                                               //1
		int size = numRecords();                                   //1 + 3 + 3n
		delete records_[idx];                                      
		for (int i = idx; i < size - 1; i++) {                     //1 + 3n
			records_[i] = records_[i + 1];                         //2n
		}
		records_[size - 1] = nullptr;                              //2
		return true;                                               //1
	}
	else {
		return false;                                               //item isn't there
	}
}


//T(n) =  15 + 14n
//T(n) = 14n
//therefore T(n) = O(n)
//function is linear








//let n be the number of elements in the list
//let T(n) be the nujmber of operations to complete the task

//copy constructor
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& rhs) {
	records_ = new Record * [rhs.capacity_ + 1];                        //2
	capacity_ = rhs.capacity_;                                          //1
	for (int i = 0; i < capacity_ + 1; i++) {                           //1 + 3n
		records_[i] = nullptr;                                          //1
	}
	for (int i = 0; i < rhs.numRecords(); i++) {                        //1 + 2n + n(3+3n) 
		update(rhs.records_[i]->key_, rhs.records_[i]->data_);          //n(17 + 26n + 3n^2)
	}
}
//T(n) = 5 + 25n + 29n^2 + 3n^3
//T(n) = 3n^3
//therefore t(n) = O(n^3)
//the function is cubic







//let n be the number of elements in the list
//let T(n) be the nujmber of operations to complete the task

//move constructor
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& rhs) {
	capacity_ = rhs.capacity_;                                           //1
	records_ = rhs.records_;											 //1
	rhs.records_ = nullptr;                                              //1
	rhs.capacity_ = 0;													 //1
}
//T(n) = 4
//therefore T(n) = O(1)
//function is constant





//let n be the number of elements in the list
//let T(n) be the nujmber of operations to complete the task

//move assignment operator
emplate <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& rhs) {
	if (records_) {                                                               //1
		while (numRecords() != 0) {                                               //n + n(3+3n)
			remove(records_[0]->key_);                                            //n(15 + 14n)
		}
		delete[] records_;                                                        //n
	}
	records_ = rhs.records_;                                                      //1
	capacity_ = rhs.capacity_;													  //1
	rhs.records_ = nullptr;														  //1
	rhs.capacity_ = 0;														      //1

	return *this;                                                                 //1
}
//T(n) = 6 + 18n + 17n^2
//T(n) = 17n^2
//therefore T(n) = O(n^2)
//function is quadratic





//let n be the number of elements in the list
//let T(n) be the nujmber of operations to complete the task


//destructor

template <class TYPE>
SimpleTable<TYPE>::~SimpleTable() {
	if (records_) {                                    //1
		int sz = numRecords();                         //1 + 3 + 3n 
		for (int i = 0; i < sz; i++) {                 //1 + 2n
			remove(records_[0]->key_);                 //n(15+ 14n)                       
		}
		delete[] records_;                             
	}
}
//T(n) = 6 + 20n + 14n^2
//T(n) = 14n^2
//therefore T(n) = O(n^2)
//function is quadratic






