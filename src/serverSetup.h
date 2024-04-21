#ifndef __ESP_HTTP_SERVER__
#define __ESP_HTTP_SERVER__

#include <vector>

struct OtaCommand {
    const char* key;
    void (*callback)(int offset, unsigned char* data);
};

void setupServer(std::vector<OtaCommand> commands);

#endif // __ESP_HTTP_SERVER__
