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
    printf("����ѧ�������༶ID: ");
    scanf("%d", &classId);

    if (!isClassIdExist(classId)) {
        printf("��Ч�İ༶ID��\n");
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
        printf("�ð༶ѧ��������\n");
        return;
    }

    Student stu;
    printf("����ѧ��ѧ��: ");
    scanf("%d", &stu.studentId);

    if (isStudentIdExist(stu.studentId)) {
        printf("ѧ��ѧ���Ѵ��ڡ�\n");
        return;
    }

    printf("����ѧ������: ");
    scanf("%s", stu.name);
    printf("����ѧ���Ա�: ");
    scanf("%s", stu.gender);
    stu.classId = classId;

    printf("ѡ����ϵ��ʽ���� (1: Email, 2: Phone, 3: None): ");
    int contactChoice;
    scanf("%d", &contactChoice);
    if (contactChoice == 1) {
        printf("����Email: ");
        scanf("%s", stu.contactInfo);
        strcpy(stu.contactType, "Email");
    }
    else if (contactChoice == 2) {
        printf("����Phone: ");
        scanf("%s", stu.contactInfo);
        strcpy(stu.contactType, "Phone");
    }
    else {
        strcpy(stu.contactInfo, "��");
        strcpy(stu.contactType, "��");
    }

    cls->students[cls->studentCount] = stu;
    cls->studentCount++;
    savedata();
    printf("ѧ����ӳɹ���\n");
}

void deletestudent() {
    int classId, studentId;
    printf("����ѧ�������༶ID: ");
    scanf("%d", &classId);

    if (!isClassIdExist(classId)) {
        printf("��Ч�İ༶ID��\n");
        return;
    }

    Class* cls = NULL;
    for (int i = 0; i < classCount; i++) {
        if (classes[i].classId == classId) {
            cls = &classes[i];
            break;
        }
    }

    printf("����Ҫɾ����ѧ��ѧ��: ");
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
            printf("ѧ��ɾ���ɹ���\n");
            break;
        }
    }

    if (!found) {
        printf("δ�ҵ�ѧ����\n");
    }
}

void showclassstudents() {
    int classId;
    printf("����༶ID: ");
    scanf("%d", &classId);

    if (!isClassIdExist(classId)) {
        printf("��Ч�İ༶ID��\n");
        return;
    }

    Class* cls = NULL;
    for (int i = 0; i < classCount; i++) {
        if (classes[i].classId == classId) {
            cls = &classes[i];
            break;
        }
    }

    printf("�༶����: %s, ѧ����: %d\n", cls->className, cls->studentCount);
    printf("��ʦ: %s\n", cls->teacher.name);
    for (int i = 0; i < cls->studentCount; i++) {
        Student* stu = &cls->students[i];
        printf("����: %s, �Ա�: %s, ѧ��: %d, ��ϵ��ʽ: %s (%s)\n",
            stu->name, stu->gender, stu->studentId, stu->contactInfo, stu->contactType);
    }
}

void searchByContactInfo() {
    char contactInfo[50];
    printf("������ϵ��ʽ: ");
    scanf("%s", contactInfo);

    int found = 0;
    // ����ѧ��
    for (int i = 0; i < classCount; i++) {
        for (int j = 0; j < classes[i].studentCount; j++) {
            if (strcmp(classes[i].students[j].contactInfo, contactInfo) == 0) {
                printf("�ҵ���ѧ��:\n");
                printf("����: %s, �Ա�: %s, ѧ��: %d, �༶ID: %d\n",
                    classes[i].students[j].name, classes[i].students[j].gender,
                    classes[i].students[j].studentId, classes[i].students[j].classId);
                found = 1;
            }
        }
    }

    // ���ҽ�ʦ
    for (int i = 0; i < teacherCount; i++) {
        if (strcmp(teachers[i].contactInfo, contactInfo) == 0) {
            printf("�ҵ��Ľ�ʦ:\n");
            printf("����: %s, �Ա�: %s, ��ѧ��Ŀ: %s, �༶ID: %d\n",
                teachers[i].name, teachers[i].gender, teachers[i].subject, teachers[i].classId);
            found = 1;
        }
    }

    if (!found) {
        printf("δ�ҵ�ƥ�����ϵ��ʽ��\n");
    }
}

void modifyOrDeleteContactInfo() {
    int entityType;
    printf("�޸Ļ�ɾ����ϵ��ʽ (1: ѧ��, 2: ��ʦ): ");
    scanf("%d", &entityType);

    int classId, id;
    printf("����༶ID: ");
    scanf("%d", &classId);

    if (!isClassIdExist(classId)) {
        printf("��Ч�İ༶ID��\n");
        return;
    }

    if (entityType == 1) {
        printf("����ѧ��ѧ��: ");
        scanf("%d", &id);

        for (int i = 0; i < classCount; i++) {
            if (classes[i].classId == classId) {
                for (int j = 0; j < classes[i].studentCount; j++) {
                    if (classes[i].students[j].studentId == id) {
                        printf("1. �޸���ϵ��ʽ\n2. ɾ����ϵ��ʽ\nѡ�����: ");
                        int choice;
                        scanf("%d", &choice);

                        if (choice == 1) {
                            printf("ѡ����ϵ��ʽ���� (1: Email, 2: Phone): ");
                            int contactChoice;
                            scanf("%d", &contactChoice);
                            if (contactChoice == 1) {
                                printf("����Email: ");
                                scanf("%s", classes[i].students[j].contactInfo);
                                strcpy(classes[i].students[j].contactType, "Email");
                            }
                            else if (contactChoice == 2) {
                                printf("����Phone: ");
                                scanf("%s", classes[i].students[j].contactInfo);
                                strcpy(classes[i].students[j].contactType, "Phone");
                            }
                        }
                        else if (choice == 2) {
                            strcpy(classes[i].students[j].contactInfo, "��");
                            strcpy(classes[i].students[j].contactType, "��");
                        }

                        savedata();
                        printf("�����ɹ���\n");
                        return;
                    }
                }
            }
        }
    }
    else if (entityType == 2) {
        printf("�����ʦ����: ");
        char name[50];
        scanf("%s", name);

        for (int i = 0; i < teacherCount; i++) {
            if (teachers[i].classId == classId && strcmp(teachers[i].name, name) == 0) {
                printf("1. �޸���ϵ��ʽ\n2. ɾ����ϵ��ʽ\nѡ�����: ");
                int choice;
                scanf("%d", &choice);

                if (choice == 1) {
                    printf("ѡ����ϵ��ʽ���� (1: Email, 2: Phone): ");
                    int contactChoice;
                    scanf("%d", &contactChoice);
                    if (contactChoice == 1) {
                        printf("����Email: ");
                        scanf("%s", teachers[i].contactInfo);
                        strcpy(teachers[i].contactType, "Email");
                    }
                    else if (contactChoice == 2) {
                        printf("����Phone: ");
                        scanf("%s", teachers[i].contactInfo);
                        strcpy(teachers[i].contactType, "Phone");
                    }
                }
                else if (choice == 2) {
                    strcpy(teachers[i].contactInfo, "��");
                    strcpy(teachers[i].contactType, "��");
                }

                for (int j = 0; j < classCount; j++) {
                    if (classes[j].classId == classId) {
                        classes[j].teacher = teachers[i];
                        break;
                    }
                }

                savedata();
                printf("�����ɹ���\n");
                return;
            }
        }
    }

    printf("δ�ҵ������Ϣ��\n");
}
