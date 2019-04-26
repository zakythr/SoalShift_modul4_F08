#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>

char password[100]={"qE1~ YMUR2\"`hNIdPzi\%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0"};
int ukuran = strlen(caesarcipher);

static const char *dirpath = "/home/zaky/shift4";
int key=17;

FILE *f2;
FILE *cp2;
char cek1[500];
char cek2[500];
char namalama[100];
char namabaru[100];
char copy[]=".copy";

void dekript(char *simpanpath)
{
  int panjangpath = strlen(simpanpath), i, j;
  for(i=0; i < panjangpath; i++)
  {
    if(simpanpath[i] == '/')
    {
     continue;
    }
    for(j=0; j<ukuran; j++)
    {
      if(simpanpath[i] == password[j])
      {
	simpanpath[i] = password[((j - key)+ukuran)%ukuran];
	break;
      }
    }
  }
}

void enkript(char *simpanpath)
{
  int panjangpath, i, j;
  panjangpath = strlen(simpanpath);

  for(int i=0; i < panjangpath; i++)
  {
    if(simpanpath[i]=='/')
    {
      continue;
    }
    for(int j=0; j < ukuran; j++)
    {
      if(simpanpath[i] == password[j])
      {
       	simpanpath[i] = password[(j + key)%ukuran];
      	break;
      }
    }
  }
}



static int xmp_getattr(const char *path, struct stat *stbuf)
{
 	int res;
	enkript(path);
	char fpath[1000];
	sprintf(fpath,"%s%s",dirpath,path);
	res = lstat(fpath, stbuf);

	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
		       off_t offset, struct fuse_file_info *fi)
{
  char fpath[1000];
	enkript(path);
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else sprintf(fpath, "%s%s",dirpath,path);
	int res = 0;

	DIR *dp;
	struct dirent *de;

	(void) offset;
	(void) fi;

	dp = opendir(fpath);
	if (dp == NULL)
		return -errno;

	while ((de = readdir(dp)) != NULL) {
		struct stat st;
		memset(&st, 0, sizeof(st));
		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;
		dekript(de->d_name);
		res = (filler(buf, de->d_name, &st, 0));
			if(res!=0) break;
	}

	closedir(dp);
	return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,
		    struct fuse_file_info *fi)
{
  char fpath[1000];
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else sprintf(fpath, "%s%s",dirpath,path);
	int res = 0;
  int fd = 0 ;

	(void) fi;
	fd = open(fpath, O_RDONLY);
	if (fd == -1)
		return -errno;

	res = pread(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	return res;
}

static int xmp_write(const char *path, const char *buf, size_t size,
		     off_t offset, struct fuse_file_info *fi)
{
	char *ekstensi;
	time_t formatime;
	struct tm *info;
	char path2[500];
	char waktu[500];

	char fpath[1000];

	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else sprintf(fpath, "%s%s",dirpath,path);

	int fd;
	int res;

	(void) fi;
	
	
	fd = open(fpath, O_WRONLY);
	

	if (fd == -1)
		return -errno;

	if(strstr(path,copy) != NULL){
		return -errno;
	}

	res = pwrite(fd, buf, size, offset);
	if (res == -1)
		res = -errno;


	f2 = fopen (fpath, "r");

	fgets(cek2, 500, f2);

	if(strcmp(cek1,cek2)!=0){
		char* argv[3] = {"mkdir", "/home/zaky/Downloads/BackUp", NULL};
		execv("/bin/mkdir", argv);
		char format[100]="/home/zaky/Downloads/BackUp";
		opendir(format);
		time(&formatime);
		info = localtime(&formatime);
		sprintf(waktu, "--%04d--%02d--%02d__%02d:%02d:%02d", info->tm_year, info->tm_mon, info->tm_mday, info->tm_hour, info->tm_min, info->tm_sec);
		ekstensi=strchr(path, '.');
		sprintf(path2, "%s", path);
		int i=strlen(path2)-4;
		if(path2[i]=='.')path2[i]='\0';
		sprintf(namalama,"/home/zaky/Downloads%s",path);
		sprintf(namabaru,"/home/zaky/Downloads/BackUp%s__%s%s", path2, waktu, ekstensi);
		cp2 = fopen(namabaru,"w+");
		fprintf(cp2, "%s", cek2);
		fclose(cp2);
	}


	fclose(f2);
	close(fd);

	return res;
}

static int xmp_truncate(const char *path, off_t size)
{

	char fpath[1000];
	sprintf(fpath,"%s%s",dirpath,path);
	
	int res;

	res = truncate(fpath, size);
	if (res == -1)
		return -errno;

	return 0;
}

static struct fuse_operations xmp_oper = {
	.getattr	= xmp_getattr,
	.readdir	= xmp_readdir,
	.read		= xmp_read,
	.write		= xmp_write,
	.truncate	= xmp_truncate,
};

int main(int argc, char *argv[])
{
	umask(0);
	return fuse_main(argc, argv, &xmp_oper, NULL);
}
