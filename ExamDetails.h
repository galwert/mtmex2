//
// Created by galwe on 05/06/2021.
using namespace std::string;
#ifndef HW2_EXAMDETAILS_H
#define HW2_EXAMDETAILS_H


class ExamDetails
{
private:
    int course_number;
    int test_month;
    int test_day;
    int test_hour;
    enum minute{0,30} test_minute;
    int length;
    string link;
};
#endif //HW2_EXAMDETAILS_H
