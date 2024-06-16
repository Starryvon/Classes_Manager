#ifndef STUDENT_H
#define STUDENT_H

#define MAX_CONTACT_INFO 50
#define MAX_CONTACT_TYPE 10

typedef struct {
    char name[50];
    char gender[10];
    int studentId;
    int classId;
    char contactInfo[MAX_CONTACT_INFO];
    char contactType[MAX_CONTACT_TYPE]; // "Email" or "Phone"
} Student;

void addstudent();
void deletestudent();
void showclassstudents();
void searchByContactInfo();
void modifyOrDeleteContactInfo();

#endif
