#include <iostream>
#include <string>
#include <vector>

class solution {
public:
  std::vector<std::vector<size_t>> numDistinct(const std::string & s, const std::string & t) {
    std::vector<std::vector<size_t>> paths = getPaths(s, t, std::vector<size_t>());
    for (auto path : paths) {
      std::copy(path.begin(), path.end(), std::ostream_iterator<size_t>(std::cout, " "));
      std::cout << std::endl;
    }

    return paths;
  }

private:
  std::vector<std::vector<size_t>> getPaths(const std::string & s, const std::string & t, const std::vector<size_t> & curr) {
    std::vector<std::vector<size_t>> result;
    if (curr.size() == t.size())
      result.push_back(curr);
    else {
      std::vector<size_t> next = getNext(s, t, curr);
      for (auto nx : next) {
	auto cpy = curr;
	cpy.push_back(nx);
	auto temp = getPaths(s, t, cpy);
	std::copy(temp.begin(), temp.end(), std::inserter(result, result.end()));
      }
    }
    return result;
  }

  std::vector<size_t> getNext(const std::string & s, const std::string & t, const std::vector<size_t> & curr) {
    std::vector<size_t> next;
    if (curr.empty()) {
      size_t found = s.find_first_of(t[0], 0);
      while (found != std::string::npos) {
	next.push_back(found);
	found = s.find_first_of(t[0], found+1);
      }
    }
    else if (curr.size() < t.size()) {
      size_t last = curr.back();
      size_t found = s.find_first_of(t[curr.size()], last+1);
      while (found != std::string::npos) {
	next.push_back(found);
	found = s.find_first_of(t[curr.size()], found+1);
      }
    }
    return next;
  }
};

int main() {
  // std::string s{"rabbbit"}, t{"rabbit"};
  std::string s{"ABCDE"}, t{"ACE"};

  solution soln;
  auto paths = soln.numDistinct(s, t);
  std::cout << "The number of distinct subsequences is:\n"
	    << paths.size() << std::endl;
}
