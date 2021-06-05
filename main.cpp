#include <iostream>
#include "ExamDetails.h"
using namespace std;
int main() {
    ExamDetails exam1 = ExamDetails::makeMatamExam();
    ExamDetails exam2(104032, 7, 11, 9.5, 3);
    ExamDetails exam3 = exam1;
    cout << "the difference between MATAM and infi 2m is " << (exam1-exam2) << " days";
    ExamDetails& closest = (exam1 < exam2) ? exam1 : exam2;
    cout << "your closest exam is:" << endl << closest << endl;
}
