struct node_t {
    struct node_t* next;
    int data;
};

struct node_t* CreateNode (struct node_t* last, int data);
void DeleteList (struct node_t* top);