#include "relationview.h"

RelationView::RelationView(QWidget *parent)
    : QWidget{parent}, ui(new Ui::RelationView)
{
    ui->setupUi(this);
    this->initialQuestionsListView();
    this->initialTagsComboBox();
}

void RelationView::initialQuestionsListView(){
    this->_questions_table_model = new QSqlRelationalTableModel;
    this->_questions_table_model->setTable(TABLE_QUESTIONS);
    this->_questions_table_model->select();

    this->ui->lv_questions->setModel(this->_questions_table_model);
    this->ui->lv_questions->setModelColumn(this->_questions_table_model->record().indexOf(COLUMN_VALUE));
}

void RelationView::initialTagsComboBox(){
    this->_tags_combo_box_model = new QSqlRelationalTableModel;
    this->_tags_combo_box_model->setTable(TABLE_TAGS);
    this->_tags_combo_box_model->select();

    this->ui->cb_tags->setModel(this->_tags_combo_box_model);
    this->ui->cb_tags->setModelColumn(this->_tags_combo_box_model->record().indexOf(COLUMN_TAG));
}

void RelationView::initialQuestionTagsListView(){
    if(this->_selected_question == nullptr){
        return;
    }

    QStringListModel *gm_model = new QStringListModel;
    this->ui->lv_question_tags->setModel(gm_model);
    QList<QString> cities;
    for(Tag *tag : this->_selected_question->get_tags()){
        qDebug() << tag->get_tag();
        cities.append(tag->get_tag());
    }
    gm_model->setStringList(cities);
}

void RelationView::on_cb_tags_currentIndexChanged(int index)
{
    int id, id_column_index, tag_column_index;
    QString tag;

    id_column_index = this->_tags_combo_box_model->record().indexOf(COLUMN_ID);
    tag_column_index = this->_tags_combo_box_model->record().indexOf(COLUMN_TAG);

    id = this->_tags_combo_box_model->index(index, id_column_index).data(Qt::DisplayRole).toInt();
    tag = this->_tags_combo_box_model->index(index, tag_column_index).data(Qt::DisplayRole).toString();

    this->_selected_cb = new Tag(id, tag);
}

void RelationView::on_lv_questions_clicked(const QModelIndex &index)
{
    int id, id_column_index, value_column_index, answer_column_index;
    QString value, answer;

    id_column_index = this->_questions_table_model->record().indexOf(COLUMN_ID);
    value_column_index = this->_questions_table_model->record().indexOf(COLUMN_VALUE);
    answer_column_index = this->_questions_table_model->record().indexOf(COLUMN_ANSWER);

    id = this->_questions_table_model->index(index.row(), id_column_index).data(Qt::DisplayRole).toInt();
    value = this->_questions_table_model->index(index.row(), value_column_index).data(Qt::DisplayRole).toString();
    answer = this->_questions_table_model->index(index.row(), answer_column_index).data(Qt::DisplayRole).toString();

    this->_selected_question = new Question(id, value, answer, {});
    vector<Tag *> tags = DbRelationQuestionTag::readRelatedTags(this->_selected_question);
    this->_selected_question->set_tags(tags);
    initialQuestionTagsListView();
}

void RelationView::on_lv_question_tags_clicked(const QModelIndex &index)
{
    qDebug() << this->_selected_question->get_tags().at(index.row())->get_tag();
}

void RelationView::on_b_create_relation_clicked()
{

}

void RelationView::on_b_remove_relation_clicked()
{

}

