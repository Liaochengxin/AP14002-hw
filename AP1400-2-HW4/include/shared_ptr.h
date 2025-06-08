#ifndef SHARED_PTR
#define SHARED_PTR

template <typename T>
class SharedPtr{
private:
  T* _p;
  int* _counter;

public:
  //constructor
  explicit SharedPtr(T* p = nullptr) : _p(p), _counter(p ? new int(1) : nullptr) {}


  //default constructor
  //SharedPtr() : _p(nullptr), _counter(nullptr) {}

  ~SharedPtr(){
    if(_counter){
      --(*_counter);
      if(*_counter == 0){
        delete _p;
        delete _counter;
      }
      _p = nullptr;
      _counter = nullptr;
    }
  }

  //copy 
  SharedPtr(const SharedPtr& other)
    : _p(other._p), _counter(other._counter){
    if (_counter) {
      ++(*_counter);
    }
  }
  
  //move
  SharedPtr(SharedPtr&& other) : _p(other._p), _counter(other._counter){
    other._p = nullptr;
    other._counter = nullptr;
  }

  SharedPtr& operator=(const SharedPtr& other) {
    if (this != &other) {  // Compare addresses using & operator
        // Decrement current reference count
        if (_counter) {
            --(*_counter);
            if (*_counter == 0) {
                delete _p;
                delete _counter;
            }
        }
        
        // Copy the data
        _p = other._p;
        _counter = other._counter;
        
        // Increment new reference count
        if (_counter) {
            ++(*_counter);
        }
    }
    return *this;
  }
  
  //move assignment
  SharedPtr& operator=(SharedPtr&& other){
    if (this != other){
      ~SharedPtr();
      _p = other._p;
      _counter = other._counter;
      other._p = nullptr;
      other._counter = nullptr;
    }
    return *this;
  }

  int use_count(){
    return _counter ? *_counter : 0; 
  }

  T* get(){
    return _p;
  }

  T& operator*() const{
    return *(this->_p);
  }

  T* operator->() const{
    return this->_p;
  }
  
  bool operator!=(const SharedPtr& other) const {
      return _p != other._p;  // Compare the raw pointers
  }

  bool operator==(const SharedPtr& other) const {
      return _p == other._p;  // Compare the raw pointers
  }

  explicit operator bool() const { return _p != nullptr; }

  void reset() {
      if (_counter) {
          if (--(*_counter) == 0) {
              delete _p;
              delete _counter;
          }
          _p = nullptr;
          _counter = nullptr;
      }
  }

  void reset(T* t = nullptr) {
    if (_counter && --(*_counter) == 0) {
        delete _p;
        delete _counter;
    }
    _p = t;
    _counter = t ? new int(1) : nullptr;
  }

};

template<typename T, typename... Args>
SharedPtr<T> make_shared(Args&&... args){
  return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

#endif //SHARED_PTR
