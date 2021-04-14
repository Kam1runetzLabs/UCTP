// Copyright 2021 VesenniyPriziv

#include <gtest/gtest.h>

#include "scheduleMaker.hpp"

// GeneralBuilderTests
class ScheduleMakerGeneralBuilderTest : public ::testing::Test
{
 protected:
  GeneralLessonBuilder genLessonBuilder;
  GeneralLessonConstructor genLessonConstructor;

  std::vector<Lesson> schedule;
  std::vector<Teacher> availableTeacher;
  Teacher* myTeacher = nullptr;

  std::vector<Auditory> availableAuditory;
  Auditory* myAuditory = nullptr;

  virtual void SetUp()
  {
    genLessonConstructor.setLessonBuilder(&genLessonBuilder);

    myTeacher = new Teacher;
    myTeacher->teacherId = 7;
    myAuditory = new Auditory;
    myAuditory->auditoryId = 1;
    availableAuditory.push_back(*myAuditory);
    availableTeacher.push_back(*myTeacher);
  }

  virtual void TearDown()
  {
    delete myTeacher;
    delete myAuditory;
  }
};

TEST_F(ScheduleMakerGeneralBuilderTest, GeneralLessonBuilderAddingTime) {
  genLessonBuilder.timeAdd(schedule);

  EXPECT_EQ(genLessonBuilder.getLesson().lessonNumber, 1);
  EXPECT_EQ(genLessonBuilder.getLesson().dayOfWeek, 1);
}

TEST_F(ScheduleMakerGeneralBuilderTest, GeneralLessonBuilderAddingTeacher) {
  genLessonBuilder.teacherAdd(schedule, availableTeacher);

  EXPECT_EQ(genLessonBuilder.getLesson().firstTeacher.teacherId, myTeacher->teacherId);
}

TEST_F(ScheduleMakerGeneralBuilderTest, GeneralLessonBuilderAddingAuditory) {
  genLessonBuilder.auditoryAdd(schedule, availableAuditory);

  EXPECT_EQ(genLessonBuilder.getLesson().firstAuditory.auditoryId, myAuditory->auditoryId);
}

// TwoTeachersBuilderTests
class ScheduleMakerTwoTeachersBuilderTest : public ::testing::Test
{
 protected:
  TwoTeachersLessonBuilder TTLessonBuilder;
  TwoTeachersLessonConstructor TTLessonConstructor;

  std::vector<Lesson> schedule;
  std::vector<Teacher> availableTeacher;
  Teacher* myTeacher = nullptr;

  std::vector<Auditory> availableAuditory;
  Auditory* myAuditory = nullptr;

  virtual void SetUp()
  {
    TTLessonConstructor.setLessonBuilder(&TTLessonBuilder);

    myTeacher = new Teacher;
    myTeacher->teacherId = 7;
    myAuditory = new Auditory;
    myAuditory->auditoryId = 1;
    availableAuditory.push_back(*myAuditory);
    availableTeacher.push_back(*myTeacher);
  }

  virtual void TearDown()
  {
    delete myTeacher;
    delete myAuditory;
  }
};

TEST_F(ScheduleMakerTwoTeachersBuilderTest, TwoTeachersLessonBuilderAddingTime) {
  TTLessonBuilder.timeAdd(schedule);

  EXPECT_EQ(TTLessonBuilder.getLesson().lessonNumber, 1);
  EXPECT_EQ(TTLessonBuilder.getLesson().dayOfWeek, 1);
}

TEST_F(ScheduleMakerTwoTeachersBuilderTest, TwoTeachersLessonBuilderAddingTeacher) {
  TTLessonBuilder.teacherAdd(schedule, availableTeacher);

  EXPECT_EQ(TTLessonBuilder.getLesson().firstTeacher.teacherId, myTeacher->teacherId);
}

TEST_F(ScheduleMakerTwoTeachersBuilderTest, TwoTeachersLessonBuilderAddingSecondTeacher) {
  TTLessonBuilder.secondTeacherAdd(schedule, availableTeacher);

  EXPECT_EQ(TTLessonBuilder.getLesson().secondTeacher.teacherId, myTeacher->teacherId);
}

TEST_F(ScheduleMakerTwoTeachersBuilderTest, TwoTeachersLessonBuilderAddingAuditory) {
  TTLessonBuilder.auditoryAdd(schedule, availableAuditory);

  EXPECT_EQ(TTLessonBuilder.getLesson().firstAuditory.auditoryId, myAuditory->auditoryId);
}

TEST_F(ScheduleMakerTwoTeachersBuilderTest, TwoTeachersLessonBuilderAddingSecondAuditory) {
  TTLessonBuilder.secondAuditoryAdd(schedule, availableAuditory);

  EXPECT_EQ(TTLessonBuilder.getLesson().secondAuditory.auditoryId, myAuditory->auditoryId);
}
