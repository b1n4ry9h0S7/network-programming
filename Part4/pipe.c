#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_NUM_ARGS 20
#define MAX_STR_LEN 200

char * error_msg[] = {
    "\nUsage: ./19pipe [\"<LHS-command>|<RHS-command>\"]\n\n",
    "\nCould not fork\n\n",
    "\nError while doing duplicating standard output\n\n",
    "\nError while doing duplicating standard input\n\n",
    "\nThere is no pipe\n\n",
    "\nNumber of arguments exceeded their limit\n\n"
};

void print_error(int msg_num, int exit_code);

int main(int argc, char * argv[])
{
    int i, j;
    int fd[2];
    char * lhs = NULL;
    char * rhs = NULL; 
    char tmpstr[MAX_STR_LEN];
    char prevchar;
    char * lhscommand = "ls";
    char * rhscommand = "sort";
    char * lhsargs[MAX_NUM_ARGS] = {
        "ls",
        "-l",
        NULL
    };
    char * rhsargs[MAX_NUM_ARGS] = {
        "sort",
        NULL
    };

    if (argc > 2) print_error(0, 2);

    if (argc == 2)
    {
        rhs = argv[1];
        lhs = strsep( & rhs, "|");
        if (rhs == NULL) print_error(4, 6);
        prevchar = ' ';
        j = 0;
        for (i = 0; i < strlen(lhs); i++)
        {
            if (prevchar == ' ' && lhs[i] == ' ') continue;
            tmpstr[j++] = lhs[i];
            prevchar = lhs[i];
            if (j > MAX_NUM_ARGS) print_error(5, 7);
        }

        if (lhs[i - 1] == ' ') tmpstr[j - 1] = '\0';

        tmpstr[j] = '\0';
        strcpy(lhs, tmpstr);
        prevchar = ' ';
        j = 0;

        for (i = 0; i < strlen(rhs); i++)
        {
            if (prevchar == ' ' && rhs[i] == ' ') continue;
            tmpstr[j++] = rhs[i];
            prevchar = rhs[i];
            if (j > MAX_NUM_ARGS) print_error(5, 7);
        }

        if (rhs[i - 1] == ' ') tmpstr[j - 1] = '\0';
        tmpstr[j] = '\0';
        strcpy(rhs, tmpstr);
        i = 0;
        while ((lhsargs[i] = strsep( & lhs, " ")) != NULL) i++;
        lhscommand = lhsargs[0];
        i = 0;
        while ((rhsargs[i] = strsep( & rhs, " ")) != NULL) i++;
        rhscommand = rhsargs[0];
    } 
    pipe(fd);
    switch (fork())
    {
        case -1:
            print_error(1, 3);
            exit(2);
        case 0:
            if (dup2(fd[1], fileno(stdout)) == -1)
                print_error(2, 4);
            close(fd[0]);
            close(fd[1]);
            execvp(lhscommand, lhsargs);
            return 1;
        default:
            if (dup2(fd[0], fileno(stdin)) == -1)
                print_error(3, 5);
            close(fd[0]);
            close(fd[1]);
            execvp(rhscommand, rhsargs);
            return 0;
    }
}

void print_error(int error_index, int exit_code)
{
    fprintf(stderr, "%s", error_msg[error_index]);
    exit(exit_code);

}