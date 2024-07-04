/*
    @ Anas
    @ Odai
    @ Haneen
*/

#include <iostream> 
#include <fstream> 
#include "json.hpp"
using namespace std;
using namespace nlohmann;

struct Data {
    string name;
    int age;
    string sex;
    int grade;
    string city;
    string fatherNumber;
};

struct Node {
    int studentId;
    Data studentData;
    Node* next;
    Node* prev;
};

class LinkedList {
    private: 
        Node* head;
        Node* tail;

    public: 
        LinkedList() {
            head = nullptr;
            tail = nullptr;
        }
        
        void insert();
        void remove(); 
        void updateIds();
        void displayTable();
        void updateJsonFile();
        void updateList();
        void insertionSortAscending();
        void insertionSortDescending();
        void linearSearch();
        void binarySearch();     
};

int validateInput();

int main() { 
    LinkedList* students = new LinkedList;
    students->updateList();

    bool key = true;
    while (key) {
        students->displayTable();

        cout << "1# Add Student             2# Delete Student    3# Sort Descending Order\n";
        cout << "4# Sort Ascending Order    5# Search by ID      6# Search by Name\n7# Exit\n\n";

        cout << "@ Enter your choice\n ~> ";
        int choice = validateInput();
        

        switch (choice) {
            case 1: students->insert();
                    students->updateJsonFile();
                    break;
            
            case 2: students->remove();
                    students->updateJsonFile();
                    break;
            
            case 3: students->insertionSortDescending();
                    students->displayTable();
                    break;
            
            case 4: students->insertionSortAscending();
                    students->displayTable();
                    break;
            
            case 5: students->binarySearch();
                    break;
            
            case 6: students->linearSearch();
                    break;
            
            case 7: system("cls");
                    system("color 0A");
                    cout << "@Haneen  @Anas  @Odai\n";
                    exit(0);
                    break;

            default: cout << "* Invalid input\n";
        }

        cout << "\n@ Press [ 1 ] ~> continue\n@ Press [ 2 ] ~> Exit the App\n ~> ";
        int exit = validateInput();
    
        if (exit == 1) {
           system("cls");
        } else {
            system("cls");
            system("color 0A");
            cout << "@Haneen  @Anas  @Odai\n";
            key = false;
        }
    }
}

void LinkedList::insert() {
    Node* newStudent = new Node;

    cout << "$ Student Name ~> ";
    cin >> newStudent->studentData.name;

    cout << "$ Student Age ~> ";
    newStudent->studentData.age = validateInput();

    cout << "\n@ Press [ 1 ] ~> Male\n@ Press [ 2 ] ~> Female\n";
    cout << "$ Student Six ~> ";
    int choice = validateInput();

    if (choice == 1) {
        newStudent->studentData.sex = "Male";
    } else if (choice == 2) {
        newStudent->studentData.sex = "Female";
    } else {
        newStudent->studentData.sex = "NULL";
    }

    cout << "$ Student Grade ~> ";
    newStudent->studentData.grade = validateInput();

    cout << "$ Student City ~> ";
    cin >> newStudent->studentData.city;

    cout << "$ Student Father Phone Number ~>";
    cin >> newStudent->studentData.fatherNumber;

    int id = 1;

    if (head == nullptr) {
        newStudent->studentId = id;
        newStudent->next = nullptr;
        newStudent->prev = nullptr;
        head = newStudent;
        tail = newStudent;
    } else {
        Node* current = tail;
        newStudent->studentId = current->studentId + 1;
        current->next = newStudent;
        tail = newStudent;

        newStudent->next = nullptr;
        newStudent->prev = current;
    }
}

void LinkedList::remove() {
    if (head == nullptr) {
        cout << "* There is no students in the school\n";
    } else {
        cout << "$ Delete Student with ID number ~> ";
        int stuId = validateInput();
        
        Node* current = head;
        while (current != nullptr && current->studentId != stuId) {
            current = current->next;
        }

        if (current == nullptr) {
            cout << "* The student with ID number { " << stuId << " } not found\n";
            return;
        }
        
        if (current == head) {
            head = current->next;
            if (head != nullptr) { 
                head->prev = nullptr;
            }
            delete current;
            current = nullptr;
            updateIds();
            return;
        }

        if (current->next == nullptr) {
            current->prev->next = current->next;
            tail = current->prev;
            delete current;
            current = nullptr;
            updateIds();
            return;
        }

        current->next->prev = current->prev;
        current->prev->next = current->next;
        
        delete current;
        current = nullptr;
        
        updateIds();
    }
}

void LinkedList::updateIds() {
    if (head != NULL) {
        Node* current = head; 
        int id = 1; 

        while (current != NULL) {
            current->studentId = id;
            current = current->next;
            id++;
        }
    }
}

