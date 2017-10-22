#include "process.h"
#include "lib.h"

const char* messages[] = {
    "I remember the year after college I was broke.",
    "I realized I was becoming impossible, more and more impossible.",
    "Fear is overcome by procedure.",
    "When I make contact with a piece of paper without looking up I am happy.",
    "The mountain skies were clear except for the umlaut of a cloud.",
    "What's more, try it sometime. It works."
};

void process_main(void) {
    unsigned i = 0;
    unsigned nmessages = sizeof(messages) / sizeof(messages[0]);
    char buf[256];

    while (1) {
        if (i % (1 << 30) == 0) {
            int len = snprintf(buf, sizeof(buf), "%s\n",
                               messages[rand() % nmessages]);
            sys_write(buf, len);
        }
        ++i;
    }
}
