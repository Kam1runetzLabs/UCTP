// Copyright 2021 VesenniyPriziv

#ifndef INCLUDE_SCHEDULEMAKER_HPP
#define INCLUDE_SCHEDULEMAKER_HPP

#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#include "entities.hpp"

class ACurrentLessonBuilder {
 public:
  ACurrentLessonBuilder() = default;
  virtual ~ACurrentLessonBuilder() = default;
  virtual void timeAdd(std::vector<Lesson> m_schedule) = 0;
  virtual void teacherAdd() = 0;
  virtual void auditoryAdd() = 0;
};

class GeneralLessonBuilder : public ACurrentLessonBuilder {
 protected:
  Lesson lesson;
 public:
  explicit GeneralLessonBuilder(Lesson newLesson): lesson(newLesson){};
  ~GeneralLessonBuilder() override = default;
  void timeAdd(std::vector<Lesson> m_schedule) override;
  void teacherAdd() override {}
  void auditoryAdd() override{}
  Lesson getLesson();
};

class ILessonConstructor {
 public:
  virtual ~ILessonConstructor() = default;
  virtual Lesson ConstructLesson(
      std::vector<Lesson> m_schedule) = 0;
};

class GeneralLessonConstructor : public ILessonConstructor {
 protected:
  GeneralLessonBuilder* m_builder = nullptr;
 public:
  GeneralLessonConstructor() = default;
  ~GeneralLessonConstructor() override = default;
  void setLessonBuilder(GeneralLessonBuilder* myLessonBuilder);
  Lesson ConstructLesson(
      std::vector<Lesson> m_schedule) override;
};

class LessonBuilder {
  ACurrentLessonBuilder* m_currentLessonBuilder = nullptr;
  ILessonConstructor* m_currentLessonConstructor = nullptr;
  Lesson m_lesson;
  std::vector<Auditory> m_availableAuditory;
  std::vector<Teacher> m_availableTeacher;

 public:
  LessonBuilder() = default;

  void setLessonBuilder(ACurrentLessonBuilder* newLessonBuilder);
  void setLessonConstructor(ILessonConstructor* newLessonConstructor);
  void setAvailable(std::vector<Auditory> AvailableAuditory,
                    std::vector<Teacher> AvailableTeachers);
  Lesson ConstructLesson(std::vector<Lesson> m_schedule);
};

class ScheduleBuilder {
  LessonBuilder m_lessonBuilder;
  AcademicPlan m_academicPlan;
  std::vector<Lesson> m_schedule;

 public:
  ScheduleBuilder(LessonBuilder LessonBuilder, AcademicPlan AcademicPlan)
      : m_lessonBuilder(std::move(LessonBuilder)),
        m_academicPlan(AcademicPlan){};

  void ConstructSchedule();
  std::vector<Lesson> getSchedule();
};

class Algorithm {
  AcademicPlan m_academicPlan;
  ScheduleBuilder m_scheduleBuilder;

 public:
  Algorithm(const AcademicPlan& AcPlan, ScheduleBuilder mScheduleBuilder)
      : m_academicPlan(AcPlan), m_scheduleBuilder(std::move(mScheduleBuilder)) {
  };
  void Run();
};

#endif  // INCLUDE_SCHEDULEMAKER_HPP