void LinkedList::displayTable() {
    int idWidth = 2;
    int nameWidth = 4;
    int ageWidth = 3; 
    int sexWidth = 4;
    int gradeWidth = 5;
    int cityWidth = 10;
    int phoneNumberWidth = 14;

    Node* current = head;
    while (current != nullptr) {
        idWidth = max(idWidth, static_cast<int>(to_string(current->studentId).length()));
        nameWidth = max(nameWidth, static_cast<int>(current->studentData.name.length()));
        ageWidth = max(ageWidth, static_cast<int>(to_string(current->studentData.age).length()));
        sexWidth = max(sexWidth, static_cast<int>(current->studentData.sex.length()));
        gradeWidth = max(gradeWidth, static_cast<int>(to_string(current->studentData.grade).length()));
        cityWidth = max(cityWidth, static_cast<int>(current->studentData.city.length()));
        phoneNumberWidth = max(phoneNumberWidth, static_cast<int>(current->studentData.fatherNumber.length()));

        current = current->next;
    }
    
    cout << "\n";
    cout << setfill('-') << setw(idWidth + nameWidth + ageWidth + sexWidth + gradeWidth + cityWidth + phoneNumberWidth + 22) << "-" << setfill(' ') << "\n";
    cout << "| " << setw(idWidth) << "ID" << " | " << setw(nameWidth) << "Name" << " | " << setw(ageWidth) << "Age" << " | " << setw(sexWidth) << "Sex" << " | " << setw(gradeWidth) << "Grade" << " | " << setw(cityWidth) << "City" << " | " << setw(phoneNumberWidth) << "Father number" << " |\n";
    cout << setfill('-') << setw(idWidth + nameWidth + ageWidth + sexWidth + gradeWidth + cityWidth + phoneNumberWidth + 22) << "-" << setfill(' ') << "\n";

    current = head;
    while (current != nullptr) {
        cout << "| " << setw(idWidth) << current->studentId << " | " << setw(nameWidth) << current->studentData.name << " | " << setw(ageWidth) << current->studentData.age << " | " << setw(sexWidth) << current->studentData.sex << " | " << setw(gradeWidth) << current->studentData.grade << " | " << setw(cityWidth) << current->studentData.city << " | " << setw(phoneNumberWidth) << current->studentData.fatherNumber << " |\n";
        current = current->next;
    }
    cout << setfill('-') << setw(idWidth + nameWidth + ageWidth + sexWidth + gradeWidth + cityWidth + phoneNumberWidth + 22) << "-" << setfill(' ') << "\n\n";
}

void LinkedList::updateJsonFile() {
    ofstream schoolDb("./school_DB.json"); 
    json newJson;

    newJson["School"] = json::array();

    if (head == nullptr) {
        schoolDb << newJson;
    } else {
        Node* current = head;

        while (current != nullptr) {
            newJson["School"].push_back({
                {"ID", current->studentId},
                {"Name", current->studentData.name},
                {"Age", current->studentData.age},
                {"Sex", current->studentData.sex},
                {"Grade", current->studentData.grade},
                {"City", current->studentData.city},
                {"FatherNumber", current->studentData.fatherNumber}
            });
            
            current = current->next;
        }
        schoolDb << setw(4) << newJson;
    }
}

void LinkedList::updateList() {
    ifstream jsonFile("./school_DB.json");
    
    if (jsonFile) {
        json jsonDate = json::parse(jsonFile);

        auto School = jsonDate["School"];

        for (auto& student : School) {
            Node* newStudent = new Node;
            newStudent->studentId = student["ID"];
            newStudent->studentData.name = student["Name"];
            newStudent->studentData.age = student["Age"];
            newStudent->studentData.sex = student["Sex"];
            newStudent->studentData.grade = student["Grade"];
            newStudent->studentData.city = student["City"];
            newStudent->studentData.fatherNumber = student["FatherNumber"];

            if (head == nullptr) {
                head = newStudent;
                tail = newStudent;
                newStudent->next = nullptr;
                newStudent->prev = nullptr;
            } else {
                Node* current = tail;
                current->next = newStudent;
                tail = newStudent;
                newStudent->next = nullptr;
                newStudent->prev = current;
            }
        }
    }
}

void LinkedList::insertionSortAscending() {
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    Node* sorted = nullptr; 
    Node* current = head;   

    while (current != nullptr) {
        Node* nextNode = current->next;

        if (sorted == nullptr || current->studentId < sorted->studentId) {
            current->next = sorted;
            if (sorted != nullptr) {
                sorted->prev = current;
            }
            sorted = current;
        } else {
            Node* temp = sorted;
            while (temp->next != nullptr && temp->next->studentId < current->studentId) {
                temp = temp->next;
            }
            current->next = temp->next;
            if (temp->next != nullptr) {
                temp->next->prev = current;
            }
            temp->next = current;
            current->prev = temp;
        }

        current = nextNode; 
    }

    head = sorted;
} 

