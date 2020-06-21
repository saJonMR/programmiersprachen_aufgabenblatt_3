#ifndef BUW_LIST_HPP
#define BUW_LIST_HPP
#include <cassert>
#include <cstddef>  //ptrdiff_t
#include <iterator> //std::bidirectional_iterator_tag
#include <iostream>

#include <initializer_list>

template <typename T>
class List;

template <typename T>
struct ListNode {
  T         value = T{};
  ListNode* prev = nullptr;
  ListNode* next = nullptr;
};


//TODO: Implementierung der Methoden des Iterators 
//      (nach Vorlesung STL-1 am 09. Juni) (Aufgabe 3.11)
template <typename T>
struct ListIterator {
  using Self              = ListIterator<T>;
  using value_type        = T;
  using pointer           = T*;
  using reference         = T&;
  using difference_type   = ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;


  /* Returns Reference to Value of current Node */
  T&  operator*()  const {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }
    return node->value;
  } //call *it

  /* Returns pointer to Reference of current node */
  T* operator->() const {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }
    return &node->value;
  }  //call it->method() or it->member


  /* PREINCREMENT, call: ++it, advances one element forward */
  ListIterator<T>& operator++() {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }
    node = node->next;
    return *this;
  }

  /* POSTINCREMENT (signature distinguishes the iterators), 
                    call:  it++, advances one element forward*/
  ListIterator<T> operator++(int) {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }
    auto newit = *this;
    ++*this;
    return newit;
  }

  /* Compares Values of Both Nodes */
  bool operator==(ListIterator<T> const& x) const {
    if(x.node == node) {
      return true;
    } 
    return false;
  } // call it: == it

  /* Compares Values of Both Nodes */
  bool operator!=(ListIterator<T> const& x) const {
    if(x.node != node) {
      return true;
    }
    return false;
  } // call it: != it

  /* Advances Iterator */
  ListIterator<T> next() const {
    if (nullptr != node) {
      return ListIterator{node->next};
    } else {
      return ListIterator{nullptr};
    }
  }


  ListNode <T>* node = nullptr;
};



template <typename T>
class List {
  public:

    //friend declarations for testing the members   
    template <typename TEST_TYPE>
    friend size_t get_size(List<TEST_TYPE> const& list_to_test);
    template <typename TEST_TYPE>
    friend ListNode<TEST_TYPE>* get_first_pointer(List<TEST_TYPE> const& list_to_test);
    template <typename TEST_TYPE>
    friend ListNode<TEST_TYPE>* get_last_pointer(List<TEST_TYPE> const& list_to_test);

    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = T const*;
    using reference       = T&;
    using const_reference = T const&;
    using iterator        = ListIterator<T>;

    /* Initializes the List with size_ = 0 and both the first and the last node pointing to null */
    List()=default;

    //Copy Constructor (Deep Copy)
    /* Initializes a new empty List and copies (deep) the elements of the input List until it reaches the last node */
    List(List<T> const& l) :
      size_{0},
      first_{nullptr},
      last_{nullptr }
    {
      ListNode<T> *node = l.first_;
      while(node != nullptr) {
        push_back(node->value);
        node = node->next;
      }
    }

    //TODO: Initializer-List Konstruktor (3.14 - Teil 1)
    /* ... */
    // test and implement:
    List(std::initializer_list<T> ini_list) {
      //not implemented yet
    }

    /* Unifying Assignment Operator */
    /* Makes Use of Swap function to Assign Pointers and Size */
    List& operator=(List rhs) {
      swap(rhs);
      return *this;
    }

    //swap function that swaps the first_ and last_ pointers as well as size_
    void swap(List& rhs) {
      std::swap(first_, rhs.first_);
      std::swap(last_, rhs.last_);
      std::swap(size_, rhs.size_);
    }

    /* ... */
    // test and implement:

