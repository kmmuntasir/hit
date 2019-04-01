#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#define MAXN 10000

using namespace std;

#include "md5.h"
#include "directory.h"
#include "custom_git.h"

int main() {
    tree root;
    string initial_directory = "dir1";
    init_app(initial_directory);
    root = init_tree(initial_directory, initial_directory);
    tree_display(root);
    cout << endl;
    cout << stringify_tree(root) << endl << endl << endl;
    cout << tree_hash(root) << endl;

    return 0;
}
