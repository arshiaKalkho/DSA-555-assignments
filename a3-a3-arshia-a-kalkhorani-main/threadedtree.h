#include <iostream>
using namespace std;

template <class T>
class ThreadedTree{
	struct Node{
		T data_;
		Node* left_;
		Node* right_;
		bool leftThread_;
		bool rightThread_;
		Node(const T& data = T{}, Node* left = nullptr, Node* right = nullptr) {
			data_ = data;
			left_ = left;
			right_ = right;
			leftThread_ = false;
			rightThread_ = false;
		}
	};	
	Node* root_;
	void print(const Node* rt, int lvl)const{
		//This function won't be tested, but you may find it useful to implement this so 
		//that you can see what the tree looks like.  lvl will allow you to use dashes to 
		//better show shape of tree.  Feel free to modify this to print in any way that will
		//help you debug.  Feel free to copy the pretty print function from lab 8 that will draw
		//the tree (though it won't draw threads)
	}

public:
	class const_iterator{
	protected:

		Node* curr_;
		const ThreadedTree* Ttree_;

		//const_iterator's constructor that takes 2 arguments, Node pointer and ThreadedTree pointer
		const_iterator(Node* curr, const ThreadedTree* tree) {
			curr_ = curr;
			Ttree_ = tree;
		}
	
		
	public:
		const_iterator(){
			curr_ = nullptr;
		}

		const_iterator operator++(int){
		
			
			const_iterator old = *this;

			if (this->curr_ != nullptr) {

				//bigger node thread exisst
				if (this->curr_->right_ && this->curr_->rightThread_ == true) {
					this->curr_ = curr_->right_;
				}
				//bigger node exists
				else if (this->curr_->right_) {

					this->curr_ = curr_->right_;

					//find next smallest node
					while (this->curr_->leftThread_ == false) {
						this->curr_ = this->curr_->left_;
					}
				}
				else {
					this->curr_ = nullptr;
				}
			}
			return old;
		

		}
		const_iterator operator--(int){
			const_iterator old = *this;

			if (this->curr_ != nullptr) {
 
				//if left thread exists
				if (this->curr_->left_ && this->curr_->leftThread_ == true) {
					this->curr_ = curr_->left_;
				}
				else if (this->curr_->left_) {

					this->curr_ = curr_->left_;
					
					//finds next biggest node
					while (this->curr_->rightThread_ == false) {
						this->curr_ = this->curr_->right_;
					}
				}
				else {
					this->curr_ = this->curr_->left_;
				}
			}
			else {


				Node* temp = this->Ttree_->root_;

				//find last node
				while (temp->right_) {
					temp = temp->right_;
				}

				//return end()
				this->curr_ = temp;
			}
			return old;


		}
		const_iterator operator++(){
			
			if (this->curr_ != nullptr) {

				//right thread exists
				if (this->curr_->right_ && this->curr_->rightThread_ == true) {
					this->curr_ = curr_->right_;
				}
				else if (this->curr_->right_) {

				
					this->curr_ = curr_->right_;

					//find next smallest node
					while (this->curr_->leftThread_ == false) {
						this->curr_ = this->curr_->left_;
					}
				}
				else {
					this->curr_ = nullptr;
				}
			}
			return *this;
		}
		const_iterator operator--(){
			
			if (this->curr_ != nullptr) {

				
				if (this->curr_->left_ && this->curr_->leftThread_ == true) {
					this->curr_ = curr_->left_;
				}
				else if (this->curr_->left_) {

					//goes left of subtree
					this->curr_ = curr_->left_;

					//goes right of subtree find biggest node while rightthread is false
					while (this->curr_->rightThread_ == false) {
						this->curr_ = this->curr_->right_;
					}
				}
				else {
					this->curr_ = this->curr_->left_;
				}
			}
			else {
				//goes here if curr is nullptr and set root to curr
				this->curr_ = this->Ttree_->root_;

				//if curr has root and it has a right node keep going right to find biggest node
				if (this->curr_) {
					while (this->curr_->right_) {
						this->curr_ = this->curr_->right_;
					}
				}
			}
			return *this;
		
		}
		const T& operator*() const{
			return this->curr_->data_;
		}
		//returns true if the two nodes are refering to the same node
		bool operator==(const const_iterator& rhs) const{
			
			bool returner = false;

			if (curr_ == rhs.curr_) {
				returner = true;
			}

			return returner;
		}//returns true if the two nodes are not refering to the same node
		bool operator!=(const const_iterator& rhs) const{
			
			bool returner = false;
			
			if (curr_ != rhs.curr_) {
				returner = true;
			}
			return returner;
		}
		friend class ThreadedTree;
	};
	class iterator:public const_iterator{
	
