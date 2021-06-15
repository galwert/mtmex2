#include "ExamDetails.h"
#include <ostream>
#include <utility>

namespace mtm
{
    using std::cout;
    using std::string;
    using std::endl;

    ExamDetails::ExamDetails(int course_number, int test_month, int test_day,
                             double test_hour,int length, std::string&& link)
    {
        if(test_month < 1 || test_month > 12 || test_day < 1 || test_day > 30)
        {
            throw ExamDetails::InvalidDateException();
        }

        if((int)test_hour < 0 || (int)test_hour > 23)
        {
            throw ExamDetails::InvalidTimeException();
        }
        int hour_with_minutes = (int)(test_hour*10);
        if(hour_with_minutes % 10 != 0 && hour_with_minutes % 10 != 5)
        {
            throw ExamDetails::InvalidTimeException();
        }

        this->length=length;
        this->course_number=course_number;
        this->test_day=test_day;
        this->test_month=test_month;
        this->test_hour=test_hour;
        this->link=link;
    }

    ExamDetails::ExamDetails(const ExamDetails& exam_details)
    {
        this->length=exam_details.length;
        this->course_number=exam_details.course_number;
        this->test_day=exam_details.test_day;
        this->test_month=exam_details.test_month;
        this->test_hour=exam_details.test_hour;
        this->link=exam_details.link;
    }

    std::string ExamDetails::getLink() const
    {
        return this->link;
    }
    void ExamDetails::setLink(std::string link1)
    {
        this->link = link1;
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
    std::ostream& operator<<(std::ostream& os, const ExamDetails& exam_details)
    {
        bool time_zero = false;
        if(60*(exam_details.test_hour-(int)exam_details.test_hour) == 0)
        {
            time_zero = true;
        }
        os << "Course Number: "<<exam_details.course_number<<endl;
        os << "Time: "<<exam_details.test_day<<"."<<exam_details.test_month;
        if(!time_zero)
        {
            os << " at " << (int) exam_details.test_hour << ":"
               << 60 * (exam_details.test_hour - (int) exam_details.test_hour) << endl;
        }
        else
        {
            os << " at " << (int) exam_details.test_hour << ":00" << endl;
        }
        os<<"Duration: "<<exam_details.length<<":00"<<endl;
        os<<"Zoom Link: "<<exam_details.link<<endl;

        return os;
    }

    ExamDetails ExamDetails::makeMatamExam()
    {
        return ExamDetails(234124, 7, 28, (double)13, 3, (std::string &&) "https://tinyurl.com/59hzps6m");
    }
}
