// Copyright 2021 VesenniyPriziv

#include <gtest/gtest.h>

#include "scheduleMaker.hpp"

TEST(ScheduleMakerConstructorTest, GeneralLessonConstructorTest) {
  GeneralLessonBuilder genLessonBuilder;
  GeneralLessonConstructor genLessonConstructor;
  genLessonConstructor.setLessonBuilder(&genLessonBuilder);

  std::vector<Lesson> schedule;
  std::vector<Teacher> availableTeacher;
  auto* myTeacher = new Teacher;
  myTeacher->teacherId = 7;
  availableTeacher.push_back(*myTeacher);

  std::vector<Auditory> availableAuditory;
  auto* myAuditory = new Auditory;
  myAuditory->auditoryId = 1;
  availableAuditory.push_back(*myAuditory);

  Lesson myLesson = genLessonConstructor.ConstructLesson(
      schedule, availableAuditory, availableTeacher);

  EXPECT_EQ(myLesson.lessonNumber, 1);
  EXPECT_EQ(myLesson.dayOfWeek, 1);
  EXPECT_EQ(myLesson.firstTeacher.teacherId, myTeacher->teacherId);
  EXPECT_EQ(myLesson.firstAuditory.auditoryId, myAuditory->auditoryId);

  delete myAuditory;
  delete myTeacher;
}

TEST(ScheduleMakerConstructorTest, TwoTeachersLessonConstructorTest) {
  TwoTeachersLessonBuilder TTLessonBuilder;
  TwoTeachersLessonConstructor TTLessonConstructor;
  TTLessonConstructor.setLessonBuilder(&TTLessonBuilder);

  std::vector<Lesson> schedule;
  std::vector<Teacher> availableTeacher;
  auto* myTeacher = new Teacher;
  myTeacher->teacherId = 7;
  availableTeacher.push_back(*myTeacher);

  std::vector<Auditory> availableAuditory;
  auto* myAuditory = new Auditory;
  myAuditory->auditoryId = 1;
  availableAuditory.push_back(*myAuditory);

  Lesson myLesson = TTLessonConstructor.ConstructLesson(
      schedule, availableAuditory, availableTeacher);

  EXPECT_EQ(myLesson.lessonNumber, 1);
  EXPECT_EQ(myLesson.dayOfWeek, 1);
  EXPECT_EQ(myLesson.firstTeacher.teacherId, myTeacher->teacherId);
  EXPECT_EQ(myLesson.firstAuditory.auditoryId, myAuditory->auditoryId);
  EXPECT_EQ(myLesson.secondTeacher.teacherId, myTeacher->teacherId);
  EXPECT_EQ(myLesson.secondAuditory.auditoryId, myAuditory->auditoryId);

  delete myTeacher;
  delete myAuditory;
}
