#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern int nw_inp_from_file_(int *, char *, int);
extern int string_to_fortchar(char *, int, char *);


int nw_inp_from_string(int rtdb, const char *input)
{
    char *filename = "temp.nw";
    FILE *file = fopen(filename,"w");
    char fstring[255];
    int status;

    if (!file) {
	fprintf(stderr,"failed to open temp.nw\n");
	return 0;
    }

    if (fwrite(input, 1, strlen(input), file) != strlen(input)) {
	fprintf(stderr,"failed to write to temp.nw\n");
	(void) fclose(file);
	return 0;
    }

    (void) fclose(file);

    if (!string_to_fortchar(fstring, sizeof(fstring), filename)) {
	fprintf(stderr,"fstring is too small?\n");
	return 0;
    }

    status = nw_inp_from_file_(&rtdb, fstring, sizeof fstring);

    (void) unlink(filename);

    return status;
}
