#ifndef MODEL_H
#define MODEL_H

#include "../Database/dbmanager.h"

class Model
{
private:
   DbManager _database;
public:
    Model();
    void ReadTag();
};

#endif // MODEL_H
