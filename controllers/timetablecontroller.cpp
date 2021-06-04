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
      QSystemSemaphore semaphore("tt", 1);
      semaphore.acquire();
#ifndef Q_OS_WIN32
      // в linux/unix разделяемая память не освобождается при аварийном завершении приложения,
      // поэтому необходимо избавиться от данного мусора
      QSharedMemory nix_fix_shared_memory("tt2");
      if(nix_fix_shared_memory.attach()){
        nix_fix_shared_memory.detach();
      }
#endif
      QSharedMemory sharedMemory("tt2");
      bool is_running;
      if (sharedMemory.attach())
        is_running = true;
      else {
        sharedMemory.create(1);
        is_running = false;
      }
      semaphore.release();

      if(is_running){
        redirect(urla("index"));
        break;
      }

      auto params = httpRequest().formItems("params");
      int population = params.take("population").toInt();
      int iterations = params.take("iterations").toInt();

      auto blockList = Block::getAll();
      auto classroomList = Classroom::getAll();
      auto timeSlotList = TimeSlot::getAll();
      auto subjectsList = Subject::getAll();

      QList<Timetable> timetableList;
      auto status = Timetable::calculate(blockList, subjectsList, classroomList,
                                         timeSlotList, timetableList,
                                         population, iterations);
      if (!status.ok()) {
        QString error = status.error();
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
