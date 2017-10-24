#include <ftw.h>
#include <stdlib.h>
#include <stdio.h>

static int num_dirs, num_regular;

static int callback(const char *fpath, const struct stat *sb, int typeflag) { 

  // Check whether the typeflag is a file or directory and
  // increments acordingly
  if (typeflag == FTW_F) {

    num_regular++;
    return 0;
  } else if (typeflag == FTW_D) {

    num_dirs++;
    return 0;
  }
  
  return 0;
}

#define MAX_FTW_DEPTH 16

int main(int argc, char** argv) { 
    // Check arguments and set things up

   if (argc != 2) {
     printf ("Usage: %s <path>\n", argv[0]);
     printf ("       where <path> is the file or root of the tree you want to summarize.\n");
    return 1;
  }


   // Recursively descend the directory hieracrhy of argv[1], incrementing
   // the count of directories and files as it goes
    ftw(argv[1], callback, MAX_FTW_DEPTH);


    // Print out the results
    
    printf("There were %d directories.\n", num_dirs);
    printf("There were %d regular files.\n", num_regular);

   
}
