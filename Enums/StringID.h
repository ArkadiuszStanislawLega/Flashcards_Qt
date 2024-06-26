#ifndef STRINGID_H
#define STRINGID_H
enum class StringID {
  ColumnAnswer,
  ColumnId,
  ColumnIsActive,
  ColumnTag,
  ColumnTagId,
  ColumnValue,
  ColumnQuestionId,
  ConnectionOk,
  DatabaseName,
  ErrorCantFindQuestion,
  ErrorConnectionWithDatabase,
  ErrorDatabase,
  ErrorPointerToTagEmpty,
  ErrorPointerToTagAndQuestionEmpty,
  ErrorPointerToQuestionEmpty,
  ErrorPropertyIdInTagZero,
  ErrorPropertyIdInQuestionZero,
  ErrorPropertyValueIsEmpty,
  ErrorPropertyAnswerIsEmpty,
  ErrorQueryFailed,
  FieldAnswerCantEmpty,
  FieldTagCantEmpty,
  FieldValueCantEmpty,
  InfoFirstSelectQuestion,
  QuestionCreatedCorrectly,
  QuestionSuccesfullyRemoved,
  QuestionUpdated,
  RemoveRelationQuestionAndTagSuccesfull,
  RemoveTagFromQuestion,
  RelationBetweenTagAndQuestionCreated,
  SelectQuestionFirst,
  SelectTagFirst,
  SelectTagFromQuestion,
  SettingsFilename,
  TableQuestions,
  TableQuestionsTags,
  TableTags,
  TagCreatedCorrectly,
  TagFromComboBoxShlouldBeSelected,
  TagSuccesfullyRemoved,
  TagUpdateSuccesfully,
  TheQueryFailed,
};
#endif
