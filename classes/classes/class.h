#ifndef CLASS_H
#define CLASS_H

#include "teacher.h"
#include "student.h"

#define MAX_CLASSES 10
#define MAX_STUDENTS 50

typedef struct {
    char className[50];
    int classId;
    int studentCount;
    Student students[MAX_STUDENTS];
    Teacher teacher;
} Class;

extern Class classes[MAX_CLASSES];
extern int classCount;

void displayclasslist();
int isClassIdExist(int classId);
void addclass();
void deleteclass();

#endif
