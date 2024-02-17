#include <stdio.h>
#include <stdlib.h>

/*
You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [7,0,8]
Explanation: 342 + 465 = 807.

Input: l1 = [0], l2 = [0]
Output: [0]

Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
Output: [8,9,9,9,0,0,0,1]

*/

struct ListNode {
    int val;
    struct ListNode *next;
};

static struct ListNode* allocNode() {
    struct ListNode* head = (struct ListNode*)calloc(1, sizeof(struct ListNode));
    if (head == NULL) {
        fprintf(stderr, "memory allocation error\n");
        return NULL;
    }
    return head;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    struct ListNode *head = NULL, *tail = NULL, *tmp;
    int carry = 0;

    head = tail = allocNode();
    do {
        if (l1) {
            tail->val += l1->val;
            l1 = l1->next;
        }
        if (l2) {
            tail->val += l2->val;
            l2 = l2->next;
        }

        if (tail->val >= 10) {
            carry = 1;
            tail->val %= 10;
        } else {
            carry = 0;
        }
        if (l1 || l2 || carry) {
            tail->next = allocNode();
            tail = tail->next;
            tail->val += carry;
            carry = 0;
        }
    } while (l1 || l2);

    return head;
}

int main(int argc, char* argv[])
{

    return 0;
}
