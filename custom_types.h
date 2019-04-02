void spacer(int level=0) {
    while(level--) printf("----");
}


class filesystem {
public:
    map <string, string> fs;
    map <string, string>::iterator itr;
    void push(string key, string value) {
        fs.insert(pair<string, string>(key, value));
    }

    string fetch(string key) {
        itr = fs.find(key);
        return (itr == fs.end()) ? "" : fs.find(key)->second;
    }

    bool exists(string key) {
        itr = fs.find(key);
        return (itr == fs.end()) ? false : true;
    }

    void display() {
        printf("%-33s | %-s\n", "Key", "Value");
        for(itr=fs.begin(); itr != fs.end(); ++itr) {
            printf("%-33s | %-s\n", itr->first.c_str(), itr->second.c_str());
        }
        printf("\n");
    }
};

filesystem FS;

class file{
public:
    string f_index, f_name, f_path, f_perm;
    time_t f_modified;
    long long int f_size;

    file (string path, string f_name) { // constructor
        struct stat f_stat;
        f_path = path;
        f_name = f_name;
        int rc = stat(path.c_str(), &f_stat);
        f_size = (rc == 0) ? f_stat.st_size : -1;
        f_modified = (rc == 0) ? f_stat.st_mtime : -1;
        f_perm = to_string(f_stat.st_mode);
        f_index = md5(path+contents());
    }

    void display(bool simple_view=false, int level=0) {
        if(simple_view) {
            spacer(level);
            printf("%s %s %s %s %lld %ld\n", f_index.c_str(), f_path.c_str(), f_name.c_str(), f_perm.c_str(), f_size, f_modified);
        }
        else {
            spacer(level);
            printf("Index: %s\n", f_index.c_str());
            spacer(level);
            printf("Name: %s\n", f_name.c_str());
            spacer(level);
            printf("Size: %lld\n", f_size);
            spacer(level);
            printf("Modified: %ld\n", f_modified);
        }
    }

    string stringify() {
        string temp = f_name;
        temp += to_string(f_size);
        temp += to_string(f_modified);
        return temp;
    }

    string contents() {
      ifstream in(f_path.c_str(), ios::in | ios::binary);
      if (in) {
        ostringstream cont;
        cont << in.rdbuf();
        in.close();
        return(cont.str());
      }
    //  throw(errno);
    }
};

vector <file> temp_objects;

class tree {
public:
    string dirname;
    vector <tree> dir_list;
    vector <file> file_list;

    tree init_tree(string path, string dir_name, bool is_commit=false) {
        tree ret_tree;
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
                        temp_objects.push_back(temp);
                    }
                    ret_tree.file_list.push_back(temp);
                }

            }
            closedir (dir);
        }
        return ret_tree;
    }

    void wipe() {
        dirname = "";
        dir_list.clear();
        file_list.clear();
    }

    void display(int level=0) {
        spacer(level);
        printf("[%s]***\n", dirname.c_str());
        for(int i=0; i<dir_list.size(); ++i) {
            dir_list[i].display(level+1);
        }
        for(int i=0; i<file_list.size(); ++i) {
            file_list[i].display(true, level+1);
        }
    }

    string stringify() {
        string temp = dirname;
        for(int i=0; i<dir_list.size(); ++i) {
            temp += dir_list[i].stringify();
        }
        for(int i=0; i<file_list.size(); ++i) {
            temp += file_list[i].stringify();
        }
        return temp;
    }

    string full_hash() {
        return md5(stringify());
    }
};

class commit {
public:
    string message, full_hash;
    vector <file> objects;

    commit(string msg, vector<file>obj, string hhash) {
        message = msg;
        objects = obj;
        full_hash = hhash;
    }

    void display() {
        printf("Message: %s\n", message.c_str());
        printf("Hash   : %s\n", full_hash.c_str());
        for(int i=0; i<objects.size(); ++i) {
            objects[i].display(true);
        }
    }

    bool checkout() {

    }
};

//class branch {
//
//};

vector <commit> all_commits;
