#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

void print_directory_structures(const fs::path& directory,
                                std::vector<std::string>& dirs_to_ignore,
                                int level = 0) {
    // indentation
    std::string indent(level * 3, ' ');

    try {
        // recursive directory traversal
        for (const auto& entry : fs::directory_iterator(directory)) {
            // name element output
            std::cout << indent << (entry.is_directory() ? "└──/" : "├── ")
                      << entry.path().filename().string() << '\n';

            // if it is a directory - recursive process its contents
            if (entry.is_directory() && [&entry, &dirs_to_ignore]() -> bool {
                    for (const auto& dir : dirs_to_ignore)
                        if (entry.path().filename().string() == dir)
                            return false;
                    return true;
                }()) {
                print_directory_structures(entry.path(), dirs_to_ignore,
                                           level + 1);
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error accessing " << directory << ": " << e.what()
                  << std::endl;
    }
}

std::vector<std::string> forming_dirs_to_ignor(
    const std::string& input_dirs_ignore) {
    std::vector<std::string> dirs_to_ignore;
    std::istringstream iss(input_dirs_ignore);
    std::string token;
    while (iss >> token) dirs_to_ignore.push_back(token);
    return dirs_to_ignore;
}

int main() {
    std::string path;
    std::cout << "Enter the path to the directory: ";
    std::getline(std::cin, path);

    if (!fs::exists(path)) {
        std::cerr << "Error: directory does not exist!" << std::endl;
        return 1;
    }

    std::vector<std::string> dirs_to_ignore;
    std::string input_dirs_ignore;
    std::cout << "Enter directories to ignore (space separated): ";
    std::getline(std::cin, input_dirs_ignore);

    if (input_dirs_ignore.size())
        dirs_to_ignore = forming_dirs_to_ignor(input_dirs_ignore);

    std::cout << "Directory structure " << path << ":\n";
    print_directory_structures(path, dirs_to_ignore);

    return 0;
}