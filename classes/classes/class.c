#include <stdio.h>
#include <string.h>
#include "class.h"
#include "utils.h"

Class classes[MAX_CLASSES];
int classCount = 0;

void displayclasslist() {
    printf("\n班级列表:\n");
    printf("班级总数: %d\n", classCount);
    for (int i = 0; i < classCount; i++) {
        printf("班级名称: %s, 班级ID: %d, 学生数: %d, 教师: %s\n",
            classes[i].className, classes[i].classId, classes[i].studentCount, classes[i].teacher.name);
    }
}

int isClassIdExist(int classId) {
    for (int i = 0; i < classCount; i++) {
        if (classes[i].classId == classId) {
            return 1;
        }
    }
    return 0;
}

void addclass() {
    if (classCount >= MAX_CLASSES) {
        printf("无法增加更多的班级。\n");
        return;
    }

    int classId;
    printf("输入班级ID: ");
    scanf("%d", &classId);

    if (isClassIdExist(classId)) {
        printf("班级ID已存在。\n");
        return;
    }

    classes[classCount].classId = classId;
    printf("输入班级名称: ");
    scanf("%s", classes[classCount].className);
    classes[classCount].studentCount = 0;
    classCount++;
    savedata();
    printf("班级添加成功。\n");
}

void deleteclass() {
    int classId;
    printf("输入要删除的班级ID: ");
    scanf("%d", &classId);

    if (!isClassIdExist(classId)) {
        printf("无效的班级ID。\n");
        return;
    }

    int i;
    for (i = 0; i < classCount; i++) {
        if (classes[i].classId == classId) {
            break;
        }
    }

    for (; i < classCount - 1; i++) {
        classes[i] = classes[i + 1];
    }
    classCount--;
    savedata();
    printf("班级删除成功。\n");
}
