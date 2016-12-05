#include <iostream>

template <typename T>
class shared_ptr {
public:
    shared_ptr();           /*noexcept*/ // конструктор по умолчанию создает пустую shared_ptr
    shared_ptr(T* ptr);     /*strong*/  // cоздает shared_ptr с ptr как управляемого объекта, создает управляющий блок
    shared_ptr(shared_ptr const & other); /*noexcept*/ // конструктор копирования
    shared_ptr(shared_ptr && other);      /*noexcept*/ // конструктор перемещения
    auto operator= (shared_ptr const & other)->shared_ptr &;  /*noexcept*/ // оператор присваивания
    auto operator =(shared_ptr && other) -> shared_ptr &;     /*noexcept*/ // оператор присваивания перемещения

    void swap(shared_ptr& other);  /*noexcept*/ // меняет местами два объекта shared_ptr
	
    T * operator ->() const;        /*strong*/ // возвращает указатель на управляемый объект
    T & operator *() const;         /*strong*/ // возвращает указанное значение
    T * get() const;                /*noexcept*/ 
	
    ~shared_ptr();
    size_t refs() const; /*noexcept*/ // возвращает количество объектов shared_ptr, которые ссылаются на тот же управляемый объект
    void reset();                   /*noexcept*/
	
private:
    
    T*   ptr_;
    size_t*   refs_;
};

template <typename T, class ...Args> // создает объект типа T, на который будет указывать shared_ptr, создает управляющий блок
auto make_shared( Args && ...args ) -> shared_ptr<T>
{
    return shared_ptr<T>( new T( std::forward<Args>(args)... ) );
}

//_____________________________________________________________________________________________________
//_____________________________________________________________________________________________________


template<typename T>   // конструктор по умолчанию создает пустую shared_ptr
shared_ptr<T>::shared_ptr():ptr_(nullptr), refs_(nullptr){}
 
template<typename T>
shared_ptr<T>::shared_ptr(T * ptr): ptr_(ptr), refs_(new size_t(1)){}
 
template<typename T>   // конструктор копирования
shared_ptr<T>::shared_ptr(shared_ptr const & other) : refs_(other.refs_), ptr_(other.ptr_) { 
    if(refs_ != nullptr) ++(*refs_);
}
 
template<typename T>   // оператор присваивания
auto shared_ptr<T>::operator =(const shared_ptr & other) -> shared_ptr & {
	if (this != &other) {
		(shared_ptr<T>(other)).swap(*this);
	}
	return *this;
}

template<typename T>   // конструктор перемещения
shared_ptr<T>::shared_ptr(shared_ptr && other): ptr_(other.ptr_),refs_(other.refs_) {
        other.ptr_ = nullptr;
        other.refs_ = nullptr;
}
    
template<typename T>   // оператор присваивания перемещения
auto shared_ptr<T>::operator =(shared_ptr && other) -> shared_ptr & {
       if(this != &other) this->swap(other);
	return *this;
}

template <class T>
void shared_ptr<T>::reset() { 
	if (ptr_ != nullptr && refs_ != nullptr && --(*refs_) == 0)
   {
	   delete ptr_;
	   delete refs_;
   }
	ptr_ = nullptr;
	refs_ = nullptr;
}

template<typename T>   // возвращает количество объектов shared_ptr, которые ссылаются на тот же управляемый объект
size_t shared_ptr<T>::refs() const {
   if (refs_ == nullptr)
		return 0;
	else
		return *refs_;
}

template<typename T>   
T * shared_ptr<T>::get() const { return ptr_; }

template<typename T>   // возвращает указатель на управляемый объект
T * shared_ptr<T>::operator ->() const {
        if (ptr_ == nullptr)
		throw ("nullptr");
	return ptr_;
}

template<typename T>   // возвращает указанное значение
T & shared_ptr<T>::operator *() const {
       if (ptr_ == nullptr)
		throw ("nullptr");
	return *ptr_;
}

template<typename T>
shared_ptr<T>::~shared_ptr() {
   if (ptr_ != nullptr && refs_ != nullptr && --(*refs_) == 0)
   {  
	   delete ptr_;
	   delete refs_;
   }
}
 
template<typename T>   // меняет местами два объекта shared_ptr
void shared_ptr<T>::swap(shared_ptr & other) {
	std::swap(ptr_, other.ptr_);
	std::swap(refs_, other.refs_);
}













