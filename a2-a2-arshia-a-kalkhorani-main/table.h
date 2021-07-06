/*************************************************************/
/*                                                           */
/*  Starter file for a2                                      */
/*                                                           */
/*  Arshia A Kalkhorani                                      */
/*                                     */
/*                                                           */
/*                                                           */
/*                                                           */
/*************************************************************/

#include <functional>
#include <string>
#include <utility>

#include "mylist.h"

template <class TYPE>
class Table {
 public:
  Table() {}
  virtual void update(const std::string& key, const TYPE& value) = 0;
  virtual bool remove(const std::string& key) = 0;
  virtual bool find(const std::string& key, TYPE& value) = 0;
  virtual int numRecords() const = 0;
  virtual bool isEmpty() const = 0;
  virtual int capacity() const = 0;
  virtual ~Table() {}
};

template <class TYPE>
class SimpleTable : public Table<TYPE> {
  struct Record {
    TYPE data_;
    std::string key_;
    Record(const std::string& key, const TYPE& data) {
      key_ = key;
      data_ = data;
    }
  };

  Record** records_;  //the table
  int capacity_;      //capacity of the array

  void grow() {
    Record** tmp = new Record*[capacity_ * 2 + 1];
    for (int i = 0; i < capacity_; i++) {
      tmp[i] = records_[i];
    }
    for (int i = capacity_; i < capacity_ * 2 + 1; i++) {
      tmp[i] = nullptr;
    }
    delete[] records_;
    records_ = tmp;
    capacity_ *= 2;
  }

 public:
  SimpleTable(int capacity);
  SimpleTable(const SimpleTable& rhs);
  SimpleTable(SimpleTable&& rhs);
  virtual void update(const std::string& key, const TYPE& value);
  virtual bool remove(const std::string& key);
  virtual bool find(const std::string& key, TYPE& value);
  virtual const SimpleTable& operator=(const SimpleTable& rhs);
  virtual const SimpleTable& operator=(SimpleTable&& rhs);
  virtual ~SimpleTable();
  virtual bool isEmpty() const { return numRecords() == 0; }
  virtual int numRecords() const;
  virtual int capacity() const { return capacity_; }
};

template <class TYPE>
int SimpleTable<TYPE>::numRecords() const {
  int rc = 0;
  for (int i = 0; records_[i] != nullptr; i++) {
    rc++;
  }
  return rc;
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int capacity) : Table<TYPE>() {
  records_ = new Record*[capacity + 1];
  capacity_ = capacity;
  for (int i = 0; i < capacity_ + 1; i++) {
    records_[i] = nullptr;
  }
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& rhs) {
  records_ = new Record*[rhs.capacity_ + 1];
  capacity_ = rhs.capacity_;
  for (int i = 0; i < capacity_ + 1; i++) {
    records_[i] = nullptr;
  }
  for (int i = 0; i < rhs.numRecords(); i++) {
    update(rhs.records_[i]->key_, rhs.records_[i]->data_);
  }
}
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& rhs) {
  capacity_ = rhs.capacity_;
  records_ = rhs.records_;
  rhs.records_ = nullptr;
  rhs.capacity_ = 0;
}

template <class TYPE>
void SimpleTable<TYPE>::update(const std::string& key, const TYPE& value) {
  int idx = -1;

  for (int i = 0; i < numRecords(); i++) {
    if (records_[i]->key_ == key) {
      idx = i;
    }
  }
  if (idx == -1) {
    if (numRecords() == capacity_) {
      grow();
    }
    records_[numRecords()] = new Record(key, value);
    for (int i = numRecords() - 1; i > 0 && records_[i]->key_ < records_[i - 1]->key_; i--) {
      Record* tmp = records_[i];
      records_[i] = records_[i - 1];
      records_[i - 1] = tmp;
    }

  } else {
    records_[idx]->data_ = value;
  }
}

