#include <bits/stdc++.h>
#include <dirent.h>
//#include <filesystem>
#define MAXN 10000

using namespace std;

//vector<string> get_directories(const string &s) {
//    vector<string> r;
//    for(auto& p : filesystem::recursive_directory_iterator(s))
//        if(p.status().type() == std::filesystem::file_type::directory)
//            r.push_back(p.path().string());
//    return r;
//}

void alt() {
    const char* PATH = ".";

    DIR *dir = opendir(PATH);

    struct dirent *entry = readdir(dir);
//    vector <string> dirs;
    char dirs[100][50];
    int c = 0;
    while (entry != NULL) {
        if (entry->d_type == DT_DIR)
            printf("%d. %s\n", entry->d_ino, entry->d_name);
//            dirs.push_back(entry->d_name);
//            strcpy(dirs[c++], entry->d_name);
            entry = readdir(dir);
    }

//    for(int i=0; i<c; ++i) {
//        printf("%s\n", dirs[i]);
//    }

    closedir(dir);
}

int main() {

    vector <string> result;

//    result = get_directories('dir1');

    alt();

    return 0;
}
