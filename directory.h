


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
