/*
// Copyright 2021 VesenniyPriziv

#include <iostream>
#include <memory>
#include <utility>
#include <vector>

struct AcademicPlan {};
struct Group {};
struct Subject {};
struct Teacher {};
struct Auditory {};
struct Lesson {
  Teacher secondTeacher;
  Teacher firstTeacher;
  Auditory firstAuditory;
  Auditory secondAuditory;
  int lessonId;
  Subject subject;
  Group group;
  int lessonNumber;
  int dayOfWeek;
  bool parity;

  void Reset(Lesson newLesson) { *this = newLesson; }

  */
/*void SetTime(int newLessonId, int newLessonNumber, bool newParity) {
      lessonId = newLessonId;
      lessonNumber = newLessonNumber;
      parity = newParity;
  };
  void SetAuditory(Auditory& newAuditory) {
    firstAuditory = newAuditory;
  }*//*

};

class ACurrentLessonBuilder {
 protected:
  std::shared_ptr<Lesson> lesson;

 public:
  ACurrentLessonBuilder() = default;
  virtual ~ACurrentLessonBuilder() = default;
  virtual void timeAdd(std::vector<Lesson> m_schedule) = 0;
  virtual void teacherAdd() = 0;
  virtual void auditoryAdd() = 0;
  virtual void createNewLesson() = 0;
  std::shared_ptr<Lesson> getLesson() { return lesson; }
};

class GeneralLessonBuilder : public ACurrentLessonBuilder {
 public:
  GeneralLessonBuilder(){};
  ~GeneralLessonBuilder() override{};
  void createNewLesson() override { lesson->Reset(*new Lesson); }
  void timeAdd(std::vector<Lesson> m_schedule) override {
    if (m_schedule.empty()) {
    }
  };
  void teacherAdd() override {}
  void auditoryAdd() override{};
};

class LessonBuilder {
  ACurrentLessonBuilder* m_currentLessonBuilder;
  std::shared_ptr<Lesson> m_lesson;
  std::vector<Auditory> m_availibleAuditory;
  std::vector<Teacher> m_availibleTeacher;

 public:
  LessonBuilder(){};
  void setLessonBuilder(ACurrentLessonBuilder* newLessonBuilder) {
    m_currentLessonBuilder = newLessonBuilder;
  }

  std::shared_ptr<Lesson> ConstructLesson(std::vector<Lesson> m_shedule) {
    m_currentLessonBuilder->createNewLesson();
    m_currentLessonBuilder->timeAdd(m_shedule);
    m_currentLessonBuilder->auditoryAdd();
    m_currentLessonBuilder->teacherAdd();
    return m_lesson;
  }
};

class ShedlueBuilder {
  LessonBuilder m_lessonBuilder;
  AcademicPlan m_academicPlan;
  std::vector<Lesson> m_shedule;

 public:
  ShedlueBuilder(LessonBuilder LessonBuilder, AcademicPlan AcademicPlan)
      : m_lessonBuilder(LessonBuilder), m_academicPlan(AcademicPlan){};

  void ConstructShedule() {
    GeneralLessonBuilder generalLessonBuilder;
    m_lessonBuilder.setLessonBuilder(&generalLessonBuilder);
    std::shared_ptr<Lesson> newLesson =
        m_lessonBuilder.ConstructLesson(m_shedule);
    m_shedule.push_back(*newLesson);
  };

  std::vector<Lesson> getShedule() { return m_shedule; }
};

class Algorithm {
  AcademicPlan m_academicPlan;
  ShedlueBuilder m_sheduleBuilder;

 public:
  Algorithm(AcademicPlan AcPlan, ShedlueBuilder shedlueBuilder)
      : m_academicPlan(AcPlan), m_sheduleBuilder(shedlueBuilder){};
  void Run() { m_sheduleBuilder.ConstructShedule(); };
};*/
