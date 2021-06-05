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
                double test_hour,int length, string&& link=string());
    ~ExamDetails()=default;
    ExamDetails(const ExamDetails& exam_details);
    ExamDetails& operator=(const ExamDetails& exam_details)=default;
    string getLink();
    bool operator<(const ExamDetails& exam_details) const;
    void setLink(string& link1);
    int operator-(const ExamDetails& exam_details) const;
    friend std::ostream& operator<<(std::ostream& os, const ExamDetails& c);
    static ExamDetails makeMatamExam();
};
#endif //HW2_EXAMDETAILS_H
