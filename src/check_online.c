#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <sys/wait.h>

#include "check_online.h"

#define RETURN_BUFFER_SIZE 1024
#define COMMAND_BUFFER_SIZE 1024
#define PING_COMMAND "ping -c 4"
#define DEFAULT_SERVER "8.8.8.8"



int main(int argc, char *argv[]) {
    (void)argc;
    if (can_ping_net(argv[1])) {
        return EXIT_SUCCESS;
    } else {
        return 2;
    };
}

int can_ping_net(char* ip_or_url) {
    FILE *command_handle;
    char command_to_run[COMMAND_BUFFER_SIZE];
    
    build_command_with_buffer_and_server(command_to_run, ip_or_url);
    command_handle = start_ping_process(command_to_run);
    display_messages(command_handle);
    return get_command_result_or_exit(command_handle);
}

bool did_command_succeed(int wait_status) {
    if (WIFEXITED(wait_status) && WEXITSTATUS(wait_status) == 0) {
        return true;
    } else {
        return false;
    }
}

void print_result_message(int command_return) {
    if (WEXITSTATUS(command_return) == 0) {
        printf("Network connected.");
    } else {
        printf("Network disconnected.");
    }
}

void stop_if_error_occurred(int command_return) {
    if (command_return == -1)
        fatal_error("pclose() failed.");
    if (!WIFEXITED(command_return))
        fatal_error("Process terminated.");
    if (WEXITSTATUS(command_return) == EXIT_FAILURE)
        fatal_error("Process failed.");
}


_Noreturn void fatal_error(char* error_message) {
    printf("%s\n", error_message);
    exit(EXIT_FAILURE);
}

void build_command_with_buffer_and_server(char *buffer, char *server) {
    if (server == NULL) server = DEFAULT_SERVER;
    snprintf(buffer, COMMAND_BUFFER_SIZE, "%s %s", PING_COMMAND, server);
}

FILE *start_ping_process(char *command) {
    FILE *command_handle;
    command_handle = popen(command, "r");
    if (!command_handle) fatal_error("Error starting command.");
    return command_handle;
}

void display_messages(FILE *command_handle) {
    char return_buffer[RETURN_BUFFER_SIZE];

    while (fgets(return_buffer, sizeof(return_buffer), command_handle)) {
        printf("%s", return_buffer);
    }
}

int get_command_result_or_exit(FILE *command_handle) {
    int ping_result;
    int command_return;
    
    command_return = pclose(command_handle);
    stop_if_error_occurred(command_return);
    ping_result = did_command_succeed(command_return);
    print_result_message(command_return);
    return ping_result;
}
