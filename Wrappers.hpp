#ifndef __Wrappers_hpp_2018_06_19_13_46
#define __Wrappers_hpp_2018_06_19_13_46
#include <utility>
#include <type_traits>
#include <typeinfo>
#include <typeindex>
template<typename T> class PolymorphicWrapper{
private:
    T* val;
    PolymorphicWrapper(const PolymorphicWrapper&)=delete;
    PolymorphicWrapper& operator=(const PolymorphicWrapper&)=delete;
public:
    PolymorphicWrapper():val(nullptr){}
    PolymorphicWrapper(PolymorphicWrapper&& r):val(std::exhcange(r.val,nullptr)){}
    template<typename U,typename=std::enable_if_t<std::is_base_of_v<T,U>>> 
        PolymorphicWrapper(PolymorphicWrapper<U>&& r):val(std::exchange(r.val,nullptr)){}
    ~PolymorphicWrapper(){
        if(val!=nullptr)
            delete val;
    }
    PolymorphicWrapper(const T& t):val(new T(t)){}
    PolymorphicWrapper(T&& t):val(new T(t)){}
    PolymorphicWrapper(const T&&)=delete;
    template<typename U,
    typename=typename std::enable_if<std::conjunction<std::is_base_of<T,U>,
    std::is_default_constructible<U>::value>::type> 
        PolymorphicWrapper(std::in_place_type_t<U>):val(new U){}
    template<typename U,typename... Args,
        typename=std::enable_if_t<std::is_base_of_v<T,U>>> 
        PolymorphicWrapper(std::in_place_type_t<U>,Args&&... args):
        val(new U(std::forward<Args>(args)...)){}
    template<typename U,typename=std::enable_if_t<std::is_base_of_v<T,U>>> 
        PolymorphicWrapper(const U& u):val(new U(u)){}
    template<typename U,typename=std::enable_if_t<std::is_base_of_v<T,U>>>
        PolymorphicWrapper(U&& u):val(new U(u)){}
    template<typename U,typename=std::enable_if_t<std::is_base_of_v<T,U>>>
        PolymorphicWrapper(const U&&)=delete;
    template<typename U,typename=std::enable_if_t<std::is_base_of_v<T,U>>>
        operator U&()&{
            return dynamic_cast<U&>(*val);
    }
    template<typename U,typename=std::enable_if_t<std::is_base_of_v<T,U>>>
        operator const U&()const{
            return dynamic_cast<const U&>(*val);
    }
    template<typename U,typename=std::enable_if_t<std::is_base_of_v<T,U>>>
        operator U&&()&&{
            return std::move(dynamic_cast<U&>(*val));
    }
    operator T&()&{
        return *val;
    }
    operator const T&()const{
        return *val;
    }
    operator T&&()&&{
        return std::move(*val);
    }
    const std::type_info& type()const{
        return typeid(*val);
    }
    template<typename U,std::enable_if_t<std::is_base_of_v<T,U>>>
        bool instanceof()const{
            return dynamic_cast<U*>(val)!=nullptr;
        }
    template<typename U,typename=std::enable_if_t<std::is_base_of_v<T,U>>>
        U& checkedcast()&{
            return dynamic_cast<U&>(*val);
        }
    template<typename U,typename=std::enable_if_t<std::is_base_of_v<T,U>>>
        const U& checkedcast()const{
            return dynamic_cast<const U&>(*val);
        }
    template<typename U,typename=std::enable_if_t<std::is_base_of_v<T,U>>>
        U&& checkedcast()&&{
            return std::move(dynamic_cast<U&>(*val));
        }
    
    T* operator->(){
        return val;
    }
    const T* operator->()const{
        return val;
    }
    T& operator*(){
        return *val;
    }
    const T& operator*()const{
        return *val;
    }
    template<typename U,typename=std::enable_if_t<std::is_base_of_v<T,U>>>
        PolymorphicWrapper<T>& operator=(const U& u){
            if(val!=nullptr)
                delete val;
            val = new U(u);
            return *this;
        }
    template<typename U,typename=std::enable_if_t<std::is_base_of_v<T,U>>>
        PolymorphicWrapper<T>& operator=(U&& u){
            if(val!=nullptr)
                delete val;
            val = new U(u);
            return *this;
    }
    PolymorphicWrapper& operator=(PolymorphicWrapper&& r){
        if(val!=nullptr)
            delete val;
        val = std::exchange(r.val);
        return *this;
    }
    template<typename U,typename=std::enable_if_t<std::is_base_of_v<T,U>>>
    PolymorphicWrapper& operator=(PolymorphicWrapper<U>&& r){
        if(val!=nullptr)
            delete val;
        val = std::exchange(r.val);
        return *this;
    }
    
};

template<typename T> class PolymorphicWrapper<std::enable_if_t<std::is_scalar_v<T>,T>>{
private:
    PolymorphicWrapper()=delete;
    PolymorphicWrapper(const PolymorphicWrapper&)=delete;
    PolymorphicWrapper(PolymorphicWrapper&&)=delete;
    PolymorphicWrapper& operator=(const PolymorphicWrapper&)=delete;
    PolymorphicWrapper& operator=(PolymorphicWrapper&&)=delete;
};
template<typename T> class PolymorphicWrapper<std::enable_if_t<std::is_enum_v<T>,T>>{
private:
    PolymorphicWrapper()=delete;
    PolymorphicWrapper(const PolymorphicWrapper&)=delete;
    PolymorphicWrapper(PolymorphicWrapper&&)=delete;
    PolymorphicWrapper& operator=(const PolymorphicWrapper&)=delete;
    PolymorphicWrapper& operator=(PolymorphicWrapper&&)=delete;
};

template<typename T> class PolymorphicWrapper<std::enable_if_t<std::is_union_v<T>,T>>{
private:
    PolymorphicWrapper()=delete;
    PolymorphicWrapper(const PolymorphicWrapper&)=delete;
    PolymorphicWrapper(PolymorphicWrapper&&)=delete;
    PolymorphicWrapper& operator=(const PolymorphicWrapper&)=delete;
    PolymorphicWrapper& operator=(PolymorphicWrapper&&)=delete;
};

template<typename T> explicit PolymorphicWrapper(T&&) ->PolymorphicWrapper<T>;
template<typename T> explicit PolymorphicWrapper(const T&) -> PolymorphicWrapper<T>;
template<typename T> explicit PolymorphicWrapper(std::in_place_type_t<T>) -> PolymorphicWrapper<T>;
template<typename T,typename... Args> explicit PolymorphicWrapper(std::in_place_type_t<T>,Args&&...) -> PolymorphicWrapper<T>;






#endif
