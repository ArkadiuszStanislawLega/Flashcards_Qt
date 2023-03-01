#include "questionview.h"

void QuestionView::initialQuestionsListView(){
    int column_value_index;
    this->_table_model = new QSqlRelationalTableModel;
    this->_table_model->setTable(TABLE_QUESTIONS);
    this->_table_model->select();
    this->_table_model->setRelation(_table_model->fieldIndex(TABLE_QUESTIONS), QSqlRelation(COLUMN_ID, COLUMN_VALUE, COLUMN_ANSWER));
    column_value_index = this->_table_model->record().indexOf(COLUMN_VALUE);

    ui->lv_created_quesions->setModel(this->_table_model);
    ui->lv_created_quesions->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->lv_created_quesions->setModelColumn(column_value_index);
}

void QuestionView::cleanTextEditors(){
   ui->te_answer->setText("");
   ui->te_value->setText("");
}

void QuestionView::printInfo(const QString &value){
    this->ui->l_info->setText(value);
}

QuestionView::QuestionView(QWidget *parent)
    : QWidget{parent}, ui(new Ui::QuestionView)
{
    this->ui->setupUi(this);
    this->_selected_question = nullptr;
    this->initialQuestionsListView();
}

void QuestionView::on_b_create_question_clicked()
{
    Question *q = new Question();
    q->set_answer(ui->te_answer->toPlainText());
    q->set_value(ui->te_value->toPlainText());

    if(DbQuestion::isCreate(q)){
        this->_table_model->select();
        this->cleanTextEditors();
        this->printInfo(QUESTION_CREATED_CORRECTLY);
    } else {
        this->printInfo(DATABASE_ERROR);
    }

    delete(q);
}

void QuestionView::on_b_update_question_clicked()
{
    QString answer, value;

    if(this->_selected_question != nullptr){
        answer = ui->te_answer->toPlainText();
        value = ui->te_value->toPlainText();

        if(answer != "" && value != ""){
            this->_selected_question->set_answer(answer);
            this->_selected_question->set_value(value);

            if(DbQuestion::isUpdate(this->_selected_question)){
                this->_table_model->select();
                this->printInfo(QUESTION_UPDATED);
            } else {
                this->printInfo(DATABASE_ERROR);
            }
        }
    }
}

void QuestionView::on_b_remove_question_clicked()
{
    if(this->_selected_question != nullptr){
        if(DbQuestion::isRemoved(this->_selected_question->get_id())){
            this->_selected_question = nullptr;
            this->_table_model->select();
            this->cleanTextEditors();
            this->printInfo(QUESTION_SUCCESFULLY_REMOVED);
        } else {
            this->printInfo(DATABASE_ERROR);
        }
    }
}

void QuestionView::on_lv_created_quesions_pressed(const QModelIndex &index)
{
    int id, id_column_index, value_column_index, answer_column_index;
    QString value, answer;

    id_column_index = this->_table_model->record().indexOf(COLUMN_ID);
    value_column_index = this->_table_model->record().indexOf(COLUMN_VALUE);
    answer_column_index = this->_table_model->record().indexOf(COLUMN_ANSWER);

    id = this->_table_model->index(index.row(), id_column_index).data(Qt::DisplayRole).toInt();
    value = this->_table_model->index(index.row(), value_column_index).data(Qt::DisplayRole).toString();
    answer = this->_table_model->index(index.row(), answer_column_index).data(Qt::DisplayRole).toString();

    this->_selected_question = new Question(id, value, answer, {});

    ui->te_answer->setText(answer);
    ui->te_value->setText(value);
}

