#include <cstddef>
#include <ios>
#include <iostream>
#include <limits>

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

    void reset() { offset = 0; }

    size_t used_memory() { return offset; }

    size_t remaining_memory() { return capacity - offset; }
};

size_t user_input() {
    size_t input;
    std::cout << "\nACTION: ";
    std::cin >> input;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nInvalid input. Enter a number.\n";
        return std::numeric_limits<size_t>::max();
    }

    return input;
}

int main() {

    BumpAllocator allocator(16);

    while (true) {

        std::cout << "\n<----Bump Allocator Menu---->\n\n"
                  << "1. Allocate memory\n"
                  << "2. Check used memory\n"
                  << "3. Check remaining memory\n"
                  << "4. Delete/Reset memory\n"
                  << "5. Quit\n"
                  << "\n<--------------------------->\n";

        size_t input = user_input();
        if (input == std::numeric_limits<size_t>::max()) {
            continue;
        }

        switch (input) {
        case 1: {
            std::cout << "\nHow much memory would you like?\n";
            size_t size = user_input();
            if (size == std::numeric_limits<size_t>::max()) continue;

            char *result = allocator.allocate(size);

            if (result == nullptr) {
                std::cout << "\n[Allocation failed]\n";
            } else {
                std::cout << "\n[Allocation successful]\n";
            }
            break;
        }
        case 2: {
            std::cout << "\n[Used memory: " << allocator.used_memory() << "]\n";
            break;
        }
        case 3: {
            std::cout << "\n[Remaining memory: " << allocator.remaining_memory() << "]\n";
            break;
        }
        case 4: {
            allocator.reset();
            std::cout << "\n[Memory reset]" << "\n";
            break;
        }
        case 5: {

            return 0;
        }
        default: {
            std::cout << "\n[Invalid choice]";
            break;
        }
        }
    }
}
