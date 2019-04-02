void spacer(int level=0) {while(level--) printf("----");}
void remove_dir(string path, int level=0, bool except_root=true) {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (path.c_str())) != NULL) {
        int cnt = 0;
        while ((ent = readdir (dir)) != NULL) {
            ++cnt;
            if(cnt < 3) continue; // for avoiding . and .. directory
            if(ent->d_type == 4) remove_dir(path+"/"+ent->d_name, level+1);
            else remove((path+"/"+ent->d_name).c_str());
        }
        closedir (dir);
        if((!except_root && level==0) || level > 0) remove(path.c_str());
    }
}

class filesystem {
public:
    map <string, string> fs;
    map <string, string>::iterator itr;
    void push(string key, string value) {fs.insert(pair<string, string>(key, value));}

    string fetch(string key) {
        itr = fs.find(key);
        return (itr == fs.end()) ? "" : fs.find(key)->second;
    }

    bool exists(string key) {
        itr = fs.find(key);
        return (itr == fs.end()) ? false : true;
    }
};
filesystem FS;

class file{
public:
    string f_index, f_name, f_path, f_perm;
    time_t f_modified;
    long long int f_size;

    file (string path, string name) {
        struct stat f_stat;
        f_path = path;
        f_name = name;
        int rc = stat(path.c_str(), &f_stat);
        f_size = (rc == 0) ? f_stat.st_size : -1;
        f_modified = (rc == 0) ? f_stat.st_mtime : -1;
        f_perm = to_string(f_stat.st_mode);
        f_index = md5(path+contents());
    }

    void display(int level=0) {
        spacer(level);
        printf("%s %s %s %s %lld %ld\n", f_index.c_str(), f_path.c_str(), f_name.c_str(), f_perm.c_str(), f_size, f_modified);
    }

    string stringify() {return f_name + to_string(f_size) + to_string(f_modified);}

    string contents() {
        ifstream in(f_path.c_str(), ios::in | ios::binary);
        if (in) {
            ostringstream cont;
            cont << in.rdbuf();
            in.close();
            return(cont.str());
        }
    }

    bool touch() {
        ofstream ff(f_path);
        ff << FS.fetch(f_index);
        ff.close();
    }
};

class tree {
public:
    string dirpath, dirname;
    vector <tree> dir_list;
    vector <file> file_list;

    tree init_tree(string path, string dir_name, bool is_commit=false) {
        tree ret_tree;
        ret_tree.dirpath = path;
        ret_tree.dirname = dir_name;
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir (path.c_str())) != NULL) {
            int cnt = 0;
            while ((ent = readdir (dir)) != NULL) {
                ++cnt;
                if(cnt < 3) continue; // for avoiding . and .. directory
                if(ent->d_type == 4) ret_tree.dir_list.push_back(init_tree(path+"/"+ent->d_name, ent->d_name, is_commit));
                else if(ent->d_type == 8) {
                    file temp(path+"/"+ent->d_name, ent->d_name);
                    if(is_commit) {
                        if(!FS.exists(temp.f_index)) FS.push(temp.f_index, temp.contents());
                    }
                    ret_tree.file_list.push_back(temp);
                }

            }
            closedir (dir);
        }
        return ret_tree;
    }

    bool time_travel() {
        for(int i=0; i<dir_list.size(); ++i) {
            mkdir(dir_list[i].dirpath.c_str(), 755);
            dir_list[i].time_travel();
        }
        for(int i=0; i<file_list.size(); ++i) file_list[i].touch();
    }

    void wipe() {
        dirname = "";
        dir_list.clear();
        file_list.clear();
    }

    string stringify() {
        string temp = dirname;
        for(int i=0; i<dir_list.size(); ++i) temp += dir_list[i].stringify();
        for(int i=0; i<file_list.size(); ++i) temp += file_list[i].stringify();
        return temp;
    }

    string full_hash() {
        return md5(stringify());
    }

    void compare(tree t) {
        tree blank;
        for(int i=0; i<dir_list.size(); ++i) {
            bool flag = true;
            for(int k=0; k<t.dir_list.size() && flag; ++k) {
                if(dir_list[i].dirname == t.dir_list[k].dirname) {
                    flag = false;
                    dir_list[i].compare(t.dir_list[k]);
                }
            }
            if(flag) {
                printf("Deleted: %s\n", dir_list[i].dirpath.c_str());
                dir_list[i].compare(blank);
            }
        }
        for(int i=0; i<t.dir_list.size(); ++i) {
            bool flag = true;
            for(int k=0; k<dir_list.size() && flag; ++k) if(t.dir_list[i].dirname == dir_list[k].dirname) flag = false;
            if(flag) {
                printf("New: %s\n", t.dir_list[i].dirpath.c_str());
                blank.compare(t.dir_list[i]);
            }
        }
        for(int i=0; i<file_list.size(); ++i) {
            bool flag = true;
            for(int k=0; k<t.file_list.size() && flag; ++k) {
                if(file_list[i].f_name == t.file_list[k].f_name) {
                    flag = false;
                    if(file_list[i].f_index != t.file_list[k].f_index) printf("Modifed: %s\n", file_list[i].f_path.c_str());
                }
            }
            if(flag) printf("Deleted: %s\n", file_list[i].f_path.c_str());
        }
        for(int i=0; i<t.file_list.size(); ++i) {
            bool flag = true;
            for(int k=0; k<file_list.size() && flag; ++k) if(t.file_list[i].f_name == file_list[k].f_name) flag = false;
            if(flag) printf("New: %s\n", t.file_list[i].f_path.c_str());
        }
    }
};

class commit {
public:
    string message, full_hash;
    tree structure;

    commit(string msg, tree str, string hhash) {
        message = msg;
        structure = str;
        full_hash = hhash;
    }

    bool checkout() {
        remove_dir(rootpath);
        structure.time_travel();
    }
};

vector <commit> all_commits;
