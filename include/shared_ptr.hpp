#include <iostream>

template <typename T>
class shared_ptr 
{
public:
    shared_ptr();            /*noexcept*/
    shared_ptr(T* ptr);     /*strong*/
    shared_ptr(shared_ptr const & other); /*noexcept*/
    shared_ptr(shared_ptr && other);      /*noexcept*/
    auto operator= (shared_ptr const & other)->shared_ptr &;  /*strong*/
    auto operator =(shared_ptr && other) -> shared_ptr &;  /*strong*/
   
    T * operator ->() const; /*strong*/
    T & operator *() const;/*strong*/
    T * get() const;/*noexcept*/
    size_t refs() const;/*noexcept*/
    auto clear() -> void;
	
    ~shared_ptr(); 
    void swap (shared_ptr & other); /*noexcept*/
    void reset(); /*noexcept*/
private:
   
    T* ptr_;
    size_t* refs_;
};


//______________________________________________________________________________________________________________________________________
//______________________________________________________________________________________________________________________________________


template<typename T>
shared_ptr<T>::shared_ptr():ptr_(nullptr), refs_(nullptr) {}
 
template<typename T>
shared_ptr<T>::shared_ptr(T * ptr): ptr_(ptr), refs_(new size_t(1)){}
 
template<typename T>
shared_ptr<T>::shared_ptr(shared_ptr const & other) : refs_(other.refs_), ptr_(other.ptr_) { 
    if(refs_ != nullptr) ++(*refs_);
}

template<typename T>
shared_ptr<T>::~shared_ptr() {
   clear();
}

auto shared_ptr<T>::clear() -> void {
	if (!--*refs_)
	{
            delete ptr_;
            delete refs_;
        }
}

template<typename T> 
T * shared_ptr<T>::get() const { return ptr_; }

template<typename T>
size_t shared_ptr<T>::refs() const {
	if (refs_ == nullptr)
		return 0;
	else
		return *refs_;
}

template<typename T>
T * shared_ptr<T>::operator ->() const {
        if (ptr_ == nullptr)
		throw ("nullptr");
	return ptr_;
}

template<typename T>
T & shared_ptr<T>::operator *() const {
       if (ptr_ == nullptr)
		throw ("nullptr");
	return *ptr_;
}

template<typename T>
void shared_ptr::swap(shared_ptr & other) {
	std::swap(ptr_, other.ptr_);
	std::swap(refs_, other.refs_);
}


template <class T>
void shared_ptr<T>::reset() { this->swap(shared_ptr()); }


template<typename T>
auto shared_ptr<T>::operator =(const shared_ptr & other) -> shared_ptr & {
	if (this != &other) {
		shared_ptr(other).swap(*this); 
	}
	return *this;
}

template<typename T>
shared_ptr<T>::shared_ptr(shared_ptr && other): ptr_(other.ptr_),count_(other.count_)  {
        other.ptr_ = nullptr;
        other.count_=nullptr;
}
    
template<typename T>
auto shared_ptr<T>::operator =(shared_ptr && other) -> shared_ptr & {
       if(this != &other) this->swap(other);
       return *this;
}

 

template <typename T, class ...Args>
auto make_shared( Args && ...args ) -> shared_ptr<T>
{

    return shared_ptr<T>( new T( std::forward<Args>(args)... ) );
}




