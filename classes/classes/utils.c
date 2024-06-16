#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "class.h"
#include "student.h"
#include "teacher.h"

void loaddata() {
    FILE* file;
    file = fopen("classes.csv", "r");
    if (file) {
        fscanf(file, "%d\n", &classCount);
        for (int i = 0; i < classCount; i++) {
            fscanf(file, "%d,%49[^,],%d\n", &classes[i].classId, classes[i].className, &classes[i].studentCount);
            for (int j = 0; j < classes[i].studentCount; j++) {
                fscanf(file, "%d,%49[^,],%9[^,],%d,%49[^,],%9[^\n]\n",
                    &classes[i].students[j].studentId, classes[i].students[j].name, classes[i].students[j].gender,
                    &classes[i].students[j].classId, classes[i].students[j].contactInfo, classes[i].students[j].contactType);
            }
        }
        fclose(file);
    }

    file = fopen("teachers.csv", "r");
    if (file) {
        fscanf(file, "%d\n", &teacherCount);
        for (int i = 0; i < teacherCount; i++) {
            fscanf(file, "%d,%49[^,],%9[^,],%49[^,],%49[^,],%9[^\n]\n",
                &teachers[i].classId, teachers[i].name, teachers[i].gender, teachers[i].subject, teachers[i].contactInfo, teachers[i].contactType);
            for (int j = 0; j < classCount; j++) {
                if (classes[j].classId == teachers[i].classId) {
                    classes[j].teacher = teachers[i];
                    break;
                }
            }
        }
        fclose(file);
    }
}

void savedata() {
    FILE* file;
    file = fopen("classes.csv", "w");
    fprintf(file, "%d\n", classCount);
    for (int i = 0; i < classCount; i++) {
        fprintf(file, "%d,%s,%d\n", classes[i].classId, classes[i].className, classes[i].studentCount);
        for (int j = 0; j < classes[i].studentCount; j++) {
            fprintf(file, "%d,%s,%s,%d,%s,%s\n",
                classes[i].students[j].studentId, classes[i].students[j].name, classes[i].students[j].gender,
                classes[i].students[j].classId, classes[i].students[j].contactInfo, classes[i].students[j].contactType);
        }
    }
    fclose(file);

    file = fopen("teachers.csv", "w");
    fprintf(file, "%d\n", teacherCount);
    for (int i = 0; i < teacherCount; i++) {
        fprintf(file, "%d,%s,%s,%s,%s,%s\n",
            teachers[i].classId, teachers[i].name, teachers[i].gender, teachers[i].subject, teachers[i].contactInfo, teachers[i].contactType);
    }
    fclose(file);
}
