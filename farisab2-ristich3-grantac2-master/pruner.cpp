#include <iostream>
#include <string>
#include <fstream>

void progress(std::string & s, long bob) {
  static long n = 0;
  static long p = 0;
  n += s.length()+1;
  long c = n/1000000;
  if (c > p) {
    p = c;
    std::cerr << "\r" << p << " MB -> " << bob/1000000 << " MB" << std::flush;
  }
}

int main() {
  std::string s;
  long n = 0;
  while (std::getline(std::cin, s)) {
    if (s.length() == 0 || s[0] == 'p' || s[7] == 'u' || s[7] == 'h' || s[8] == 'c') {
      std::cout << s << std::endl;
      n += s.length() + 1;
    }
    progress(s,n);
  }
  std::cerr << "\rFinal Size: " << n/1000000 << " MB" << std::endl;
}