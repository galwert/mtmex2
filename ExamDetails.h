//
// Created by galwe on 05/06/2021.
#include <iostream>
#include <string>
using std::string;
#ifndef HW2_EXAMDETAILS_H
#define HW2_EXAMDETAILS_H

class ExamDetails
{
private:
    int course_number;
    int test_month;
    int test_day;
    double test_hour;
    int length;
    string link;
public:
    ExamDetails(int course_number, int test_month, int test_day,
                double test_hour,int length, string& link);
    ~ExamDetails()=default;
    ExamDetails(const ExamDetails& exam_details);
    ExamDetails& operator=(const ExamDetails& exam_details)=default;
    string getLink();
    bool operator<
    void setLink(string& link1);
    friend int operator-(const ExamDetails& exam_details1, const ExamDetails& exam_details2);
    friend std::ostream& operator<<(std::ostream& os, const ExamDetails& c);
    static ExamDetails makeMatamExam();
};
#endif //HW2_EXAMDETAILS_H
