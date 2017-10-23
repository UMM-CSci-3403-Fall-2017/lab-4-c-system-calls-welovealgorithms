#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

static int num_dirs, num_regular;

bool is_dir(const char* path) {
  /*
   * Use the stat() function (try "man 2 stat") to determine if the file
   * referenced by path is a directory or not.  Call stat, and then use
   * S_ISDIR to see if the file is a directory. Make sure you check the
   * return value from stat in case there is a problem, e.g., maybe the
   * the file doesn't actually exist.
   */

  // struct stat variable
  struct stat buf;
  
  // Check code to see if an error occured, if not, check if it is a directory
  if(stat(path, &buf) != 0) {
    printf("Error!");
    return false;
  } else {
    return(S_ISDIR(buf.st_mode));
  }
}

/* 
 * I needed this because the multiple recursion means there's no way to
 * order them so that the definitions all precede the cause.
 */
void process_path(const char*);

void process_directory(const char* path) {
  /*
   * Update the number of directories seen, use opendir() to open the
   * directory, and then use readdir() to loop through the entries
   * and process them. You have to be careful not to process the
   * "." and ".." directory entries, or you'll end up spinning in
   * (infinite) loops. Also make sure you closedir() when you're done.
   *
   * You'll also want to use chdir() to move into this new directory,
   * with a matching call to chdir() to move back out of it when you're
   * done.
   */

  // Increment number of directories
  num_dirs++;

  // Create directory variable and dirent structure
  DIR *dir;
  struct dirent *cur_dir;

  // Open the directory path
  dir = opendir(path);

  // Move into the path directory
  chdir(path);

  
  // Check if dir is NULL, if so don't do anything
  if(dir == NULL) {
    return;
  }

  
  // Set cur_dir to readdir of the current directory
  cur_dir = readdir(dir);
 
  
  // Loop while the current directory isn't NULL
  while(cur_dir != NULL) {

    // Check the current directories d_name to see if it is equal to "." or ".."
    if(strcmp(cur_dir->d_name, ".") !=0 && strcmp(cur_dir->d_name, "..") != 0)
      {
	process_path(cur_dir->d_name);
      }

    // Set cur_dir to readdir of the current directory
    cur_dir = readdir(dir);
    
  }
  
  // Move out of the path directory
  chdir("..");

  // Close the directory
  closedir(dir);
 
}

void process_file(const char* path) {
  /*
   * Update the number of regular files.
   */

  num_regular++;
}

void process_path(const char* path) {
  if (is_dir(path)) {
    process_directory(path);
  } else {
    process_file(path);
  }
}

int main (int argc, char *argv[]) {
  // Ensure an argument was provided.
  if (argc != 2) {
    printf ("Usage: %s <path>\n", argv[0]);
    printf ("       where <path> is the file or root of the tree you want to summarize.\n");
    return 1;
  }

  num_dirs = 0;
  num_regular = 0;

  process_path(argv[1]);

  printf("There were %d directories.\n", num_dirs);
  printf("There were %d regular files.\n", num_regular);

  return 0;
}
