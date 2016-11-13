#include <iostream>
#include <utility>
#include <stdexcept>
template <typename T>
class shared_ptr {
public:
    shared_ptr();/*noexcept*/
    shared_ptr(T* ptr);/*strong*/
    shared_ptr(shared_ptr const & other);
    shared_ptr(shared_ptr && other);/*noexcept*/
    auto operator= (shared_ptr const & other)->shared_ptr &;/*noexcept*/
    auto operator =(shared_ptr && other) -> shared_ptr &;/*noexcept*/
    auto swap(shared_ptr& other) noexcept -> void;/*noexcept*/
    auto operator ->() const -> T *;/*strong*/
    auto operator *() const -> T *;/*strong*/
    auto get() const noexcept -> T *;/*noexcept*/
    ~shared_ptr();
    auto count() const->size_t;/*noexcept*/
 
private:
   auto swap(shared_ptr&& other) noexcept -> void;
    T* ptr_;
    size_t *count_;
};

//_____________________________________________________________________________________________________
//_____________________________________________________________________________________________________
//_____________________________________________________________________________________________________
//_____________________________________________________________________________________________________
template <typename T, class ...Args>
auto make_shared( Args && ...args ) -> shared_ptr<T>
{
    return shared_ptr<T>( new T( std::forward<Args>(args)... ) );
}

template<typename T> 
auto shared_ptr<T>::get() const noexcept -> T * {
	return ptr_;
}

template<typename T> 
auto shared_ptr<T>::swap(shared_ptr & other) noexcept -> void {
	std::swap(ptr_, other.ptr_);
	std::swap(count_, other.count_);
}

template<typename T>
auto shared_ptr<T>::swap(shared_ptr && other) noexcept -> void{
	std::swap(ptr_, other.ptr_);
	std::swap(count_, other.count_);
}

template<typename T>
shared_ptr<T>::shared_ptr():ptr_(nullptr), count_(nullptr){}
 
template<typename T>
shared_ptr<T>::shared_ptr(T * ptr): ptr_(ptr), count_(new size_t(1)){}
 
template<typename T>
shared_ptr<T>::shared_ptr(shared_ptr const & other) : count_(other.count_), ptr_(other.ptr_) { 
    if(count_ != nullptr) ++(*count_);
}
 
template<typename T>
auto shared_ptr<T>::operator =(const shared_ptr & other) -> shared_ptr & {
	if (this != &other) {
		(shared_ptr<T>(other)).swap(*this);
	}
	return *this;
}

template<typename T>
 shared_ptr<T>::shared_ptr(shared_ptr && other): ptr_(other.ptr_),count_(other.count_)
    {
        other.ptr_ = nullptr;
	 other.count_=nullptr;
    }
    
    template<typename T>
    auto shared_ptr<T>::operator =(shared_ptr && other) -> shared_ptr &
    {
       if(this !=&other) this->swap(std::move(other));
	return *this;
    }

 
template<typename T>
shared_ptr<T>::~shared_ptr(){
    if (count_) {
        if (*count_ == 1) {
            delete count_;
            delete ptr_;
        }
        else (*count_)--;
    }
}
 
template<typename T>
auto shared_ptr<T>::count() const->size_t{
   return (count_ != nullptr ? *count_ : 0);
}
template<typename T>
auto shared_ptr<T>::operator ->() const -> T *{
        if(count_) {return ptr_;}else {throw std::logic_error("Error");}
}
template<typename T>
auto shared_ptr<T>::operator *() const -> T *{
       if(count_) {return *ptr_;}else {throw std::logic_error("Error");}
}




