#ifndef PTRCOMPONENT_H
#define PTRCOMPONENT_H
#include <string>
#include <map>
#include "debug.h"

class ptrComponent
{
public:
    static ptrComponent * INS(){
        return &objp;
    }
    template<typename T>
    void addComponent_(void * comp,const std::string & id=""){
        if(comp==nullptr){
            errorL("error: the comp  is nullptr");
             return ;
        }
       const std::type_info & info=typeid (T);
       std::string id_=id+info.name();
       auto iter=allComponent.find(id_);

       if(iter!=allComponent.end()){
           errorL("error: the type %s   Already exists" , id_);
           return;
       }else{
            allComponent[id_]=comp;
       }
    }
    template<typename T>
    T * getComponent_(const std::string & id=""){
        T * ret=nullptr;
        const std::type_info & info=typeid (T);
        std::string id_=id+info.name();
        auto iter=allComponent.find(id_);

        if (iter != allComponent.end()) {
            ret= static_cast<T*>(iter->second);
        }
        else {
            return nullptr;
        }
        return ret;

        /*if(iter!=allComponent.end()){
            ret=static_cast<T*>(iter.value());
            if(ret==nullptr){
                errorL("error:type error " << info.name());
            }

            return ret;
        }else{
           
        }*/
    }
private:
    ptrComponent(){}
   std::map<std::string,void *> allComponent;
   static ptrComponent objp;

};

template<typename T>
void addComponent(void * comp,const std::string & id=""){
    ptrComponent::INS()->addComponent_<T>(comp,id);
}

template<typename T>
T *  getComponent(const std::string & id=""){
    return ptrComponent::INS()->getComponent_<T>(id);
}

#endif // PTRCOMPONENT_H
