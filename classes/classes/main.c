#include <stdio.h>
#include "class.h"
#include "student.h"
#include "teacher.h"
#include "utils.h"

void displaymenu() {
    printf("\n主菜单:\n");
    printf("1. 显示班级列表\n");
    printf("2. 增加班级\n");
    printf("3. 删除班级\n");
    printf("4. 班级同学录入\n");
    printf("5. 班级同学删除\n");
    printf("6. 显示指定班级同学录\n");
    printf("7. 查找学生或教师\n");
    printf("8. 增加教师\n");
    printf("9. 删除教师\n");
    printf("10. 修改或删除联系方式\n");
    printf("11. 退出\n");
    printf("请选择一个选项: ");
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
            printf("下次记得想我！\n");
            break;
        default:
            printf("不要捣乱啦~\n");
        }

    } while (choice != 11);
}

int main() {
    run();
    return 0;
}
