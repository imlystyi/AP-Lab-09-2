// ??????????? ?????????, ??Ͳ, в-11, ??, ?? 09.2, ?????? ?, ??????? 24
#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

enum Specialization { COMPUTER_SCIENCE, IT, MATH_AND_ECONOMICS, PHYSICS_AND_IT, WORK_EDUCATION };

string specializations[]{ "??", "???????????", "??", "Բ", "??" };

struct Student
{
    string surname = "";
    Specialization specialization = COMPUTER_SCIENCE;

    int course = 1, physicsGrade = 1, mathGrade = 1, ITGrade = 1;
};

void CreateStructure(Student* students, const int studentsCount)
{
    int specialization;

    for (int ii = 0; ii < studentsCount; ii++)
    {
        cout << "???????  ? " << ii + 1 << ":" << endl;
        cin.get(); cin.sync();

        cout << "1) ????????: "; getline(cin, students[ii].surname);
        cout << "2) ????: "; cin >> students[ii].course;
        cout << "3) ????????????? (1 - KH, 2 - ???????????, 3 - ??, 4 - Բ, 5 - ??): "; cin >> specialization;
        cout << "4) ?????? ? ??????: "; cin >> students[ii].physicsGrade;
        cout << "5) ?????? ? ??????????: "; cin >> students[ii].mathGrade;
        cout << "6) ?????? ? ???????????: "; cin >> students[ii].ITGrade;

        students[ii].specialization = (Specialization)(specialization - 1);
    }
}

void DisplayStructure(Student* students, const int studentsCount)
{
    cout << "\n============================================================================================================"
        << endl;
    cout << "| ? |    ????????    | ???? | ????????????? | ?????? ? ?????? | ?????? ? ?????????? | ?????? ? ??????????? |"
        << endl;
    cout << "------------------------------------------------------------------------------------------------------------"
        << endl;

    for (int ii = 0; ii < studentsCount; ii++)
    {
        cout << "| " << setw(2) << ii + 1
            << "| " << setw(15) << students[ii].surname
            << "| " << setw(5) << students[ii].course
            << "| " << setw(14) << specializations[students[ii].specialization]
            << "| " << setw(16) << students[ii].physicsGrade
            << "| " << setw(20) << students[ii].mathGrade
            << "| " << setw(21) << students[ii].ITGrade << "|" << endl;
    }

    cout << "============================================================================================================"
        << endl;
}

void DisplayStructureSortedByIndex(Student* students, const int studentsCount, int* indexes)
{
    cout << "\n============================================================================================================"
        << endl;
    cout << "| ? |    ????????    | ???? | ????????????? | ?????? ? ?????? | ?????? ? ?????????? | ?????? ? ??????????? |"
        << endl;
    cout << "------------------------------------------------------------------------------------------------------------"
        << endl;

    for (int ii = 0; ii < studentsCount; ii++)
    {
        cout << "| " << setw(2) << ii + 1
            << "| " << setw(15) << students[indexes[ii]].surname
            << "| " << setw(5) << students[indexes[ii]].course
            << "| " << setw(14) << specializations[students[indexes[ii]].specialization]
            << "| " << setw(16) << students[indexes[ii]].physicsGrade
            << "| " << setw(20) << students[indexes[ii]].mathGrade
            << "| " << setw(21) << students[indexes[ii]].ITGrade << "|" << endl;
    }

    cout << "============================================================================================================"
        << endl;
}

float AverageGrade(Student student) 
{
    return (static_cast<float>(student.physicsGrade) + student.mathGrade + student.ITGrade) / 3;
}

void PhysicalSortArrayOfStructure(Student* students, const int studentsCount)
{ 
    for (int ii = 0; ii < studentsCount - 1; ii++)
        for (int jj = 0; jj < studentsCount - ii - 1; jj++)
            if ((students[jj].course > students[jj + 1].course) ||
                (students[jj].course == students[jj + 1].course && AverageGrade(students[jj]) > AverageGrade(students[jj + 1])) ||
                    (students[jj].course == students[jj + 1].course && AverageGrade(students[jj]) == AverageGrade(students[jj + 1]) && students[jj].surname < students[jj + 1].surname))
                swap(students[jj], students[jj + 1]);          
}

