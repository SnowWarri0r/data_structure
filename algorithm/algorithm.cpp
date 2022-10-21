//
// Created by SnowWarrior on 2021/12/23.
//
#include <vector>
#include <random>
#include <algorithm>
#include<iostream>
#include<chrono>
#include <utility>
#include <queue>

using namespace std;

struct Node {
    int val;
    Node *next{};

    explicit Node(int val) : val(val) {}
};

struct TreeNode {
    int val;
    TreeNode *left{};
    TreeNode *right{};

    explicit TreeNode(int val) : val(val) {}
};

TreeNode *createBST(vector<int> &nums) {
    if (nums.empty()) return nullptr;
    auto *root = new TreeNode(nums[0]);
    for (int i = 1; i < nums.size(); i++) {
        auto *cur = root;
        int x = nums[i];
        while (cur != nullptr) {
            if (x < cur->val) {
                if (cur->left != nullptr) {
                    cur = cur->left;
                } else {
                    cur->left = new TreeNode(x);
                    break;
                }
            } else if (x > cur->val) {
                if (cur->right != nullptr) {
                    cur = cur->right;
                } else {
                    cur->right = new TreeNode(x);
                    break;
                }
            } else break;
        }
    }
    return root;
}

void level_order_traversal(TreeNode *root) {
    if (root == nullptr) return;
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
        auto *cur = q.front();
        q.pop();
        cout << cur->val << " ";
        if (cur->left != nullptr) q.push(cur->left);
        if (cur->right != nullptr) q.push(cur->right);
    }
}

Node *generateRandom(Node *head, int n) {
    random_device rd{};
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(1, n);
    Node *p = head;
    for (int i = 0; i < n; ++i) {
        dist.param(uniform_int_distribution<int>(i, n).param());
        Node *node = new Node(dist(mt));
        node->next = p;
        p = node;
    }
    return p;
}

vector<int> generateRandom(int n) {
    random_device rd{};
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(1, n);
    vector<int> res;
    for (int i = 0; i < n; i++) {
        dist.param(uniform_int_distribution<int>(i, n).param());
        res.push_back(dist(mt));
    }
    return res;
}

int find_sequence(vector<int> &nums, int num) {
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] == num) {
            return i;
        }
    }
    return -1;
}

int find_split(vector<int> &nums, int num) {
    vector<pair<int, int>> pairs(nums.size());
    for (int i = 0; i < nums.size(); ++i) {
        pairs[i] = make_pair(nums[i], i);
    }
    sort(pairs.begin(), pairs.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
        return a.first < b.first;
    });
    int l = 0, r = (int) pairs.size();
    while (l < r) {
        int mid = l + ((r - l) >> 1);
        if (pairs[mid].first == num) return pairs[mid].second;
        if (pairs[mid].first < num) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return -1;
}

int find_node(Node *head, int x) {
    Node *p = head;
    int i = 0;
    while (p != nullptr) {
        if (p->val == x) {
            return i;
        }
        p = p->next;
        i++;
    }
    return -1;
}

void test1();

void test2();

void test3();

void test4();

int main() {
    test1();
    test2();
    test3();
    test4();
    return 0;
}

