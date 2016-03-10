#include "types.h"
#include "user.h"
int main()
{
	int i, j, pid, old;
	for (i = 0; i < 5; i++)
	{
  		pid = fork();
  		if (pid == 0)
  		{
    		old = setpriority(i * 10);
    		printf(1,"%d\n", old);
    		for (j = 0; j < 5; j++) 
    		{}
  		}
	}
	wait();
	exit();
}