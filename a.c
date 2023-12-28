#include <stdio.h>
#include "pipex.h"
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[]) {
    // Çevresel değişkenleri ekrana yazdırma
    for (int i = 0; envp[i] != NULL; i++) {
        printf("%s\n",envp[i]);
    }
    (envp++);
    (envp++);
    (envp++);
    (envp++);
    // printf("%s",argv[1]);
    // char **a=envp;
    // printf("%s",a[1]);
    // printf("%d",access("/usr/bin/ls",X_OK));
	// printf("%s\n",*(envp));
    // char **a=ft_split(*(envp) + 5,':');
    // printf("%s\n",a[0]);
    // printf("%s\n",a[1]);
    // printf("%s\n",a[2]);
    // printf("%s\n",a[3]);
    return 0;
}