	public:
		
		
		iterator():const_iterator(){
		}
		const T& operator*() const{
			return this->curr_->data_;
		}
		T& operator*(){
			return this->curr_->data_;
		}		
		iterator operator++(int){

			iterator old = *this;

			if (this->curr_ != nullptr) {

				//if right hand thread exist
				if (this->curr_->right_ && this->curr_->rightThread_ == true) {
					this->curr_ = this->curr_->right_;
				}
				//if right hand node exists
				else if (this->curr_->right_) {

					this->curr_ = this->curr_->right_;

					//find smallest node
					while (this->curr_->leftThread_ == false) {
						this->curr_ = this->curr_->left_;
					}
				}
				else {
					this->curr_ = nullptr;
				}
			}
			return old;


		}
		iterator operator--(int){

			iterator old = *this;

			if (this->curr_ != nullptr) {

				//if link to a smaller thrad exists
				if (this->curr_->left_ && this->curr_->leftThread_ == true) {
					this->curr_ = this->curr_->left_;
				}
				else if (this->curr_->left_) {
					
					//if a node to a smaller node exists
					this->curr_ = this->curr_->left_;

					//find the biggest node 
					while (this->curr_->rightThread_ == false) {
						this->curr_ = this->curr_->right_;
					}

				}
				else {
					this->curr_ = this->curr_->left_;
				}
			}
			else {

				Node* temp = this->Ttree_->root_;

				//find biggest node
				while (temp->right_) {
					temp = temp->right_;
				}

				this->curr_ = temp;
			}
			return old;


		}
		iterator operator++(){


			if (this->curr_ != nullptr) {
			    
				//if right hand node exists  
				if (this->curr_->right_ && this->curr_->rightThread_ == true) {
					this->curr_ = this->curr_->right_;
				}
				
				//if right thread exists
				else if (this->curr_->right_) {

					this->curr_ = this->curr_->right_;

					//find the smallest node after the current
					while (this->curr_->leftThread_ == false) {
						this->curr_ = this->curr_->left_;
					}
				}
				else {
					this->curr_ = nullptr;
				}
			}
			return *this;
		}
		iterator operator--(){
			
			if (this->curr_ != nullptr) {

				//if link to a smaller node than the current exists
				if (this->curr_->left_ && this->curr_->leftThread_ == true) {
					this->curr_ = this->curr_->left_;
				}
				//if a Thread to a smaller node exists
				else if (this->curr_->left_) {

					
					this->curr_ = this->curr_->left_;

					//find the biggest node 
					while (this->curr_->rightThread_ == false) {
						this->curr_ = this->curr_->right_;
					}
				}
				else {//if smaller node doesn't exists the left will be nullptr, return nullptr
					this->curr_ = this->curr_->left_;
				}
			}
			else {//if current is nullptr
				this->curr_ = this->Ttree_->root_;

				
				if (this->curr_) {
					//until the biggest node
					while (this->curr_->right_) {
						
						this->curr_ = this->curr_->right_;
					}
				}
			}//return the last node in the list
			return *this;
		}

		friend class ThreadedTree;
	};

	private:
		//recursive helper function for node insertion
		template <typename T>
		Node* insertNode(const T& data, Node* node) {


			//if node not null
			if (node) {
				//insert left
				if (data < node->data_) {

					//if left node is null, make a new node with data and set it to left
					if (node->left_ == nullptr) {
						node->left_ = new Node(data, nullptr, node);
						node->left_->rightThread_ = true;
					}
					//if there is a node to the left and no threads
					else if (node->leftThread_ == false && node->left_) {
						
						//call this function again but with the left node
						insertNode(data, node->left_);
					}
					
					else if (node->leftThread_ == true && node->left_) {
						
						node->leftThread_ = false;
						
						//make the nw node on the left of the current
						node->left_ = new Node(data, node->left_, node);
						
						//both left and right thread = true
						node->left_->leftThread_ = true;
						node->left_->rightThread_ = true;
					}
					
					//insert right
				}else if (!(data < node->data_)){// the > operator for record wasn't implemented

					//if no bigger node
					if (node->right_ == nullptr) {
						
						node->right_ = new Node(data, node, nullptr);
						node->right_->leftThread_ = true;
					}
					//if there is a node to the right
					else if (node->rightThread_ == false && node->right_) {
						
						//call this function again but with the right node
						insertNode(data, node->right_);
					}
					
					else if (node->rightThread_ == true && node->right_) {
						
						node->rightThread_ = false;
						
						//make the new node on the right of the current
						node->right_ = new Node(data, node, node->right_);
						
						//both left and right thread = true
						node->right_->leftThread_ = true;
						node->right_->rightThread_ = true;

					}
				}
				//go left
				
			}

			//return pointer to the node that was passed in
			return node;

		}

