#ifndef DBCRUD_H
#define DBCRUD_H
#include <QList>

template<typename T, typename B>
class Db_crud{
public:
    virtual bool isCreate() = 0;
    virtual T *isRead() = 0;
    virtual bool isUpdate() = 0;
    virtual bool isRemoved() = 0;
    virtual int findId() = 0;
    virtual bool isRelationCreated(B *) = 0;
    virtual bool isRemovedRelation(B *) = 0;
    virtual QList<B *> getAllRelated() = 0;
    virtual QList<T *> getAll() = 0;
    virtual bool isAllRelationRemoved() = 0;
};

#endif // DBCRUD_H
