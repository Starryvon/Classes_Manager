#include <stdio.h>
#include "class.h"
#include "student.h"
#include "teacher.h"
#include "utils.h"

void displaymenu() {
    printf("\n���˵�:\n");
    printf("1. ��ʾ�༶�б�\n");
    printf("2. ���Ӱ༶\n");
    printf("3. ɾ���༶\n");
    printf("4. �༶ͬѧ¼��\n");
    printf("5. �༶ͬѧɾ��\n");
    printf("6. ��ʾָ���༶ͬѧ¼\n");
    printf("7. ����ѧ�����ʦ\n");
    printf("8. ���ӽ�ʦ\n");
    printf("9. ɾ����ʦ\n");
    printf("10. �޸Ļ�ɾ����ϵ��ʽ\n");
    printf("11. �˳�\n");
    printf("��ѡ��һ��ѡ��: ");
}

void run() {
    loaddata();
    int choice;
    do {
        displaymenu();
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            displayclasslist();
            break;
        case 2:
            addclass();
            break;
        case 3:
            deleteclass();
            break;
        case 4:
            addstudent();
            break;
        case 5:
            deletestudent();
            break;
        case 6:
            showclassstudents();
            break;
        case 7:
            searchByContactInfo();
            break;
        case 8:
            addteacher();
            break;
        case 9:
            deleteteacher();
            break;
        case 10:
            modifyOrDeleteContactInfo();
            break;
        case 11:
            printf("�´μǵ����ң�\n");
            break;
        default:
            printf("��Ҫ������~\n");
        }

    } while (choice != 11);
}

int main() {
    run();
    return 0;
}
