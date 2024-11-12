#pragma once
#include <unordered_set>
#include <string>
#include <fstream>
#include <set>
#include <iostream>


class Word2Word
{

  static std::vector<std::string> bfs(const std::set<std::string>& words, const std::vector<std::unordered_set<int>>& matrix, const std::string& s, const std::string& e)
  {
    int start = std::distance(words.begin(), words.find(s));
    int end = std::distance(words.begin(), words.find(e));

    std::vector<int> visited(matrix.size(), 0);
    std::vector<int> prev(matrix.size(), -1);
    std::vector<int> queue;
    queue.push_back(start);
    visited[start] = 1;
    while(!queue.empty()) {
      int current = queue.front();
      queue.erase(queue.begin());
      for(const auto& i : matrix[current]) {
        if(/*matrix[current].contains(i) &&*/ visited[i] == 0) {
          visited[i] = visited[current] + 1;
          queue.push_back(i);
          prev[i] = current;
        }
      }
    }

    std::vector<std::string> path;
    int p = end;
    while(p != -1) {
      auto vi = words.begin();
      std::advance(vi, p);
      path.push_back(*vi);
      p = prev[p];
    }
    std::reverse(path.begin(), path.end());
    return path;
  }
public:
  static std::vector<std::string> word2word(const std::string& filepath, const std::string& start, const std::string& end)
  {

    std::ifstream file(filepath);
    if(!file) {
      throw std::runtime_error("File not found");
    }
    if(start.size() != end.size()) {
      throw std::runtime_error("Start and end words must be the same length");
    }

    std::set<std::string> words;
    std::string w;
    while(std::getline(file, w)) {
      if(w.size() != start.size()) {
        continue;
      }
      words.insert(w);
    }

    if(words.find(start) == words.end()) {
      throw std::runtime_error("Start word not found in dictionary");
    }
    if(words.find(end) == words.end()) {
      throw std::runtime_error("End word not found in dictionary");
    }


    std::vector<std::unordered_set<int>> matrix(words.size());
    for(const auto& w : words) {
      auto distance_word = std::distance(words.begin(), words.find(w));
      for(int i = 0; i < w.size(); ++i) {
        for(char c = 'a'; c <= 'z'; ++c) {
          std::string new_word = w;
          new_word[i] = c;
          auto found = words.find(new_word);
          if(found != words.end()) {
            auto distance_new_word = std::distance(words.begin(), found);
            matrix[distance_word].insert(distance_new_word);
            matrix[distance_new_word].insert(distance_word);
          }
        }
      }
    }
    return bfs(words, matrix, start, end);
  }

};
