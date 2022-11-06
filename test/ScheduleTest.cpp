#ifndef SCHEDULETEST_H
#define SCHEDULETEST_H

#include <string>

#include "gtest/gtest.h"
#include "Schedule.hpp"


TEST(Schedule, loadSchedule) {
    auto s = Schedule::loadSchedule();
    ASSERT_NE(s.events.size(), 0);
    ASSERT_NE(s.summary, "");
}

TEST(Schedule, convertToISODateTime) {
    std::string date = "27.02.2023";
    std::string time = "12:20:00";
    ASSERT_NO_THROW(Schedule::toISODatetime(date, time));
    std::string datetime = Schedule::toISODatetime(date, time);
    ASSERT_NE(datetime, "");
}

#endif /* SCHEDULETEST_H */