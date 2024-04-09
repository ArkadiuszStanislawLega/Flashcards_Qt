#ifndef STRINGS
#define STRINGS
#include <QString>

static const QString ERROR_CONNECTION_WITH_DATABASE =
    "Error: connection with database failed";
static const QString CONNECTION_OK = "Database: connection ok";
static const QString DATABASE_NAME = "fiszka.db";
static const QString SETTINGS_FILENAME = "settings.ini";
static const QString TABLE_QUESTIONS = "Questions";
static const QString TABLE_TAGS = "Tags";
static const QString TABLE_QUESTIONS_TAGS = "Questions_tags";
static const QString COLUMN_ID = "Id";
static const QString COLUMN_VALUE = "Value";
static const QString COLUMN_ANSWER = "Answer";
static const QString COLUMN_TAG = "Tag";
static const QString COLUMN_QUESTION_ID = "Question_id";
static const QString COLUMN_TAG_ID = "Tag_id";
static const QString COLUMN_IS_ACTIVE = "Is_active";
static const QString CREATE_TABLE_IF_NOT_EXISTS = "CREATE TABLE IF NOT EXISTS ";
static const QString INTEGER_NOT_NULL = "INTEGER NOT NULL";
static const QString PRIMARY_KEY = "INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL";
static const QString TEXT = "TEXT NOT NULL";
static const QString FOREIGN_KEY = "FOREIGN KEY ";
static const QString REFERENCES = "REFERENCES ";
static const QString SELECT = "SELECT ";
static const QString FROM = "FROM ";
static const QString WHERE = "WHERE ";
static const QString INSERT = "INSERT INTO ";
static const QString VALUES = "VALUES";
static const QString UPDATE = "UPDATE ";
static const QString SET = "SET ";
static const QString DELETE = "DELETE FROM ";
static const QString INNER_JOIN = "INNER JOIN ";
static const QString ON = "ON ";
static const QString AND = "AND ";
static const QString LIMIT = "LIMIT ";
static const QString ORDER_BY = "ORDER BY ";

static const char ANSWER_YES_LARGE = 'Y';
static const char ANSWER_YES_SMALL = 'y';

static const QString TAG_LIST = "Tags list";
static const QString ADD_TAG = "Add tag";
static const QString ADD_QUESTION = "Add question";
static const QString REMOVE_TAG = "Remove the tag";
static const QString MAKE_SERIES = "Make questions series";
static const QString QUESTIONS_MENU = "Questions menu";
static const QString TAGS_MENU = "Tags menu";
static const QString MAIN_MENU = "MAIN MENU";
static const QString SELECTED_TAG = "Selected tag";
static const QString CHOSE_NUMBER = "Chose number";
static const QString WRONG_VALUE = "Wrong value";
static const QString WRONG_VALUE_TRY_AGAIN = "Wrong value. Try again.";
static const QString SELECT_TAG_FIRST = "Select the tag first";
static const QString TAGS_LIST = "Tags list";
static const QString TAG_CREATED_CORRECTLY = "The tag created correctly";
static const QString DATABASE_ERROR = "Database error";
static const QString INFO_CREATING_QUESTION =
    "Add a question. First, the query, and then after pressing the ENTER key, "
    "the answer. Then confirm by pressing the ENTER key.";
static const QString QUESTION_CREATED_CORRECTLY =
    "The question created correctly";
static const QString CHOSE_TAG = "Choose the tag from the list";
static const QString ADD_THE_TAG = "Add the tag";
static const QString TO_THE_QUESTION = "to the question";
static const QString TAG_ADDED_SUCCESFULLY = "The tag added succesfully";
static const QString INFO_CONFIRM_REMOVE = "Confirm deletion by typing (Y)";
static const QString THE_TAG = "The tag";
static const QString TAG_SUCCESFULLY_REMOVED =
    "The tag has been successfully removed from database";
static const QString QUESTIONS_LIST_TO_REMOVED =
    "List of the questions to removed";
static const QString CHOOSE_QUESTION = "Choose one question";
static const QString NO_QUESTIONS_TO_REMOVE =
    "There are no questions to remove";
static const QString QUESTION_SUCCESFULLY_REMOVED =
    "The question has been succesfully deleted";
