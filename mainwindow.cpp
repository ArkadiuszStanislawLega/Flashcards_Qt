#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  QObject::connect(ui->quesiton_view, &QuestionView::added_question_to_db,
                   ui->relation_view, &RelationView::added_question_to_db);
  QObject::connect(ui->quesiton_view, &QuestionView::update_question_from_db,
                   ui->relation_view, &RelationView::update_question_from_db);
  QObject::connect(ui->quesiton_view, &QuestionView::remove_question_from_db,
                   ui->relation_view, &RelationView::remove_question_from_db);

  QObject::connect(ui->tag_view, &TagView::updated_tag_from_db,
                   ui->relation_view, &RelationView::update_tag_from_db);
  QObject::connect(ui->tag_view, &TagView::remove_tag_from_db,
                   ui->relation_view, &RelationView::remove_tag_from_db);
  QObject::connect(ui->tag_view, &TagView::remove_tag_from_db,
                   ui->relation_view, &RelationView::remove_tag_from_db);

  QObject::connect(ui->quesiton_view, &QuestionView::added_question_to_db,
                   ui->learn_view, &LearnView::added_question_to_db);
  QObject::connect(ui->quesiton_view, &QuestionView::remove_question_from_db,
                   ui->learn_view, &LearnView::removed_question_from_db);

  QObject::connect(ui->tag_view, &TagView::added_tag_to_db, ui->relation_view,
                   &RelationView::added_tag_to_db);
  QObject::connect(ui->tag_view, &TagView::added_tag_to_db, ui->learn_view,
                   &LearnView::added_tag_to_db);
  QObject::connect(ui->tag_view, &TagView::added_tag_to_db, ui->quesiton_view,
                   &QuestionView::added_tag_to_db);
  QObject::connect(ui->tag_view, &TagView::updated_tag_from_db, ui->learn_view,
                   &LearnView::update_tag_in_db);
  QObject::connect(ui->tag_view, &TagView::remove_tag_from_db, ui->learn_view,
                   &LearnView::removed_tag_from_db);

  QObject::connect(ui->relation_view, &RelationView::create_relation,
                   ui->learn_view, &LearnView::create_relation);
  QObject::connect(ui->relation_view, &RelationView::remove_relation,
                   ui->learn_view, &LearnView::remove_relation);
  QObject::connect(ui->quesiton_view, &QuestionView::update_question_from_db,
                   ui->learn_view, &LearnView::update_question);

  setWindowTitle("Cards");
}

MainWindow::~MainWindow() { delete ui; }
