// 标题
// 单链表每隔k个元素做一次反转

// 题目描述
// 给定一个链表,每隔k个元素做一次反转

// Example:
// Inputs: 1->2->3->4->5->6->7->8->NULL and k = 3
// Output: 3->2->1->6->5->4->8->7->NULL.

// Inputs: 1->2->3->4->5->6->7->8->NULL and k = 5
// Output: 5->4->3->2->1->8->7->6->NULL.

# include <iostream>

struct ListNode {
    ListNode* next;
    int val;
    ListNode(int x, ListNode* h): val(x),next(h) {}
    ListNode(int x): val(x),next(nullptr) {}
};

ListNode* reverseK(ListNode* head, int k) {
    if (!head || k<=1) {
        return head;
    }
    ListNode* dummy = new ListNode(0, nullptr);
    ListNode* pretail = dummy;
    ListNode* cur = head;
    int cnt = 0;
    while (cur) {
        ListNode* curhead = cur;
        while (cur && cnt<k) {
            ListNode* tmp = pretail->next;
            pretail->next = cur;
            cur = cur->next;
            pretail->next->next = tmp;
            cnt++;
        }
        pretail = curhead;
        cnt = 0;
    }
    ListNode* ans = dummy->next;
    delete dummy;
    return ans;
}

int main() {
    ListNode* list = new ListNode(1);
    list->next = new ListNode(2);
    list->next->next = new ListNode(3);
    list->next->next->next = new ListNode(4);
    list->next->next->next->next = new ListNode(5);
    list->next->next->next->next->next = new ListNode(6);
    list->next->next->next->next->next->next = new ListNode(7);
    list->next->next->next->next->next->next->next = new ListNode(8);
    list = reverseK(list, 3);
    ListNode * tmp = list;
    while (tmp) {
        std::cout << tmp->val << " ";
        tmp = tmp->next;
    }
    std::cout<<"\n";
    while(tmp) {
        ListNode* d = tmp;
        delete d;
        tmp = tmp->next;
    }
    return 0;
}
