#include<bits/stdc++.h>
using namespace std;

int main(){

    char command_str[50];
    int checkpoint[100], total_ck = 0;
    char checkpoint_messages[100][100];

    while(1){
        scanf("%s", command_str);
        getchar();

        if(strcmp(command_str, "ck") == 0) {
            char checkpoint_message[100];

            scanf("%s", checkpoint_messages[total_ck]);
            getchar();
            total_ck = total_ck + 1;

            freopen("content.txt", "r", stdin);

            char content[1000][100];
            int i=0;

            while((scanf("%s", content[i])) != EOF){

                printf("%s\n", content[i]);
                i = i+1;
            }
            fclose(stdin);


            cerr << i << "\n";

            freopen("1.txt", "w", stdout);
            for(int idx=0; idx<i; idx++){
                printf("%s ", content[idx]);
            }
            fclose(stdout);
//            break;
        }
        else if(strcmp(command_str, "st") == 0){
            freopen("content.txt", "r", stdin);

            char content[1000][100];
            int i=0;

            while((scanf("%s", content[i])) != EOF){

//                printf("%s\n", content[i]);
                i = i+1;
            }


        }
        else if(strcmp(command_str, "list") == 0){

            for(int k=0; k<total_ck; k++){
                printf("%d %s\n", k, checkpoint_messages[k]);
            }

        }
        else if(strcmp(command_str, "goto") == 0){

        }
        else{
            break;
        }



    }

    return 0;
}
