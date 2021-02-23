#include <stdio.h>
#include "conversion.h"
#include "transmitter.h"

int main() {
    char* message = "1.3,2.5,5.8\n1.1,2.2,3";
    printf("%s\n", message);

    message = encode_message(message);
    printf("%s\n", message);

    send_data(message);

    message = decode_message(message);
    printf("%s\n", message);

    return 0;
}
