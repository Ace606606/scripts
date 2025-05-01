#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

void print_directory_structures(const fs::path& directory, int level = 0) {
    // indentation
    std::string indent(level * 3, ' ');

    try {
        // recursive directory traversal
        for (const auto& entry : fs::directory_iterator(directory)) {
            // name element output
            std::cout << indent << "├──  " << entry.path().filename().string()
                      << std::endl;

            // if it is a directory - recursive process its contents
            if (entry.is_directory()) {
                print_directory_structures(entry.path(), level + 1);
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error accessing " << directory << ": " << e.what()
                  << std::endl;
    }
}

int main() {
    std::string path;
    std::cout << "Enter the path to the directory: ";
    std::getline(std::cin, path);

    if (!fs::exists(path)) {
        std::cerr << "Error: directory does not exist!" << std::endl;
        return 1;
    }

    std::cout << "Directory structure " << path << ":\n";
    print_directory_structures(path);

    return 0;
}