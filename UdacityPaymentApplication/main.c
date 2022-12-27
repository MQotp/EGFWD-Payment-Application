/*
 * main.c
 *
 *  Created on: Dec 12, 2022
 *      Author: Mahmoud Qotp
 */
#include "Application/app.h"

int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	while (1)
	{
		appStart();
	}
}
