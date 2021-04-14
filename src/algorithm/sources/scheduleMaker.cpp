// Copyright 2021 VesenniyPriziv

#include "scheduleMaker.hpp"

#include <utility>

// GeneralLessonBuilder
void GeneralLessonBuilder::timeAdd(std::vector<Lesson> m_schedule) {
  if (m_schedule.empty()) {
  }
}

Lesson GeneralLessonBuilder::getLesson() { return lesson; }

// GeneralLessonConstructor
void GeneralLessonConstructor::setLessonBuilder(
    GeneralLessonBuilder* myLessonBuilder) {
  m_builder = myLessonBuilder;
}

Lesson GeneralLessonConstructor::ConstructLesson(
    std::vector<Lesson> m_schedule) {
  m_builder->timeAdd(m_schedule);
  m_builder->auditoryAdd();
  m_builder->teacherAdd();
  return m_builder->getLesson();
}

// LessonBuilder
void LessonBuilder::setLessonBuilder(ACurrentLessonBuilder* newLessonBuilder) {
  m_currentLessonBuilder = newLessonBuilder;
}

void LessonBuilder::setLessonConstructor(
    ILessonConstructor* newLessonConstructor) {
  m_currentLessonConstructor = newLessonConstructor;
}

void LessonBuilder::setAvailable(std::vector<Auditory> AvailableAuditory,
                                 std::vector<Teacher> AvailableTeachers) {
  m_availableAuditory = std::move(AvailableAuditory);
  m_availableTeacher = std::move(AvailableTeachers);
}

Lesson LessonBuilder::ConstructLesson(
    std::vector<Lesson> m_schedule) {
  m_lesson = m_currentLessonConstructor->ConstructLesson(std::move(m_schedule));
  return m_lesson;
}

// ScheduleBuilder
void ScheduleBuilder::ConstructSchedule() {
  for (int i = 0; i < 2; ++i) {
    auto* newLesson = new Lesson;
    GeneralLessonBuilder generalLessonBuilder(*newLesson);
    m_lessonBuilder.setLessonBuilder(&generalLessonBuilder);
    GeneralLessonConstructor generalLessonConstructor;
    generalLessonConstructor.setLessonBuilder(&generalLessonBuilder);
    m_lessonBuilder.setLessonConstructor(&generalLessonConstructor);
    m_lessonBuilder.ConstructLesson(m_schedule);
    m_schedule.push_back(*newLesson);
  }
}

std::vector<Lesson> ScheduleBuilder::getSchedule() { return m_schedule; }

// Main Algorithm
void Algorithm::Run() { m_scheduleBuilder.ConstructSchedule(); }