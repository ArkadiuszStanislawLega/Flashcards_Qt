#ifndef CRUD_H
#define CRUD_H
#include <QList>

template<typename T>
class Crud{
public:
    virtual bool isCreate() = 0;
    virtual T *isRead() = 0;
    virtual bool isUpdate() = 0;
    virtual bool isRemoved() = 0;
    virtual int findId() = 0;
};

#endif // CRUD_H
