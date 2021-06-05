//
// Created by galwe on 05/06/2021.
//
#include "ExamDetails.h"

#include <utility>
using namespace std;
ExamDetails::ExamDetails(int course_number, int test_month, int test_day,
            double test_hour,int length, string&& link)
{
    this->length=length;
    this->course_number=course_number;
    this->test_day=test_day;
    this->test_month=test_month;
    this->test_hour=test_hour;
    this->link=link;
}
/*ExamDetails::~ExamDetails()
{
    delete[] this->link.data();
    delete this;
}*/
ExamDetails::ExamDetails(const ExamDetails& exam_details)
{
    this->length=exam_details.length;
    this->course_number=exam_details.course_number;
    this->test_day=exam_details.test_day;
    this->test_month=exam_details.test_month;
    this->test_hour=exam_details.test_hour;
    this->link=exam_details.link;
}
/*
ExamDetails& ExamDetails::operator=(const ExamDetails& exam_details)= default;
{
    this->length=exam_details.length;
    this->course_number=exam_details.course_number;
    this->test_day=exam_details.test_day;
    this->test_month=exam_details.test_month;
    this->test_hour=exam_details.test_hour;
    this->link=exam_details.link;
    return *this;
}
*/
string ExamDetails::getLink()
{
    return this->link;
}
void ExamDetails::setLink(string& link1)
{
    this->link=link1;
}
int ExamDetails::operator-(const ExamDetails& exam_details) const
{
    return (this->test_month-exam_details.test_month)*30+this->test_day-exam_details.test_day;
}
bool ExamDetails::operator<(const ExamDetails& exam_details) const
{
    if(this->test_month==exam_details.test_month)
    {
        return this->test_day<exam_details.test_day;
    }
    return this->test_month<exam_details.test_month;

}
ostream& operator<<(ostream& os, const ExamDetails& examDetails)
{
    os << "Course Number: "<<examDetails.course_number<<endl;
    os << "Time: "<<examDetails.test_day<<"."<<examDetails.test_month;
    os<< " at "<<(int)examDetails.test_hour<<":"<<60*(examDetails.test_hour-(int)examDetails.test_hour)<<endl;
    os<<"Duration: "<<examDetails.length<<":00"<<endl;
    os<<"Zoom Link:"<<examDetails.link<<endl;
    return os;
}
ExamDetails ExamDetails::makeMatamExam()
{
    return ExamDetails(234124, 7, 28, (double)13, 3, (string &&) "https://tinyurl.com/59hzps6m");
}