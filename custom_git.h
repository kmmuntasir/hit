bool init_app() {
    struct dirent info;
    if (!dir_exists(hitpath)) {
        printf( "Initializing Empty Hit Repository\n");
        if(mkdir(hitpath.c_str(), 755) != 0) {
            printf("Hit Initialization Failed!\n");
            return false;
        }
        ofstream last_hash (hitpath+"/last_hash.txt");
        last_hash.close();
    }
    return true;
}
