#include <cstdlib>

int main()
{
	int *a = NULL;

	delete a;
    free(a);

	return(0);
}
