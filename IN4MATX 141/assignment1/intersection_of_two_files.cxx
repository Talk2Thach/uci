#include <iostream>
#include <fstream>
#include <functional>
#include <locale>
#include <string>
#include <unordered_set>

void each_token(const char* filename, std::function<void(std::string)> lambda)
{
  std::ifstream in(filename);
  std::string token = "";
  char ch;

  if (in.is_open()) {
    while (in.good()) {
      in.get(ch);
      if (ch >= 'A' && ch <= 'Z') {
        token += tolower(ch);
      } else if ((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9')) {
        token += ch;
      } else {
        if (token.length() > 0) {
          lambda(token);
        }
        token = "";
      }
    }
  }

  if (!in.eof() && in.fail()) {
    std::cerr << "Error reading file: " << filename << std::endl;
  }

  in.close();
}

std::size_t intersection(const char* filename, const char* another_filename)
{
  std::size_t result = 0;
  std::unordered_set<std::string> tokens;

  each_token(filename, [&] (std::string token) {
    tokens.insert(token);
  });

  each_token(another_filename, [&] (std::string token) {
    std::unordered_set<std::string>::iterator find = tokens.find(token);
    if (find != tokens.end()) {
      tokens.erase(find);
      ++result;
      // std::cout << token << std::endl;
    }
  });

  return result;
}

std::ifstream::pos_type filesize(const char* filename)
{
  std::ifstream in(filename, std::ifstream::ate|std::ifstream::binary);
  return in.tellg();
}

int main(int argc, char *argv[])
{
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " filename filename2" << std::endl;
    return 1;
  }

  // Error handling
  std::ifstream::pos_type size1 = filesize(argv[1]);
  std::ifstream::pos_type size2 = filesize(argv[2]);
  if (size1 < 0) std::cerr << "Error reading file: " << argv[1] << std::endl;
  if (size2 < 0) std::cerr << "Error reading file: " << argv[2] << std::endl;
  if (size1 < 0 || size2 < 0) return 1;

  // pass the smaller file as the first parameter
  // so the hashmap will have a higher chance to be smaller thus faster
  if (size1 <= size2) {
    std::cout << intersection(argv[1], argv[2]) << std::endl;
  } else {
    std::cout << intersection(argv[2], argv[1]) << std::endl;
  }

  return 0;
}
