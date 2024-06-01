#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Tree.h"
#include "List.h"
using namespace std;

struct Student
{
    string FIO;
    int groupNum;
    int grades[5];
    int scholarship;
    string passportID;

    Student() : FIO(""), groupNum(0), scholarship(0), passportID("")
    {
        for (int i = 0; i < 5; i++) {
            grades[i] = 0;
        }
    }

    Student(string FIO, int groupNum, int gradesArray[5], int scholarship, string passportID)
        : FIO(FIO.substr(0, 50)), groupNum(groupNum), scholarship(scholarship), passportID(passportID)
    {
        for (int i = 0; i < 5; i++)
        {
            this->grades[i] = gradesArray[i];
        }
    }

    void setFIO(string& newFIO)
    {
        FIO = newFIO;
    }

    void setGroupNum(int newGroupNum)
    {
        groupNum = newGroupNum;
    }

    void setGrades(int newGrades[5])
    {
        for (int i = 0; i < 5; i++)
        {
            grades[i] = newGrades[i];
        }
    }

    void setScholarship(int newScholarship)
    {
        scholarship = newScholarship;
    }

    void setPassportID(string& newPassportID)
    {
        passportID = newPassportID;
    }
};

class Group
{
private:
    int groupNum;
    List<Student> students;

public:
    Group(int groupNum) : groupNum(groupNum) {}

    int getGroupNum() const
    {
        return groupNum;
    }

    List<Student>& getStudents()
    {
        return students;
    }

    bool addStudent(Student& student)
    {
        if (findStudent(student.passportID) != nullptr)
        {
            cout << "A student with the same Passport ID already exists in the group. " << endl;
            return false;
        }
        students.add(student);
        return true;
    }

    void removeStudent(string & passportID)
    {
        for (int i = 0; i < students.count(); i++)
        {
            if (students.elementAt(i).passportID == passportID)
            {
                students.removeAt(i);
                return;
            }
        }
    }

    void clearStudents()
    {
        students.clear();
    }

    Student* findStudent(const string& passportID)
    {
        for (int i = 0; i < students.count(); i++)
        {
            if (students.elementAtRef(i).passportID == passportID)
            {
                return &students.elementAtRef(i);
            }
        }
        return nullptr;
    }

    bool updateStudentFIO(string& passportID, string& newFIO)
    {
        Student* student = findStudent(passportID);
        if (student) {
            student->setFIO(newFIO);
            return true;
        }
        return false;
    }

    bool updateStudentGroupNum(string& passportID, int newGroupNum)
    {
        Student* student = findStudent(passportID);
        if (student) {
            student->setGroupNum(newGroupNum);
            return true;
        }
        return false;
    }

    bool updateStudentGrades(string& passportID, int newGrades[5])
    {
        Student* student = findStudent(passportID);
        if (student) {
            student->setGrades(newGrades);
            return true;
        }
        return false;
    }

    bool updateStudentScholarship(string& passportID, int newScholarship)
    {
        Student* student = findStudent(passportID);
        if (student) {
            student->setScholarship(newScholarship);
            return true;
        }
        return false;
    }

    bool updateStudentPassportID(string& passportID, string& newPassportID)
    {
        if (findStudent(newPassportID) != nullptr)
        {
            cout << "A student with the same Paspport ID already exists in the group. " << endl;
            return false;
        }
        Student* student = findStudent(passportID);
        if (student)
        {
            student->setPassportID(newPassportID);
            return true;
        }
        return false;
    }

