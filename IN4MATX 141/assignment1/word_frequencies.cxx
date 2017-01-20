#include <iostream>
#include <fstream>
#include <functional>
#include <locale>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

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

std::vector<std::string> tokenize(const char* filename)
{
  std::vector<std::string> tokens;
  each_token(filename, [&] (std::string token) {
    tokens.push_back(token);
  });
  return tokens;
}

std::unordered_map<std::string, std::size_t> compute_word_frequencies(std::vector<std::string> tokens)
{
  std::unordered_map<std::string, std::size_t> frequencies;
  for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); ++it) {
    ++frequencies[*it];
  }
  return frequencies;
}

// A faster alternative that builds the hashmap without creating a list first
std::unordered_map<std::string, std::size_t> fast_word_frequencies(const char* filename)
{
  std::unordered_map<std::string, std::size_t> frequencies;
  each_token(filename, [&] (std::string token) {
    ++frequencies[token];
  });
  return frequencies;
}

void print(std::unordered_map<std::string, std::size_t>& frequencies)
{
  std::map<std::size_t, std::vector<std::string>, std::greater<std::size_t> > by_frequencies;

  for (std::unordered_map<std::string, std::size_t>::iterator it = frequencies.begin(); it != frequencies.end(); ++it) {
    by_frequencies[it->second].push_back(it->first);
  }

  for (std::map<std::size_t, std::vector<std::string> >::iterator it = by_frequencies.begin(); it != by_frequencies.end(); ++it) {
    for (std::vector<std::string>::iterator s_it = it->second.begin(); s_it != it->second.end(); ++s_it) {
      std::cout << *s_it << ": " << it->first << std::endl;
    }
  }
}

int main(int argc, char *argv[])
{
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " " << "filename" << std::endl;
    return 1;
  }

  std::unordered_map<std::string, std::size_t> frequencies = compute_word_frequencies(tokenize(argv[1]));
  // std::unordered_map<std::string, std::size_t> frequencies = fast_word_frequencies(argv[1]);
  print(frequencies);
  return 0;
}
