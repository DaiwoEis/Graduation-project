#include "QueueGeneric.h"
#include "IntQueue.h"

void PrintQueueData(int data)
{
	printf("%d ", data);
}

int main()
{
	Queue(int)* queue = Queue_Create(int)();

	for (int i = 0; i < 10; ++i)
	{
		Queue_EnQueue(int)(queue, i);
	}

	for (int i = 0; i < 2; ++i)
	{
		Queue_DeQueue(int)(queue);
	}

	printf("%d\n", Queue_Size(int)(queue));

	Queue_Traverse(int)(queue, PrintQueueData);

	Queue_Destroy(int)(queue);

	return 0;
}