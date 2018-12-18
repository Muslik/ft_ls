#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/acl.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char *argv[])
{
	//nlink_t  st_nlink
	struct passwd *pws; struct group *grp; struct stat *lbuf;
	time_t filetime;
	char link[256];
	char rights[12];
	memset(link, 0, 256);
	time(&filetime);
	lbuf = malloc(sizeof(struct stat));
	lstat(argv[argc - 1], lbuf);

	pws = getpwuid(lbuf->st_uid);
	grp = getgrgid(lbuf->st_gid);
	/* FILE TYPE */
	rights[0] = (S_ISDIR(lbuf->st_mode)) ? 'd' : rights[0];
	rights[0] = (S_ISCHR(lbuf->st_mode)) ? 'c' : rights[0];
	rights[0] = (S_ISBLK(lbuf->st_mode)) ? 'b' : rights[0];
	rights[0] = (S_ISREG(lbuf->st_mode)) ? '-' : rights[0];
	rights[0] = (S_ISFIFO(lbuf->st_mode)) ? 'p' : rights[0];
	rights[0] = (S_ISLNK(lbuf->st_mode)) ? 'l' : rights[0];
	rights[0] = (S_ISSOCK(lbuf->st_mode)) ? 's' : rights[0];
	rights[1] = (lbuf->st_mode & S_IRUSR) ? 'r' : '-';
    rights[2] = (lbuf->st_mode & S_IWUSR) ? 'w' : '-';
    rights[3] = (lbuf->st_mode & S_IXUSR) ? 'x' : '-';
	if (lbuf->st_mode & S_ISUID)
		rights[3] = ('x' == rights[3] ? 's' : 'S');
    rights[4] = (lbuf->st_mode & S_IRGRP) ? 'r' : '-';
    rights[5] = (lbuf->st_mode & S_IWGRP) ? 'w' : '-';
    rights[6] = (lbuf->st_mode & S_IXGRP) ? 'x' : '-';
	if (lbuf->st_mode & S_ISGID)
		rights[6] = ('x' == rights[6] ? 's' : 'S');
    rights[7] = (lbuf->st_mode & S_IROTH) ? 'r' : '-';
    rights[8] = (lbuf->st_mode & S_IWOTH) ? 'w' : '-';
    rights[9] = (lbuf->st_mode & S_IXOTH) ? 'x' : '-';
	if (lbuf->st_mode & S_ISVTX)
		rights[9] = ('x' == rights[9] ? 't' : 'T');
	// ACL AND EXTENDED ATTRIBUTES
	char str[10];
	acl_entry_t dummy;
	acl_t acl = NULL;
	ssize_t xattr;
	acl = acl_get_link_np(argv[argc - 1], ACL_TYPE_EXTENDED);
    if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1) {
        acl_free(acl);
        acl = NULL;
    }
	xattr = listxattr(argv[argc - 1], NULL, 0, XATTR_NOFOLLOW);
    str[1] = '\0';
	rights[10] = (xattr > 0) ? '@' : ' ';
	rights[10] = (acl != NULL) ? '+' : rights[10];
	rights[11] = ' ';
    /* if (xattr > 0) */
    /*     str[0] = '@'; */
    /* else if (acl != NULL) */
    /*     str[0] = '+'; */
    /* else */
    /*     str[0] = ' '; */
	write(1, rights, 12);
	printf("%zd ", lbuf->st_nlink);
	fflush(stdout);
	printf("%s  ", pws->pw_name);
	fflush(stdout);
	printf("%s  ", grp->gr_name);
	fflush(stdout);
	if (rights[0] != 'b' && rights[0] != 'c')
		printf("%zd ", lbuf->st_size);
	else
	{
		printf(" %zd,   ", major(lbuf->st_rdev));
		printf("%zd ", minor(lbuf->st_rdev));
	}
	fflush(stdout);
	char *file_time = ctime(&lbuf->st_mtime);
	write(1, file_time + 4, 12);
	write(1, " ", 1);
	if (S_ISLNK(lbuf->st_mode))
	{
		readlink(argv[argc - 1], link, 256);
		printf("%s -> %s", argv[argc-1], link);
		fflush(stdout);
	}
	else
	{
		printf("%s", argv[argc-1]);
		fflush(stdout);
	}
	printf("\n%d\n", lbuf->st_mode & S_IFMT);
	return 0;
}