static const QString INFO_QUESTIONS_NUMBER_IN_SERIES =
    "Enter number of questions you want to do in series. The number must be "
    "less than";
static const QString VALUE = "Value";
static const QString ANSWER = "Answer";
static const QString LIST_OF_TAGS_FROM_DATABASE = "List of tags from databse";
static const QString RANDOM_QUESTION_LIST = "Random question list";
static const QString PLEASE_SELECT_OPTION = "Please select option";
static const QString CREATE = "Create";
static const QString SELECT_QUESTION = "Select question";
static const QString UPDATE_QUESTION = "Update selected question";
static const QString REMOVE_QUESTION = "Remove selected question";
static const QString ADD_TAG_TO_QUESTION = "Add tag to selected question";
static const QString REMOVE_TAG_FROM_QUESTION =
    "Remove tag from selected question";
static const QString EXIT = "Exit";
static const QString QUESTION_MENU = "QUESTION MENU";
static const QString INFO_SELECT_QUESTION = "To select question, choose number";
static const QString INFO_FIRST_SELECT_QUESTION = "Select question first";
static const QString INFO_SELECTED_QUESTION = "Currently selected question";
static const QString EMPTY_LIST_RELATED_TAGS_WITH_QUESTION =
    "I have nothing to do here, the list of connected tags with a question is "
    "empty.";
static const QString INFO_ARE_YOU_SURE_TO_REMOVE_QUESTION =
    "Are you sure do you want to remove selected question? If yes push (Y).";
static const QString INFO_SELECT_TAG_TO_REMOVE_FROM_QUESTION =
    "Select tag from the list below to remove it from the quesiton.\n";
static const QString TAG_HAS_BEEN_REMOVED = "Tag has been removed";
static const QString LIST_OF_QUESTIONS = "List of questions";
static const QString LIST_OF_TAGS = "List of tags";
static const QString NO_TAGS = "No tags";
static const QString NO_QUESTIONS = "No questions";
static const QString ALREADY_HAVING_TAG =
    "This question already having this same tag";
static const QString QUESTION_UPDATED = "Question has been sucessfully updated";

static const QString TAG_MENU = "TAG MENU";
static const QString SELECT_TAG = "Select tag";
static const QString SET_NEW_TAG = "Set new tag";
static const QString UPDATE_TAG = "Update selected tag";
static const QString REMOVE_SELECTED_TAG = "Remove selected tag";
static const QString ADD_QUESTION_TO_TAG = "Add question to selected tag";
static const QString REMOVE_QUESTION_FROM_TAG =
    "Remove question from selected tag";
static const QString CURRENTLY_SELECTED_TAG = "Currently selected tag";
static const QString INFO_SELECT_TAG_TO_ADD_QUESTION =
    "Select tag from the list below to add the question";
static const QString TAG_UPDATE_SUCCESFULLY = "Tag updated succesfully";
static const QString SELECT_QUESTION_TO_REMOVE_FROM_TAG =
    "Select the qestion to remove from below list available questios";
static const QString EMPTY_LIST_RELATED_QUESTIONS_WITH_TAG =
    "I have nothing to do here, the list of connected questions with a tag is "
    "empty.";
static const QString REMOVED_RELATION_QUESTION_AND_TAG_SUCCESFULLY =
    "Removing relation of the question with the tag has been succesfully "
    "finished";
static const QString TAG_ALREADY_CONNECTED_WITH_QUESTION =
    "Selected question is already related with this tag";
static const QString FIELD_TAG_CANT_EMPTY = "The tag field can't be empty.";
static const QString FIELD_VALUE_CANT_EMPTY = "The value field can't be empty.";
static const QString FIELD_ANSWER_CANT_EMPTY =
    "The answer field can't be empty.";
static const QString TAG_FROM_COMBO_BOX_SHOULD_BE_SELECTED =
    "Tag from combo box should be selected";
static const QString SELECT_TAG_FROM_QUESTION =
    "Tag from question should be selected.";
static const QString SELECT_QUESTION_FIRST = "Quest should be selected.";
static const QString RELATION_QUESTION_WIT_TAG_CREATED =
    "Relation between question and tag was corectly created.";
#endif