int* IndexSortArrayOfStructure(Student* students, const int studentsCount)
{
    int* indexes = new int[studentsCount];

    for (int ii = 0; ii < studentsCount; ii++)
        indexes[ii] = ii;

    int ii, jj, value;

    for (ii = 1; ii < studentsCount; ii++)
    {
        value = indexes[ii];

        for (jj = ii - 1; jj >= 0 &&
            ((students[indexes[jj]].course > students[value].course) ||
                (students[indexes[jj]].course == students[value].course && AverageGrade(students[indexes[jj]]) > AverageGrade(students[value])) ||
                (students[indexes[jj]].course == students[value].course && AverageGrade(students[indexes[jj]]) == AverageGrade(students[value]) && students[indexes[jj]].surname < students[value].surname));
            jj--)
        {
            indexes[jj + 1] = indexes[jj];
        }
    }

    return indexes;
}

int BinSearch(Student* students, const int studentsCount, string searchedSurname, int searchedCourse, float searchedAverageGrade)
{
    int left = 0, right = studentsCount - 1, chk;

    do
    {
        chk = (left + right) / 2;

        if (students[chk].surname == searchedSurname && students[chk].course == searchedCourse && AverageGrade(students[chk]) == searchedAverageGrade)
            return chk;

        if ((AverageGrade(students[chk]) < searchedAverageGrade) ||
            (AverageGrade(students[chk]) == searchedAverageGrade && students[chk].course < searchedCourse) ||
            (AverageGrade(students[chk]) == searchedAverageGrade && students[chk].course == searchedCourse && students[chk].surname < searchedSurname))
        {
            left = chk + 1;
        }

        else right = chk - 1;
    } while (left <= right);

    return -1;    
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int studentsCount;

    cout << "??????? ????????? ?????????: "; cin >> studentsCount;

    Student* students = new Student[studentsCount];

    int menuItem;

    string searchedSurname;
    int searchedCourse;
    float searchedAverageGrade;

    do
    {
        cout << endl;
        cout << "???????? ???:" << endl << endl;
        cout << " [1] - ???????? ????? ? ??????????" << endl;
        cout << " [2] - ????? ????? ?? ?????" << endl;  
        cout << " [3] - ??????? ????????????? ?????" << endl;
        cout << " [4] - ???????? ????? ???????? ?? ?????????, ?????? ?? ???????? ?????" << endl;
        cout << " [5] - ???????? ????????????? ?? ????? ?????" << endl << endl;
        cout << " [0] - ????? ?? ?????????? ?????? ????????" << endl << endl;

        cout << "??????? ????????: "; cin >> menuItem;

        cout << endl;

        switch (menuItem)
        {
        case 1:
            CreateStructure(students, studentsCount);
            break;

        case 2:
            DisplayStructure(students, studentsCount);
            break;

        case 3:
            PhysicalSortArrayOfStructure(students, studentsCount);
            break;

        case 4:
            cin.sync();
            cout << "??????? ?????? ????????: "; cin >> searchedSurname;
            cout << "??????? ??????? ????: "; cin >> searchedCourse; 
            cout << "??????? ??????? ???????? ???: "; cin >> searchedAverageGrade; 

            BinSearch(students, studentsCount, searchedSurname, searchedCourse, searchedAverageGrade) == -1 ? cout << "\n?????? ???????? ?????." : cout << "\n????? ??????? ?.";

            break;

        case 5:
            DisplayStructureSortedByIndex(students, studentsCount, IndexSortArrayOfStructure(students, studentsCount));

            break;

        case 0:
            break;

        default:
            cout << "???????! ??????? ????? ???? ?????????!";
        } 
    } while (menuItem != 0);

    system("pause");
}   
