#include "model.h"

Model::Model()
{
    const QString db_name = "fiszka.db";
    this->_database = DbManager(db_name);
}

void Model::ReadTag(){
    this->_database.ReadTag(2);
}
