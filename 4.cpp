#include <iostream>
#include<string>
#include<algorithm>
using namespace std;
class tnode
{
public:
    char ch;
    tnode *left;
    tnode *right;
};
class tree
{
public:
    tnode *tree;
    void creat(char *);
    tnode *construct_Postfix(string postfix);
    tnode *construct_Prefix(string pretfix);
    bool isOperator(char c);
    void inorder_recursive(tnode *);
    void preorder_recursive(tnode *);
    void postorder_recursive(tnode *);
    void inorder_nonrecursive(tnode *);
    void preorder_nonrecursive(tnode *);
    void postorder_nonrecursive(tnode *);
};
class snode
{
public:
    tnode *ptval;
    snode *nxt;
};
class stack
{
public:
    snode *top;

    stack()
    {
        top = NULL;
    }
    void push(tnode *);
    bool empty();
    snode *pop();
};
bool stack ::empty()
{
    if (top == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void stack ::push(tnode *new_data)
{
    snode *new_node = new snode();
    new_node->ptval = new_data;
    new_node->nxt = top;
    top = new_node;
}
snode *stack ::pop()
{
    if (empty())
    {
        cout << "Stack is Empty" << endl;
    }
    else
    {
        snode *temp = top;
        top = top->nxt;
        delete (temp);
        return top;
    }
}
bool tree ::isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}


tnode *tree ::construct_Postfix(string postfix)
{
    if (postfix.length() == 0)
    {
        return nullptr;
    }

    stack s;

    for (char c : postfix)
    {

        if (isOperator(c))
        {
            tnode *x = s.top->ptval;
            s.pop();

            tnode *y = s.top->ptval;
            s.pop();

            tnode *node = new tnode;
            node->ch = c;
            node->left = y;
            node->right = x;
            s.push(node);
        }
        else
        {
            tnode *node = new tnode;
            node->ch = c;
            node->left = NULL;
            node->right = NULL;
            s.push(node);
        }
    }
    return s.top->ptval;
}
tnode *tree :: construct_Prefix(string prefix)
{
    tnode* temp;
    tnode* root = NULL ;
    reverse(prefix.begin(),prefix.end());
    stack s;
    for (int i = 0; i < prefix.length() ; i++)
    {
        if(prefix[i] >= 'a'  && prefix[i] <= 'z')
        {
            temp = new tnode();
            temp->ch = prefix[i];
            temp->left = temp->right = NULL;
            s.push(temp);
        }
        else
        {
            root = new tnode();
            root->ch = prefix[i];
            root->left = root->right = NULL;
            s.pop();
            root->left = s.top->ptval;
            s.pop();
            root->right = s.top->ptval;
            s.push(root);
        }
    }
    s.pop();
    return s.top->ptval;
}
void tree::inorder_recursive(tnode *root)
{
    if (root != NULL)
    {
        inorder_recursive(root->left);
        cout << root->ch << " ";
        inorder_recursive(root->right);
    }
}
void tree::preorder_recursive(tnode *root)
{
    if (root != NULL)
    {
        cout << root->ch << " ";
        preorder_recursive(root->left);
        preorder_recursive(root->right);
    }
}
void tree::postorder_recursive(tnode *root)
{
    if (root != NULL)
    {
        postorder_recursive(root->left);
        postorder_recursive(root->right);
        cout << root->ch << " ";
    }
}
void tree::inorder_nonrecursive(tnode *root)
{
    stack s;
    tnode *curr = root;

    while (curr != NULL || s.empty() == false)
    {
        while (curr != NULL)
        {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top->ptval;
        s.pop();

        cout << curr->ch << " ";
        curr = curr->right;
    }
}
void tree::preorder_nonrecursive(tnode *root)
{
    if (root == NULL)
        return;

    stack s;
    s.push(root);

    while (s.empty() == false)
    {
        struct tnode *node = s.top->ptval;
        printf("%c ", node->ch);
        s.pop();

        if (node->right)
            s.push(node->right);
        if (node->left)
            s.push(node->left);
    }
}
void tree::postorder_nonrecursive(tnode *root)
{
    if (root == NULL)
        return;

    stack s1, s2;

    s1.push(root);
    tnode *node;

    while (!s1.empty())
    {

        node = s1.top->ptval;
        s1.pop();
        s2.push(node);

        if (node->left)
            s1.push(node->left);
        if (node->right)
            s1.push(node->right);
    }

    while (!s2.empty())
    {
        node = s2.top->ptval;
        s2.pop();
        cout << node->ch << " ";
    }
}
int main()
{
    string postfix = "+ab";
    tree t;
    tnode *root = t.construct_Prefix(postfix);

    cout << "\nInfix Expression with recursion: ";
    t.inorder_recursive(root);

    cout << "\nPrefix Expression with recursion: ";
    t.preorder_recursive(root);

    cout << "\nPostfix Expression with recursion: ";
    t.postorder_recursive(root);

    cout << "\nInfix Expression with non-recursion: ";
    t.inorder_nonrecursive(root);

    cout << "\nPrefix Expression with non-recursion: ";
    t.preorder_nonrecursive(root);

    cout << "\nPostfix Expression with non-recursion: ";
    t.postorder_nonrecursive(root);

    return 0;
}
