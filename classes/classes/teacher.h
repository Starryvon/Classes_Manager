#ifndef TEACHER_H
#define TEACHER_H

#define MAX_TEACHERS 50

typedef struct {
    char name[50];
    char gender[10];
    char subject[50];
    int classId;
    char contactInfo[50];
    char contactType[10]; // "Email" or "Phone"
} Teacher;

extern Teacher teachers[MAX_TEACHERS];
extern int teacherCount;

void addteacher();
void deleteteacher();

#endif
