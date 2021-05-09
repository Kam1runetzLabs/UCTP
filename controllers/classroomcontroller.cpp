#include "classroomcontroller.h"

#include "classroom.h"

void ClassroomController::index() {
  auto classroomList = Classroom::getAll();
  texport(classroomList);
  render();
}

void ClassroomController::show(const QString &id) {
  auto classroom = Classroom::get(id.toInt());
  texport(classroom);
  render();
}

void ClassroomController::create() {
  switch (httpRequest().method()) {
    case Tf::Get:
      render();
      break;

    case Tf::Post: {
      auto classroom = httpRequest().formItems("classroom");
      auto model = Classroom::create(classroom);

      if (!model.isNull()) {
        QString notice = "Created successfully.";
        tflash(notice);
        redirect(urla("show", model.id()));
      } else {
        QString error = "Failed to create.";
        texport(error);
        texport(classroom);
        render();
      }
      break;
    }

    default:
      renderErrorResponse(Tf::NotFound);
      break;
  }
}

void ClassroomController::save(const QString &id) {
  switch (httpRequest().method()) {
    case Tf::Get: {
      auto model = Classroom::get(id.toInt());
      if (!model.isNull()) {
        auto classroom = model.toVariantMap();
        texport(classroom);
        render();
      }
      break;
    }

    case Tf::Post: {
      QString error;
      auto model = Classroom::get(id.toInt());

      if (model.isNull()) {
        error =
            "Original data not found. It may have been updated/removed by "
            "another transaction.";
        tflash(error);
        redirect(urla("save", id));
        break;
      }

      auto classroom = httpRequest().formItems("classroom");
      model.setProperties(classroom);
      if (model.save()) {
        QString notice = "Updated successfully.";
        tflash(notice);
        redirect(urla("show", model.id()));
      } else {
        error = "Failed to update.";
        texport(error);
        texport(classroom);
        render();
      }
      break;
    }

    default:
      renderErrorResponse(Tf::NotFound);
      break;
  }
}

void ClassroomController::remove(const QString &id) {
  if (httpRequest().method() != Tf::Post) {
    renderErrorResponse(Tf::NotFound);
    return;
  }

  auto classroom = Classroom::get(id.toInt());
  classroom.remove();
  redirect(urla("index"));
}

// Don't remove below this line
T_DEFINE_CONTROLLER(ClassroomController)
