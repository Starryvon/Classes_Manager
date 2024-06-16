#include <stdio.h>
#include <string.h>
#include "student.h"
#include "class.h"
#include "utils.h"

int isStudentIdExist(int studentId) {
    for (int i = 0; i < classCount; i++) {
        for (int j = 0; j < classes[i].studentCount; j++) {
            if (classes[i].students[j].studentId == studentId) {
                return 1;
            }
        }
    }
    return 0;
}

void addstudent() {
    int classId;
    printf("输入学生所属班级ID: ");
    scanf("%d", &classId);

    if (!isClassIdExist(classId)) {
        printf("无效的班级ID。\n");
        return;
    }

    Class* cls = NULL;
    for (int i = 0; i < classCount; i++) {
        if (classes[i].classId == classId) {
            cls = &classes[i];
            break;
        }
    }

    if (cls->studentCount >= MAX_STUDENTS) {
        printf("该班级学生已满。\n");
        return;
    }

    Student stu;
    printf("输入学生学号: ");
    scanf("%d", &stu.studentId);

    if (isStudentIdExist(stu.studentId)) {
        printf("学生学号已存在。\n");
        return;
    }

    printf("输入学生姓名: ");
    scanf("%s", stu.name);
    printf("输入学生性别: ");
    scanf("%s", stu.gender);
    stu.classId = classId;

    printf("选择联系方式类型 (1: Email, 2: Phone, 3: None): ");
    int contactChoice;
    scanf("%d", &contactChoice);
    if (contactChoice == 1) {
        printf("输入Email: ");
        scanf("%s", stu.contactInfo);
        strcpy(stu.contactType, "Email");
    }
    else if (contactChoice == 2) {
        printf("输入Phone: ");
        scanf("%s", stu.contactInfo);
        strcpy(stu.contactType, "Phone");
    }
    else {
        strcpy(stu.contactInfo, "无");
        strcpy(stu.contactType, "无");
    }

    cls->students[cls->studentCount] = stu;
    cls->studentCount++;
    savedata();
    printf("学生添加成功。\n");
}

void deletestudent() {
    int classId, studentId;
    printf("输入学生所属班级ID: ");
    scanf("%d", &classId);

    if (!isClassIdExist(classId)) {
        printf("无效的班级ID。\n");
        return;
    }

    Class* cls = NULL;
    for (int i = 0; i < classCount; i++) {
        if (classes[i].classId == classId) {
            cls = &classes[i];
            break;
        }
    }

    printf("输入要删除的学生学号: ");
    scanf("%d", &studentId);

    int found = 0;
    for (int i = 0; i < cls->studentCount; i++) {
        if (cls->students[i].studentId == studentId) {
            found = 1;
            for (int j = i; j < cls->studentCount - 1; j++) {
                cls->students[j] = cls->students[j + 1];
            }
            cls->studentCount--;
            savedata();
            printf("学生删除成功。\n");
            break;
        }
    }

    if (!found) {
        printf("未找到学生。\n");
    }
}

void showclassstudents() {
    int classId;
    printf("输入班级ID: ");
    scanf("%d", &classId);

    if (!isClassIdExist(classId)) {
        printf("无效的班级ID。\n");
        return;
    }

    Class* cls = NULL;
    for (int i = 0; i < classCount; i++) {
        if (classes[i].classId == classId) {
            cls = &classes[i];
            break;
        }
    }

    printf("班级名称: %s, 学生数: %d\n", cls->className, cls->studentCount);
    printf("教师: %s\n", cls->teacher.name);
    for (int i = 0; i < cls->studentCount; i++) {
        Student* stu = &cls->students[i];
        printf("姓名: %s, 性别: %s, 学号: %d, 联系方式: %s (%s)\n",
            stu->name, stu->gender, stu->studentId, stu->contactInfo, stu->contactType);
    }
}

