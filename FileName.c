#define  _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100
#define M 2

typedef struct student {
    long long id;       // 学号
    char name[15];      // 姓名
    char major[15];     // 专业
    int score[M];       // 成绩
    int sum;            // 总分
    struct student* next;
} stu;

// 菜单函数
void menu() {
    printf("******************学生信息管理系统******************\n");
    printf("1、输入信息\n");
    printf("2、输出全部信息\n");
    printf("3、删除信息\n");
    printf("4、修改信息\n");
    printf("5、搜索信息\n");
    printf("6、总成绩按降序排列\n");
    printf("7、总成绩按升序排列\n");
    printf("8、学号按降序排列\n");
    printf("9、学号按升序排列\n");
    printf("10、班级平均分\n");
    printf("11、写入文件\n");
    printf("12、读入文件\n");
    printf("13、查看菜单\n");
    printf("0、退出\n");
}

// 添加学生信息
stu* input(stu* head, int n) {
    long long id;
    char name[15];
    char major[15];
    int score[M];

    for (int j = 0; j < n; ++j) {
        int sum = 0;

        printf("请输入第%d位学生的学号：", j + 1);
        scanf("%lld", &id);
        printf("请输入姓名：");
        scanf("%s", name);
        printf("请输入专业：");
        scanf("%s", major);

        for (int i = 0; i < M; i++) {
            printf("请输入成绩%d：", i + 1);
            scanf("%d", &score[i]);
            sum += score[i];
        }

        stu* newStudent = (stu*)malloc(sizeof(stu));
        if (newStudent == NULL) {
            printf("内存分配失败\n");
            return head;
        }

        newStudent->id = id;
        strcpy(newStudent->name, name);
        strcpy(newStudent->major, major);

        for (int i = 0; i < M; i++) {
            newStudent->score[i] = score[i];
        }
        newStudent->sum = sum;
        newStudent->next = head;
        head = newStudent;
    }

    return head;
}

// 删除学生信息
stu* del(stu* head, long long id) {
    stu* current = head;
    stu* previous = NULL;

    while (current != NULL && current->id != id) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("学号为 %lld 的学生不存在.\n", id);
        return head;
    }

    if (previous == NULL) {
        head = current->next;
    }
    else {
        previous->next = current->next;
    }

    free(current);
    return head;
}

// 输出所有学生信息
void output(stu* head) {
    stu* current = head;
    printf("\n\n-------------------------------------------------------\n");
    printf("学号\t\t姓名\t专业\t成绩\t\t总分\n");
    printf("=======================================================\n");
    while (current != NULL) {
        printf("%lld\t%s\t%s\t", current->id, current->name, current->major);
        for (int j = 0; j < M; j++) {
            printf("%d\t", current->score[j]);
        }
        printf("%d\n", current->sum);
        printf("-------------------------------------------------------\n");
        current = current->next;
    }
}

// 查找学生信息
void search(stu* head) {
    stu* current = head;
    long long id;
    char name[15];
    int q;
    int found = 0;

    printf("请确定使用姓名查找还是使用学号查找\n");
    printf("若要使用姓名查找请输入 1\n");
    printf("若要使用学号查找请输入 2\n");

    if (scanf("%d", &q) != 1 || (q != 1 && q != 2)) {
        printf("输入错误，请重新输入\n");
        return;
    }

    switch (q) {
    case 1:
        printf("请输入想要查找学生的姓名：");
        scanf("%s", name);
        break;
    case 2:
        printf("请输入想要查找学生的学号：");
        if (scanf("%lld", &id) != 1) {
            printf("输入错误，请重新输入\n");
            return;
        }
        break;
    }

    while (current != NULL) {
        if ((q == 1 && strcmp(current->name, name) == 0) || (q == 2 && current->id == id)) {
            printf("\n\n-------------------------------------------------------\n");
            printf("学号\t\t姓名\t专业\t成绩\t\t总分\n");
            printf("=======================================================\n");
            printf("%lld\t%s\t%s\t", current->id, current->name, current->major);
            for (int j = 0; j < M; j++) {
                printf("%d\t", current->score[j]);
            }
            printf("%d\n", current->sum);
            printf("-------------------------------------------------------\n");
            found = 1;
            break;
        }
        current = current->next;
    }

    if (!found) {
        printf("未找到符合条件的学生。\n");
    }
}
//修改学生

