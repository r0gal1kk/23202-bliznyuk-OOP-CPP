#include <algorithm>
#include <fstream>
#include <string>
#include <map>
#include <utility>
#include <iterator>
#include <vector>

using std::string;
using std::vector;
using std::pair;

class FileReader {
private:
  string fileName;
  std::ifstream input;
public:
  FileReader(string fileName) {
    this->fileName = fileName;
  }
  ~FileReader() {
    input.close();
  }
  void open() {
    input.open(fileName);
  }
  void close() {
    input.close();
  }
  bool hasNext() {
    return !(input.eof());
  }
  string getNextString() {
    string buffer;
    getline(input, buffer);
    return buffer;
  }
};

class Statistic {
private:
  std::map<string, int> wordsMap;
  unsigned long long wordsTotal;
  const int PERCENT = 100;
  void convertMapIntoVector(vector<pair<string, int>>& statisticVector) {
    int index = 0;
    for (const auto& element : wordsMap) {
      statisticVector[index].first = element.first;
      statisticVector[index].second = element.second;
      index++;
    }
  }
  static bool comparePairs(const pair<string, int>& a, const pair<string, int>& b) {
    return a.second > b.second;
  }
  void sortMapByValue(vector<pair<string, int>>& statisticVector) {
    convertMapIntoVector(statisticVector);
    std::sort(statisticVector.begin(), statisticVector.end(), comparePairs);
  }
public:
  Statistic() {
    wordsTotal = 0;
  }
  void pushWord(const string& word) {
    if (wordsMap.count(word)) {
      wordsMap[word]++;
    }
    else {
      wordsMap[word] = 1;
    }
    wordsTotal++;
  }
  void pushWordsVector(const vector<string>& splittedString) {
    for (string key : splittedString) {
      if (wordsMap.count(key)) {
        wordsMap[key] += 1;
      }
      else {
        wordsMap[key] = 1;
      }
    }
    wordsTotal += splittedString.size();
  }
  double getFreqency(const string& word) {
    if (!wordsMap.count(word)) {
      return 0;
    }
    return (double)wordsMap[word] / wordsTotal * PERCENT;
  }
  vector<pair<string, int>> getSortedStatistic() {
    vector<pair<string, int>> statisticVector(wordsMap.size());
    sortMapByValue(statisticVector);
    return statisticVector;
  }
};

class Parser {
private:
  void toLowerString(string& line) {
    std::transform(line.begin(), line.end(), line.begin(), [](unsigned char c) {
      return std::tolower(c);
      });
  }
  void splitIntoWords(const string& line, vector<string>& splittedString) {
    string currentWord;
    for (unsigned char symbol : line) {
      if (std::isalnum(symbol)) {
        currentWord += symbol;
      }
      else {
        if (!currentWord.empty()) {
          splittedString.push_back(currentWord);
          currentWord.clear();
        }
      }
    }
    if (!currentWord.empty()) {
      splittedString.push_back(currentWord);
    }
  }
public:
  vector<string> getSplittedString(string& line) {
    vector<string> splittedString;
    toLowerString(line);
    splitIntoWords(line, splittedString);
    return splittedString;
  }
};

class FileWriter {
private:
  string fileName;
  std::ofstream output;
public:
  FileWriter(string fileName) {
    this->fileName = fileName;
  }
  ~FileWriter() {
    output.close();
  }
  void open() {
    output.open(fileName);
  }
  void close() {
    output.close();
  }
  void writeStatisticToCSV(Statistic& statistic) {
    vector<pair<string, int>> statisticVector = statistic.getSortedStatistic();
    for (const auto& element : statisticVector) {
      output << element.first << '\t' << element.second << '\t' << statistic.getFreqency(element.first) << '%' << '\n';
    }
  }
};

int main(int argc, char* argv[]) {
  FileReader reader(argv[1]);
  reader.open();
  Statistic statistic;
  Parser parser;
  while (reader.hasNext()) {
    string currentLine = reader.getNextString();
    vector<string> splittedString = parser.getSplittedString(currentLine);
    statistic.pushWordsVector(splittedString);
  }
  reader.close();
  FileWriter writer(argv[2]);
  writer.open();
  writer.writeStatisticToCSV(statistic);
  writer.close();
  return 0;
}
