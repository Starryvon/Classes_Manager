#include <stdio.h>
#include <string.h>
#include "class.h"
#include "utils.h"

Class classes[MAX_CLASSES];
int classCount = 0;

void displayclasslist() {
    printf("\n�༶�б�:\n");
    printf("�༶����: %d\n", classCount);
    for (int i = 0; i < classCount; i++) {
        printf("�༶����: %s, �༶ID: %d, ѧ����: %d, ��ʦ: %s\n",
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
        printf("�޷����Ӹ���İ༶��\n");
        return;
    }

    int classId;
    printf("����༶ID: ");
    scanf("%d", &classId);

    if (isClassIdExist(classId)) {
        printf("�༶ID�Ѵ��ڡ�\n");
        return;
    }

    classes[classCount].classId = classId;
    printf("����༶����: ");
    scanf("%s", classes[classCount].className);
    classes[classCount].studentCount = 0;
    classCount++;
    savedata();
    printf("�༶��ӳɹ���\n");
}

void deleteclass() {
    int classId;
    printf("����Ҫɾ���İ༶ID: ");
    scanf("%d", &classId);

    if (!isClassIdExist(classId)) {
        printf("��Ч�İ༶ID��\n");
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
    printf("�༶ɾ���ɹ���\n");
}