void modify(stu* head, long long id) {
    char name[15];
    char major[15];
    int score[M];
    int sum = 0;
    stu* current = head;
    while (current != NULL) {
        
        if (current->id == id) {
            printf("请输入该学号学生修改后的姓名: ");
            scanf("%s", current->name);
            printf("请输入该学号学生修改后的专业: ");
            scanf("%s", current->major);
            for (int i = 0; i < M; i++) {
            printf("请输入该学号学生修改后的成绩%d: ",i+1);
            scanf("%d", &(current->score[i]));
            sum += current->score[i];
            }
            current->sum = sum;
            printf("学号为 %lld 的学生信息已修改完成。\n", id);
            return;
        }
        current = current->next;
    }
    printf("没有找到学号为 %lld 的学生。\n", id);
}

//按学号升序排序学生
stu* sort_na(stu* head) {
    if (!head || !head->next) return head;

    stu* sorted = NULL;

    while (head) {
        stu* current = head;
        head = head->next;

        if (!sorted || current->id < sorted->id) {
            current->next = sorted;
            sorted = current;
        }
        else {
            stu* temp = sorted;
            while (temp->next && current->id > temp->next->id) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }
        // 打印排序后的链表
        printf("\n\n-------------------------------------------------------\n");
        printf("学号\t\t姓名\t专业\t成绩\t\t总分\n");
        printf("=======================================================\n");
        stu* print_node = sorted;
        while (print_node != NULL) {
            printf("%lld\t%s\t%s\t", print_node->id, print_node->name, print_node->major);
            for (int j = 0; j < M; j++) {
                printf("%d\t", print_node->score[j]);
            }
            printf("%d\n", print_node->sum);
            print_node = print_node->next;
            printf("-------------------------------------------------------\n");
        }
    
    return sorted;
}


// 排序学生（按学号降序）
stu* sort_nd(stu* head) {
    if (!head || !head->next) return head;

    stu* sorted = NULL;

    while (head) {
        stu* current = head;
        head = head->next;

        if (!sorted || current->id > sorted->id) {
            current->next = sorted;
            sorted = current;
        }
        else {
            stu* temp = sorted;
            while (temp->next && current->id < temp->next->id) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }
    printf("\n\n-------------------------------------------------------\n");
    printf("学号\t\t姓名\t专业\t成绩\t\t总分\n");
    printf("=======================================================\n");
    stu* print_node = sorted;
    while (print_node != NULL) {
        printf("%lld\t%s\t%s\t", print_node->id, print_node->name, print_node->major);
        for (int j = 0; j < M; j++) {
            printf("%d\t", print_node->score[j]);
        }
        printf("%d\n", print_node->sum);
        print_node = print_node->next;
        printf("-------------------------------------------------------\n");
    }

    return sorted;
}

// 排序学生（按成绩升序）
stu* sort_sa(stu* head) {
    if (!head || !head->next) return head;

    stu* sorted = NULL;

    while (head) {
        stu* current = head;
        head = head->next;

        if (!sorted || current->sum < sorted->sum) {
            current->next = sorted;
            sorted = current;
        }
        else {
            stu* temp = sorted;
            while (temp->next && current->sum > temp->next->sum) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }
    printf("\n\n-------------------------------------------------------\n");
    printf("学号\t\t姓名\t专业\t成绩\t\t总分\n");
    printf("=======================================================\n");
    stu* print_node = sorted;
    while (print_node != NULL) {
        printf("%lld\t%s\t%s\t", print_node->id, print_node->name, print_node->major);
        for (int j = 0; j < M; j++) {
            printf("%d\t", print_node->score[j]);
        }
        printf("%d\n", print_node->sum);
        print_node = print_node->next;
        printf("-------------------------------------------------------\n");
    }

    return sorted;
}

// 排序学生（按成绩降序）
stu* sort_sd(stu* head) {
    if (!head || !head->next) return head;

    stu* sorted = NULL;

    while (head) {
        stu* current = head;
        head = head->next;

        if (!sorted || current->sum > sorted->sum) {
            current->next = sorted;
            sorted = current;
        }
        else {
            stu* temp = sorted;
            while (temp->next && current->sum < temp->next->sum) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }
    printf("\n\n-------------------------------------------------------\n");
    printf("学号\t\t姓名\t专业\t成绩\t\t总分\n");
    printf("=======================================================\n");
    stu* print_node = sorted;
    while (print_node != NULL) {
        printf("%lld\t%s\t%s\t", print_node->id, print_node->name, print_node->major);
        for (int j = 0; j < M; j++) {
            printf("%d\t", print_node->score[j]);
        }
        printf("%d\n", print_node->sum);
        print_node = print_node->next;
        printf("-------------------------------------------------------\n");
    }


    return sorted;
}

// 求学生的总成绩平均值
void average(stu* head) {
    stu* current = head;
    float ave;
    int sumscore = 0;
    int count = 0;

    while (current != NULL) {
        sumscore += current->sum;
        count++;
        current = current->next;
    }

    if (count == 0) {
        printf("学生数量为0，无法计算平均成绩。\n");
        return;
    }

    ave = (float)sumscore / count;
    printf("平均总分: %.2f\n", ave);
}

// 将学生信息写入文件
void write_to_file(stu* head) {
    FILE* file = fopen("students.txt", "w");
    if (!file) {
        printf("无法打开文件写入.\n");
        return;
    }

    stu* current = head;
    while (current != NULL) {
        fprintf(file, "%lld %s %s", current->id, current->name, current->major);
        for (int j = 0; j < M; j++) {
            fprintf(file, " %d", current->score[j]);
        }
        fprintf(file, " %d\n", current->sum);
        current = current->next;
    }

    printf("写入文件成功！\n");
    fclose(file);
}

// 从文件读取学生信息并插入链表
stu* read_from_file() {
    FILE* file = fopen("students.txt", "r");
    if (!file) {
        printf("无法打开文件读取.\n");
        return NULL;
    }

    stu* head = NULL;
    long long id;
    int score[M];
    char name[15];
    char major[15];
    int sum;

    while (fscanf(file, "%lld %s %s", &id, name, major) != EOF) {
        for (int j = 0; j < M; j++) {
            fscanf(file, "%d", &score[j]);
        }
        fscanf(file, "%d", &sum);

        stu* newStudent = (stu*)malloc(sizeof(stu));
        if (newStudent == NULL) {
            printf("内存分配失败\n");
            fclose(file);
            return head;
        }

        newStudent->id = id;
        strcpy(newStudent->name, name);
        strcpy(newStudent->major, major);
        for (int i = 0; i < M; i++) {
            newStudent->score[i] = score[i];
        }
        newStudent->sum = sum;
        printf("读取文件成功！");
        newStudent->next = head;
        head = newStudent;
    }

    fclose(file);
    return head;
}

int main() {
    stu* head = NULL;
    int choice;
    long long id;
    int score[M];
    char name[15];
    char major[15];
    int sum;
    stu* student;
    const char* filename = "students.txt";
    menu();

    int n;
    printf("\n请输入要处理学生的个数 :\n");
    scanf("%d", &n);

    while (1) {
        printf("\n\n请输入编号：\n");
        int m;
        scanf("%d", &m);

        switch (m) {
        case 1: head = input(head, n); break;
        case 2: output(head); break;
        case 3: {
            printf("请输入被删除学生的学号：\n");
            scanf("%lld", &id);
            head = del(head, id); break;
        }
        case 4: {
             printf("请输入被修改学生的学号：\n");
             long long id;
             scanf("%lld", &id);
             modify( head, id);
            break;
        }
        case 5: search(head); break;
        case 6: head = sort_sd(head); break;
        case 7: head = sort_sa(head); break;
        case 8: head = sort_nd(head); break;
        case 9: head = sort_na(head); break;
        case 10: average(head); break;
        case 11: write_to_file(head); break;
        case 12: head = read_from_file(); break;
        case 13: menu(); break;
        case 0:
            // 退出程序前释放所有学生的内存
            while (head != NULL) {
                stu* temp = head;
                head = head->next;
                free(temp);
            }
            return 0;
        default:
            printf("输入错误，请重新输入。\n");
            break;
        }
    }

    return 0;
}