    bool operator==(List const& rhs) {
      bool status = false;
      if(size_ == rhs.size_) {
        status = true;
        ListNode<T> *nodelhs = first_;
        ListNode<T> *noderhs = rhs.first_;
        while(nodelhs != nullptr && status) {
          if(nodelhs->value == noderhs->value) {
            nodelhs = nodelhs->next;
            noderhs = noderhs->next;
          } else {
            status = false;
          }
        }
      }
      return status;
    }

    bool operator!=(List const& rhs)
    {
      if(*this == rhs) {
        return false;
      } else {
        return true;
      }
    }

    /* calls clear function */
    ~List() {
      clear();
    } //can not really be tested

    /* Returns iterator that points to first node */
    ListIterator<T> begin() {
      auto begin = first_;
      return {begin};
    }

    /* Returns iterator that points behind last node (nullptr) */
    ListIterator<T> end() {
      auto end = nullptr;
      return {end};
    }

    /* Calls pop_front until first_ = last_ and then pops the last element indivdually */ 
    void clear() {
      while(size_ > 0) {
        pop_back();
      }
    }

    /* ... */
    //TODO: member function insert (Aufgabe 3.12)

    /* ... */ 
    //TODO: member function insert (Aufgabe 3.13)

    /* Reverses List by changing the direction of the pointers, from front to back*/
    //TODO: member function reverse (Aufgabe 3.7 - Teil 1)
    void reverse() {
      ListNode<T> *node = last_;
      last_ = first_;
      first_ = node;
      while(node != nullptr) {
        std::swap(node->next, node->prev);
        node = node->next;
      }
    }


    /* Insert Element at the front of the List */
    void push_front(T const& element) {
      ListNode<T> *node = new ListNode<T>{element};
      if (first_ == nullptr) {
        first_ = node;
        last_ = node;
        node->next = nullptr;
        node->prev = nullptr;
      } else {
        node->next = first_;
        first_->prev = node;
        first_ = node;
      }
      size_++;
    }

    /* Insert Element at the back of the List */
    void push_back(T const& element) {
      ListNode<T> *node = new ListNode<T>{element};
      if (first_ == nullptr) {
        first_ = node;
        last_ = node;
        node->next = nullptr;
        node->prev = nullptr;
      } else {
        last_->next = node;
        node->prev = last_;
        last_ = node;
      }
      size_++;
    }

    /* Checks if list has one or more than one item and adjusts pointers */
    void pop_front() {
      if(empty()) {
        throw "List is empty";
      }
      if(first_ == last_) {
        first_ = nullptr;
        last_ = nullptr;
      } else {
        ListNode<T> *newFirst = first_->next;
        first_->next = nullptr;
        delete first_;
        first_ = newFirst;
        first_->prev = nullptr;
      }
      size_--;
    }

    /* Checks if list has one or more than one item and adjusts pointers */
    void pop_back() {
      if(empty()) {
        throw "List is empty";
      }
      if(first_ == last_) {
        first_ = nullptr;
        last_ = nullptr;
      } else {
        ListNode<T> *newLast = last_->prev;
        last_->prev = nullptr;
        delete last_;
        last_ = newLast;
        last_->next = nullptr;
      }
      size_--;
    }

    /* returns value of first node */
    T& front() {
      if(empty()) {
        throw "List is empty";
      }
      return first_->value;
    }

    /* returns value of last node */
    T& back() {
      if(empty()) {
        throw "List is empty";
      }
      return last_->value;
    }

    /* Returns wether List is empty or not*/
    bool empty() const {
      return size_ == 0;
    };


    /* Size */
    std::size_t size() const{   
      return size_;
  };


  // list members
  private: 
    std::size_t size_ = 0;
    ListNode<T>* first_ = nullptr;
    ListNode<T>* last_ = nullptr;
};

/* Makes use of member function reverse - takes a List as input and returns a new one */
//TODO: Freie Funktion reverse 
//(Aufgabe 3.7 - Teil 2, benutzt Member-Funktion reverse)
template<typename T>
List<T> reverse(List<T> const& list) {
  List<T> newL = list;
  newL.reverse();
  return newL;
}

/* ... */
//TODO: Freie Funktion operator+ (3.14 - Teil 2)

#endif // # define BUW_LIST_HPP
