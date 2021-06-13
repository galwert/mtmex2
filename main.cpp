#include <iostream>
#include "ExamDetails.h"
#include "SortedList.h"
//using namespace std;
//int main() {
//    ExamDetails exam1 = ExamDetails::makeMatamExam();
//    ExamDetails exam2(104032, 7, 11, 9.5, 3);
//    ExamDetails exam3 = exam1;
//    cout << "the difference between MATAM and infi 2m is " << (exam1-exam2) << " days";
//    ExamDetails& closest = (exam1 < exam2) ? exam1 : exam2;
//    cout << "your closest exam is:" << endl << closest << endl;
//}
//
//using namespace std;
//
//string getLen(string str)
//{
//    return std::to_string(str.length());
//}
//template<class T>
//void printList(SortedList<T> list) {
//    for (auto it = list.begin(); !(it == list.end()); ++it) {
//        cout << *it << endl;
//    }
//    cout << endl;
//}
//int main()
//{
//    SortedList <string> lst1 = SortedList<string>();
//    lst1.insert("Charlie");
//    lst1.insert("Bob");
//    lst1.insert("Alice");
//    lst1.insert("Donald");
//    printList(lst1);
//    SortedList <string> lst2 = lst1;
//    lst2 = lst2.apply(getLen);
//    printList(lst2);
//    SortedList<string>::const_iterator it = lst2.begin();
//    cout << *it << endl << endl;
//    ++it;
//    lst2.remove(it);
//    printList(lst2);
//    return 0;
//}

using std::string;
string getLen(string str)
{
    return std::to_string(str.length());
}
template<class T>
void printList(SortedList<T> list) {
    for (auto it = list.begin(); !(it == list.end()); ++it) {
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
}
int main()
{
    SortedList<string> lst1 = SortedList<string>();
    lst1.insert("Charlie");
    lst1.insert("Bob");
    lst1.insert("Alice");
    lst1.insert("Donald");
    printList(lst1);
    SortedList<string> lst2 = lst1;
    lst2 = lst2.apply(getLen);
    printList(lst2);
    SortedList<string>::const_iterator it = lst2.begin();
    std::cout << *it << std::endl << std::endl;
    ++it;
    lst2.remove(it);
    printList(lst2);
    return 0;
}