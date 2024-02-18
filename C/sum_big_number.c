#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
You are given two non-empty linked lists representing two non-negative
integers. The digits are stored in reverse order, and each of their nodes 
contains a single digit. Add the two numbers and return the sum as a linked 
list.

You may assume the two numbers do not contain any leading zero, except the 
number 0 itself.

Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [7,0,8]
Explanation: 342 + 465 = 807.

Input: l1 = [0], l2 = [0]
Output: [0]

Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
Output: [8,9,9,9,0,0,0,1]

*/
#define BASE 10

typedef struct ListNode {
    int val;
    struct ListNode *next;
} node_t;

static struct ListNode* alloc_node() {
    struct ListNode* head = calloc(1, sizeof(struct ListNode));
    if (head == NULL) {
        fprintf(stderr, "memory allocation error\n");
        return NULL;
    }
    head->val = 0;
    head->next = NULL;
    return head;
}

node_t* append_node(node_t* pre_node, int bit_value) {
    node_t* node = alloc_node();
    if (!node) {
        return NULL;
    }

    node->val = bit_value;
    node->next = pre_node->next;
    pre_node->next = node;
    return node;
}

void free_list(node_t* head) {
    node_t* next = NULL;

    while (head) {
        next = head->next;
        free(head);
        head = next;
    }
}

node_t* int_to_number(unsigned long long integer) {
    node_t* node = alloc_node();
    if (!node) {
        return NULL;
    }

    node_t* head = node;
    node->val = integer % BASE;
    integer /= BASE;

    while (integer) {
        if (!(node = append_node(node, integer % BASE))) {
            free_list(head);
            return NULL;
        }
        integer /= BASE;
    }

    return head;
}

void dump_list(const node_t* head) {
    while (head) {
        fprintf(stderr, "%d", head->val);
        head = head->next;
    }
    fprintf(stderr, "\n");
}

static int semi_adder(int lhs, int rhs, int* carry) {
    assert(carry);

    int sum = lhs + rhs + *carry;
    if (sum >= BASE) {
        *carry = 1;
        sum -= BASE;
    } else {
        *carry = 0;
    }

    return sum;
}

node_t* add_two_numbers(const node_t* num1, const node_t* num2) {
    node_t* head = NULL, *tail = NULL;
    int carry = 0, lhs = 0, rhs = 0;

    while (carry || num1 || num2) {
        if (num1) {
            lhs = num1->val;
            num1 = num1->next;
        } else {
            lhs = 0;
        }
        if (num2) {
            rhs = num2->val;
            num2 = num2->next;
        } else {
            rhs = 0;
        }

        if (!head) {
            head = alloc_node();
            tail = head;
            tail->val = semi_adder(lhs, rhs, &carry);
        } else {
            tail = append_node(tail, semi_adder(lhs, rhs, &carry));
        }
    }

    return head;
}


int main(int argc, char* argv[])
{
    node_t* number1 = int_to_number(342);
    node_t* number2 = int_to_number(465);
    dump_list(number1);
    dump_list(number2);

    node_t* number3 = add_two_numbers(number1, number2);
    dump_list(number3);

    free_list(number1);
    number1 = NULL;
    free_list(number2);
    number2 = NULL;
    free_list(number3);
    number3 = NULL;
    return 0;
}
