#ifndef UNIQUE_PTR
#define UNIQUE_PTR

template <typename T>

class UniquePtr {
private:
    T* _p;

public:
    //constructor
    explicit UniquePtr(T* p = nullptr) : _p(p) {}

    //Destructor
    ~UniquePtr() {
      delete _p;
    }

    //default constructor
    //UniquePtr() : _p(nullptr) {} 


    //copy constructor
    UniquePtr(const UniquePtr&) = delete;
    //copy assignment
    UniquePtr& operator=(const UniquePtr&) = delete;

    explicit operator bool() const { return _p != nullptr; }

    T* get(){ return this->_p; } 

    T& operator*() const { return *(this->_p); }

    //cpp automatically use -> again
    T* operator->() const { return this->_p; }


    void reset(){
      delete _p;
      _p = nullptr;
    }

    void reset(T* t){
      delete _p;
      _p = t;
    }

    T* release(){
      T* temp = _p;
      _p = nullptr;
      return temp;
    }

    
};

template<typename T, typename... Args>
UniquePtr<T> make_unique(Args&&... args){
  return UniquePtr<T>(new T(std::forward<Args>(args)...));
};









#endif //UNIQUE_PTR
