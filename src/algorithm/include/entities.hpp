// Copyright 2021 VesenniyPriziv

#ifndef INCLUDE_ENTITIES_HPP
#define INCLUDE_ENTITIES_HPP

struct Departmnet {};

struct AcademicPlan {};

struct Group {};

struct Subject {};

struct Teacher {
  int teacherId;
  std::string teacherName;
  std::vector<std::vector<int>> availableTime;
  std::vector<std::vector<int>> busySlots;
};

struct Auditory {
  int auditoryId;
  int type;
  std::string AuditoryName;
  int capacity;
  std::vector<std::vector<int>> busySlots;
};

struct Lesson {
  Teacher secondTeacher;
  Teacher firstTeacher;
  Auditory firstAuditory;
  Auditory secondAuditory;
  int lessonId{};
  Subject subject;
  Group group;
  int lessonNumber{};
  int dayOfWeek{};
  bool parity{};

  /*void Reset(Lesson newLesson) { *this = newLesson; }*/
};

#endif  // INCLUDE_ENTITIES_HPP
