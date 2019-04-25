#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

int get_cid_file(char *path){
  int l = strlen(path);
  if(l < 3) return 0;
  if(path[l-3] != '$') return 0;
  int cid = (path[l-2]-'0') * 10 + (path[l-1]-'0');
  path[l-3] = '\0';
  return cid;
}

#define ST_SIZE 200
char done_print_list[ST_SIZE][512];
int indexing[ST_SIZE];
int type[ST_SIZE], ino[ST_SIZE], size[ST_SIZE];

void
ls(char *path)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  // **added @Manish
  for(int i=0;i<200;i++)
    done_print_list[i][0] = ')';
  int cnt_done = 0;
  int i;
  // **

  if((fd = open(path, 0)) < 0){
    printf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    printf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_FILE:
    printf(1, "%s %d %d %d\n", fmtname(path), st.type, st.ino, st.size);
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf(1, "ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf(1, "ls: cannot stat %s\n", buf);
        continue;
      }
      int cid = get_cid();
      int in_container_id = get_cid_file(buf);
      for(i=0;i<cnt_done;i++){
        if(strcmp(buf, done_print_list[i]) == 0){
          break;
        }
      }
      // printf(1,"cid : %d, fcid : %d\n", cid, in_container_id);
      if(cid == in_container_id){
        type[i] = st.type;
        ino[i] = st.ino;
        size[i] = st.size;
        int j = 0;
        while(buf[j] != '\0')
          done_print_list[i][j] = buf[j], j++;
        done_print_list[i][j] = '\0';
        if(i == cnt_done) cnt_done++;
      }
      else if(i == cnt_done && in_container_id == 0){
        type[i] = st.type;
        ino[i] = st.ino;
        size[i] = st.size;
        int j = 0;
        while(buf[j] != '\0')
          done_print_list[i][j] = buf[j], j++;
        done_print_list[i][j] = '\0';        
        if(i == cnt_done) cnt_done++;
      }
      // printf(1, "%s %d %d %d %d %d\n", fmtname(buf), st.type, st.ino, st.size, cid, in_container_id);
    }
    break;
  }
  for(i=0;i<cnt_done;i++){
    printf(1, "%s %d %d %d\n", fmtname(done_print_list[i]), type[i], ino[i], size[i]);
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
  int i;

  if(argc < 2){
    ls(".");
    exit();
  }
  for(i=1; i<argc; i++)
    ls(argv[i]);
  exit();
}
