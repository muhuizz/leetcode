/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
#include <algorithm>
#include <vector>
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* head = nullptr;
        ListNode* tail = nullptr;

        // 1. 剔除空节点
        int i = 0;
        while (i < lists.size()) {
            if (lists[i] == nullptr) {
                lists[i] = lists[lists.size()-1];
                lists.pop_back();
            } else {
                i++;
            }
        }
        if (lists.empty()) return nullptr;

        // 2. merge
        std::make_heap(lists.begin(), lists.end(), Solution::Less);
        while (!lists.empty()) {
            ListNode* new_node = lists[0]->next;
            if (head == nullptr) {
                head = lists[0];
                tail = lists[0];
            } else {
                tail->next = lists[0];
                tail = tail->next;
            }

            std::pop_heap(lists.begin(), lists.end(), Solution::Less);
            lists.pop_back();
            if (new_node) {
                lists.push_back(new_node);
                std::push_heap(lists.begin(), lists.end(), Solution::Less);
            }
        }
        return head;
    }
    static bool Less(ListNode* left, ListNode* right) {
        return left->val > right->val;
    }
};
