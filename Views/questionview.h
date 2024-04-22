#ifndef QUESTIONVIEW_H
#define QUESTIONVIEW_H

#include "../Constants/strings.h"
#include "../Models/question.h"
#include "ui_questionview.h"
#include <QDebug>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QStringListModel>
#include <QTextEdit>
#include <QWidget>

using namespace std;

namespace Ui {
class QuestionView;
}

class QuestionView : public QWidget {
public:
  explicit QuestionView(QWidget *parent = nullptr);

signals:
  void added_question_to_db();
  void remove_question_from_db();
  void update_question_from_db();

private slots:
  void on_b_update_question_clicked();
  void on_b_remove_question_clicked();
  void on_b_create_question_clicked();

  void on_lv_created_quesions_pressed(const QModelIndex &index);

  void on_cb_tags_currentIndexChanged(int index);

private:
  Q_OBJECT
  Question *_selected_question;
  Ui::QuestionView *ui;
  QSqlRelationalTableModel *_table_model, *_cb_tags_model;
  Tag *_selected_tag;
  void initialQuestionsListView();
  void initialTagsComboBoxData();
  void cleanTextEditors();
  void printInfo(const QString &, bool);
  Question *addQuestionToDb();
  void createRelationQuestionAndTag(Question *q);
};

#endif // QUESTIONVIEW_H
