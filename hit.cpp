#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#define MAXN 10000

using namespace std;

string rootpath = "dir";
int head=-1;
//string hitpath = rootpath + "/.hit";

// st
// ck
// list
// goto

#include "md5.h"
#include "custom_types.h"

tree root;

#include "directory.h"
#include "custom_git_mem.h" // Primary Memory Depended, no persistence available

int main() {
    init_app();
    string event, message;
    int commit_no;
    bool exit_flag=false;

    do {
        cout << "Hit Command: ";
        cin >> event;
        getchar();
        if(!event.compare("st")) {
            cout << "Status" << endl;
        }
        else if(!event.compare("ck")) {
            getline(cin, message);
            cout << message << endl;
//            cout << "Performing Commit" << endl;
//            perform_commit();
        }
        else if(!event.compare("list")) {
            cout << "Commit List" << endl;
        }
        else if(!event.compare("goto")) {
            cout << "Checkout" << endl;
            cin >> commit_no;
            cout << "Commit " << commit_no << endl;
        }
        else if(!event.compare("exit")) exit_flag=true;
        else cout << "Invalid Command\n";
    } while(!exit_flag);

    return 0;
}
