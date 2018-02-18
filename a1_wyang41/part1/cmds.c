#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#define MAX 1000
char *getpwd()
{
	static char pwd[MAX];
	getcwd(pwd, MAX);
	return pwd;
}
	
char *cmd_ls()
{
	DIR    *dp;
   	struct dirent   *dirp;
	static char buf[MAX];
	int bufi = 0;

	memset(buf, 0, MAX);
	if ((dp = opendir(getpwd())) == NULL){
		return "open cwd error\n";
	}
	while ((dirp = readdir(dp)) != NULL){
		sprintf(buf + bufi, "%s ", dirp->d_name);
		bufi += strlen(dirp->d_name) + 1;
	}
	buf[bufi - 1] = '\n';

    	closedir(dp);

	return buf;
}
char *cmd_mkdir(char *dir)
{
	static char buf[MAX];
	if (dir[0] == '\0'){
		sprintf(buf, "usage mkdir <dir>\n");
	} else if (mkdir(dir, 0755) < 0){
		if (errno == EEXIST){
			sprintf(buf, "%s exist\n", dir);
		} else {
			sprintf(buf, "%s\n", strerror(errno));
		}
	} else {
		sprintf(buf, "mkdir %s success\n", dir);
	}
	return buf;
}
char *cmd_rmdir(char *dir)
{
	static char buf[MAX];
	if (dir[0] == '\0'){
		sprintf(buf, "usage rmdir <dir>\n");
	} else if (rmdir(dir) < 0){
		if (errno == ENOTDIR || errno == ENOENT){
			sprintf(buf, "%s does not exist\n", dir);
		} else {
			sprintf(buf, "%s\n", strerror(errno));
		}
	} else {
		sprintf(buf, "rmdir %s success\n", dir);
	}
	return buf;
}
char *cmd_cd(char *path)
{
	static char buf[MAX];
	if (path[0] == '\0'){
		sprintf(buf, "usage cd <dir-relative-path>\n");
	} else if (path[0] == '/'){
		sprintf(buf, "absolute path not supported\n");
	} else if (chdir(path) < 0){
		sprintf(buf, "%s does not exist\n", path);
	} else {
		sprintf(buf, "cd success\n");
	}
	return buf;
}
char *cmd_pwd()
{
	static char buf[MAX];
	sprintf(buf, "%s\n", getpwd());
	return buf;
}
char *cmd_404(char *cmd)
{
	static char buf[MAX];
	sprintf(buf, "command `%s` not found\n", cmd);
	return buf;
}
char *cmd_process(char *cmdline)
{
	char cmd[30], param[70];
	static char buf[100];
	int ret;
	memset(cmd, 0, 30);
	memset(param, 0, 70);
	ret = sscanf(cmdline, "%s %s", cmd, param);
	
	if (strcmp(cmd, "ls") == 0){
		if (ret == 1){
			return cmd_ls();
		} else {
			sprintf(buf, "invalid command `%s`\n", cmdline);
			return buf;
		}
	} else if (strcmp(cmd, "pwd") == 0){
		if (ret == 1){
			return cmd_pwd();
		} else {
			sprintf(buf, "invalid  command `%s`\n", cmdline);
			return buf;
		}
	} else if (strcmp(cmd, "mkdir") == 0){
		return cmd_mkdir(param);
	} else if (strcmp(cmd, "rmdir") == 0){
		return cmd_rmdir(param);
	} else if (strcmp(cmd, "cd") == 0){
		return cmd_cd(param);
	} else {
		return cmd_404(cmdline);
	}
}
/*
// test
int main(int c, char **a)
{
	printf("%s", cmd_process(a[1]));
}
*/
