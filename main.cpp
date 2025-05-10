#include <cstddef>

class BumpAllocator {
private:
    char *buffer;
    size_t capacity;
    size_t offset;

public:
    char *allocate(size_t size) {

        if (!((offset + size) <= capacity)) {
            return nullptr;
        } else {
            char *ptr = buffer + offset;
            offset += size;
            return ptr;
        }
    }

    BumpAllocator(size_t size) {
        buffer = new char[size];
        capacity = size;
        offset = 0;
    }
    ~BumpAllocator() { delete[] buffer; }
};

int main() {
    return 0;
}
