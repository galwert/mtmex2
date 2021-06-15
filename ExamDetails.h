#ifndef HW2_EXAMDETAILS_H
#define HW2_EXAMDETAILS_H

#include <iostream>
#include "string"
namespace mtm
{
    class ExamDetails
    {
    public:
        int course_number;
        int test_month;
        int test_day;
        double test_hour;
        int length;
        std::string link;

        class InvalidDateException{};
        class InvalidTimeException{};
        class InvalidArgException {};

        ExamDetails(int course_number, int test_month, int test_day,
                    double test_hour, int length, std::string &&link = std::string());

        ~ExamDetails() = default;

        ExamDetails(const ExamDetails &exam_details);

        ExamDetails &operator=(const ExamDetails &exam_details) = default;

        std::string getLink() const;

        bool operator<(const ExamDetails &exam_details) const;

        void setLink(std::string link1);

        int operator-(const ExamDetails &exam_details) const;

        friend std::ostream &operator<<(std::ostream &os, const ExamDetails &c);

        static ExamDetails makeMatamExam();
    };
}
#endif //HW2_EXAMDETAILS_H
