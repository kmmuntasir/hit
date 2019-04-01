bool init_app(string rootpath=".") {
    string hitpath = rootpath + "/.hit";
    if(mkdir(hitpath.c_str(), 755) != 0) {
        printf("Hit Initialization Failed!\n");
        return false;
    }

//    if( stat( pathname, &info ) != 0 )
//        printf( "cannot access %s\n", pathname );
//    else if( info.st_mode & S_IFDIR )  // S_ISDIR() doesn't exist on my windows
//        printf( "%s is a directory\n", pathname );
//    else
//        printf( "%s is no directory\n", pathname );l


    ofstream last_hash (hitpath+"/last_hash.txt");
    last_hash.close();

    return true;
}
