#include <stdio.h>
#include <stdlib.h>

// 定义二叉树节点结构体
typedef struct Node
{
    int data;           // 节点存储的数据
    struct Node *left;  // 左子节点指针
    struct Node *right; // 右子节点指针
} Node;

Node *temp, *newNode; // 全局变量，用于插入操作和遍历操作

// 定义二叉树结构体
typedef struct
{
    Node *root; // 根节点指针
} Tree;

// 向二叉搜索树中插入一个新的节点
void insertTree(Node **root, int num) // 获取二级指针,因为传入的是tree.root,一级指针递归是无法影响到实际根节点的变动的
{
    newNode = (Node *)malloc(sizeof(Node)); // 分配新节点内存空间
    newNode->data = num;                    // 设置新节点的数据
    newNode->left = NULL;                   // 初始化左子节点为空
    newNode->right = NULL;                  // 初始化右子节点为空

    if (*root == NULL) // 如果根节点为空，直接将新节点作为根节点
    {
        *root = newNode;
        return;
    }

    temp = *root; // 临时变量指向根节点

    // 根据二叉搜索树的性质，将新节点插入到合适的位置
    if (num < temp->data) // 如果新节点的值小于当前节点的值，递归插入左子树
    {
        insertTree(&(*root)->left, num); // 将*root的地址传递,正确的更新根节点
    }
    else if (num > temp->data) // 如果新节点的值大于当前节点的值，递归插入右子树
    {
        insertTree(&(*root)->right, num);
    }
    else if (num == temp->data) // 如果新节点的值等于当前节点的值，不允许插入相同值的节点
    {
        printf("不能输入相同值");
        return;
    }
}

// 先序遍历二叉树
void proshow(Node *ndoe)
{
    if (ndoe == NULL) // 如果节点为空，返回
    {
        return;
    }

    printf("%d ", ndoe->data); // 访问当前节点
    proshow(ndoe->left);       // 递归遍历左子树
    proshow(ndoe->right);      // 递归遍历右子树
}

// 中序遍历二叉树
void modshow(Node *ndoe)
{
    if (ndoe == NULL) // 如果节点为空，返回
    {
        return;
    }

    modshow(ndoe->left);       // 递归遍历左子树
    printf("%d ", ndoe->data); // 访问当前节点
    modshow(ndoe->right);      // 递归遍历右子树
}

// 后序遍历二叉树
void lastshow(Node *ndoe)
{
    if (ndoe == NULL) // 如果节点为空，返回
    {
        return;
    }

    lastshow(ndoe->left);      // 递归遍历左子树
    lastshow(ndoe->right);     // 递归遍历右子树
    printf("%d ", ndoe->data); // 访问当前节点
}

// 获取二叉树的高度
int get_hight_(Node *node)
{
    if (node == NULL) // 如果节点为空，返回0
    {
        return 0;
    }
    else
    {
        int left_h = get_hight_(node->left);   // 递归计算左子树的高度
        int right_h = get_hight_(node->right); // 递归计算右子树的高度
        int max = left_h;                      // 初始化最大高度为左子树的高度
        if (left_h < right_h)                  // 如果右子树的高度大于左子树的高度，更新最大高度
        {
            max = right_h;
        }
        return max + 1; // 返回最大高度加1（包括当前节点）
    }
}

// 获取二叉树的最大值
int get_MAxnum(Node *node)
{
    if (node == NULL) // 如果节点为空，返回-1表示不存在最大值
    {
        return -1;
    }
    else
    {
        int left_num = get_MAxnum(node->left);   // 递归获取左子树的最大值
        int right_num = get_MAxnum(node->right); // 递归获取右子树的最大值
        int nude = node->data;                   // 当前节点的值
        int max = left_num;                      // 初始化最大值为左子树的最大值
        if (right_num > max)                     // 如果右子树的最大值大于当前最大值，更新最大值
        {
            max = right_num;
        }
        if (nude > max) // 如果当前节点的值大于当前最大值，更新最大值
        {
            max = nude;
        }
        return max; // 返回最大值
    }
}

// 在二叉树中查找指定值的节点
void find_Tree(Node *node, int find)
{
    if (node != NULL) // 如果节点不为空，继续查找
    {
        if (find == node->data) // 如果找到目标值，输出并返回
        {
            printf("\n存在 值为：%d", node->data);
            return;
        }
        else // 如果目标值不在当前节点，根据二叉搜索树的性质，向左或向右子树查找
        {
            if (find < node->data)
            {
                find_Tree(node->left, find);
            }
            else
            {
                find_Tree(node->right, find);
            }
        }
    }
    else if (node == NULL) // 如果节点为空，说明查找失败，输出提示信息
    {
        printf("\n查找值不存在！");
    }
}
Node* findMin(Node* node) {
    if (node == NULL) {
        return NULL;
    }
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}
// 删除二叉树
Node *deleteTree(Node **node, int num)
{
    if (*node == NULL)
    {
        return NULL;
    }
    if (num > (*node)->data)
    {
        (*node)->left = deleteTree(&(*node)->left, num);
    }
    else if (num < (*node)->data)
    {
        (*node)->right = deleteTree(&(*node)->right, num);
    }
    else if (num == (*node)->data)
    {
        if ((*node)->right == NULL && (*node)->left == NULL)
        { 
            Node *temp = *node;
            free(temp);
            *node = NULL;
        }
        else if ((*node)->right && (*node)->left == NULL)
        {
            Node *temp = *node;
            *node = (*node)->right;
            free(temp);
        }
        else if ((*node)->right == NULL && (*node)->left)
        {
            Node *temp = *node;
            *node = (*node)->left;
            free(temp);
        }
        else
        {
            Node *minValueNode = findMin((*node)->right);
            (*node)->data = minValueNode->data;
            (*node)->right = deleteTree(&(*node)->right, minValueNode->data);
        }
    }
    return *node;
}


int main()
{
    Tree tree;        // 创建二叉树对象
    tree.root = NULL; // 初始化根节点为空
    int str[7] = {6, 3, 8, 2, 5, 1, 7};
    for (int i = 0; i < 7; i++)
    {
        insertTree(&tree.root, str[i]); // 调用插入函数插入数值到二叉搜索树中 需要用到二级指针
    }
    printf("先序遍历：");                      // 输出先序遍历结果
    proshow(tree.root);                        // 调用先序遍历函数进行遍历并输出结果
    printf("\n中序遍历：");                    // 输出中序遍历结果
    modshow(tree.root);                        // 调用中序遍历函数进行遍历并输出结果
    printf("\n后序遍历：");                    // 输出后序遍历结果
    lastshow(tree.root);                       // 调用后序遍历函数进行遍历并输出结果
    int h = get_hight_(tree.root);             // 获取二叉树的高度并赋值给变量h
    printf("\n数的度为：%d", h);               // 输出二叉树的高度
    printf("\nmax:%d", get_MAxnum(tree.root)); // 输出二叉树的最大值并赋值给变量max，然后输出该值
    find_Tree(tree.root, 7);                   // 查找值为1的节点并输出结果
    find_Tree(tree.root, 9);                   // 查找值为9的节点并输出结果（不存在）
    deleteTree(&tree.root, 7);
    printf("\n中序遍历：");
    modshow(tree.root);  
    return 0; 
}