void test1() {
    vector<int> nums1 = generateRandom(10000);
    chrono::steady_clock::time_point start1 = chrono::steady_clock::now();
    cout << find_sequence(nums1, 7) << endl;
    chrono::steady_clock::time_point end1 = chrono::steady_clock::now();
    chrono::duration<double> time_span1 = duration_cast<chrono::duration<double>>(end1 - start1);
    cout << time_span1.count() * 1000 << "ms" << endl;

    vector<int> nums2 = generateRandom(50000);
    chrono::steady_clock::time_point start2 = chrono::steady_clock::now();
    cout << find_sequence(nums2, 7) << endl;
    chrono::steady_clock::time_point end2 = chrono::steady_clock::now();
    chrono::duration<double> time_span2 = duration_cast<chrono::duration<double>>(end2 - start2);
    cout << time_span2.count() * 1000 << "ms" << endl;

    vector<int> nums3 = generateRandom(100000);
    chrono::steady_clock::time_point start3 = chrono::steady_clock::now();
    cout << find_sequence(nums3, 7) << endl;
    chrono::steady_clock::time_point end3 = chrono::steady_clock::now();
    chrono::duration<double> time_span3 = duration_cast<chrono::duration<double>>(end3 - start3);
    cout << time_span3.count() * 1000 << "ms" << endl;

    vector<int> num4 = generateRandom(200000);
    chrono::steady_clock::time_point start4 = chrono::steady_clock::now();
    cout << find_sequence(num4, 7) << endl;
    chrono::steady_clock::time_point end4 = chrono::steady_clock::now();
    chrono::duration<double> time_span4 = duration_cast<chrono::duration<double>>(end4 - start4);
    cout << time_span4.count() * 1000 << "ms" << endl;

    vector<int> num5 = generateRandom(300000);
    chrono::steady_clock::time_point start5 = chrono::steady_clock::now();
    cout << find_sequence(num5, 7) << endl;
    chrono::steady_clock::time_point end5 = chrono::steady_clock::now();
    chrono::duration<double> time_span5 = duration_cast<chrono::duration<double>>(end5 - start5);
    cout << time_span5.count() * 1000 << "ms" << endl;

    vector<int> num6 = generateRandom(400000);
    chrono::steady_clock::time_point start6 = chrono::steady_clock::now();
    cout << find_sequence(num6, 7) << endl;
    chrono::steady_clock::time_point end6 = chrono::steady_clock::now();
    chrono::duration<double> time_span6 = duration_cast<chrono::duration<double>>(end6 - start6);
    cout << time_span6.count() * 1000 << "ms" << endl;

    vector<int> num7 = generateRandom(500000);
    chrono::steady_clock::time_point start7 = chrono::steady_clock::now();
    cout << find_sequence(num7, 7) << endl;
    chrono::steady_clock::time_point end7 = chrono::steady_clock::now();
    chrono::duration<double> time_span7 = duration_cast<chrono::duration<double>>(end7 - start7);
    cout << time_span7.count() * 1000 << "ms" << endl;
}

void test2() {
    Node *nums1 = new Node(-1);
    nums1 = generateRandom(nums1, 10000);
    chrono::steady_clock::time_point start1 = chrono::steady_clock::now();
    cout << find_node(nums1, 7) << endl;
    chrono::steady_clock::time_point end1 = chrono::steady_clock::now();
    chrono::duration<double> time_span1 = duration_cast<chrono::duration<double>>(end1 - start1);
    cout << time_span1.count() * 1000 << "ms" << endl;

    Node *nums2 = new Node(-1);
    nums2 = generateRandom(nums2, 50000);
    chrono::steady_clock::time_point start2 = chrono::steady_clock::now();
    cout << find_node(nums2, 7) << endl;
    chrono::steady_clock::time_point end2 = chrono::steady_clock::now();
    chrono::duration<double> time_span2 = duration_cast<chrono::duration<double>>(end2 - start2);
    cout << time_span2.count() * 1000 << "ms" << endl;

    Node *nums3 = new Node(-1);
    nums3 = generateRandom(nums3, 100000);
    chrono::steady_clock::time_point start3 = chrono::steady_clock::now();
    cout << find_node(nums3, 7) << endl;
    chrono::steady_clock::time_point end3 = chrono::steady_clock::now();
    chrono::duration<double> time_span3 = duration_cast<chrono::duration<double>>(end3 - start3);
    cout << time_span3.count() * 1000 << "ms" << endl;

    Node *num4 = new Node(-1);
    num4 = generateRandom(num4, 200000);
    chrono::steady_clock::time_point start4 = chrono::steady_clock::now();
    cout << find_node(num4, 7) << endl;
    chrono::steady_clock::time_point end4 = chrono::steady_clock::now();
    chrono::duration<double> time_span4 = duration_cast<chrono::duration<double>>(end4 - start4);
    cout << time_span4.count() * 1000 << "ms" << endl;

    Node *num5 = new Node(-1);
    num5 = generateRandom(num5, 300000);
    chrono::steady_clock::time_point start5 = chrono::steady_clock::now();
    cout << find_node(num5, 7) << endl;
    chrono::steady_clock::time_point end5 = chrono::steady_clock::now();
    chrono::duration<double> time_span5 = duration_cast<chrono::duration<double>>(end5 - start5);
    cout << time_span5.count() * 1000 << "ms" << endl;

    Node *num6 = new Node(-1);
    num6 = generateRandom(num6, 400000);
    chrono::steady_clock::time_point start6 = chrono::steady_clock::now();
    cout << find_node(num6, 7) << endl;
    chrono::steady_clock::time_point end6 = chrono::steady_clock::now();
    chrono::duration<double> time_span6 = duration_cast<chrono::duration<double>>(end6 - start6);
    cout << time_span6.count() * 1000 << "ms" << endl;

    Node *num7 = new Node(-1);
    num7 = generateRandom(num7, 500000);
    chrono::steady_clock::time_point start7 = chrono::steady_clock::now();
    cout << find_node(num7, 7) << endl;
    chrono::steady_clock::time_point end7 = chrono::steady_clock::now();
    chrono::duration<double> time_span7 = duration_cast<chrono::duration<double>>(end7 - start7);
    cout << time_span7.count() * 1000 << "ms" << endl;
}

