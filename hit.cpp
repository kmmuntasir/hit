#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#define MAXN 10000

using namespace std;

string rootpath = "dir";
int head=-1;

#include "cpp_md5.h"
#include "directory.h"
#include "custom_types.h"

tree root;

#include "hit.h" // Primary Memory Depended, no persistence available

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
            compare();
        }
        else if(!event.compare("ck")) {
            getline(cin, message);
            perform_commit(message);
            cout << "Commit Successful: \"" << message << "\"" << endl;
        }
        else if(!event.compare("list")) {
            cout << "Commit List" << endl;
            list_commits();
        }
        else if(!event.compare("show")) {
            cin >> commit_no;
            commit_details(commit_no);
        }
        else if(!event.compare("goto")) {
            cin >> commit_no;
            checkout(commit_no);
        }
        else if(!event.compare("exit")) exit_flag=true;
        else cout << "Invalid Command\n";
    } while(!exit_flag);

    return 0;
}
