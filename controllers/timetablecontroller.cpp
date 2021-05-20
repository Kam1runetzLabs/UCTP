#include "timetablecontroller.h"

#include "block.h"
#include "classroom.h"
#include "group.h"
#include "subject.h"
#include "teacher.h"
#include "timeslot.h"
#include "timetable.h"

void TimetableController::index() {
  auto timetableList = Timetable::getAll();
  QList<TimeSlot> timeSlots;
  QList<Classroom> classrooms;
  Block block;
  QList<Group> groups;
  QList<Teacher> teachers;
  QList<Subject> subjects;
  for (auto const &timetable : timetableList) {
    timeSlots.append(TimeSlot::get(timetable.timeId()));
    classrooms.append(Classroom::get(timetable.timeId()));
    block = Block::get(timetable.blockId());
    groups.append(Group::get(block.groupId()));
    teachers.append(Teacher::get(block.teacherId()));
    subjects.append(Subject::get(block.subjectId()));
  }
  texport(timetableList);
  texport(timeSlots);
  texport(classrooms);
  texport(groups);
  texport(teachers);
  texport(subjects);
  render();
}

void TimetableController::show(const QString &id) {
  auto timetable = Timetable::get(id.toInt());
  texport(timetable);
  render();
}

void TimetableController::create() {
  switch (httpRequest().method()) {
    case Tf::Get:
      render();
      break;

    case Tf::Post: {
      auto blockList = Block::getAll();
      auto classroomList = Classroom::getAll();
      auto timeSlotList = TimeSlot::getAll();

      QList<Timetable> timetableList;
      auto status = Timetable::calculate(blockList, classroomList, timeSlotList,
                                         timetableList);
      if (!status.ok()) {
        QString error = "unable to create timetable";
        tflash(error);
        break;
      }
      texport(timetableList);
      redirect(urla("index"));
      break;
    }

    default:
      renderErrorResponse(Tf::NotFound);
      break;
  }
}

void TimetableController::removeAll() {
  auto timetableList = Timetable::getAll();
  for (auto obj : timetableList) {
    obj.remove();
  }
  redirect(urla("index"));
}

// Don't remove below this line
T_DEFINE_CONTROLLER(TimetableController)