void test3() {
    vector<int> nums1 = generateRandom(10000);
    chrono::steady_clock::time_point start1 = chrono::steady_clock::now();
    cout << find_split(nums1, 7) << endl;
    chrono::steady_clock::time_point end1 = chrono::steady_clock::now();
    chrono::duration<double> time_span1 = duration_cast<chrono::duration<double>>(end1 - start1);
    cout << time_span1.count() * 1000 << "ms" << endl;

    vector<int> nums2 = generateRandom(50000);
    chrono::steady_clock::time_point start2 = chrono::steady_clock::now();
    cout << find_split(nums2, 7) << endl;
    chrono::steady_clock::time_point end2 = chrono::steady_clock::now();
    chrono::duration<double> time_span2 = duration_cast<chrono::duration<double>>(end2 - start2);
    cout << time_span2.count() * 1000 << "ms" << endl;

    vector<int> nums3 = generateRandom(100000);
    chrono::steady_clock::time_point start3 = chrono::steady_clock::now();
    cout << find_split(nums3, 7) << endl;
    chrono::steady_clock::time_point end3 = chrono::steady_clock::now();
    chrono::duration<double> time_span3 = duration_cast<chrono::duration<double>>(end3 - start3);
    cout << time_span3.count() * 1000 << "ms" << endl;

    vector<int> num4 = generateRandom(200000);
    chrono::steady_clock::time_point start4 = chrono::steady_clock::now();
    cout << find_split(num4, 7) << endl;
    chrono::steady_clock::time_point end4 = chrono::steady_clock::now();
    chrono::duration<double> time_span4 = duration_cast<chrono::duration<double>>(end4 - start4);
    cout << time_span4.count() * 1000 << "ms" << endl;

    vector<int> num5 = generateRandom(300000);
    chrono::steady_clock::time_point start5 = chrono::steady_clock::now();
    cout << find_split(num5, 7) << endl;
    chrono::steady_clock::time_point end5 = chrono::steady_clock::now();
    chrono::duration<double> time_span5 = duration_cast<chrono::duration<double>>(end5 - start5);
    cout << time_span5.count() * 1000 << "ms" << endl;

    vector<int> num6 = generateRandom(400000);
    chrono::steady_clock::time_point start6 = chrono::steady_clock::now();
    cout << find_split(num6, 7) << endl;
    chrono::steady_clock::time_point end6 = chrono::steady_clock::now();
    chrono::duration<double> time_span6 = duration_cast<chrono::duration<double>>(end6 - start6);
    cout << time_span6.count() * 1000 << "ms" << endl;

    vector<int> num7 = generateRandom(500000);
    chrono::steady_clock::time_point start7 = chrono::steady_clock::now();
    cout << find_split(num7, num7[200000]) << endl;
    chrono::steady_clock::time_point end7 = chrono::steady_clock::now();
    chrono::duration<double> time_span7 = duration_cast<chrono::duration<double>>(end7 - start7);
    cout << time_span7.count() * 1000 << "ms" << endl;
}

void test4() {
    vector<int> nums = generateRandom(10);
    for (auto &i: nums) {
        cout << i << " ";
    }
    cout << endl;
    auto tree = createBST(nums);
    level_order_traversal(tree);
}