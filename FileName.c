#define  _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100
#define M 2

typedef struct student {
    long long id;       // ѧ��
    char name[15];      // ����
    char major[15];     // רҵ
    int score[M];       // �ɼ�
    int sum;            // �ܷ�
    struct student* next;
} stu;

// �˵�����
void menu() {
    printf("******************ѧ����Ϣ����ϵͳ******************\n");
    printf("1��������Ϣ\n");
    printf("2�����ȫ����Ϣ\n");
    printf("3��ɾ����Ϣ\n");
    printf("4���޸���Ϣ\n");
    printf("5��������Ϣ\n");
    printf("6���ܳɼ�����������\n");
    printf("7���ܳɼ�����������\n");
    printf("8��ѧ�Ű���������\n");
    printf("9��ѧ�Ű���������\n");
    printf("10���༶ƽ����\n");
    printf("11��д���ļ�\n");
    printf("12�������ļ�\n");
    printf("13���鿴�˵�\n");
    printf("0���˳�\n");
}

// ���ѧ����Ϣ
stu* input(stu* head, int n) {
    long long id;
    char name[15];
    char major[15];
    int score[M];

    for (int j = 0; j < n; ++j) {
        int sum = 0;

        printf("�������%dλѧ����ѧ�ţ�", j + 1);
        scanf("%lld", &id);
        printf("������������");
        scanf("%s", name);
        printf("������רҵ��");
        scanf("%s", major);

        for (int i = 0; i < M; i++) {
            printf("������ɼ�%d��", i + 1);
            scanf("%d", &score[i]);
            sum += score[i];
        }

        stu* newStudent = (stu*)malloc(sizeof(stu));
        if (newStudent == NULL) {
            printf("�ڴ����ʧ��\n");
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

// ɾ��ѧ����Ϣ
stu* del(stu* head, long long id) {
    stu* current = head;
    stu* previous = NULL;

    while (current != NULL && current->id != id) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("ѧ��Ϊ %lld ��ѧ��������.\n", id);
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

// �������ѧ����Ϣ
void output(stu* head) {
    stu* current = head;
    printf("\n\n-------------------------------------------------------\n");
    printf("ѧ��\t\t����\tרҵ\t�ɼ�\t\t�ܷ�\n");
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

// ����ѧ����Ϣ
void search(stu* head) {
    stu* current = head;
    long long id;
    char name[15];
    int q;
    int found = 0;

    printf("��ȷ��ʹ���������һ���ʹ��ѧ�Ų���\n");
    printf("��Ҫʹ���������������� 1\n");
    printf("��Ҫʹ��ѧ�Ų��������� 2\n");

    if (scanf("%d", &q) != 1 || (q != 1 && q != 2)) {
        printf("�����������������\n");
        return;
    }

    switch (q) {
    case 1:
        printf("��������Ҫ����ѧ����������");
        scanf("%s", name);
        break;
    case 2:
        printf("��������Ҫ����ѧ����ѧ�ţ�");
        if (scanf("%lld", &id) != 1) {
            printf("�����������������\n");
            return;
        }
        break;
    }

    while (current != NULL) {
        if ((q == 1 && strcmp(current->name, name) == 0) || (q == 2 && current->id == id)) {
            printf("\n\n-------------------------------------------------------\n");
            printf("ѧ��\t\t����\tרҵ\t�ɼ�\t\t�ܷ�\n");
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
        printf("δ�ҵ�����������ѧ����\n");
    }
}
//�޸�ѧ��

void modify(stu* head, long long id) {
    char name[15];
    char major[15];
    int score[M];
    int sum = 0;
    stu* current = head;
    while (current != NULL) {
        
        if (current->id == id) {
            printf("�������ѧ��ѧ���޸ĺ������: ");
            scanf("%s", current->name);
            printf("�������ѧ��ѧ���޸ĺ��רҵ: ");
            scanf("%s", current->major);
            for (int i = 0; i < M; i++) {
            printf("�������ѧ��ѧ���޸ĺ�ĳɼ�%d: ",i+1);
            scanf("%d", &(current->score[i]));
            sum += current->score[i];
            }
            current->sum = sum;
            printf("ѧ��Ϊ %lld ��ѧ����Ϣ���޸���ɡ�\n", id);
            return;
        }
        current = current->next;
    }
    printf("û���ҵ�ѧ��Ϊ %lld ��ѧ����\n", id);
}

//��ѧ����������ѧ��
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
        // ��ӡ����������
        printf("\n\n-------------------------------------------------------\n");
        printf("ѧ��\t\t����\tרҵ\t�ɼ�\t\t�ܷ�\n");
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


// ����ѧ������ѧ�Ž���
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
    printf("ѧ��\t\t����\tרҵ\t�ɼ�\t\t�ܷ�\n");
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

// ����ѧ�������ɼ�����
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
    printf("ѧ��\t\t����\tרҵ\t�ɼ�\t\t�ܷ�\n");
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

// ����ѧ�������ɼ�����
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
    printf("ѧ��\t\t����\tרҵ\t�ɼ�\t\t�ܷ�\n");
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

// ��ѧ�����ܳɼ�ƽ��ֵ
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
        printf("ѧ������Ϊ0���޷�����ƽ���ɼ���\n");
        return;
    }

    ave = (float)sumscore / count;
    printf("ƽ���ܷ�: %.2f\n", ave);
}

// ��ѧ����Ϣд���ļ�
void write_to_file(stu* head) {
    FILE* file = fopen("students.txt", "w");
    if (!file) {
        printf("�޷����ļ�д��.\n");
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

    printf("д���ļ��ɹ���\n");
    fclose(file);
}

// ���ļ���ȡѧ����Ϣ����������
stu* read_from_file() {
    FILE* file = fopen("students.txt", "r");
    if (!file) {
        printf("�޷����ļ���ȡ.\n");
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
            printf("�ڴ����ʧ��\n");
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
        printf("��ȡ�ļ��ɹ���");
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
    printf("\n������Ҫ����ѧ���ĸ��� :\n");
    scanf("%d", &n);

    while (1) {
        printf("\n\n�������ţ�\n");
        int m;
        scanf("%d", &m);

        switch (m) {
        case 1: head = input(head, n); break;
        case 2: output(head); break;
        case 3: {
            printf("�����뱻ɾ��ѧ����ѧ�ţ�\n");
            scanf("%lld", &id);
            head = del(head, id); break;
        }
        case 4: {
             printf("�����뱻�޸�ѧ����ѧ�ţ�\n");
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
            // �˳�����ǰ�ͷ�����ѧ�����ڴ�
            while (head != NULL) {
                stu* temp = head;
                head = head->next;
                free(temp);
            }
            return 0;
        default:
            printf("����������������롣\n");
            break;
        }
    }

    return 0;
}
