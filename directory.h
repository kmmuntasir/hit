bool dir_exists(string dirpath) {
    DIR *dir = opendir(dirpath.c_str());
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