    void filterStudents(int field, const string& value, int intValue = 0, const int* gradesArray = nullptr)
    {
        for (int i = 0; i < students.count(); i++)
        {
            bool match = false;
            switch (field)
            {
            case 1:
                if (students.elementAt(i).FIO == value) match = true;
                break;
            case 2:
                if (students.elementAt(i).passportID == value) match = true;
                break;
            case 3:
                if (students.elementAt(i).groupNum == intValue) match = true;
                break;
            case 4:
                if (students.elementAt(i).scholarship == intValue) match = true;
                break;
            case 5:
                if (gradesArray != nullptr)
                {
                    match = true;
                    for (int j = 0; j < 5; j++)
                    {
                        if (students.elementAt(i).grades[j] != gradesArray[j])
                        {
                            match = false;
                            break;
                        }
                    }
                }
                break;
            }
            if (match)
            {
                cout << "FIO: " << students.elementAt(i).FIO << ", Group number: " << students.elementAt(i).groupNum
                    << ", Scholarship: " << students.elementAt(i).scholarship << ", PassportID: " << students.elementAt(i).passportID << endl;
                cout << "Grades: ";
                for (int j = 0; j < 5; j++)
                {
                    cout << students.elementAt(i).grades[j] << " ";
                }
                cout << endl;
            }
        }
    }

    void printStudents()
    {
        for (int i = 0; i < students.count(); i++)
        {
            cout << "FIO: " << students.elementAt(i).FIO << ", Group number : " << students.elementAt(i).groupNum
                << ", Scholarship: " << students.elementAt(i).scholarship << ", PassportID: " << students.elementAt(i).passportID << endl;
            cout << "Grades: ";
            for (int j = 0; j < 5; j++)
            {
                cout << students.elementAt(i).grades[j] << " ";
            }
            cout << endl;
        }
    }

    void saveToFile(ofstream& file)
    {
        for (int i = 0; i < students.count(); i++)
        {
            file << students.elementAt(i).FIO << "," << students.elementAt(i).groupNum << "," << students.elementAt(i).scholarship << "," << students.elementAt(i).passportID;
            for (int j = 0; j < 5; j++)
            {
                file << "," << students.elementAt(i).grades[j];
            }
            file << endl;
        }
    }

    void loadFromFile(ifstream& file)
    {
        string line;
        while (getline(file, line) && line.find("Group:") == string::npos)
        {
            stringstream ss(line);
            string FIO, passportID;
            int number, scholarship, grades[5];

            getline(ss, FIO, ',');
            ss >> number;
            ss.ignore();
            ss >> scholarship;
            ss.ignore();
            getline(ss, passportID, ',');

            for (int i = 0; i < 5; i++) {
                ss >> grades[i];
                if (i < 4) ss.ignore();
            }

            Student student(FIO, number, grades, scholarship, passportID);
            addStudent(student);
        }

        // Если строка начинается с "Group:", мы должны вернуть указатель на начало строки, чтобы StudentFlow знал, что это новая группа
        if (!file.eof())
        {
            file.seekg(-(std::streamoff)line.length(), ios_base::cur);
        }
    }
};


class StudentFlow
{
private:
    Tree<Group*> groupTree;

    bool isExcellent(const Student& student)
    {
        for (int i = 0; i < 5; ++i) {
            if (student.grades[i] != 5)
            {
                return false;
            }
        }
        return true;
    }

public:
    Group* findGroup(int groupNum)
    {
        auto* root = groupTree.getRoot();
        while (root != nullptr) {
            if (groupNum == root->data->getGroupNum())
            {
                return root->data;
            }
            else if (groupNum < root->data->getGroupNum())
            {
                root = root->left;
            }
            else {
                root = root->right;
            }
        }
        return nullptr;
    }

    void addGroup(int groupNum)
    {
        groupTree.add(new Group(groupNum));
    }

    void removeGroup(Group* group)
    {
        if (group)
        {
            group->clearStudents();
            groupTree.remove(group);
            delete group;
        }
    }

    void addStudent(int groupNum, Student& student)
    {
        Group* group = findGroup(groupNum);
        if (group)
        {
            group->addStudent(student);
        }
        else
        {
            Group* newGroup = new Group(groupNum);
            newGroup->addStudent(student);
            groupTree.add(newGroup);
        }
    }

    void removeStudent(int groupNum, string& passportID)
    {
        Group* group = findGroup(groupNum);
        if (group)
        {
            group->removeStudent(passportID);
        }
    }