template <class TYPE>
bool SimpleTable<TYPE>::remove(const std::string& key) {
  int idx = -1;
  for (int i = 0; i < numRecords(); i++) {
    if (records_[i]->key_ == key) {
      idx = i;
    }
  }
  if (idx != -1) {
    int size = numRecords();
    delete records_[idx];
    for (int i = idx; i < size - 1; i++) {
      records_[i] = records_[i + 1];
    }
    records_[size - 1] = nullptr;
    return true;
  } else {
    return false;
  }
}

template <class TYPE>
bool SimpleTable<TYPE>::find(const std::string& key, TYPE& value) {
  int idx = -1;
  for (int i = 0; i < numRecords(); i++) {
    if (records_[i]->key_ == key) {
      idx = i;
    }
  }
  if (idx == -1)
    return false;
  else {
    value = records_[idx]->data_;
    return true;
  }
}

template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& rhs) {
  if (this != &rhs) {
    if (records_) {
      while (numRecords() != 0) {
        remove(records_[0]->key_);
      }
      delete[] records_;
    }
    records_ = new Record*[rhs.capacity_ + 1];
    capacity_ = rhs.capacity_;
    for (int i = 0; i < capacity_; i++) {
      records_[i] = nullptr;
    }
    for (int i = 0; i < rhs.numRecords(); i++) {
      update(rhs.records_[i]->key_, rhs.records_[i]->data_);
    }
  }
  return *this;
}
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& rhs) {
  if (records_) {
    while (numRecords() != 0) {
      remove(records_[0]->key_);
    }
    delete[] records_;
  }
  records_ = rhs.records_;
  capacity_ = rhs.capacity_;
  rhs.records_ = nullptr;
  rhs.capacity_ = 0;

  return *this;
}
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable() {
  if (records_) {
    int sz = numRecords();
    for (int i = 0; i < sz; i++) {
      remove(records_[0]->key_);
    }
    delete[] records_;
  }
}

/*------------------------------ ChainingTable -------------------------------*/
template <class TYPE>
class ChainingTable : public Table<TYPE> {
  struct Record {
    std::string key;
    TYPE data;
    // required for sentinel nodes
    Record() {}
    Record(const std::string& key, const TYPE& data) : key{key}, data{data} {}
    // key-only comparison makes the search operations easier
    bool operator==(const Record& other) {
      return key == other.key;
    }
  };

  std::hash<std::string> hashFunction;
  RecentList<Record>** records_ = nullptr;  // the table
  int capacity_;                            // number of slots
  int num_records_;                         // number of records
  double load_factor_;                      // max allowed load factor

  // calculate which slot this key falls into
  int getIndex(const std::string& key) const {
    return hashFunction(key) % capacity_;
  }

  // delete all records and the table
  void clear() {
    if (records_ != nullptr) {
      for (int i = 0; i < capacity_; i++) {
        if (records_[i] != nullptr) {
          delete records_[i];
        }
      }

      delete[] records_;
      records_ = nullptr;
    }
  }

  // double the number of slots and rehash the existing keys
  void grow() {
    ChainingTable<TYPE> new_table = ChainingTable(capacity_ * 2, load_factor_);

    for (int i = 0; i < capacity_; i++) {
      if (records_[i] != nullptr) {
        typename RecentList<Record>::const_iterator it = records_[i]->begin();
        while (it != records_[i]->end()) {
          new_table.update(it->key, it->data);
          it++;
        }
      }
    }

    *this = std::move(new_table);
  }

 public:
  ChainingTable(int capacity, double maxLoadFactor);
  ChainingTable(const ChainingTable& other);
  ChainingTable(ChainingTable&& other);
  virtual void update(const std::string& key, const TYPE& value);
  virtual bool remove(const std::string& key);
  virtual bool find(const std::string& key, TYPE& value);
  virtual const ChainingTable& operator=(const ChainingTable& other);
  virtual const ChainingTable& operator=(ChainingTable&& other);
  virtual ~ChainingTable();
  virtual bool isEmpty() const;
  virtual int numRecords() const;
  virtual int capacity() const;
};

