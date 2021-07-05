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
		Node(const T& data=T{},Node* left=nullptr, Node* right=nullptr){
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

		//iterator advances to next biggest node in tree if iterator is not currently at end()
		//returns iterator to node before the increment
		const_iterator operator++(int){
			//x++  

			const_iterator oldNode = *this;

			if (this->curr_ != nullptr) {
				
				//current node has a right node and current node has right thread
				if (this->curr_->right_ && this->curr_->rightThread_ == true) {
					this->curr_ = curr_->right_;
				}
				else if (this->curr_->right_) {

					//goes right of subtree and set it to curr
					this->curr_ = curr_->right_;

					//goes left of subtree to find smallest node and set to curr while leftthread is false
					while (this->curr_->leftThread_ == false) {
						this->curr_ = this->curr_->left_;
					}
				}
				else {
					this->curr_ = nullptr;
				}
			}
			return oldNode;

		}
		const_iterator operator--(int){
			//x--

			const_iterator oldNode = *this;

			if (this->curr_ != nullptr) {

				//current node has a left node and current node has left thread
				if (this->curr_->left_ && this->curr_->leftThread_ == true) {
					this->curr_ = curr_->left_;
				}
				else if (this->curr_->left_) {

					//goes to left node of subtree and set to curr
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
			else{

				//make a temp variable
				//goes here if curr is nullptr and set root to curr
				Node* temp = this->Ttree_->root_;

				//while temp has right node set temp variable to the right node
				//wont execute if tree is empty
				while(temp->right_){
					temp = temp->right_;
				}

				this->curr_ = temp;
			}
			return oldNode;
		}
		
		//iterator advances to next biggest node in tree if iterator is not currently at end()
		//returns iterator to current node
		const_iterator operator++(){
			//++x 

			if (this->curr_ != nullptr) {

				//current node has a right node and current node has right thread
				if (this->curr_->right_ && this->curr_->rightThread_ == true) {
					this->curr_ = curr_->right_;
				}
				else if (this->curr_->right_) {

					//goes right of subtree and set it to curr
					this->curr_ = curr_->right_;

					//goes left of subtree to find smallest node while leftthread is false
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

		//iterator goes to the next smallest node in the tree
		//prefix operator returns iterator to current node
		const_iterator operator--(){
			//--x

			if (this->curr_ != nullptr) {

				//current node has a left node and current node has left thread
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
			else{
				//goes here if curr is nullptr and set root to curr
				this->curr_ = this->Ttree_->root_;

				//if curr has root and it has a right node keep going right to find biggest node
				if(this->curr_){
					while(this->curr_->right_){
						this->curr_ = this->curr_->right_;
					}
				}
			}
			return *this;
		}

		//returns data in the current node 
		const T& operator*() const{
			return this->curr_->data_;
		}

		//returns rc= true if rhs and current object refer to the same node else rc = false
		bool operator==(const const_iterator& rhs) const{
			bool rc = false;

			if (curr_ == rhs.curr_) {
				rc = true;
			}

			return rc;

		}

		//returns rc= true if rhs and current object does not refer to the same node else rc = false
		bool operator!=(const const_iterator& rhs) const{
			bool rc = false;

			if (curr_ != rhs.curr_) {
				rc = true;
			}

			return rc;

		}
		friend class ThreadedTree;
	};
	class iterator:public const_iterator{
		iterator(Node* curr, const ThreadedTree* tree):const_iterator(curr, tree){
		}	

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
			//x++
			iterator oldNode = *this;

			if (this->curr_ != nullptr) {

				//current node has a right node and current node has right thread
				if (this->curr_->right_ && this->curr_->rightThread_ == true) {
					this->curr_ = this->curr_->right_;
				}
				else if (this->curr_->right_) {

					//goes right of subtree and set it to curr
					this->curr_ = this->curr_->right_;

					//goes left of subtree to find smallest node and set to curr
					while (this->curr_->leftThread_ == false) {
						this->curr_ = this->curr_->left_;
					}
				}
				else {
					this->curr_ = nullptr;
				}
			}
			return oldNode;
		}
		iterator operator--(int){
			//x--

			iterator oldNode = *this;

			if (this->curr_ != nullptr) {

				//current node has a left node and current node has left thread
				if (this->curr_->left_ && this->curr_->leftThread_ == true) {
					this->curr_ = this->curr_->left_;
				}
				else if (this->curr_->left_) {
					//goes to left node of subtree and set to curr
					this->curr_ = this->curr_->left_;

					//goes right of subtree find biggest node
					while (this->curr_->rightThread_ == false) {
						this->curr_ = this->curr_->right_;
					}
				}
				else {
					this->curr_ = this->curr_->left_;
				}
			}
			else {

				//make a temp variable
				//goes here if curr is nullptr and set root to curr
				Node* temp = this->Ttree_->root_;

				//while temp has right node set temp variable to the right node
				//wont execute if tree is empty
				while (temp->right_) {
					temp = temp->right_;
				}

				this->curr_ = temp;
			}
			return oldNode;
		}
		iterator operator++(){
			//++x

			if (this->curr_ != nullptr) {

				//current node has a right node and current node has right thread
				if (this->curr_->right_ && this->curr_->rightThread_ == true) {
					this->curr_ = this->curr_->right_;
				}
				else if (this->curr_->right_) {

					//goes right of subtree and set it to curr
					this->curr_ = this->curr_->right_;

					//goes left of subtree to find smallest node
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
			//--x

			if (this->curr_ != nullptr) {

				//current node has a left node and current node has left thread
				if (this->curr_->left_ && this->curr_->leftThread_ == true) {
					this->curr_ = this->curr_->left_;
				}
				else if (this->curr_->left_) {

					//goes left of subtree
					this->curr_ = this->curr_->left_;

					//goes right of subtree find biggest node
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

		friend class ThreadedTree;
	};

	private:

		//made a function to be called by insert below
		//insertNode takes 2 arguments
		Node* insertNode(const T& data, Node* P_node) {

			if (P_node) {

				//insert nodes to right of tree
				if (data > P_node->data_) {

					//if right is null make new node with passed in data and set left to point at node passed in
					//then set leftThread which is boolean to true
					if (P_node->right_ == nullptr) {
						P_node->right_ = new Node(data, P_node, nullptr);
						P_node->right_->leftThread_ = true;
					}
					//if node doesnt have right thread and has a node to its right
					//call this function again with current data and pointer to right of current node
					else if (P_node->rightThread_ == false && P_node->right_) {
						insertNode(data, P_node->right_);
					}
					//if passed in node has right thread and has a right
					//set this current node right thread to false
					//and create new node where its left is pointing at current node
					//and right is pointing at where current node was pointing at
					//set both right and left threads to true
					else if (P_node->rightThread_ == true && P_node->right_) {
						P_node->rightThread_ = false;
						P_node->right_ = new Node(data, P_node, P_node->right_);
						P_node->right_->leftThread_ = true;
						P_node->right_->rightThread_ = true;

					}
				}

				//insert node to the left of tree
				else if (data < P_node->data_) {

					//if left is null make new node with passed in data and set right to point at node passed in
					//then set right thread which is boolean to true
					if (P_node->left_ == nullptr) {
						P_node->left_ = new Node(data, nullptr, P_node);
						P_node->left_->rightThread_ = true;
					}
					//if node doesnt have leftt thread and has a node to its left
					//call this function again with current data and pointer to left of current node
					else if (P_node->leftThread_ == false && P_node->left_) {
						insertNode(data, P_node->left_);
					}
					//if passed in node has left thread and has a left
					//set this current node left thread to false
					//and create new node where its right is pointing at current node
					//and left is pointing at where current node was pointing at
					//set both right and left threads to true
					else if (P_node->leftThread_ == true && P_node->left_) {
						P_node->leftThread_ = false;
						P_node->left_ = new Node(data, P_node->left_, P_node);
						P_node->left_->leftThread_ = true;
						P_node->left_->rightThread_ = true;
					}
				}
			}
			
			//return pointer to the node that was passed in
			return P_node; 

		}
   public:
	ThreadedTree(){
		root_ = nullptr;
	}

	//insert function thats takes type T as argument and calls insertNode function from above
	void insert(const T& data){
		
		//makes new node if root is null
		if (root_ == nullptr) {
			root_ = new Node(data, nullptr, nullptr);	
		}
		else {		
			//calls insertNode function passing data and the root
			root_ = insertNode(data, root_);
		}

	}

	//find takes type T as argument
	//searches for node and returns an iterator to the node containing that data
	iterator find(const T& data){

		iterator it;

		Node* node = root_;

		bool found = false;

		while (root_ && found == false) {

			if (data == node->data_) {
				found = true;
				it.curr_ = node;
			}
			else if (data < node->data_ && node->leftThread_ == false) {
				node = node->left_;
			}
			else if (data > node->data_ && node->rightThread_ == false) {
				node = node->right_;
			}
			else {
				found = true;
				it.curr_ = nullptr;
			}
		}
		
		//set the tree_ property to current tree's iterator
		it.Ttree_ = this; 

		return it;

	}

	//find takes type T as argument
	//searches for node and returns an iterator to the node containing that data
	const_iterator find(const T& data) const{

		const_iterator it;

		Node* node = root_;

		bool found = false;

		while (root_ && found == false) {

			if (data == node->data_) {
				found = true;
				it.curr_ = node;
			}
			else if (data < node->data_ && node->leftThread_ == false) {
				node = node->left_;
			}
			else if (data > node->data_ && node->rightThread_ == false) {
				node = node->right_;
			}
			else {
				found = true;
				it.curr_ = nullptr;
			}
		}

		//set the tree_ property to current tree's iterator
		it.Ttree_ = this;

		return it;

	}

	//This function returns the appropriate iterator to the smallest node in the tree.
	iterator begin(){
		
		iterator it;

		if (root_) {

			it.curr_ = root_;

			while (it.curr_->left_ != nullptr) {
				it.curr_ = it.curr_->left_;
			}
		}

		//set the tree_ property to current tree's iterator
		it.Ttree_ = this;

		return it;
		
	}

	//This function returns the appropriate iterator to the node to the right of the node with biggest value (which can be a nullptr)
	iterator end(){

		iterator it;

		if (root_) {

			it.curr_ = root_;

			while (it.curr_ != nullptr) {
				it.curr_ = it.curr_->right_;
			}
		}

		//set the tree_ property to current tree's iterator
		it.Ttree_ = this;

		return it;
	}

	//This function returns the appropriate iterator to the smallest node in the tree.
	const_iterator cbegin()const{

		const_iterator it;

		if (root_) {

			it.curr_ = root_;

			while (it.curr_->left_ != nullptr) {
				it.curr_ = it.curr_->left_;
			}
		}

		//set the tree_ property to current tree's iterator
		it.Ttree_ = this;

		return it;

	}

	//This function returns the appropriate iterator to the node to the right of the node with biggest value (which can be a nullptr)
	const_iterator cend() const{
		
		const_iterator it;

		if (root_) {

			it.curr_ = root_;

			while (it.curr_ != nullptr) {
				it.curr_ = it.curr_->right_;
			}
		}

		//set the tree_ property to current tree's iterator
		it.Ttree_ = this;

		return it;

	}
	void print() const{
	    //this function won't be tested, but you may wish to implement this 
		//to help you debug.  You won't need to implement this for submission
	}

	//destructor
	~ThreadedTree(){

		iterator it = begin();
		Node* node;
		
		if (root_) {

			while (it.curr_) {

				node = it.curr_;
				it++;
				delete node;
				node = nullptr;

			}

		}

	}
};