#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
	char op;
	char *src;
	char *target;
	if (argc < 3) {
		exit(1);
	}
	op = (char) *argv[1];
	if ( op == 'l' ) {
		if (argc < 4) {
			fprintf(stderr, "file_link l src target [link]\n");
			exit(1);
		}
		src = argv[2];
		target = argv[3];
		if (link(src, target) < 0) {
			perror("link");
			exit(1);
		}
	}
	else if (op == 's') {
		if (argc < 4) {
			fprintf(stderr, "file_link l src target [link]\n");
			exit(1);
		}
		src = argv[2];
		target = argv[3];
		if (symlink(src, target) < 0) {
			perror("symlink");
			exit(1);
		}
	}
	else if (op == 'u') {
		src = argv[2];
		if (unlink(src) < 0) {
			perror("unlink");
			exit(1);
		}
	}
	else {
		fprintf(stderr, "wrong command\n");
	}
}