    bool updateStudentFIO(int groupNum, string& passportID, string& newFIO)
    {
        Group* group = findGroup(groupNum);
        if (group)
        {
            return group->updateStudentFIO(passportID, newFIO);
        }
        return false;
    }

    bool editStudentGroupNum(int currentGroupNum, string& passportID, int newGroupNum)
    {
        Group* currentGroup = findGroup(currentGroupNum);
        Group* newGroup = findGroup(newGroupNum);

        if (currentGroup && newGroup)
        {
            if (newGroup->findStudent(passportID))
            {
                cout << "A student with the same Passport ID already exists in the group. " << endl;
                return false; 
            }
            Student* student = currentGroup->findStudent(passportID);
            if (student)
            {
                // Копируем данные студента
                Student newStudent = *student;
                newStudent.setGroupNum(newGroupNum);

                // Добавляем студента в новую группу
                newGroup->addStudent(newStudent);

                // Удаляем студента из текущей группы
                currentGroup->removeStudent(passportID);
                return true;
            }
        }
        else if (currentGroup && !newGroup)
        {
            // Если новой группы еще не существует, создаем ее и перемещаем студента
            Student* student = currentGroup->findStudent(passportID);
            if (student)
            {
                Group* newGroup = new Group(newGroupNum);
                Student newStudent = *student;
                newStudent.setGroupNum(newGroupNum);

                newGroup->addStudent(newStudent);
                currentGroup->removeStudent(passportID);
                groupTree.add(newGroup);
                return true;
            }
        }
        return false;
    }

    bool updateStudentGrades(int groupNum, string& passportID, int newGrades[5])
    {
        Group* group = findGroup(groupNum);
        if (group)
        {
            return group->updateStudentGrades(passportID, newGrades);
        }
        return false;
    }

    bool updateStudentScholarship(int groupNum, string& passportID, int newScholarship)
    {
        Group* group = findGroup(groupNum);
        if (group)
        {
            return group->updateStudentScholarship(passportID, newScholarship);
        }
        return false;
    }

    bool updateStudentPassportID(int groupNum, string& passportID, string& newPassportID)
    {
        Group* group = findGroup(groupNum);
        if (group)
        {
            return group->updateStudentPassportID(passportID, newPassportID);
        }
        return false;
    }

    void filterStudents(int field, const string& value, int intValue = 0, const int* gradesArray = nullptr)
    {
        Group** groupsArray = groupTree.ToArray(Tree<Group*>::Infix);
        for (int i = 0; i < groupTree.count(); i++)
        {
            Group* group = groupsArray[i];
            group->filterStudents(field, value, intValue, gradesArray);
        }
        delete[] groupsArray;
    }

    void printGroups()
    {
        Group** groupsArray = groupTree.ToArray(Tree<Group*>::Infix);
        for (int i = 0; i < groupTree.count(); i++)
        {
            Group* group = groupsArray[i];
            cout << "Group number: " << group->getGroupNum() << endl;
            group->printStudents();
        }
        delete[] groupsArray;
    }

    void saveToFile(const string& filename)
    {
        ofstream file(filename);
        if (!file.is_open())
        {
            cout << "Unable to open file!" << endl;
            return;
        }

        Group** groupsArray = groupTree.ToArray(Tree<Group*>::Infix);
        for (int i = 0; i < groupTree.count(); i++)
        {
            Group* group = groupsArray[i];
            file << "Group: " << group->getGroupNum() << endl;
            group->saveToFile(file);
        }

        delete[] groupsArray;
        file.close();
    }

    void loadFromFile(const string& filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Unable to open file!" << endl;
            return;
        }

        string line;
        Group* currentGroup = nullptr;

        while (getline(file, line))
        {
            if (line.find("Group:") != string::npos)
            {
                int groupNum = stoi(line.substr(line.find(":") + 1));
                currentGroup = findGroup(groupNum);
                if (currentGroup == nullptr)
                {
                    currentGroup = new Group(groupNum);
                    groupTree.add(currentGroup);
                }
            }
            else if (currentGroup != nullptr)
            {
                stringstream ss(line);
                string FIO, passportID;
                int number, scholarship, grades[5];

                getline(ss, FIO, ',');
                ss >> number;
                ss.ignore();
                ss >> scholarship;
                ss.ignore();
                getline(ss, passportID, ',');

                for (int i = 0; i < 5; i++)
                {
                    ss >> grades[i];
                    if (i < 4) ss.ignore();
                }

                Student student(FIO, number, grades, scholarship, passportID);
                currentGroup->addStudent(student);
            }
        }

