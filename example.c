#include "types.h"
#include "user.h"
int main()
{
	int i, j, pid;
	for (i = 0; i < 5; i++)
	{
  		pid = fork();
  		if (pid == 0)
  		{
    		setpriority(i * 10);
    		for (j = 0; j < 20; j++) 
    		{}
  		}
	}
	wait();
	exit();
}