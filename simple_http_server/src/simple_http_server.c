#include <stdio.h>

#include "http.h"
#include "socket_tcp_manager.h"

int main() {
    printf("%s.\n", http_exposed());

    printf("%s.\n", socket_tcp_manager_exposed());
}
