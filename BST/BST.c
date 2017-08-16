#include "BST.h"

typedef struct Node Node;

static int(*cmpFun)(Key left, Key right);

struct BST
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
};

Node* Node_Create(Key key, Value value, int size);
void Node_Destroy(Node* root);
Node* Node_Min(Node* root);
Node* Node_Max(Node* root);
Node* Node_DeleteMin(Node* root);
Node* Node_DeleteMax(Node* root);
int Node_Size(const Node* node);
void Node_RecaculateSize(Node* node);

Node* Node_Create(Key key, Value value, int size)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->key = key;
	node->value = value;
	node->size = size;
	node->left = node->right = NULL;
	return node;
}

int Node_Size(const Node* node)
{
	if (node == NULL) return 0;
	return node->size;
}

void Node_RecaculateSize(Node* node)
{
	node->size = Node_Size(node->left) + Node_Size(node->right) + 1;
}

void Node_Destroy(Node* root)
{
	if (root == NULL) return;

	Node_Destroy(root->left);
	Node_Destroy(root->right);
	free(root);
	root = NULL;
}

int BST_DefaultCmp(Key left, Key right)
{
	if (left < right) return -1;
	if (left > right) return 1;
	return 0;
}

BST* BST_Create_Cmp(int(*cmp)(Key left, Key right))
{
	BST* bst = (BST*)malloc(sizeof(BST));
	bst->root = NULL;
	if (cmp == NULL)
		cmpFun = BST_DefaultCmp;
	else
		cmpFun = cmp;
	return bst;
}

BST* BST_Create()
{
	return BST_Create_Cmp(NULL);
}


void BST_Destroy(BST* bst)
{
	if (bst == NULL) return;
	Node_Destroy(bst->root);
	free(bst);
}

Node* Node_Add(Node* root, Key key, Value value)
{
	if (root == NULL) return Node_Create(key, value, 1);

	int cmp = cmpFun(key, root->key);
	if (cmp < 0) root->left = Node_Add(root->left, key, value);
	else if (cmp > 0) root->right = Node_Add(root->right, key, value);
	else root->value = value;
	Node_RecaculateSize(root);
	return root;
}

void BST_Add(BST* bst, Key key, Value value)
{
	bst->root = Node_Add(bst->root, key, value);
}

Node* Node_Get(Node* root, Key key)
{
	if (root == NULL) return NULL;
	int cmp = cmpFun(key, root->key);
	if (cmp < 0) return Node_Get(root->left, key);
	else if (cmp > 0) return Node_Get(root->right, key);
	else return root;
}

