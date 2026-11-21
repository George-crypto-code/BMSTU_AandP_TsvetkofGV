#include <iostream>
#include <string>
#include <utility>


void permute(std::string& s, int i)
{
    if (s.empty()) return;
    if (i == static_cast<int>(s.size()) - 1)
    {
        std::cout << s << std::endl;
        return;
    }

    for (int k = i; k < static_cast<int>(s.size()); ++k)
    {
        std::swap(s[i], s[k]);
        permute(s, i + 1);
        std::swap(s[i], s[k]);
    }
}

int main()
{
    std::string s;
    std::cout << "Enter string: ";
    if (std::cin >> s) permute(s, 0);
    return 0;
}
