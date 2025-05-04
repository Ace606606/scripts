#include <cstring>
#include <filesystem>
#include <iostream>
#include <string>

void copyVSCodeConfig(const std::filesystem::path& source_path) {
    const std::filesystem::path target_path =
        std::filesystem::current_path() / ".vscode";

    try {
        if (std::filesystem::exists(target_path)) {
            std::filesystem::remove_all(target_path);
            std::cout << "[INFO] old .vscode folder remove\n";
        }

        std::filesystem::copy(source_path, target_path,
                              std::filesystem::copy_options::recursive);
        std::cout << "[SUCCESS] Config copied from " << source_path << "\n";
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "[ERROR] " << e.what() << '\n';
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2 || strcmp(argv[1], "create") != 0) {
        std::cerr << "Usage: " << argv[0]
                  << " create [path_to_vscode_folder]\n";
        std::cerr << "Default path: ~/.config/Code/User/.vscode\n";
        return 1;
    }

    std::filesystem::path default_path = std::filesystem::path(getenv("HOME")) /
                                         ".config" / "Code" / "User" /
                                         ".vscode";

    std::filesystem::path source_path =
        (argc >= 3) ? std::filesystem::path(argv[2]) : default_path;

    if (!std::filesystem::exists(source_path)) {
        std::cerr << "[ERROR] Source folde not found: " << source_path << '\n';
    }

    copyVSCodeConfig(source_path);

    return 0;
}