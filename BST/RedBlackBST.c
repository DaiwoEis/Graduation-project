#include "RedBlackBST.h"

typedef struct Node Node;

int(*cmpFun)(Key left, Key right);

static const RED = true;
static const BLACK = false;

struct RedBlackBST
{
	Node* root;
};

struct Node
{
	Node* left;
	Node* right;
	Key key;
	Value value;
	int size;
	bool color;
};

Node* RBNode_Create(Key key, Value value, bool color, int size);
int RBNode_Size(const Node* node);
bool Node_IsRed(const Node* node);
void RBNode_RecaculateSize(Node* node);
Node* RBNode_RotateRight(Node* root);
Node* RBNode_RotateLeft(Node* root);
void RBNode_FlipColors(Node* root);
Node* RBNode_Add(Node* root, Key key, Value value);
Node* RBNode_Get(Node* root, Key key);
void RBNode_Keys(Node* root, Queue* queue);

int RedBlackBST_DefaultCmp(Key left, Key right);
void RedBlackBST_DeleteNode(Node* root);

Node* RBNode_Create(Key key, Value value,bool color, int size)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->key = key;
	node->value = value;
	node->color = color;
	node->size = size;
	node->left = node->right = NULL;
	return node;
}

int RBNode_Size(const Node* node)
{
	if (node == NULL) return 0;
	return node->size;
}

bool Node_IsRed(const Node* node)
{
	if (node == NULL) return false;
	return node->color == RED;
}

void RBNode_RecaculateSize(Node* node)
{
	node->size = RBNode_Size(node->left) + RBNode_Size(node->right) + 1;
}

RedBlackBST* RedBlackBST_Create()
{
	return RedBlackBST_Create_Cmp(NULL);
}

RedBlackBST* RedBlackBST_Create_Cmp(int(*pCmp)(Key left, Key right))
{
	RedBlackBST* bst = (RedBlackBST*)malloc(sizeof(RedBlackBST));
	bst->root = NULL;
	if (pCmp == NULL)
		cmpFun = RedBlackBST_DefaultCmp;
	else
		cmpFun = pCmp;
	return bst;
}

void RedBlackBST_Delete(RedBlackBST** bst)
{
	if (*bst == NULL) return;
	RedBlackBST_DeleteNode((*bst)->root);
	free(*bst);
	*bst = NULL;
}

void RedBlackBST_Add(RedBlackBST* bst, Key key, Value value)
{
	bst->root = RBNode_Add(bst->root, key, value);
	bst->root->color = BLACK;
}

Value RedBlackBST_Get(const RedBlackBST* bst, Key key)
{
	Node* node = RBNode_Get(bst->root, key);
	if (node == NULL)
	{
		puts("Not found!");
		return 0;
	}
	else
	{
		return node->value;
	}
}

bool RedBlackBST_Contains(const RedBlackBST* bst, Key key)
{
	Node* node = RBNode_Get(bst->root, key);
	return node == NULL;
}

bool RedBlackBST_IsEmpty(const RedBlackBST* bst)
{
	return bst->root == NULL;
}

int RedBlackBST_Size(const RedBlackBST* bst)
{
	return RBNode_Size(bst->root);
}

Queue* RedBlackBST_Keys(RedBlackBST* bst)
{
	Queue* queue = Queue_Create();
	RBNode_Keys(bst->root, queue);
	return queue;
}

void RBNode_Keys(Node* root, Queue* queue)
{
	if (root == NULL) return;

	RBNode_Keys(root->left, queue);
	Queue_EnQueue(queue, root->key);
	RBNode_Keys(root->right, queue);
}

Node* RBNode_Get(Node* root, Key key)
{
	if (root == NULL) return NULL;
	int cmp = cmpFun(key, root->key);
	if (cmp < 0) return RBNode_Get(root->left, key);
	else if (cmp > 0) return RBNode_Get(root->right, key);
	else return root;
}

Node* RBNode_Add(Node* root, Key key, Value value)
{
	if (root == NULL)
		return RBNode_Create(key, value, BLACK, 1);

	int cmp = cmpFun(key, root->key);
	if (cmp < 0) root->left = RBNode_Add(root->left, key, value);
	else if (cmp > 0) root->right = RBNode_Add(root->right, key, value);
	else root->value = value;

	if (Node_IsRed(root->right) && !Node_IsRed(root->left)) root = RBNode_RotateRight(root);
	if (Node_IsRed(root->left) && Node_IsRed(root->left->left)) root = RBNode_RotateLeft(root);
	if (Node_IsRed(root->left) && Node_IsRed(root->right)) RBNode_FlipColors(root);
	RBNode_RecaculateSize(root);
	return root;
}

void RedBlackBST_DeleteNode(Node* root)
{
	if (root == NULL) return;

	RedBlackBST_DeleteNode(root->left);
	RedBlackBST_DeleteNode(root->right);
	free(root);
	root = NULL;
}

int RedBlackBST_DefaultCmp(Key left, Key right)
{
	if (left < right) return -1;
	if (left > right) return 1;
	return 0;
}

Node* RBNode_RotateRight(Node* root)
{
	Node* x = root->left;
	root->left = x->right;
	x->right = root;
	x->color = x->right->color;
	x->right->color = RED;
	x->size = root->size;
	RBNode_RecaculateSize(root);
	return root;
}

Node* RBNode_RotateLeft(Node* root)
{
	Node* x = root->right;
	root->right = x->left;
	x->left = root;
	x->color = x->left->color;
	x->left->color = RED;
	x->size = root->size;
	RBNode_RecaculateSize(root);
	return root;
}

void RBNode_FlipColors(Node* root)
{
	root->color = !root->color;
	root->left->color = !root->left->color;
	root->right->color = !root->right->color;
}