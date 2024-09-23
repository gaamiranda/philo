#include "../include/philo.h"

void	error_message(int num)
{
	char	*msg;

	msg = NULL;
	if (num == 0)
		msg = "Invalid argc number";
	else if (num == 1)
		msg = "Invalid argv";
	else if (num == 2)
		msg = "Invalid timestamps";
	else if (num == 3)
		msg = "Error creating dinner";
	else if (num == 4)
		msg = "Error creating thread";
	else if (num == 5)
		msg = "Invalid philo number";
	printf("%s\n", msg);
}
