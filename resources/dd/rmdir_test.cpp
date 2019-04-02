#include <bits/stdc++.h>
#include <dirent.h>

using namespace std;

void remove_dir(string path, int level=0, bool except_root=true) {
    printf("%s\n", path.c_str());
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (path.c_str())) != NULL) {
        int cnt = 0;
        while ((ent = readdir (dir)) != NULL) {
            ++cnt;
            if(cnt < 3) continue;
            /* ======== Remove this section when done ========= */
            if(strcmp(ent->d_name, ".git") == 0) continue; // For avoiding git config folder
            if(strcmp(ent->d_name, "resources") == 0) continue; // For avoiding resource folder
            if(strcmp(ent->d_name, "hit") == 0) continue; // For avoiding hit executable binary file
            if(strcmp(ent->d_name, "hit.o") == 0) continue; // For avoiding hit object file
            /* ================================================ */

            if(ent->d_type == 4) {
                remove_dir(path+"/"+ent->d_name, level+1);
            }
            else {
                remove((path+"/"+ent->d_name).c_str());
            }

        }
        closedir (dir);
        if((!except_root && level==0) || level > 0) remove(path.c_str());
    }
}

int main() {
    remove_dir(".");
    return 0;
}
