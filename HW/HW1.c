#include <stdio.h>
#include <stdlib.h>

// 定义树节点的孩子链结构
typedef struct ChildNode {
    int childIndex;             // 孩子的索引
    struct ChildNode *next;     // 指向下一个孩子的指针
} ChildNode;

// 定义树的节点
typedef struct TreeNode {
    char data;                  // 节点数据
    ChildNode *firstChild;      // 指向第一个孩子的指针
} TreeNode;

// 定义树
TreeNode tree[10];              // 假设最多有 10 个节点
int nodeCount = 0;              // 当前节点数量

// 创建一个新节点
int createNode(char data) {
    tree[nodeCount].data = data;
    tree[nodeCount].firstChild = NULL;
    return nodeCount++;
}

// 为节点添加一个孩子
void addChild(int parentIndex, int childIndex) {
    ChildNode *newChild = (ChildNode *)malloc(sizeof(ChildNode));
    newChild->childIndex = childIndex;
    newChild->next = NULL;

    if (tree[parentIndex].firstChild == NULL) {
        tree[parentIndex].firstChild = newChild;
    } else {
        ChildNode *temp = tree[parentIndex].firstChild;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newChild;
    }
}

// 显示树的孩子表示法
void displayTree() {
    printf("\n树的孩子表示法:\n");
    for (int i = 0; i < nodeCount; i++) {
        printf("%d(%c) -> ", i, tree[i].data);
        ChildNode *temp = tree[i].firstChild;
        while (temp != NULL) {
            printf("%d ", temp->childIndex);
            temp = temp->next;
        }
        printf("^"); // 表示链表结束
        printf("\n");
    }
}

// 先序遍历
void preOrderTraversal(int index) {
    if (index == -1) return;

    // 访问当前节点
    printf("%c ", tree[index].data);

    // 遍历孩子链
    ChildNode *child = tree[index].firstChild;
    while (child != NULL) {
        preOrderTraversal(child->childIndex);
        child = child->next;
    }
}

// 主函数
int main() {
    int rootIndex, childIndex;
    char data;

    printf("请输入根节点的数据: ");
    scanf(" %c", &data);
    rootIndex = createNode(data); // 创建根节点

    // 动态输入树的结构
    while (1) {
        char parentData, childData;
        printf("请输入父节点数据和子节点数据（输入 ^ ^ 表示结束）：");
        scanf(" %c %c", &parentData, &childData);

        if (parentData == '^' && childData == '^') {
            break; // 结束输入
        }

        // 找到父节点索引
        int parentIndex = -1;
        for (int i = 0; i < nodeCount; i++) {
            if (tree[i].data == parentData) {
                parentIndex = i;
                break;
            }
        }

        if (parentIndex == -1) {
            printf("未找到父节点 %c\n", parentData);
            continue;
        }

        // 创建子节点并添加到父节点的孩子链
        childIndex = createNode(childData);
        addChild(parentIndex, childIndex);
    }

    // 显示树的孩子表示法
    displayTree();

    // 先序遍历
    printf("\n先序遍历结果:\n");
    preOrderTraversal(rootIndex);
    printf("\n");

    return 0;
}