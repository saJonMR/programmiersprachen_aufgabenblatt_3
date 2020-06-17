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


  /* DESCRIPTION  operator*() */
  T&  operator*()  const {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: remaining implementation of derefenciation of 
    //      iterator using operator* (Aufgabe 3.11 - Teil 1)

  } //call *it

  /* DESCRIPTION  operator->() */
  T* operator->() const {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: remaining implementation of derefenciation of 
    //      iterator using operator-> (Aufgabe 3.11 - Teil 2)
  }  //call it->method() or it->member


  /* PREINCREMENT, call: ++it, advances one element forward */
  ListIterator<T>& operator++() {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: Implement Postincrement-Operation for Iterator
    //      (Aufgabe 3.11 - Teil 3)
    
  }

  /* POSTINCREMENT (signature distinguishes the iterators), 
                    call:  it++, advances one element forward*/
  ListIterator<T> operator++(int) {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: Implement Postincrement-Operation for Iterator
    //      (Aufgabe 3.11 - Teil 4)

  }


  /* ... */
  bool operator==(ListIterator<T> const& x) const {
    //TODO: Implement Equality-Operation for Iterator
    //      (Aufgabe 3.11 - Teil 5)
    // Iterators should be the same if they refer to the same node
    return false;
  } // call it: == it

  /* ... */
  bool operator!=(ListIterator<T> const& x) const {
    //TODO: Implement Inequality-Operation for Iterator  
    //      (Aufgabe 3.11 - Teil 6)
    // Reuse operator==
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

    // test and implement:
    //TODO: Copy-Konstruktor using Deep-Copy semantics (Aufgabe 3.5)

    /* Unifying Assignment Operator */
    List& operator=(List<T> rhs) {
      swap(rhs);
      return *this;
    }

    void swap(List<T>& rhs) {
      std::swap(first_, rhs.first_);
      std::swap(last_, rhs.last_);
      std::swap(size_, rhs.size_);
    }

    /* ... */
    // test and implement:

    bool operator==(List const& rhs)
    {
      //TODO: operator== (Aufgabe 3.8)
    }

    bool operator!=(List const& rhs)
    {
      //TODO: operator!= (Aufgabe 3.8)
      // make use of operator==
    }

    /* calls clear function */
    ~List() {
      clear();
    } //can not really be tested

    /* ... */
    ListIterator<T> begin() {
      //TODO: begin-Method returning an Iterator to the 
      //      first element in the List (Aufgabe 3.10)
      return {};
    }

    /* ... */
    ListIterator<T> end() {
      //TODO: end-Method returning an Iterator to element after (!) 
      //      the last element in the List (Aufgabe 3.10)
      return {};
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

    /* ... */

    //TODO: member function reverse (Aufgabe 3.7 - Teil 1)


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

    /* Checks if the pointer to the first element points to nothing */
    bool empty() const {
      return size_ == 0;
    };


    /* ... */
    std::size_t size() const{   
      return size_;
  };


  // list members
  private: 
    std::size_t size_ = 0;
    ListNode<T>* first_ = nullptr;
    ListNode<T>* last_ = nullptr;
};

/* ... */
//TODO: Freie Funktion reverse 
//(Aufgabe 3.7 - Teil 2, benutzt Member-Funktion reverse)

/* ... */
//TODO: Freie Funktion operator+ (3.14 - Teil 2)

#endif // # define BUW_LIST_HPP
