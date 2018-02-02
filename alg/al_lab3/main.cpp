#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

typedef struct node {
    int val;
    struct node * next;
} node_t;

node *head, *tail;

void print_list(node_t *head) {
    node_t *current = head;

    while (current != NULL) {
        printf("%d\t", current->val);
        current = current->next;
    }
    printf("\n");
}

//int pop(node_t ** head);
int remove_by_value(node_t **head, int val);

void insert_max_elem(node **head, int x);
void sort(node **head);

//void delete_list(node_t *head) {
//    node_t  *current = head,
//            *next = head;
//
//    while (current) {
//        next = current->next;
//        free(current);
//        current = next;
//    }
//}

void createnode(int value, node **head) {
    node *temp = new node;

    temp->val=value;
    temp->next=NULL;

    if (*head==NULL) {
        *head=temp;
        tail=temp;
        temp=NULL;
    } else {
        tail->next=temp;
        tail=temp;
    }
}
//
//void change_position(node *first_elem, node *first_prev, node *second_elem, node *second_prev) {
//    if (first_elem == second_elem) {
//        return;
//    }
//    node *tmp = first_elem;
//    first_elem->next = second_elem->next;
//    second_elem->next = tmp->next;
//
//    first_prev->next = second_elem;
//    second_prev->next = first_elem;
//}

void swap(struct node **Node, int x, int y);

int main(void) {
    srand (time(NULL));
    int val;

    int list_length = 10;
    int arr[9] = {63, 98, 13, 48, 39, 75, 49, 41, 19};
    for(int i = 1; i < list_length; i++) {
//        val = rand() % 100 + 1;
        val = arr[i-1];
        createnode(val, &head);
    }

    printf("Print list: \n");
    print_list(head);
    printf("\n *********** \n");
//
    int min_val, max_val;
    min_val = max_val = head->val;
    node *current = head;

    while (current) {
        if (current->val < min_val)
            min_val = current->val;
        if (current->val > max_val)
            max_val = current->val;
        current = current->next;
    }

    printf("Min: %d \n", min_val);
    printf("Max: %d \n", max_val);
    swap(&head, min_val, max_val);
    print_list(head);


    printf("********** Remove 10 \n");
    remove_by_value(&head, 9);
    print_list(head);

    printf("********** Find next max and insert max \n");
    int some_max = 4;
    insert_max_elem(&head, some_max);
    print_list(head);

    printf("********** Sort \n");
    sort(&head);
    print_list(head);

    printf("Adding at the end of list desc list \n");

    int array[9] = {1, 2, 3, 1, 2, 3, 3, 2, 1};

    for (int l = sizeof(array)/sizeof(array[0]) - 1;l >= 0; l--) {
        createnode(array[l], &head);
    }
    print_list(head);


    return 0;
}


void swap(struct node **Node, int x, int y) {
    if (x == y) return;

    struct node * prevX = NULL, *currX = *Node;
    while(currX && currX->val != x) {
        prevX = currX;
        currX = currX->next;
    }

    struct node * prevY = NULL, *currY = *Node;
    while(currY && currY->val != y) {
        prevY = currY;
        currY = currY->next;
    }

    if (prevX != NULL)
        prevX->next = currY;
    else
        *Node = currY;

    if (prevY != NULL)
        prevY->next = currX;
    else
        *Node = currX;

    struct node *tmp = currY->next;
    currY->next = currX->next;
    currX->next = tmp;
}

int remove_by_value(node_t **head, int val) {
    node_t *previous, *current;

    if (*head == NULL) {
        return -1;
    }

    if ((*head)->val == val) {
        node *next_node = NULL;
        next_node = (*head)->next;
        free(*head);
        *head = next_node;
    }

    previous = current = (*head)->next;

    while (current) {
        if (current->val == val) {
            previous->next = current->next;
            free(current);
            return val;
        }

        previous = current;
        current  = current->next;
    }

    return -1;
}

void insert_max_elem(node **head, int x) {
    struct node * prevX = NULL, *next_max = NULL, *currX = *head;

    while(currX->next != NULL) {

        if (currX->val > x) {
            next_max = currX;
            break;
        }

        currX = currX->next;

//        printf("\n currX->val < x: %d , x - %d \n", currX->val < x, currX->val );
    }

    if (currX->next == NULL) {
        return;
    }

    printf("Some text\n");
    printf("next_max %d \n", next_max->val);

    //TODO find max in head.
//    int arr[9] = {96, 21, 85, 8, 15, 18, 22, 73, 47};
    struct node *max = *head;
    struct node *current = *head;
    struct node *previous = *head, *max_prev = NULL;

    while (current->next != NULL) {
        if (current->val > max->val) {
            max_prev = previous;
            max = current;
        }
        previous = current;
        current = current->next;
    }

    printf("max in head %d \n", max->val);
    if (max_prev)
        printf("prev of max head %d \n", max_prev->val);

    // Inserting.

    if (next_max == max) {
        return;
    }
    if (max_prev)
    {
        max_prev->next = max->next;
    } else {
        *head = next_max;
    }


    max->next = next_max->next;
    next_max->next = max;
}

void sort(node **head) {
    struct node *outer = *head, *inner = NULL;
    struct node *inner_next = NULL, *inner_last = NULL;
    int count = 0;
    while (outer != NULL) {
        count++;
        outer = outer->next;
    }

    for (int i = 0; i < count; i++) {
        inner = *head;
        while(inner->next != NULL && inner != inner_last) {
            inner_next = inner->next;
            if (inner->val > inner_next->val) {
                swap(head, inner->val, inner_next->val);
            } else {
                inner = inner->next;
            }
        }
        if(inner->next == NULL) {
            tail = inner;
        }

        inner_last = inner;
    }

}

