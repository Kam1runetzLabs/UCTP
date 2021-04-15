// Copyright 2021 VesenniyPriziv

#include "scheduleMaker.hpp"

#include <utility>

// GeneralLessonBuilder
void GeneralLessonBuilder::timeAdd(std::vector<Lesson> schedule) {
  if (schedule.empty()) {
    lesson.dayOfWeek = 1;
  }
  lesson.dayOfWeek = 1;
  lesson.lessonNumber = 1;
}

void GeneralLessonBuilder::teacherAdd(std::vector<Lesson> schedule,
                                      std::vector<Teacher> availableTeacher) {
  if (schedule.empty()) {
    lesson.firstTeacher.teacherId = 9;
  }
  if (!availableTeacher.empty()) {
    lesson.firstTeacher = availableTeacher[0];
  }
}

void GeneralLessonBuilder::auditoryAdd(
    std::vector<Lesson> schedule, std::vector<Auditory> availableAuditory) {
  if (schedule.empty() && availableAuditory.empty()) {
    lesson.firstTeacher.teacherId = 9;
  }
  if (!availableAuditory.empty()) {
    lesson.firstAuditory = availableAuditory[0];
  }
}

Lesson GeneralLessonBuilder::getLesson() { return lesson; }

// TwoTeachersLessonBuilder
void TwoTeachersLessonBuilder::timeAdd(std::vector<Lesson> schedule) {
  if (schedule.empty()) {
    lesson.dayOfWeek = 1;
  }
  lesson.dayOfWeek = 1;
  lesson.lessonNumber = 1;
}

void TwoTeachersLessonBuilder::teacherAdd(
    std::vector<Lesson> schedule, std::vector<Teacher> availableTeacher) {
  if (schedule.empty()) {
    lesson.firstTeacher.teacherId = 7;
  }
  if (!availableTeacher.empty()) {
    lesson.firstTeacher = availableTeacher[0];
  }
}

void TwoTeachersLessonBuilder::auditoryAdd(
    std::vector<Lesson> schedule, std::vector<Auditory> availableAuditory) {
  if (schedule.empty() && availableAuditory.empty()) {
    lesson.dayOfWeek = 1;
  }
  if (!availableAuditory.empty()) {
    lesson.firstAuditory = availableAuditory[0];
  }
}

void TwoTeachersLessonBuilder::secondTeacherAdd(
    std::vector<Lesson> schedule, std::vector<Teacher> availableTeacher) {
  if (schedule.empty()) {
    lesson.secondTeacher.teacherId = 9;
  }
  if (!availableTeacher.empty()) {
    lesson.secondTeacher = availableTeacher[0];
  }
}

void TwoTeachersLessonBuilder::secondAuditoryAdd(
    std::vector<Lesson> schedule, std::vector<Auditory> availableAuditory) {
  if (schedule.empty() && availableAuditory.empty()) {
    lesson.secondAuditory.auditoryId = 9;
  }
  if (!availableAuditory.empty()) {
    lesson.secondAuditory = availableAuditory[0];
  }
}

Lesson TwoTeachersLessonBuilder::getLesson() { return lesson; }

// GeneralLessonConstructor
void GeneralLessonConstructor::setLessonBuilder(
    GeneralLessonBuilder* myLessonBuilder) {
  m_builder = myLessonBuilder;
}

Lesson GeneralLessonConstructor::ConstructLesson(
    std::vector<Lesson> schedule, std::vector<Auditory> availableAuditory,
    std::vector<Teacher> availableTeacher) {
  m_builder->timeAdd(schedule);
  m_builder->auditoryAdd(schedule, availableAuditory);
  m_builder->teacherAdd(schedule, availableTeacher);
  return m_builder->getLesson();
}

// TwoTeachersLessonConstructor
void TwoTeachersLessonConstructor::setLessonBuilder(
    TwoTeachersLessonBuilder* myLessonBuilder) {
  m_builder = myLessonBuilder;
}

Lesson TwoTeachersLessonConstructor::ConstructLesson(
    std::vector<Lesson> schedule, std::vector<Auditory> availableAuditory,
    std::vector<Teacher> availableTeacher) {
  m_builder->timeAdd(schedule);
  m_builder->auditoryAdd(schedule, availableAuditory);
  m_builder->secondAuditoryAdd(schedule, availableAuditory);
  m_builder->teacherAdd(schedule, availableTeacher);
  m_builder->secondTeacherAdd(schedule, availableTeacher);
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

Lesson LessonBuilder::ConstructLesson(std::vector<Lesson> schedule,
                                      std::vector<Auditory> availableAuditory,
                                      std::vector<Teacher> availableTeacher) {
  m_lesson = m_currentLessonConstructor->ConstructLesson(
      std::move(schedule), std::move(availableAuditory),
      std::move(availableTeacher));
  return m_lesson;
}

// ScheduleBuilder
void ScheduleBuilder::ConstructSchedule() {
  for (int i = 0; i < 2; ++i) {
    GeneralLessonBuilder generalLessonBuilder;
    m_lessonBuilder.setLessonBuilder(&generalLessonBuilder);
    GeneralLessonConstructor generalLessonConstructor;
    generalLessonConstructor.setLessonBuilder(&generalLessonBuilder);
    m_lessonBuilder.setLessonConstructor(&generalLessonConstructor);

    std::vector<Teacher> availableTeacher;
    std::vector<Auditory> availableAuditory;
    auto* newLesson = new Lesson;
    *newLesson = m_lessonBuilder.ConstructLesson(m_schedule, availableAuditory,
                                                 availableTeacher);
    m_schedule.push_back(*newLesson);
  }
}

std::vector<Lesson> ScheduleBuilder::getSchedule() { return m_schedule; }

// Main Algorithm
void Algorithm::Run() { m_scheduleBuilder.ConstructSchedule(); }
