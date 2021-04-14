// Copyright 2021 VesenniyPriziv

#include <gtest/gtest.h>

#include "scheduleMaker.hpp"

TEST(EmtpyTest, EmtpyTest) {
  LessonBuilder LB;
  AcademicPlan myAcademicPlan;
  ScheduleBuilder myScheduleBuilder(LB, myAcademicPlan);
  Algorithm myAlgorithm(myAcademicPlan, myScheduleBuilder);
  myAlgorithm.Run();

  EXPECT_TRUE(true);
}
