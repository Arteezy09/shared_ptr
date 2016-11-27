#include <iostream>
#include <stdexcept>
#include <utility>
template <typename T>
class shared_ptr {
public:
    shared_ptr();           /*noexcept*/
    shared_ptr(T* ptr);     /*strong*/
    shared_ptr(shared_ptr const & other); /*noexcept*/
    shared_ptr(shared_ptr && other);      /*noexcept*/
    auto operator= (shared_ptr const & other)->shared_ptr &;  /*strong*/
    auto operator =(shared_ptr && other) -> shared_ptr &;     /*strong*/

    void swap(shared_ptr& other);  /*noexcept*/
	
    T * operator ->() const;        /*strong*/
    T & operator *() const;         /*strong*/
    T * get() const;                /*noexcept*/
	
    ~shared_ptr();
    auto refs() const->size_t;/*noexcept*/
 
private:
    
    T*   ptr_;
    size_t*   refs_;
};


//_____________________________________________________________________________________________________
//_____________________________________________________________________________________________________


template <typename T, class ...Args>
auto make_shared( Args && ...args ) -> shared_ptr<T>
{
    return shared_ptr<T>( new T( std::forward<Args>(args)... ) );
}

template<typename T> 
T * shared_ptr<T>::get() const { return ptr_; }

template<typename T> 
void shared_ptr<T>::swap(shared_ptr & other) {
	std::swap(ptr_, other.ptr_);
	std::swap(refs_, other.refs_);
}





template<typename T>
shared_ptr<T>::shared_ptr():ptr_(nullptr), refs_(nullptr){}
 
template<typename T>
shared_ptr<T>::shared_ptr(T * ptr): ptr_(ptr), refs_(new size_t(1)){}
 
template<typename T>
shared_ptr<T>::shared_ptr(shared_ptr const & other) : refs_(other.refs_), ptr_(other.ptr_) { 
    if(refs_ != nullptr) ++(*refs_);
}
 
template<typename T>
auto shared_ptr<T>::operator =(const shared_ptr & other) -> shared_ptr & {
	if (this != &other) {
		(shared_ptr<T>(other)).swap(*this);
	}
	return *this;
}

template<typename T>
 shared_ptr<T>::shared_ptr(shared_ptr && other): ptr_(other.ptr_),refs_(other.refs_)
    {
        other.ptr_ = nullptr;
	 other.refs_=nullptr;
    }
    
    template<typename T>
    auto shared_ptr<T>::operator =(shared_ptr && other) -> shared_ptr &
    {
       if(this !=&other) this->swap(std::move(other));
	return *this;
    }

 
template<typename T>
shared_ptr<T>::~shared_ptr(){
    if (refs_) {
        if (*refs_ == 1) {
            delete refs_;
            delete ptr_;
        }
        else (*refs_)--;
    }
}
 
template<typename T>
auto shared_ptr<T>::refs() const->size_t{
   return (refs_ != nullptr ? *refs_ : 0);
}
template<typename T>
T * shared_ptr<T>::operator ->() const {
        if(refs_) {return ptr_;}else {throw std::logic_error("Error");}
}
template<typename T>
T & shared_ptr<T>::operator *() const {
       if(refs_) {return *ptr_;}else {throw std::logic_error("Error");}
}

 






