#include "subjectcontroller.h"

#include "subject.h"

void SubjectController::index() {
  auto subjectList = Subject::getAll();
  texport(subjectList);
  render();
}

void SubjectController::show(const QString &id) {
  auto subject = Subject::get(id.toInt());
  texport(subject);
  render();
}

void SubjectController::create() {
  switch (httpRequest().method()) {
    case Tf::Get:
      render();
      break;

    case Tf::Post: {
      auto subject = httpRequest().formItems("subject");
      auto model = Subject::create(subject);

      if (!model.isNull()) {
        QString notice = "Created successfully.";
        tflash(notice);
        redirect(urla("show", model.id()));
      } else {
        QString error = "Failed to create.";
        texport(error);
        texport(subject);
        render();
      }
      break;
    }

    default:
      renderErrorResponse(Tf::NotFound);
      break;
  }
}

void SubjectController::save(const QString &id) {
  switch (httpRequest().method()) {
    case Tf::Get: {
      auto model = Subject::get(id.toInt());
      if (!model.isNull()) {
        auto subject = model.toVariantMap();
        texport(subject);
        render();
      }
      break;
    }

    case Tf::Post: {
      QString error;
      auto model = Subject::get(id.toInt());

      if (model.isNull()) {
        error =
            "Original data not found. It may have been updated/removed by "
            "another transaction.";
        tflash(error);
        redirect(urla("save", id));
        break;
      }

      auto subject = httpRequest().formItems("subject");
      model.setProperties(subject);
      if (model.save()) {
        QString notice = "Updated successfully.";
        tflash(notice);
        redirect(urla("show", model.id()));
      } else {
        error = "Failed to update.";
        texport(error);
        texport(subject);
        render();
      }
      break;
    }

    default:
      renderErrorResponse(Tf::NotFound);
      break;
  }
}

void SubjectController::remove(const QString &id) {
  if (httpRequest().method() != Tf::Post) {
    renderErrorResponse(Tf::NotFound);
    return;
  }

  auto subject = Subject::get(id.toInt());
  subject.remove();
  redirect(urla("index"));
}

// Don't remove below this line
T_DEFINE_CONTROLLER(SubjectController)
