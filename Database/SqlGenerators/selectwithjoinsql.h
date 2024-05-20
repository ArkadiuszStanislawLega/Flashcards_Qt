#ifndef SELECTWITHJOINSQL_H
#define SELECTWITHJOINSQL_H

#include <QObject>

class SelectWithJoinSql : public QObject {
private:
  Q_OBJECT
  QString _table, _criteria;
  QList<QString> _requiredColumns;
  QList<std::pair<QString, QString>> _connectedTables, _connectedValues;

public:
  ///
  /// \brief SelectWithJoinSql Prepering sql query with inner joins.
  /// \param table Table from were data we want.
  /// \param columns Columns from table were data we want.
  /// \param connectedTables Pair of tables connected.
  /// \param connectedValues Pair of values connected in tables.
  /// \param criteria Critieria of selection.
  /// \param parent
  ///
  explicit SelectWithJoinSql(QString table, QList<QString> columns,
                             QList<std::pair<QString, QString>> tables,
                             QList<std::pair<QString, QString>> values,
                             QString criteria, QObject *parent = nullptr);
  QString generate();

signals:
};

#endif // SELECTWITHJOINSQL_H