// create a chaining table with given number of slots and max load factor
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(int capacity, double maxLoadFactor)
    : Table<TYPE>(), capacity_{capacity}, load_factor_{maxLoadFactor} {
  records_ = new RecentList<Record>* [capacity_] {};
  num_records_ = 0;
}

// copy construct a chaining table using copy assignment
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(const ChainingTable<TYPE>& other) {
  *this = other;
}

// move construct a chaining table using move assignment
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(ChainingTable<TYPE>&& other) {
  *this = std::move(other);
}

// if the given key exists in the table, update the existing records with the
// new value; otherwise, add a new record to the table with given key & value
//
// if the load factor exceeds the max allowed value, grow the table
template <class TYPE>
void ChainingTable<TYPE>::update(const std::string& key, const TYPE& value) {
  int idx = getIndex(key);
  RecentList<Record>* chain = records_[idx];
  Record new_record(key, value);

  if (chain != nullptr) {
    typename RecentList<Record>::iterator it = chain->search(new_record);
    if (it != chain->end()) {
      // found
      *it = new_record;
    } else {
      // not found
      chain->insert(new_record);
      num_records_++;
    }
  } else {
    // this slot is empty; start a new chain
    chain = new RecentList<Record>();
    chain->insert(new_record);
    records_[idx] = chain;
    num_records_++;
  }

  if (static_cast<double>(num_records_) / capacity_ > load_factor_) {
    grow();
  }
}

// if the key exists in the table, delete the matching record and return true
// otherwise do nothing and return false
template <class TYPE>
bool ChainingTable<TYPE>::remove(const std::string& key) {
  bool found = false;
  int idx = getIndex(key);
  RecentList<Record>* chain = records_[idx];

  // if the slot is not empty, search for the key
  if (chain != nullptr) {
    Record temp(key, TYPE{});
    typename RecentList<Record>::iterator it = chain->search(temp);
    if (it != chain->end()) {
      found = true;
      chain->erase(it);
      num_records_--;
    }
  }

  return found;
}

// if the key exists in the table true, otherwise return false
template <class TYPE>
bool ChainingTable<TYPE>::find(const std::string& key, TYPE& value) {
  bool found = false;
  int idx = getIndex(key);
  RecentList<Record>* chain = records_[idx];

  // if the slot is not empty, search for the key
  if (chain != nullptr) {
    Record temp(key, TYPE{});
    typename RecentList<Record>::const_iterator it = chain->search(temp);
    if (it != chain->end()) {
      found = true;
      value = it->data;
    }
  }

  return found;
}

// deep copy the input table to this table, and return this table
template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(const ChainingTable<TYPE>& other) {
  if (this != &other) {
    clear();
    capacity_ = other.capacity_;
    num_records_ = other.num_records_;
    load_factor_ = other.load_factor_;
    records_ = new RecentList<Record>* [capacity_] {};

    // copy construct chains if they exist
    for (int i = 0; i < capacity_; i++) {
      if (other.records_[i] != nullptr) {
        records_[i] = new RecentList<Record>(*other.records_[i]);
      }
    }
  }

  return *this;
}

// transfer the ownership of the input table to this table, and return this table
template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(ChainingTable<TYPE>&& other) {
  if (this != &other) {
    // cathy spec
    std::swap(records_, other.records_);
    std::swap(capacity_, other.capacity_);
    std::swap(num_records_, other.num_records_);
    std::swap(load_factor_, other.load_factor_);
  }

  return *this;
}

// delete all records and the table
template <class TYPE>
ChainingTable<TYPE>::~ChainingTable() {
  clear();
}

// if there are no records return true, otherwise return false
template <class TYPE>
bool ChainingTable<TYPE>::isEmpty() const {
  return num_records_ == 0;
}

// return the number of records in the table
template <class TYPE>
int ChainingTable<TYPE>::numRecords() const {
  return num_records_;
}

// return the number of slots in the table
template <class TYPE>
int ChainingTable<TYPE>::capacity() const {
  return capacity_;
}
