#include <bits/stdc++.h>
#include <dirent.h>
#define MAXN 10000

/*************************

d_type value meanings
----------------------
4 - Directory
8 - Files
10 - Shortcuts (linux)

P.S: Note that Windows Shortcuts (.lnk) are also treated as files in d_type, so the d_type value will be 8

*************************/

using namespace std;

int list_all(const char *path) {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (path)) != NULL) {
      /* print all the files and directories within directory */
      while ((ent = readdir (dir)) != NULL) {

//        if (ent->d_type == DT_DIR)
        printf ("%d - %s\n", ent->d_type, ent->d_name);
      }
      closedir (dir);
    } else {
      /* could not open directory */
      perror ("");
      return EXIT_FAILURE;
    }
}

int main() {

    list_all(".");

    return 0;
}
