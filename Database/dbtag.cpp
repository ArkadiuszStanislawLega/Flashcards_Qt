#include "dbtag.h"

DbTag::DbTag()
{

}

bool DbTag::isCreate(Tag *t){
    if(t != nullptr){

    }
    return false;
}

Tag *DbTag::read(int id){
    Tag *tag = new Tag();
    if(id > 0){

    }
    return tag;
}

bool DbTag::isUpdate(Tag *t){
    if(t != nullptr){

    }
   return false;
}

bool DbTag::isRemoved(int id){
    if(id > 0){

    }
    return false;
}

int findId(Qstring tag){
    if (tag != nullptr)
    {

    }
    return -1;
}
