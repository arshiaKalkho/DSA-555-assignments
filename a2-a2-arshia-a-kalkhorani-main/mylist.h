/*******************************************************/
/*                                                     */
/*  Put your linked list code from A1/lab3/lab4 into   */
/*  this file                                          */
/*                                                     */
/*******************************************************/

/*******************************************************************/
/*                                                                 */
/*  A1 Part 2: RecentList starter file                             */
/*                                                                 */
/*  Author1 Name: David (Su) Lee                                   */
/*      - Assignment 1 Principal Developer                         */
/*                                                                 */
/*******************************************************************/

#include <utility>
template <typename T>

// Sentinel version
class RecentList {
  struct Node {
    T data;
    Node* nx;
    Node* pr;
    Node(const T& data = T{}, Node* nx = nullptr, Node* pr = nullptr) : data(data), nx(nx), pr(pr) {}
  };
  Node* front_ = nullptr;
  Node* back_ = nullptr;
  void clear();

 public:
  class const_iterator {
    friend class RecentList<T>;

   protected:
    Node* curr_;
    const RecentList<T>* this_list_;
    const_iterator(Node* node, const RecentList<T>* this_list) : curr_(node), this_list_(this_list) {}

   public:
    const_iterator() : curr_(nullptr), this_list_(nullptr) {}
    const_iterator operator++() {
      curr_ = curr_->nx;
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator old = *this;
      curr_ = curr_->nx;
      return old;
    }
    const_iterator operator--() {
      if (curr_ != nullptr) {
        curr_ = curr_->pr;
      } else {
        curr_ = this_list_->back_;
      }

      return *this;
    }
    const_iterator operator--(int) {
      const_iterator old = *this;

      if (curr_ != nullptr) {
        curr_ = curr_->pr;
      } else {
        curr_ = this_list_->back_;
      }

      return old;
    }
    bool operator==(const_iterator rhs) {
      return curr_ == rhs.curr_;
    }
    bool operator!=(const_iterator rhs) {
      return curr_ != rhs.curr_;
    }
    const T& operator*() const {
      return curr_->data;
    }
    const T* operator->() const {
      return &(curr_->data);
    }
  };
  class iterator : public const_iterator {
    friend class RecentList<T>;
    iterator(Node* node, const RecentList<T>* this_list) : const_iterator(node, this_list) {}

   public:
    iterator() {}
    iterator operator++() {
      const_iterator::curr_ = const_iterator::curr_->nx;
      return *this;
    }
    iterator operator++(int) {
      iterator old = *this;
      const_iterator::curr_ = const_iterator::curr_->nx;
      return old;
    }
    iterator operator--() {
      if (const_iterator::curr_ != nullptr) {
        const_iterator::curr_ = const_iterator::curr_->pr;
      } else {
        const_iterator::curr_ = const_iterator::this_list_->back_;
      }

      return *this;
    }
    iterator operator--(int) {
      iterator old = *this;

      if (const_iterator::curr_ != nullptr) {
        const_iterator::curr_ = const_iterator::curr_->pr;
      } else {
        const_iterator::curr_ = const_iterator::this_list_->back_;
      }

      return old;
    }
    T& operator*() {
      return const_iterator::curr_->data;
    }
    const T& operator*() const {
      return const_iterator::curr_->data;
    }
    T* operator->() {
      return &(const_iterator::curr_->data);
    }
    const T* operator->() const {
      return &(const_iterator::curr_->data);
    }
  };
  RecentList();
  ~RecentList();
  RecentList(const RecentList& rhs);
  RecentList& operator=(const RecentList& rhs);
  RecentList(RecentList&& rhs);
  RecentList& operator=(RecentList&& rhs);
  iterator begin() {
    return iterator(front_->nx, this);
  }
  iterator end() {
    return iterator(back_, this);
  }
  const_iterator cbegin() const {
    return const_iterator(front_->nx, this);
  }
  const_iterator cend() const {
    return const_iterator(back_, this);
  }
  void insert(const T& data);
  iterator search(const T& data);
  iterator erase(iterator it);
  iterator erase(iterator first, iterator last);
  bool empty() const;
  int size() const;
};

template <typename T>
void RecentList<T>::clear() {
  Node* curr = front_->nx;
  Node* next = nullptr;

  while (curr != back_) {
    next = curr->nx;
    delete curr;
    curr = next;
  }
}

template <typename T>
RecentList<T>::RecentList() {
  // create sentinel nodes
  Node* front = new Node();
  Node* back = new Node();
  front->nx = back;
  back->pr = front;
  front_ = front;
  back_ = back;
}

template <typename T>
RecentList<T>::~RecentList() {
  clear();
  delete front_;
  delete back_;
}

template <typename T>
RecentList<T>::RecentList(const RecentList& rhs) : RecentList<T>::RecentList() {
  *this = rhs;
}

template <typename T>
RecentList<T>& RecentList<T>::operator=(const RecentList& rhs) {
  if (this != &rhs) {
    clear();
    Node* orig = rhs.front_->nx;
    Node* copy = new Node(orig->data, nullptr, front_);
    front_->nx = copy;

    while (orig->nx != rhs.back_) {
      orig = orig->nx;
      copy = new Node(orig->data, nullptr, copy);
      copy->pr->nx = copy;
    }
    copy->nx = back_;
    back_->pr = copy;
  }

  return *this;
}

template <typename T>
RecentList<T>::RecentList(RecentList&& rhs) : RecentList<T>::RecentList() {
  *this = std::move(rhs);
}

template <typename T>
RecentList<T>& RecentList<T>::operator=(RecentList&& rhs) {
  // nether swap
  if (this != &rhs) {
    Node* temp = front_;
    front_ = rhs.front_;
    rhs.front_ = temp;

    temp = back_;
    back_ = rhs.back_;
    rhs.back_ = temp;
  }
  return *this;
}

template <typename T>
void RecentList<T>::insert(const T& data) {
  Node* new_node = new Node(data, front_->nx, front_);
  front_->nx->pr = new_node;
  front_->nx = new_node;
}

template <typename T>
typename RecentList<T>::iterator RecentList<T>::search(const T& data) {
  Node* found = front_->nx;
  while (found != back_) {
    if (found->data == data) {
      break;
    }
    found = found->nx;
  }
  // link the prev and next nodes from the found node, then move to front
  if (found != back_) {
    found->pr->nx = found->nx;
    found->nx->pr = found->pr;
    found->nx = front_->nx;
    found->pr = front_;
    front_->nx->pr = found;
    front_->nx = found;
    return begin();
  } else {
    return end();
  }
}

template <typename T>
typename RecentList<T>::iterator RecentList<T>::erase(iterator it) {
  Node* curr = it++.curr_;
  curr->pr->nx = curr->nx;
  curr->nx->pr = curr->pr;
  delete curr;
  return it;
}

template <typename T>
typename RecentList<T>::iterator RecentList<T>::erase(iterator first, iterator last) {
  while (first != last) {
    first = erase(first);
  }
  return last;
}

template <typename T>
bool RecentList<T>::empty() const {
  return front_->nx == back_;
}

template <typename T>
int RecentList<T>::size() const {
  const_iterator it = cbegin();
  const_iterator end = cend();
  int size = 0;
  while (it != end) {
    it++;
    size++;
  }
  return size;
}