#include "model.h"

Model::Model()
{
    const QString db_name = DATABASE_NAME;
    this->_database = DbManager(db_name);
}