Value BST_Get(const BST* bst, Key key)
{
	Node* node = Node_Get(bst->root, key);
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

Node* Node_Delete(Node* root, Key key)
{
	if (root == NULL) return NULL;

	int cmp = cmpFun(key, root->key);
	if (cmp < 0) root->left = Node_Delete(root->left, key);
	else if (cmp > 0) root->right = Node_Delete(root->right, key);
	else
	{
		if (root->left == NULL) return root->right;
		if (root->right == NULL) return root->left;
		Node* t = root;
		root = Node_Min(t->right);
		root->right = Node_DeleteMin(t->right);
		root->left = t->left;
		free(t);
	}
	Node_RecaculateSize(root);
	return root;
}

void BST_Delete(BST* bst, Key key)
{
	bst->root = Node_Delete(bst->root, key);
}

bool BST_Contains(const BST* bst, Key key)
{
	return Node_Get(bst->root, key) != NULL;
}

bool BST_IsEmpty(const BST* bst)
{
	return Node_Size(bst->root) == 0;
}

int BST_Size(const BST* bst)
{
	return Node_Size(bst->root);
}

int BST_PartSize(const BST* bst, Key lo, Key hi)
{
	if (BST_Contains(bst, hi)) return BST_Rank(bst, hi) - BST_Rank(bst, lo) + 1;
	else return BST_Rank(bst, hi) - BST_Rank(bst, lo);
}

Node* Node_Min(Node* root)
{
	if (root->left == NULL)
	{
		return root;
	}

	return Node_Min(root->left);
}

Key BST_Min(const BST* bst)
{
	if (BST_IsEmpty(bst))
	{
		puts("BST is empty");
		return 0;
	}

	return Node_Min(bst->root)->key;
}

Node* Node_Max(Node* root)
{
	if (root->right == NULL)
	{
		return root;
	}

	return Node_Max(root->right);
}


Key BST_Max(const BST* bst)
{
	if (BST_IsEmpty(bst))
	{
		puts("BST is empty");
		return 0;
	}

	return Node_Max(bst->root)->key;
}

Node* Node_Floor(Node* root, Key key)
{
	if (root == NULL) return NULL;

	int cmp = cmpFun(key, root->key);
	if (cmp < 0) return Node_Floor(root->left, key);
	if (cmp == 0) return root;
	Node* t = Node_Floor(root->right, key);
	if (t == NULL)
		return root;
	else
		return t;
}

Key BST_Floor(const BST* bst, Key key)
{
	if (BST_IsEmpty(bst))
	{
		puts("BST is empty");
		return 0;
	}

	Node* t = Node_Floor(bst->root, key);
	if (t == NULL)
	{
		puts("the key is not in the st");
		return 0;
	}
	else
	{
		return t->key;
	}
}

Node* Node_Ceiling(Node* root, Key key)
{
	if (root == NULL) return NULL;

	int cmp = cmpFun(key, root->key);
	if (cmp > 0) return Node_Ceiling(root->right, key);
	if (cmp == 0) return root;
	Node* t = Node_Ceiling(root->left, key);
	if (t == NULL)
		return root;
	else
		return t;
}

Key BST_Ceiling(const BST* bst, Key key)
{
	if (BST_IsEmpty(bst))
	{
		puts("BST is empty");
		return 0;
	}

	Node* t = Node_Ceiling(bst->root, key);
	if (t == NULL)
	{
		puts("the key is not in the st");
		return 0;
	}
	else
	{
		return t->key;
	}
}

int Node_Rank(Node* root, Key key)
{
	if (root == NULL) return 0;

	int cmp = cmpFun(key, root->key);
	if (cmp < 0) return Node_Rank(root->left, key);
	if (cmp == 0) return Node_Rank(root->left, key);
	return Node_Size(root->left) + 1 + Node_Rank(root->right, key);
}

int BST_Rank(const BST* bst, Key key)
{
	return Node_Rank(bst->root, key);
}

Node* Node_Select(Node* root, int k)
{
	if (root == NULL) return NULL;

	int leftChildSize = Node_Size(root->left);
	if (leftChildSize > k) return Node_Select(root->left, k);
	if (leftChildSize < k) return Node_Select(root->right, k - leftChildSize - 1);
	return root;
}

Key BST_Select(const BST* bst, int k)
{
	return Node_Select(bst->root, k)->key;
}

void Node_PartKeys(Node* root, Queue* queue, Key lo, Key hi)
{
	if (root == NULL) return;
	int cmpLo = cmpFun(lo, root->key);
	int cmpHi = cmpFun(hi, root->key);
	if (cmpLo < 0) Node_PartKeys(root->left, queue, lo, hi);
	if (cmpLo <= 0  &&  cmpHi >= 0) Queue_EnQueue(queue, root->key);
	if (cmpHi > 0) Node_PartKeys(root->right, queue, lo, hi);
}

Queue* BST_PartKeys(BST* bst, Key lo, Key hi)
{
	Queue* queue = Queue_Create();
	Node_PartKeys(bst->root, queue, lo, hi);
	return queue;
}

Queue* BST_Keys(BST* bst)
{
	return BST_PartKeys(bst, BST_Min(bst), BST_Max(bst));
}

Node* Node_DeleteMax(Node* root)
{
	if (root->right == NULL)
	{
		Node* t = root->left;
		free(root);
		return t;
	}

	root->right = Node_DeleteMax(root->right);
	Node_RecaculateSize(root);
	return root;
}

void BST_DeleteMax(BST* bst)
{
	if (BST_IsEmpty(bst))
	{
		puts("BST is empty");
		return;
	}

	bst->root = Node_DeleteMax(bst->root);
}

Node* Node_DeleteMin(Node* root)
{
	if (root->left == NULL)
	{
		Node* t = root->right;
		free(root);
		return t;
	}

	root->left = Node_DeleteMin(root->left);
	Node_RecaculateSize(root);
	return root;
}

void BST_DeleteMin(BST* bst)
{
	if (BST_IsEmpty(bst))
	{
		puts("BST is empty");
		return;
	}

	bst->root = Node_DeleteMin(bst->root);
}

void Node_Traverse(Node* root, void(*fun)(Key key))
{
	if (root == NULL) return;

	Node_Traverse(root->left, fun);
	fun(root->key);
	Node_Traverse(root->right, fun);	
}

void BST_Traverse(BST* bst, void(*fun)(Key key))
{
	Node_Traverse(bst->root, fun);
}