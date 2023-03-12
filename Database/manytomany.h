#ifndef MANYTOMANY_H
#define MANYTOMANY_H
#include <QList>

template<typename T>
class ManyToMany{
public:
    virtual bool isRelationCreated(T *) = 0;
    virtual bool isRemovedRelation(T *) = 0;
    virtual QList<T *> getAllRelated() = 0;
    virtual bool isAllRelationRemoved() = 0;
};

#endif // MANYTOMANY_H
