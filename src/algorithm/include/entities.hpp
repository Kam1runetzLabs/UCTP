// Copyright 2021 VesenniyPriziv

#ifndef INCLUDE_ENTITIES_HPP
#define INCLUDE_ENTITIES_HPP

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
  /*void Reset(Lesson newLesson) { *this = newLesson; }*/
};

#endif  // INCLUDE_ENTITIES_HPP
