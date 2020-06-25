#include <stdio.h>
#include <stdlib.h>
#include "LogColour.h"

void LogGreen()
{
	printf("\033[0;32m");
}

void LogRed()
{
	printf("\033[0;31m");
}

void LogYellow()
{
	printf("\033[0;33m");
}

void ResetLogColour()
{
	printf("\033[0m");
}
