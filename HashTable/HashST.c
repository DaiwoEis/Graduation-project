#include "HashST.h"

#define INIT_CAPACITY 97

typedef struct Node
{
	struct Node* next;
	Key key;
	Value value;
}Node, *pNode;

struct HashST
{
	int size;
	pNode* chains;
	int chainSize;	
	int(*hashFun)(Key key);
	bool(*eqlFun)(Key left, Key right);
};

Node* Node_Create(Key key, Value value, Node* next);
void Node_Destroy(Node* root);

int HashST_GetHash(const HashST* hashST, Key key);
void HashST_Resize(HashST* st, int size);
Node* HashST_GetNode(const HashST* hashST, Key key);

Node* Node_Create(Key key, Value value, Node* next)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->key = key;
	node->value = value;
	node->next = next;
	return node;
}

void Node_Destroy(Node* root)
{
	if (root == NULL) return;

	Node* node = root;
	while (node != NULL)
	{
		Node* temp = node;
		node = node->next;
		free(temp);
	}
}

int HashST_GetHash(const HashST* hashST, Key key)
{
	return (hashST->hashFun(key) & 0x7fffffff) % hashST->chainSize;
}

HashST* HashST_Create(int(*hasnFun)(Key key))
{
	return HashST_Create_E(hasnFun, NULL);
}

HashST* HashST_Create_E(int(*hasnFun)(Key key), bool(*eqlFun)(Key left, Key right))
{
	return HashST_Create_ES(hasnFun, eqlFun, INIT_CAPACITY);
}

HashST* HashST_Create_ES(int(*hasnFun)(Key key), bool(*eqlFun)(Key left, Key right), int chainSize)
{
	HashST* hashST = (HashST*)malloc(sizeof(HashST));
	hashST->hashFun = hasnFun;
	if (eqlFun == NULL)
		hashST->eqlFun = DefaultEqlFun;
	else
		hashST->eqlFun = eqlFun;
	hashST->size = 0;
	hashST->chainSize = chainSize;
	hashST->chains = (pNode*)calloc(chainSize, sizeof(pNode));
	return hashST;
}

void HashST_Destroy(HashST* hashST)
{
	if (hashST == NULL) return;

	int i;
	for (i = 0; i < hashST->chainSize; ++i)
	{
		Node_Destroy(hashST->chains[i]);
	}
	free(hashST);
}

void HashST_Resize(HashST* st, int size)
{
	HashST* newST = HashST_Create_ES(st->hashFun, st->eqlFun, size);
	for (int i = 0; i < st->chainSize; ++i)
	{
		for (Node* node = st->chains[i]; node != NULL; node = node->next)
			HashST_Add(newST, node->key, node->value);
		Node_Destroy(st->chains[i]);
	}
	st->chains = newST->chains;
	st->chainSize = newST->chainSize;
	st->size = newST->size;
	free(newST);
}

Node* HashST_GetNode(const HashST* hashST, Key key)
{
	int hash = HashST_GetHash(hashST, key);
	pNode root;
	for (root = hashST->chains[hash]; root != NULL; root = root->next)
	{
		if (hashST->eqlFun(root->key, key))
		{
			return root;
		}
	}
	return NULL;
}

void HashST_Add(HashST* hashST, Key key, Value value)
{
	if (hashST->size >= 10 * hashST->chainSize)
		HashST_Resize(hashST, 2 * hashST->chainSize);

	int hash = HashST_GetHash(hashST, key);
	for (pNode node = hashST->chains[hash]; node != NULL; node = node->next)
	{
		if (hashST->eqlFun(node->key, key))
		{
			node->value = value;
			return;
		}
	}
	hashST->size++;
	hashST->chains[hash] = Node_Create(key, value, hashST->chains[hash]);
}

Value HashST_Get(const HashST* hashST, Key key)
{
	Node* node = HashST_GetNode(hashST, key);
	if (node == NULL)
	{
		puts("Not contains");
		return 0;
	}
	else
	{
		return node->value;
	}	
}

void HashST_Delete(HashST* hashST, Key key)
{
	int hash = HashST_GetHash(hashST, key);
	Node* curNode = hashST->chains[hash];
	Node* parentNode = NULL;
	while (curNode != NULL)
	{
		if (hashST->eqlFun(curNode->key, key))
		{
			// head node
			if (parentNode == NULL)
			{
				hashST->chains[hash] = curNode->next;
			}
			else
			{
				parentNode->next = curNode->next;
			}
			hashST->size--;
			free(curNode);
			return;
		}

		parentNode = curNode;
		curNode = curNode->next;		
	}

	if (hashST->chainSize > INIT_CAPACITY&&hashST->size < 2 * hashST->chainSize)
		HashST_Resize(hashST, hashST->chainSize / 2);
}

bool HashST_Contains(const HashST* hashST, Key key)
{
	Node* node = HashST_GetNode(hashST, key);
	return node != NULL;
}

bool HashST_IsEmpty(const HashST* hashST)
{
	return hashST->size == 0;
}

int HashST_Size(const HashST* hashST)
{
	return hashST->size;
}

Array(Key)* HashST_Keys(const HashST* hashST)
{
	Array(Key)* arr = Array_Create(Key)(HashST_Size(hashST));
	int count = 0;
	for (int i = 0; i < hashST->chainSize; ++i)
	{
		for (Node* node = hashST->chains[i]; node != NULL; node = node->next)
		{
			Array_Set(Key)(arr, count++, node->key);
		}
	}
	return arr;
}