void searchByContactInfo() {
    char contactInfo[50];
    printf("输入联系方式: ");
    scanf("%s", contactInfo);

    int found = 0;
    // 查找学生
    for (int i = 0; i < classCount; i++) {
        for (int j = 0; j < classes[i].studentCount; j++) {
            if (strcmp(classes[i].students[j].contactInfo, contactInfo) == 0) {
                printf("找到的学生:\n");
                printf("姓名: %s, 性别: %s, 学号: %d, 班级ID: %d\n",
                    classes[i].students[j].name, classes[i].students[j].gender,
                    classes[i].students[j].studentId, classes[i].students[j].classId);
                found = 1;
            }
        }
    }

    // 查找教师
    for (int i = 0; i < teacherCount; i++) {
        if (strcmp(teachers[i].contactInfo, contactInfo) == 0) {
            printf("找到的教师:\n");
            printf("姓名: %s, 性别: %s, 教学科目: %s, 班级ID: %d\n",
                teachers[i].name, teachers[i].gender, teachers[i].subject, teachers[i].classId);
            found = 1;
        }
    }

    if (!found) {
        printf("未找到匹配的联系方式。\n");
    }
}

void modifyOrDeleteContactInfo() {
    int entityType;
    printf("修改或删除联系方式 (1: 学生, 2: 教师): ");
    scanf("%d", &entityType);

    int classId, id;
    printf("输入班级ID: ");
    scanf("%d", &classId);

    if (!isClassIdExist(classId)) {
        printf("无效的班级ID。\n");
        return;
    }

    if (entityType == 1) {
        printf("输入学生学号: ");
        scanf("%d", &id);

        for (int i = 0; i < classCount; i++) {
            if (classes[i].classId == classId) {
                for (int j = 0; j < classes[i].studentCount; j++) {
                    if (classes[i].students[j].studentId == id) {
                        printf("1. 修改联系方式\n2. 删除联系方式\n选择操作: ");
                        int choice;
                        scanf("%d", &choice);

                        if (choice == 1) {
                            printf("选择联系方式类型 (1: Email, 2: Phone): ");
                            int contactChoice;
                            scanf("%d", &contactChoice);
                            if (contactChoice == 1) {
                                printf("输入Email: ");
                                scanf("%s", classes[i].students[j].contactInfo);
                                strcpy(classes[i].students[j].contactType, "Email");
                            }
                            else if (contactChoice == 2) {
                                printf("输入Phone: ");
                                scanf("%s", classes[i].students[j].contactInfo);
                                strcpy(classes[i].students[j].contactType, "Phone");
                            }
                        }
                        else if (choice == 2) {
                            strcpy(classes[i].students[j].contactInfo, "无");
                            strcpy(classes[i].students[j].contactType, "无");
                        }

                        savedata();
                        printf("操作成功。\n");
                        return;
                    }
                }
            }
        }
    }
    else if (entityType == 2) {
        printf("输入教师姓名: ");
        char name[50];
        scanf("%s", name);

        for (int i = 0; i < teacherCount; i++) {
            if (teachers[i].classId == classId && strcmp(teachers[i].name, name) == 0) {
                printf("1. 修改联系方式\n2. 删除联系方式\n选择操作: ");
                int choice;
                scanf("%d", &choice);

                if (choice == 1) {
                    printf("选择联系方式类型 (1: Email, 2: Phone): ");
                    int contactChoice;
                    scanf("%d", &contactChoice);
                    if (contactChoice == 1) {
                        printf("输入Email: ");
                        scanf("%s", teachers[i].contactInfo);
                        strcpy(teachers[i].contactType, "Email");
                    }
                    else if (contactChoice == 2) {
                        printf("输入Phone: ");
                        scanf("%s", teachers[i].contactInfo);
                        strcpy(teachers[i].contactType, "Phone");
                    }
                }
                else if (choice == 2) {
                    strcpy(teachers[i].contactInfo, "无");
                    strcpy(teachers[i].contactType, "无");
                }

                for (int j = 0; j < classCount; j++) {
                    if (classes[j].classId == classId) {
                        classes[j].teacher = teachers[i];
                        break;
                    }
                }

                savedata();
                printf("操作成功。\n");
                return;
            }
        }
    }

    printf("未找到相关信息。\n");
}
