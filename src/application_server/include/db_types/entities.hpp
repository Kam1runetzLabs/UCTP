#ifndef UCTP_ENTITIES_H
#define UCTP_ENTITIES_H

enum SubjectType {
  "lecture",
  "seminar",
  "lab",
  "pe"
};

struct Auditory {
  int id;
  SubjectType auditoryType;
  std::string name;
  int capacity;
};

struct Teacher {
  int id;
  std::string name;
  std::map<int, unordered_map<int>> unavailableTime;
};

struct Group {
  int id;
  int studentsNumber;
  int admissionYear;
  std::string code;
};

struct Subject {
  int id;
  std::string name;
  SubjectType subjectType;
};

struct Speciality {
  int id;
  std::string code;
  std::string name;
};

struct Department {
  int id;
  std::string code;
  std::string name;
};

struct AcademicPlan {
  int id;
  Subject subject;
  int lessonsNumber;
  std::vector<Group> groups;
  int auditoriesNumber;
  int teachersNumber;
  std::vector<Auditory> auditories;
  std::vector<Teacher> teachers;
};

struct StudyStream {
  int id;
  int semester;
  Speciality speciality;
  Department department;
  AcademicPlan academicPlan;
};

#endif  // UCTP_ENTITIES_H
