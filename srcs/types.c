#include "../inc/ft_strace.h"

static void int_type(char *arg_type, pid_t pid, unsigned long long int reg_addr) {
    (void) arg_type;
    (void) pid;
    fprintf(stdout, "%d", (int) reg_addr);
}

static void long_type(char *arg_type, pid_t pid, unsigned long long int reg_addr) {
    (void) arg_type;
    (void) pid;
    fprintf(stdout, "%ld", (long) reg_addr);
}

void unsigned_int_type(char *arg_type, pid_t pid, unsigned long long int reg_addr) {
    (void) arg_type;
    (void) pid;
    fprintf(stdout, "%u", (unsigned int) reg_addr);
}

static void unsigned_long_type(char *arg_type, pid_t pid, unsigned long long int reg_addr) {
    (void) arg_type;
    (void) pid;
    fprintf(stdout, "%lu", (unsigned long int) reg_addr);
}

static void charptr_type(char *arg_type, pid_t pid, unsigned long long int reg_addr) {
    char *str = peekdata(pid, reg_addr, 256);
        if (str) {
            fprintf(stdout, "\"%s\"", (char *)peekdata(pid, reg_addr, 256));
            free(str);
        } else
            fprintf(stdout, "%s", arg_type);
}

static void chardoubleptr_type(char *arg_type, pid_t pid, unsigned long long int reg_addr) {
    char **doubleptr = peekdoubleptr(pid, reg_addr);
    if (doubleptr) {
        char *str = to_string(doubleptr);
        fprintf(stdout, "%s", str);
        free(str);
        free_tab(doubleptr);
    } else
        fprintf(stdout, "%s", arg_type);
}

static void intptr_type(char *arg_type, pid_t pid, unsigned long long int reg_addr) {
    int *value = peekdata(pid, reg_addr, sizeof(int));
    if (value) {
        fprintf(stdout, "%d", value[0]);
        free(value);
    } else
        fprintf(stdout, "%s", arg_type);
}

static void generic_type(char *arg_type, pid_t pid, unsigned long long int reg_addr) {
    (void) arg_type;
    (void) pid;
    (void) reg_addr;
    fprintf(stdout, "%s", arg_type);
}

t_type types[] = {
    {"int", int_type},
    {"long", long_type},
    {"unsigned int", unsigned_int_type},
    {"unsigned long", unsigned_long_type},
    {"char*", charptr_type},
    {"char**", chardoubleptr_type},
    {"int*", intptr_type},
    {"void*", generic_type},
    {"struct", generic_type},
    {"sigset_t", generic_type},
    {"fd_set", generic_type},
    {NULL, NULL},
};