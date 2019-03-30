#include "header.h"
#include "compact.h"
#include "descompact.h"

int main () {
	char choice;
	printf("#####################################\n");
	printf("#                                   #\n");
	printf("#------------- WELCOME -------------#\n");
	printf("# <1> COMPRESS FILE                 #\n");
	printf("# <2> DESCOMPRESS FILE              #\n");
	printf("#####################################\n");
	printf("===> ");
	scanf("%c", &choice);
	if (choice == '1') {
		compact();
		printf("File successfully compressed\n");
	} else if (choice == '2') {
		descompact();
		printf("File successfully descompressed\n");
	} else {
		printf("Invalid option, try again\n");
		main ();
	}

    return 0;
}