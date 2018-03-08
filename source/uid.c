#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	uid_t uid = getuid();
	uid_t euid = geteuid();

	printf("uid is %d and euid is %d\n", uid, euid);
}
