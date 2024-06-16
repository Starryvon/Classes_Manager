#include <stdio.h>
#include <string.h>
#include "teacher.h"
#include "class.h"
#include "utils.h"

Teacher teachers[MAX_TEACHERS];
int teacherCount = 0;

void addteacher() {
    if (teacherCount >= MAX_TEACHERS) {
        printf("�޷����Ӹ���Ľ�ʦ��\n");
        return;
    }

    Teacher teacher;
    printf("�����ʦ�༶ID: ");
    scanf("%d", &teacher.classId);

    if (!isClassIdExist(teacher.classId)) {
        printf("��Ч�İ༶ID��\n");
        return;
    }

    printf("�����ʦ����: ");
    scanf("%s", teacher.name);
    printf("�����ʦ�Ա�: ");
    scanf("%s", teacher.gender);
    printf("�����ѧ��Ŀ: ");
    scanf("%s", teacher.subject);

    printf("ѡ����ϵ��ʽ���� (1: Email, 2: Phone, 3: None): ");
    int contactChoice;
    scanf("%d", &contactChoice);
    if (contactChoice == 1) {
        printf("����Email: ");
        scanf("%s", teacher.contactInfo);
        strcpy(teacher.contactType, "Email");
    }
    else if (contactChoice == 2) {
        printf("����Phone: ");
        scanf("%s", teacher.contactInfo);
        strcpy(teacher.contactType, "Phone");
    }
    else {
        strcpy(teacher.contactInfo, "��");
        strcpy(teacher.contactType, "��");
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
    printf("��ʦ��ӳɹ���\n");
}

void deleteteacher() {
    int classId;
    printf("�����ʦ�༶ID: ");
    scanf("%d", &classId);

    if (!isClassIdExist(classId)) {
        printf("��Ч�İ༶ID��\n");
        return;
    }

    int i;
    for (i = 0; i < teacherCount; i++) {
        if (teachers[i].classId == classId) {
            break;
        }
    }

    if (i == teacherCount) {
        printf("δ�ҵ���ʦ��\n");
        return;
    }

    for (int j = i; j < teacherCount - 1; j++) {
        teachers[j] = teachers[j + 1];
    }
    teacherCount--;

    for (int k = 0; k < classCount; k++) {
        if (classes[k].classId == classId) {
            strcpy(classes[k].teacher.name, "��");
            break;
        }
    }

    savedata();
    printf("��ʦɾ���ɹ���\n");
}
