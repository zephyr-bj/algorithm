#include <fstream> // Required for file stream operations (ifstream)
#include <iostream> // Required for input/output operations (cout, cerr)
#include <string>   // Required for using std::string
#include <vector>
#include <unordered_map>

int readTextLine(const std::string & filename) {
    std::ifstream inputFile(filename);
    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            std::cout << line << std::endl;
        }
        inputFile.close();
    } else {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return -1;
    }
    return 0;
}

#include <fstream>
#include <vector>
#include <iostream>

int read4K(const std::string & filename) {
    std::ifstream file("filename", std::ios::binary); // Open in binary mode for raw data

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    // Define a buffer size (e.g., 4KB)
    const int bufferSize = 4096;
    std::vector<char> buffer(bufferSize);

    while (file) { // Loop as long as the stream is in a good state
        file.read(buffer.data(), buffer.size()); // Read a chunk into the buffer
        std::streamsize bytesRead = file.gcount(); // Get the number of bytes actually read

        if (bytesRead > 0) {
            // Process the data in the buffer
            // For example, print it (careful with binary data, may not be printable)
            for (int i = 0; i < bytesRead; ++i) {
                std::cout << buffer[i];
            }
        } else if (file.eof()) {
            // Reached end of file
            break;
        } else if (file.fail() && !file.eof()) {
            // An error occurred during reading (not just EOF)
            std::cerr << "Error reading file!" << std::endl;
            break;
        }
    }

    file.close(); // Close the file
    return 0;
}

int writeTextLine(const std::string & filename) {
    std::ofstream outputFile(filename);

    if (outputFile.is_open()) {
        outputFile << "This is the first line of text.\n";
        outputFile << "This is the second line.\n";
        outputFile << "Numbers can also be written: " << 123 << std::endl;

        outputFile.close();
        std::cout << "Data successfully written to example.txt" << std::endl;
    } else {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return -1;
    }

    return 0;
}

std::vector<char> readBinaryFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg); // Seek back to beginning

    std::vector<char> buffer(size);
    if (file.read(buffer.data(), size)) {
        return buffer;
    } else {
        std::cerr << "Error reading file: " << filename << std::endl;
        return {};
    }
}


int writeBinaryFile(const std::string& filename) {
    std::ofstream outputFile(filename, std::ios::out | std::ios::binary);

    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return 1; // Indicate an error
    }
    int integerValue = 12345;
    float floatValue = 3.14159f;
    char charArray[] = "Hello Binary!";

    outputFile.write(reinterpret_cast<const char*>(&integerValue), sizeof(integerValue));
    outputFile.write(reinterpret_cast<const char*>(&floatValue), sizeof(floatValue));
    outputFile.write(reinterpret_cast<const char*>(charArray), sizeof(charArray));
    outputFile.close();

    return 0; // Indicate success
}

enum class test_type{
    RED_TXT,
    WRT_TXT,
    RED_BIN,
    WRT_BIN,
};

int main(int argc, char* argv[]) {
    std::unordered_map<std::string, test_type>test_map;
    test_map["read_text"] =   test_type::RED_TXT;
    test_map["write_text"] =  test_type::WRT_TXT;
    test_map["read_binary"] = test_type::RED_BIN;
    test_map["write_binary"] =test_type::WRT_BIN;

    if (argc < 2) {
        printf("please enter test option\n");
    return 1;
    }
    auto it = test_map.find(std::string(argv[1]));
    if (it == test_map.end()) {
        printf("test '%s' is not supported\n", argv[1]);
        return 1;
    }
    const std::string filename(argv[2]);
    test_type test = it->second;
    switch (test) {
        case test_type::RED_TXT:
            readTextLine(filename);
            break;
        case test_type::WRT_TXT:
            writeTextLine(filename);
            break;
        case test_type::RED_BIN:
            readBinaryFile(filename);
            break;
        case test_type::WRT_BIN:
            writeBinaryFile(filename);
            break;
        default:
        printf("test function not implemented for '%s'\n", argv[1]);
        break;
    }

    return 0;
}

