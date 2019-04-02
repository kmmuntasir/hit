#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#define MAXN 10000

using namespace std;

string rootpath = ".";
string head;
//string hitpath = rootpath + "/.hit";
map <string, string> fs;

#include "md5.h"
#include "directory.h"
#include "custom_git_mem.h" // Primary Memory Depended, no persistence available

int main() {
    tree root;
//    init_app();
    root = init_tree(rootpath, rootpath);
    tree_display(root);
    cout << endl;
//    cout << stringify_tree(root) << endl << endl << endl;
    cout << tree_hash(root) << endl;

//    fs_display(fs);


    return 0;
}
