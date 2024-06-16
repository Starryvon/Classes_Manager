#include <stdio.h>
#include <string.h>
#include "teacher.h"
#include "class.h"
#include "utils.h"

Teacher teachers[MAX_TEACHERS];
int teacherCount = 0;

void addteacher() {
    if (teacherCount >= MAX_TEACHERS) {
        printf("无法增加更多的教师。\n");
        return;
    }

    Teacher teacher;
    printf("输入教师班级ID: ");
    scanf("%d", &teacher.classId);

    if (!isClassIdExist(teacher.classId)) {
        printf("无效的班级ID。\n");
        return;
    }

    printf("输入教师姓名: ");
    scanf("%s", teacher.name);
    printf("输入教师性别: ");
    scanf("%s", teacher.gender);
    printf("输入教学科目: ");
    scanf("%s", teacher.subject);

    printf("选择联系方式类型 (1: Email, 2: Phone, 3: None): ");
    int contactChoice;
    scanf("%d", &contactChoice);
    if (contactChoice == 1) {
        printf("输入Email: ");
        scanf("%s", teacher.contactInfo);
        strcpy(teacher.contactType, "Email");
    }
    else if (contactChoice == 2) {
        printf("输入Phone: ");
        scanf("%s", teacher.contactInfo);
        strcpy(teacher.contactType, "Phone");
    }
    else {
        strcpy(teacher.contactInfo, "无");
        strcpy(teacher.contactType, "无");
    }

    teachers[teacherCount] = teacher;
    for (int i = 0; i < classCount; i++) {
        if (classes[i].classId == teacher.classId) {
            classes[i].teacher = teacher;
            break;
        }
    }
    teacherCount++;
    savedata();
    printf("教师添加成功。\n");
}

void deleteteacher() {
    int classId;
    printf("输入教师班级ID: ");
    scanf("%d", &classId);

    if (!isClassIdExist(classId)) {
        printf("无效的班级ID。\n");
        return;
    }

    int i;
    for (i = 0; i < teacherCount; i++) {
        if (teachers[i].classId == classId) {
            break;
        }
    }

    if (i == teacherCount) {
        printf("未找到教师。\n");
        return;
    }

    for (int j = i; j < teacherCount - 1; j++) {
        teachers[j] = teachers[j + 1];
    }
    teacherCount--;

    for (int k = 0; k < classCount; k++) {
        if (classes[k].classId == classId) {
            strcpy(classes[k].teacher.name, "无");
            break;
        }
    }

    savedata();
    printf("教师删除成功。\n");
}