        file.close();
    }

    List<Student> getExcellentStudents(const string& prefix)
    {
        List<Student> excellentStudents;
        Group** groupsArray = groupTree.ToArray(Tree<Group*>::Infix);
        for (int i = 0; i < groupTree.count(); i++)
        {
            Group* group = groupsArray[i];
            List<Student>& students = group->getStudents();
            for (int j = 0; j < students.count(); j++)
            {
                Student student = students.elementAtRef(j);
                if (isExcellent(student) && student.FIO.find(prefix) == 0)
                {
                    excellentStudents.add(student);
                }
            }
        }
        delete[] groupsArray;

        // Сортировка студентов по алфавиту
        for (int i = 0; i < excellentStudents.count() - 1; i++)
        {
            for (int j = i + 1; j < excellentStudents.count(); j++)
            {
                if (excellentStudents.elementAt(i).FIO > excellentStudents.elementAt(j).FIO)
                {
                    Student temp = excellentStudents.elementAt(i);
                    excellentStudents.setElementAt(i, excellentStudents.elementAt(j));
                    excellentStudents.setElementAt(j, temp);
                }
            }
        }

        return excellentStudents;
    }
};

int main()
{
    StudentFlow studentFlow;
    int choice;

    do {
        cout << "1. Add Student" << endl;
        cout << "2. Remove Student" << endl;
        cout << "3. Add Group" << endl;
        cout << "4. Remove Group" << endl;
        cout << "5. Edit Student FIO" << endl;
        cout << "6. Edit Student Group Number" << endl;
        cout << "7. Edit Student Grades" << endl;
        cout << "8. Edit Student Scholarship" << endl;
        cout << "9. Edit Student Passport ID" << endl;
        cout << "10. Display All Students" << endl;
        cout << "11. Save to File" << endl;
        cout << "12. Load from File" << endl;
        cout << "13. Display Excellent Students" << endl;
        cout << "14. Filter Students" << endl;
        cout << "0. Exit" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string fio;
            int groupNumber;
            int grades[5] = { 0 };
            int scholarship;
            string passportID;

            cout << "Enter FIO: ";
            cin.ignore();
            getline(cin, fio);
            cout << "Enter Group Number: ";
            cin >> groupNumber;
            cout << "Enter Grades (5 values): ";
            for (int i = 0; i < 5; ++i)
            {
                cin >> grades[i];
            }
            cout << "Enter Scholarship: ";
            cin >> scholarship;
            cout << "Enter Passport ID: ";
            cin.ignore();
            getline(cin, passportID);

            Student student(fio, groupNumber, grades, scholarship, passportID);
            studentFlow.addStudent(groupNumber, student);
            break;
        }
        case 2:
        {
            string passportID;
            int groupNumber;

            cout << "Enter Passport ID of the student to remove: ";
            cin.ignore();
            getline(cin, passportID);
            cout << "Enter Group Number: ";
            cin >> groupNumber;

            studentFlow.removeStudent(groupNumber, passportID);
            break;
        }
        case 3:
        {
            int groupNumber;
            cout << "Enter Group Number to add: ";
            cin >> groupNumber;
            studentFlow.addGroup(groupNumber);
            break;
        }
        case 4:
        {
            int groupNumber;
            cout << "Enter Group Number to remove: ";
            cin >> groupNumber;
            Group* group = studentFlow.findGroup(groupNumber);
            studentFlow.removeGroup(group);
            break;
        }
        case 5:
        {
            string passportID;
            int groupNumber;
            string newFIO;

            cout << "Enter Passport ID of the student to edit FIO: ";
            cin.ignore();
            getline(cin, passportID);
            cout << "Enter Group Number: ";
            cin >> groupNumber;
            cout << "Enter new FIO: ";
            cin.ignore();
            getline(cin, newFIO);

            studentFlow.updateStudentFIO(groupNumber, passportID, newFIO);
            break;
        }
        case 6:
        {
            string passportID;
            int currentGroupNumber, newGroupNumber;

            cout << "Enter Passport ID of the student to edit Group Number: ";
            cin.ignore();
            getline(cin, passportID);
            cout << "Enter current Group Number: ";
            cin >> currentGroupNumber;
            cout << "Enter new Group Number: ";
            cin >> newGroupNumber;

            studentFlow.editStudentGroupNum(currentGroupNumber, passportID, newGroupNumber);
            break;
        }
        case 7:
        {
            string passportID;
            int groupNumber;
            int newGrades[5];

            cout << "Enter Passport ID of the student to edit Grades: ";
            cin.ignore();
            getline(cin, passportID);
            cout << "Enter Group Number: ";
            cin >> groupNumber;
            cout << "Enter new Grades (5 values): ";
            for (int& grade : newGrades) {
                cin >> grade;
            }

            studentFlow.updateStudentGrades(groupNumber, passportID, newGrades);
            break;
        }
        case 8:
        {
            string passportID;
            int groupNumber;
            int newScholarship;

            cout << "Enter Passport ID of the student to edit Scholarship: ";
            cin.ignore();
            getline(cin, passportID);
            cout << "Enter Group Number: ";
            cin >> groupNumber;
            cout << "Enter new Scholarship: ";
            cin >> newScholarship;

            studentFlow.updateStudentScholarship(groupNumber, passportID, newScholarship);
            break;
        }
        case 9:
        {
            string oldPassportID;
            int groupNumber;
            string newPassportID;

            cout << "Enter old Passport ID of the student to edit Passport ID: ";
            cin.ignore();
            getline(cin, oldPassportID);
            cout << "Enter Group Number: ";
            cin >> groupNumber;
            cout << "Enter new Passport ID: ";
            cin.ignore();
            getline(cin, newPassportID);

            studentFlow.updateStudentPassportID(groupNumber, oldPassportID, newPassportID);
            break;
        }
        case 10:
        {
            studentFlow.printGroups();
            break;
        }
        case 11:
        {
            string filename;
            cout << "Enter filename to save: ";
            cin.ignore();
            getline(cin, filename);
            studentFlow.saveToFile(filename);
            break;
        }
        case 12:
        {
            string filename;
            cout << "Enter filename to load: ";
            cin.ignore();
            getline(cin, filename);
            studentFlow.loadFromFile(filename);
            break;
        }
        case 13:
        {
            string prefix;
            cout << "Enter prefix to filter excellent students: ";
            cin.ignore();
            getline(cin, prefix);
            List<Student> excellentStudents = studentFlow.getExcellentStudents(prefix);
            for (int i = 0; i < excellentStudents.count(); ++i) {
                const Student& student = excellentStudents.elementAt(i);
                cout << student.FIO << "\n";
            }
            break;
        }
        case 14:
        {
            int field;
            string value;
            int intValue = 0;
            int grades[5] = { 0 };

            cout << "Enter field to filter (1: FIO, 2: Passport ID, 3: Group Number, 4: Scholarship, 5: Grade): ";
            cin >> field;
            if (field == 1 || field == 2)
            {
                cout << "Enter value to filter by: ";
                cin.ignore();
                getline(cin, value);
            }
            else if (field == 3 || field == 4)
            {
                cout << "Enter integer value to filter by: ";
                cin >> intValue;
            }
            else if (field == 5)
            {
                cout << "Enter 5 grades to filter by: ";
                for (int& grade : grades)
                {
                    cin >> grade;
                }
            }

            studentFlow.filterStudents(field, value, intValue, grades);
            break;
        }
        case 0:
            break;
        default:
            cout << "Unknown command! Try again." << endl;
            break;
        }
    } while (choice != 0);

    return 0;
}
