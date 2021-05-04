#include "teachercontroller.h"
#include "teacher.h"


void TeacherController::index()
{
    auto teacherList = Teacher::getAll();
    texport(teacherList);
    render();
}

void TeacherController::show(const QString &id)
{
    auto teacher = Teacher::get(id.toInt());
    texport(teacher);
    render();
}

void TeacherController::create()
{
    switch (httpRequest().method()) {
    case Tf::Get:
        render();
        break;

    case Tf::Post: {
        auto teacher = httpRequest().formItems("teacher");
        auto model = Teacher::create(teacher);

        if (!model.isNull()) {
            QString notice = "Created successfully.";
            tflash(notice);
            redirect(urla("show", model.id()));
        } else {
            QString error = "Failed to create.";
            texport(error);
            texport(teacher);
            render();
        }
        break; }

    default:
        renderErrorResponse(Tf::NotFound);
        break;
    }
}

void TeacherController::save(const QString &id)
{
    switch (httpRequest().method()) {
    case Tf::Get: {
        auto model = Teacher::get(id.toInt());
        if (!model.isNull()) {
            auto teacher = model.toVariantMap();
            texport(teacher);
            render();
        }
        break; }

    case Tf::Post: {
        QString error;
        auto model = Teacher::get(id.toInt());
        
        if (model.isNull()) {
            error = "Original data not found. It may have been updated/removed by another transaction.";
            tflash(error);
            redirect(urla("save", id));
            break;
        }

        auto teacher = httpRequest().formItems("teacher");
        model.setProperties(teacher);
        if (model.save()) {
            QString notice = "Updated successfully.";
            tflash(notice);
            redirect(urla("show", model.id()));
        } else {
            error = "Failed to update.";
            texport(error);
            texport(teacher);
            render();
        }
        break; }

    default:
        renderErrorResponse(Tf::NotFound);
        break;
    }
}

void TeacherController::remove(const QString &id)
{
    if (httpRequest().method() != Tf::Post) {
        renderErrorResponse(Tf::NotFound);
        return;
    }

    auto teacher = Teacher::get(id.toInt());
    teacher.remove();
    redirect(urla("index"));
}


// Don't remove below this line
T_DEFINE_CONTROLLER(TeacherController)
