#include <stdio.h>
#include <errno.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
	struct passwd * www_data = getpwnam("www-data"); 
	printf("username is %s, user id is %d\n", www_data->pw_name, www_data->pw_uid);
	int ret = setgid(www_data->pw_uid);
	ret = setuid(www_data->pw_gid);
	printf("ret = %d\n", ret);
	if (ret == -1) {
		if (errno == EAGAIN) {
			printf("The call would change the caller's real UID");
			return 0;
		}
		
		if (errno == EINVAL) {
			printf("The user ID specified in uid is not valid in this user namespace");
			return 0;
		}
		
		if (errno == EPERM) {
			printf("The user is not privileged (Linux: does not have the CAP_SETUID capability) and uid does not match the real UID or saved set-user-ID of the calling process.");
			return 0;
		}
		return 0;
	}

	int fd = open("helloworld", O_CREAT);
	if (fd != -1) {
		return 0;
	}

	if (errno == EACCES) {
		printf("The requested access to the file is not allowed, or search permission is denied for one of the directories in the path prefix of pathname, or the file  did  not  exist  yet  and  writaccess to the parent directory is not allowed.  (See also path_resolution(7).)");
	}
	return 0;
}
