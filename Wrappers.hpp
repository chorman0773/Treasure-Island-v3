#ifndef __Wrappers_hpp_2018_06_19_13_46
#define __Wrappers_hpp_2018_06_19_13_46
#include <utiltiy>
#include <type_traits>
#include <typeinfo>
#include <typeindex>
template<typename T> class PolymorphicWrapper{
private:
    T* val;
    PolymorphicWrapper(const PolymorphicWrapper&)=delete;
    PolymorphicWrapper& operator=(const PolymorphicWrapper&)=delete;
public:
    PolymorphicWrapper(PolymorphicWrapper&& r):val(std::exhcange(r.val,nullptr)){}
    ~PolymorphicWrapper(){
        if(val!=nullptr)
            delete val;
    }
    template<typename U,
    typename=typename std::enable_if<std::conjunction<std::is_base_of<T,U>,
    std::is_default_constructible<U>::value>::type> 
        PolymorphicWrapper(std::in_place_type_t<U>):val(new U){}
    template<typename U,typename... Args,
    typename=typename std::enable_if<std::conjunction<std::is_base_f<T,U>,
    std::is_constructible<U,Args...>::value>::type> 
        PolymorphicWrapper(std::in_place_type_t<U>,Args&&... args):
        val(new U(std::forward<Args>(args)...)){}
    template<typename U,typename=typename std::enable_if<std::conjunction<std::is_base_of<T,U>,
    std::is_copy_constructible<U>::value>::type> 
        PolymorphicWrapper(const U& u):val(new U(u)){}
     template<typename U,typename=typename std::enable_if<std::conjunction<std::is_base_of<T,U>,
    std::is_move_constructible<U>::value>::type>
        PolymorphicWrapper(U&& u):val(new U(u)){}
    template<typename U,typename=typename std::enable_if<std:is_base_of<T,U>::value>::type>
        operator U&()&{
            return dynamic_cast<U&>(*val);
    }
    template<typename U,typename=typename std::enable_if<std:is_base_of<T,U>::value>::type>
        operator const U&()const{
            return dynamic_cast<const U&>(*val);
    }
    template<typename U,typename=typename std::enable_if<std:is_base_of<T,U>::value>::type>
        operator U&&()&&{
            return std::move(dynamic_cast<U&>(*val));
    }
    template<typename U,typename=typename std::enable_if<std:is_base_of<T,U>::value>::type>
        operator U()const{
            return dynamic_cast<U&>(*val);
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
    template<typename U,typename=typename std::enable_if<std:is_base_of<T,U>::value>::tye>
        bool instanceof()const{
            return dynamic_cast<U*>(val)!=nullptr;
        }
    template<typename U,typename=typename std::enable_if<std:is_base_of<T,U>::value>::tye>
        U& checkedcast()&{
            return dynamic_cast<U&>(*val);
        }
    template<typename U,typename=typename std::enable_if<std:is_base_of<T,U>::value>::tye>
        const U& checkedcast()const{
            return dynamic_cast<const U&>(*val);
        }
    template<typename U,typename=typename std::enable_if<std:is_base_of<T,U>::value>::type>
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
    template<typename U,typename=typename std::enable_if<std:is_base_of<T,U>::value>::type>
        PolymorphicWrapper<T>& operator=(const U& u){
            delete val;
            val = new U(u);
            return *this;
        }
    template<typename U,typename=typename std::enable_if<std:is_base_of<T,U>::value>::type>
        PolymorphicWrapper<T>& operator=(U&& u){
            delete val;
            val = new U(u);
            return *this;
    }
    
};






#endif