void LinkedList::insertionSortDescending() {
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    Node* sorted = nullptr; 
    Node* current = head;   

    while (current != nullptr) {
        Node* nextNode = current->next; 

        if (sorted == nullptr || current->studentId > sorted->studentId) {
            current->next = sorted;
            if (sorted != nullptr) {
                sorted->prev = current;
            }
            sorted = current;
        } else {
            Node* temp = sorted;
            while (temp->next != nullptr && temp->next->studentId > current->studentId) {
                temp = temp->next;
            }
            current->next = temp->next;
            if (temp->next != nullptr) {
                temp->next->prev = current;
            }
            temp->next = current;
            current->prev = temp;
        }

        current = nextNode; 
    }

    head = sorted; 
}

void LinkedList::linearSearch() {
    if (head == nullptr) {
        cout << "There is no students in the school!\n";
    } else {
        string stuName;
        cout << "$ Search for Student with the Name ~> ";
        cin >> stuName;
        
        Node* current = head;
        while (current != nullptr && current->studentData.name != stuName) {
            current = current->next;
        }

        if (current == nullptr) {
            cout << "* There is no Student with the name { " << stuName << " } the school\n";
            return;
        } 

        cout << setfill('-') << setw(2 + 8 + 3 + 6 + 2 + 8 + 15 + 25) << "-" << setfill(' ') << "\n";
        cout << "| " << setw(2) << "ID" << " | " << setw(8) << "Name" << " | " << setw(3) << "Age" << " | " << setw(6) << "Sex" << " | " << setw(2) << "Grade" << " | " << setw(8) << "City" << " | " << setw(15) << "Father number" << " |\n";
        cout << setfill('-') << setw(2 + 8 + 3 + 6 + 2 + 8 + 15 + 25) << "-" << setfill(' ') << "\n";
        cout << "| " << setw(2) << current->studentId << " | " << setw(8) << current->studentData.name << " | " << setw(3) << current->studentData.age << " | " << setw(6) << current->studentData.sex << " | " << setw(5) << current->studentData.grade << " | " << setw(8) << current->studentData.city << " | " << setw(15) << current->studentData.fatherNumber << " |\n";
        cout << setfill('-') << setw(2 + 8 + 3 + 6 + 2 + 8 + 15 + 25) << "-" << setfill(' ') << "\n\n";
    }
}

void LinkedList::binarySearch() {
    if (head == nullptr) {
        cout << "There is no students in the school!\n";
    } else {
        cout << "$ Search for Student with ID number ~> ";
        int stuId = validateInput();

        const int size = tail->studentId;
        Node list[size];

        Node* current = head;
        for (int index = 0; index < size && current != nullptr; index++) {
            list[index].studentId = current->studentId;
            list[index].studentData.name= current->studentData.name;
            list[index].studentData.age = current->studentData.age;
            list[index].studentData.sex = current->studentData.sex;
            list[index].studentData.grade = current->studentData.grade;
            list[index].studentData.city = current->studentData.city;
            list[index].studentData.fatherNumber = current->studentData.fatherNumber;
            
            current = current->next;
           
        }

        int left = 0;
        int right = size - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (list[mid].studentId == stuId) {
                cout << setfill('-') << setw(2 + 8 + 3 + 6 + 2 + 8 + 15 + 25) << "-" << setfill(' ') << "\n";
                cout << "| " << setw(2) << "ID" << " | " << setw(8) << "Name" << " | " << setw(3) << "Age" << " | " << setw(6) << "Sex" << " | " << setw(2) << "Grade" << " | " << setw(8) << "City" << " | " << setw(15) << "Father number" << " |\n";
                cout << setfill('-') << setw(2 + 8 + 3 + 6 + 2 + 8 + 15 + 25) << "-" << setfill(' ') << "\n";
                cout << "| " << setw(2) << list[mid].studentId << " | " << setw(8) << list[mid].studentData.name << " | " << setw(3) << list[mid].studentData.age << " | " << setw(6) << list[mid].studentData.sex << " | " << setw(5) << list[mid].studentData.grade << " | " << setw(8) << list[mid].studentData.city << " | " << setw(15) << list[mid].studentData.fatherNumber << " |\n";
                cout << setfill('-') << setw(2 + 8 + 3 + 6 + 2 + 8 + 15 + 25) << "-" << setfill(' ') << "\n\n";
                return;
            }

            if (list[mid].studentId < stuId) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        cout << "* There is no Student with ID number { " << stuId << " } in the school\n";
    }
}

int validateInput() {
    int choice = 0;
    while (true) {
        if (!(cin >> choice)) {
            cout << "* Invalid input! Please enter a number ~> ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        return choice;
    }
}
