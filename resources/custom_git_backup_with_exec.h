typedef struct{
    string f_name, f_modified;
    long long int f_size;
} file;

void file_display(file f) {
    printf("Name: %s\n", f.f_name.c_str());
    printf("Size: %lld\n", f.f_size);
    printf("Modified: %s\n", f.f_modified.c_str());
}

string exec(const char* cmd) {
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

file prop(const char *path, const char *f_name) {
    string result, temp;
    file ret_file;
    ret_file.f_name = f_name;
    int i, filesize;
    result = exec("stat 'testfile.txt' | grep Size:");
    for(i=8; i<result.size() && result[i]!=' '; ++i) temp += result[i];
    filesize = atoi(temp.c_str());
//    printf("Filesize: %d\n", filesize);
    ret_file.f_size = filesize;


    temp="";
    result = exec("stat 'testfile.txt' | grep Modify:");
    for(i=28; i<result.size() && result[i]!=' '; ++i) temp += result[i];
//    printf("Modified: %s\n", temp.c_str());
    ret_file.f_modified = temp;
    return ret_file;
}


int list_all(const char *path) {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (path)) != NULL) {
      while ((ent = readdir (dir)) != NULL) {
        printf ("%d - %s\n", ent->d_type, ent->d_name);
      }
      closedir (dir);
    } else {
      /* could not open directory */
      perror ("");
      return EXIT_FAILURE;
    }
}

long GetFileSize(string filename)
{
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

long datemodified(string filename) {
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_mtime : -1;
}
