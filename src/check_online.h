#ifndef HAS_CHECK_ONLINE
#define HAS_CHECK_ONLINE

#include <stdio.h>
#include <stdlib.h>

int can_ping_net(char *ip_or_url);
void print_result_message(int command_return);
bool did_command_succeed(int wait_status);
void fatal_error(char* error_message);
void stop_if_error_occurred(int command_return);
void build_command_with_buffer_and_server(char *buffer, char *server);
FILE *start_ping_process(char *command);
void display_messages(FILE *command_handle);
int get_command_result_or_exit(FILE *command_handle);


#endif