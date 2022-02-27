#include <limits.h>
struct tree_t {
  struct tree_t *left;
  struct tree_t *right;
  int data;
};

int Real_Check_Is_Bst (struct tree_t *top, int left_bord, int right_bord)
{
    int res = -1;
    if (top->left)
    {
        if (top->left->data <= top->data && top->left->data >= left_bord)
        {
            res = Real_Check_Is_Bst (top->left, left_bord, top->data);
            if (res == 0)
                return 0;
        }
        else
            return 0;
    }
    if (top->right)
    {
        if (top->right->data >= top->data && top->right->data <= right_bord)
            res = Real_Check_Is_Bst (top->right, top->data, right_bord);
        else
            return 0;
    }

    if (res == -1)
        return 1;
    return res;
}

int check_is_bst(struct tree_t *top)
{
    return Real_Check_Is_Bst (top, 0, INT_MAX);
}
