
void perform_commit(string message) {
    root.wipe();
    root = root.init_tree(rootpath, rootpath, true);
    commit temp(message, temp_objects);
    temp_objects.clear();
    all_commits.push_back(temp);
    ++head;
    cout << endl;

}

bool init_app() {
    perform_commit("Initial Commit");

//    root.display();
//    all_commits[head].display();
//
    FS.display();
}
