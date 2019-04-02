
void perform_commit(string message) {
    root.wipe();
    root = root.init_tree(rootpath, rootpath, true);
    commit temp(message, root, root.full_hash());
    all_commits.push_back(temp);
    ++head;
}

void list_commits() {
    printf("================= Commit List ==============\n");
    for(int i=all_commits.size()-1; i>=0; --i) {
        printf("Commit %2d | %s\n", i+1, all_commits[i].message.c_str());
    }
    printf("============================================\n");
}

void checkout(int h) {
    --h;
    if(h >= 0 && h < all_commits.size()) {
        printf("Checkout Commit #%d\n", h+1);
        all_commits[h].checkout();
        root.wipe();
        root = all_commits[h].structure;
        printf("Checkout Complete\n");
    }
    else printf("Commit #%d doesn't exist\n", h+1);
}

void commit_details(int h) {
    --h;
    if(h >= 0 && h < all_commits.size()) {
        printf("Details of Commit #%d\n", h+1);
        all_commits[h].display();
    }
    else if(h==-1) {
        root.display();
    }
    else printf("Commit #%d doesn't exist\n", h+1);
}

void compare() {
    tree temp;
    temp = temp.init_tree(rootpath, rootpath);
    printf("\n=========== Status ===========\n");
    root.compare(temp);
    printf("\n");
}

bool init_app() {
    perform_commit("Initial Commit");
}
