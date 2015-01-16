//Tianya Chen #59359881
//Edward Xia  #73387315
//We certify that we worked cooperatively on this programming
//  assignment, according to the rules for pair programming

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>                           //I used std::numeric_limits<int>::max()
#include "ics46goody.hpp"
#include "array_queue.hpp"
#include "array_priority_queue.hpp"
#include "array_set.hpp"
#include "array_map.hpp"


typedef ics::ArrayQueue<std::string>         WordQueue;
typedef ics::ArraySet<std::string>           FollowSet;
typedef ics::pair<WordQueue,FollowSet>       CorpusEntry;
typedef ics::ArrayPriorityQueue<CorpusEntry> CorpusPQ;
typedef ics::ArrayMap<WordQueue,FollowSet>   Corpus;


//Return a random word in the words set (use in produce_text)
std::string random_in_set(const FollowSet& words) {
  int index = ics::rand_range(1, words.size());
  int i = 0;
  for (std::string s : words)
    if (++i == index)
      return s;
  return "?";
}


//Read an open file of lines of words (separated by spaces) and return a
//  Corpus (Map) of each sequence (Queue) of os (Order-Statistic) words
//  associated with the Set of all words that follow them somewhere in the
//  file.
//You may assume the first line contains at least Order-Statstic words.
Corpus read_corpus(int os, std::ifstream &file) {
    Corpus result;
    std::string line;
    WordQueue wq;
    while (std::getline(file, line)) {
        std::vector<std::string> v = ics::split(line, " ");
        for (auto &i : v) {
            if (wq.size() >= os) {
                result[wq].insert(i);
                wq.dequeue();
            }
            wq.enqueue(i);
        }
    }
    return result;
}


//Print "Corpus" and all entries in the Corpus, in lexical alphabetical order
//  (with the minimum and maximum set sizes at the end).
//Use a "can be followed by any of" to separate the key word from the Set of words
//  that can follow it.

//One queue is lexically greater than another, if its first value is smaller; or if
//  its first value is the same and its second value is smaller; or if its first
//  and second values are the same and its third value is smaller...
//If any of its values is less than the corresponding value in the other queue,
//  the first queue is not greater.
//Note that the queues sizes are the same: each stores Order-Statistic words
//Important: Use iterators for examining the queue values: DO NOT CALL DEQUEUE.

bool queue_gt(const CorpusEntry& a, const CorpusEntry& b) {
    for (ics::Iterator<std::string> &i = a.first.ibegin(), &j = b.first.ibegin(); i != a.first.iend() && j != b.first.iend(); ++i, ++j) {
        if (*i < *j) {
            return true;
        } else if (*i > *j) {
            return false;
        }
    }
    return false;
}

void print_corpus(const Corpus& corpus) {
    std::cout << "Corpus" << std::endl;
    CorpusPQ pq(corpus.ibegin(), corpus.iend(), *queue_gt);
    int min = std::numeric_limits<int>::max();
    int max = 0;
    for (auto &kv : pq) {
        std::cout << "  " << kv.first << " -> " << kv.second << std::endl;
        if (kv.second.size() < min) {
            min = kv.second.size();
        }
        if (kv.second.size() > max) {
            max = kv.second.size();
        }
    }
    std::cout << "min/max = " <<  min << "/" << max << std::endl;
}


//Return a Queue of words, starting with those in start and including count more
//  randomly selected words using corpus to decide which word comes next.
//If there is no word that follows the previous ones, put "None" into the queue
//  and return immediately this list (whose size is <= start.size() + count).
WordQueue produce_text(const Corpus& corpus, const WordQueue& start, int count) {
    WordQueue result = start;
    WordQueue q = start;
    int i = 0;
    while (i < count) {
        if (corpus.has_key(q)) {
            std::string next = random_in_set(corpus[q]);
            q.dequeue();
            q.enqueue(next);
            result.enqueue(next);
        } else {
            result.enqueue("None");
            break;
        }
        ++i;
    }
    return result;
}



//Prompt the user for (a) the order statistic and (b) the file storing the text.
//Read the text as a Corpus and print it appropriately.
//Prompt the user for order statistic words from the text.
//Prompt the user for number of random words to generate
//Call the functions above to solve the problem, and print the appropriate information
int main() {
  try {
      std::ifstream file;
      int os = ics::prompt_int("Enter order statistic", 2);
      ics::safe_open(file, "Enter file name to process", "wginput1.txt");
      std::cout << std::endl;
      Corpus corpus = read_corpus(os, file);
      file.close();
      print_corpus(corpus);
      std::cout << std::endl;
      std::cout << "Enter " << os << " words to start with" << std::endl;
      std::stringstream ss;
      WordQueue start;
      for (int i = 1; i <= os; ++i) {
          ss.str("");
          ss << "Enter word ";
          ss << i;
          start.enqueue(ics::prompt_string(ss.str()));
      }
      int count = ics::prompt_int("Enter # of words to generate");
      std::cout << "Random text = " << produce_text(corpus, start, count) << std::endl;
  } catch (ics::IcsError& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
