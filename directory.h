void spacer(int level=0) {
    while(level--) printf("----");
}

typedef struct{
    string f_name;
    time_t f_modified;
    long long int f_size;
} file;

struct dirr {
    string dirname;
    vector <dirr> dir_list;
    vector <file> file_list;
};

typedef dirr tree;

void file_display(file f, bool simple_view=false, int level=0) {
    if(simple_view) {
        spacer(level);
        printf("%s %lld %ld\n", f.f_name.c_str(), f.f_size, f.f_modified);
    }
    else {
        spacer(level);
        printf("Name: %s\n", f.f_name.c_str());
        spacer(level);
        printf("Size: %lld\n", f.f_size);
        spacer(level);
        printf("Modified: %ld\n", f.f_modified);
    }
}

string stringify_file(file f) {
    string temp = f.f_name;
    temp += to_string(f.f_size);
    temp += to_string(f.f_modified);
    return temp;
}

file prop(string path, string f_name) {
    struct stat f_stat;
    file ret_file;
    ret_file.f_name = f_name;
    int rc = stat(path.c_str(), &f_stat);
    ret_file.f_size = (rc == 0) ? f_stat.st_size : -1;
    ret_file.f_modified = (rc == 0) ? f_stat.st_mtime : -1;
    return ret_file;
}

tree init_tree(string path, string dirname) {
//    printf("%s\n", path.c_str());
    tree ret_tree;
    ret_tree.dirname = dirname;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (path.c_str())) != NULL) {
        int cnt = 0;
        while ((ent = readdir (dir)) != NULL) {
            ++cnt;
            if(cnt < 3) continue;
            if(strcmp(ent->d_name, ".hit") == 0) continue; // For avoiding hit config folder

            /* ======== Remove this section when done ========= */
            if(strcmp(ent->d_name, ".git") == 0) continue; // For avoiding git config folder
            if(strcmp(ent->d_name, "hit") == 0) continue; // For avoiding hit executable binary file
            if(strcmp(ent->d_name, "hit.o") == 0) continue; // For avoiding hit object file
            /* ================================================ */

            if(ent->d_type == 4) ret_tree.dir_list.push_back(init_tree(path+"/"+ent->d_name, ent->d_name));
            else if(ent->d_type == 8) {
                file temp = prop(path+"/"+ent->d_name, ent->d_name);
                ret_tree.file_list.push_back(temp);
            }

        }
        closedir (dir);
    }
    return ret_tree;
}

void tree_display(tree current, int level=0) {
    spacer(level);
    printf("[%s]***\n", current.dirname.c_str());
    for(int i=0; i<current.dir_list.size(); ++i) {
        tree_display(current.dir_list[i], level+1);
    }
    for(int i=0; i<current.file_list.size(); ++i) {
        file_display(current.file_list[i], true, level+1);
    }
}

string stringify_tree(tree current) {
    string temp = current.dirname;
    for(int i=0; i<current.dir_list.size(); ++i) {
        temp += stringify_tree(current.dir_list[i]);
    }
    for(int i=0; i<current.file_list.size(); ++i) {
        temp += stringify_file(current.file_list[i]);
    }
    return temp;
}

string tree_hash(tree current) {
    string temp = stringify_tree(current);
    return md5(temp);
}

bool dir_exists(string dirpath) {
    DIR *dir = opendir(hitpath.c_str());
    if (dir) { // Directory exists.
        closedir(dir);
        return true;
    }
    else if (ENOENT == errno) return false; // Directory does not exist.
//    else {
//        printf("Unknown Error Occurred\n");
//        return false;
//    }
}
