
void perform_commit(string message) {
    root.wipe();
    root = root.init_tree(rootpath, rootpath, true);
    commit temp(message, temp_objects, root.full_hash());
    temp_objects.clear();
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

bool init_app() {
    perform_commit("Initial Commit");
}