		public:
	ThreadedTree(){//initialize
		root_ = nullptr;
	}
	
	template <typename T>
	void insert(const T& data){

		//if its the first element of the tree
		if (root_ == nullptr) {
			//make new node
			root_ = new Node(data, nullptr, nullptr);
		}
		else {
			//calls insertnode 
			root_ = insertNode(data, root_);
		}


	}
	

	template <typename T>
	iterator find(const T& data){

		iterator it;
		bool found = false;
		
		Node* node = root_;
		
		//while tree not empty and the data "it" isn't found
		while (root_ && found == false) {

			//if found
			if (data == node->data_) {
				found = true;
				it.curr_ = node;
			}
			//if smaller go back(left)
			else if (data < node->data_ && node->leftThread_ == false) {
				node = node->left_;
			}
			//if bigger go right(right)
			else if (!(data < node->data_) && node->rightThread_ == false) {
				node = node->right_;
			}
			//if nothing was found set found to true to end the while loop
			//setting iterator to nullptr
			else {
				found = true;
				it.curr_ = nullptr;
			}
		}
		
		it.Ttree_ = this; 

		return it;

	}

	
	template <typename T>
	const_iterator find(const T& data) const {

		const_iterator it;
        bool found = false;
		
		Node* node = root_;

		
		//while tree not empty and the data "it" isn't found
		while (root_ && found == false) {

			//if found
			if (data == node->data_) {
				found = true;
				it.curr_ = node;
			}
			//if smaller go back(left)
			else if (data < node->data_ && node->leftThread_ == false) {
				node = node->left_;
			}
			//if bigger go right(right)
			else if (data > node->data_ && node->rightThread_ == false) {
				node = node->right_;
			}
			//if nothing was found set found to true to end the while loop
			//setting iterator to nullptr
			else {
				found = true;
				it.curr_ = nullptr;
			}
		}

		it.Ttree_ = this;

		return it;

	}
	iterator begin(){

		iterator it;
		//if not empty
		if (root_) {
			
			//start from root
			it.curr_ = root_;
			
			//go till the left(smaller) node is nullptr,
			//meaning there is nothing smaller than that node
			while (it.curr_->left_ != nullptr) {
				it.curr_ = it.curr_->left_;
			}
		}

		it.Ttree_ = this;

		return it;
	}
	iterator end(){
		
		iterator it;
		
		//if not empty
		if (root_) {
			
			//start from root
			it.curr_ = root_;
		
			//until the end iterate through the tree
			while (it.curr_ != nullptr) {
				it.curr_ = it.curr_->right_;
			}
		}

		
		it.Ttree_ = this;

		return it;
	}
	const_iterator cbegin()const{

		const_iterator it;
		//if not empty
		if (root_) {
			
			//start from root
			it.curr_ = root_;
			
			//go till the left(smaller) node is nullptr,
			//meaning there is nothing smaller than that node
			while (it.curr_->left_ != nullptr) {
				it.curr_ = it.curr_->left_;
			}
		}

		it.Ttree_ = this;

		return it;
	}
	const_iterator cend() const{

		const_iterator it;
		
		//if not empty
		if (root_) {
			
			//start from root
			it.curr_ = root_;
			
			//iterate till the end
			while (it.curr_ != nullptr) {
				it.curr_ = it.curr_->right_;
			}
		}

		it.Ttree_ = this;

		return it;
	}
	void print() const{
		//this function won't be tested, but you may wish to implement this 
		//to help you debug.  You won't need to implement this for submission
	}
	int size() const{
		
		int size = 0;
		const_iterator it = this->cbegin();
		
		//from 0 iterate through till nullptr
		while (it.curr_) {
			it++;
			size++;
		}
		
		return size;
	}


	bool empty() const{
		//if root is null return true
		if (root_ == nullptr) {
			return true;
		}
		return false;
	}
	
	~ThreadedTree(){


		iterator it = begin();
		Node* node;
		
		//if the tree wasn't empty
		if (root_) {

			//while there is a node
			while (it.curr_) {

				//iterate forward and delete until the end and set to nul/ptr
				node = it.curr_;
				it++;
				delete node; 
				node = nullptr;

			}

		}

	}

	
};



