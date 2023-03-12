#include "questionview.h"

void QuestionView::initialQuestionsListView(){
    this->_table_model = new QSqlRelationalTableModel;
    this->_table_model->setTable(TABLE_QUESTIONS);
    this->_table_model->select();

    this->ui->lv_created_quesions->setModel(this->_table_model);
    this->ui->lv_created_quesions->setModelColumn(this->_table_model->record().indexOf(COLUMN_VALUE));
}

void QuestionView::cleanTextEditors(){
   this->ui->te_answer->setText("");
   this->ui->te_value->setText("");
}

void QuestionView::printInfo(const QString &value, bool isError=false){
    QPalette pal = this->ui->l_info->palette();
    pal.setColor(QPalette::Window, QColor( isError ? Qt::red : Qt::transparent));

    this->ui->l_info->setText(value);
    this->ui->l_info->setPalette(pal);
}

QuestionView::QuestionView(QWidget *parent)
    : QWidget{parent}, ui(new Ui::QuestionView)
{
    this->ui->setupUi(this);
    this->_selected_question = new Question(this);
    this->initialQuestionsListView();
}

void QuestionView::on_b_create_question_clicked()
{
    if(ui->te_answer->toPlainText() == ""){
        this->printInfo(FIELD_ANSWER_CANT_EMPTY, true);
        return;
    }

    if(ui->te_value->toPlainText() == ""){
        this->printInfo(FIELD_VALUE_CANT_EMPTY, true);
        return;
    }

    Question *q = new Question();
    q->set_answer(ui->te_answer->toPlainText());
    q->set_value(ui->te_value->toPlainText());

    if(q->isCreate()){
        this->_table_model->select();
        this->cleanTextEditors();
        this->printInfo(QUESTION_CREATED_CORRECTLY);
    } else {
        this->printInfo(DATABASE_ERROR, true);
    }

    delete q;
}

void QuestionView::on_b_update_question_clicked()
{
    if(this->_selected_question == nullptr){
        this->printInfo(INFO_FIRST_SELECT_QUESTION, true);
        return;
    }

    if(ui->te_answer->toPlainText() == ""){
        this->printInfo(FIELD_ANSWER_CANT_EMPTY, true);
        return;
    }

    if(ui->te_value->toPlainText() == ""){
        this->printInfo(FIELD_VALUE_CANT_EMPTY, true);
        return;
    }

    this->_selected_question->set_answer(this->ui->te_answer->toPlainText());
    this->_selected_question->set_value(this->ui->te_value->toPlainText());

    if(this->_selected_question->isUpdate()){
        this->_table_model->select();
        this->printInfo(QUESTION_UPDATED);
        this->cleanTextEditors();
    } else {
        this->printInfo(DATABASE_ERROR, true);
    }
}

void QuestionView::on_b_remove_question_clicked()
{
    if(this->_selected_question == nullptr){
        this->printInfo(INFO_FIRST_SELECT_QUESTION, true);
        return;
    }

    if(this->_selected_question->isRemoved()){
        this->_selected_question = nullptr;
        this->_table_model->select();
        this->cleanTextEditors();
        this->printInfo(QUESTION_SUCCESFULLY_REMOVED);
    } else {
        this->printInfo(DATABASE_ERROR, true);
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
    this->_selected_question->getAllRelated();

    this->ui->te_answer->setText(answer);
    this->ui->te_value->setText(value);
}

