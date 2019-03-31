#include <bits/stdc++.h>
#include <sys/stat.h>
#include <dirent.h>
#define MAXN 10000

using namespace std;

#include "md5.h"
#include "custom_git.h"

int main() {

    tree root;
    root = init_tree("dir1", "dir1");
    tree_display(root);
    cout << endl;
    cout << stringify_tree(root) << endl << endl << endl;
    cout << tree_hash(root) << endl;

    return 0;
}
