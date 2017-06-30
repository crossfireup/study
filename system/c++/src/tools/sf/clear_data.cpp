#include <string>
#include <functional>
#include <iostream>

//Private data
struct PrivateData
{
  size_t m_hash;
  char m_pswd[100];
};

//Function performs some operations on password
void doSmth(PrivateData& data)
{
  std::string s(data.m_pswd);
  std::hash<std::string> hash_fn;

  data.m_hash = hash_fn(s);
}

//Function for password entering and processing
int funcPswd()
{
  PrivateData data;
  std::cin >> data.m_pswd;

  doSmth(data);
  memset(&data, 0, sizeof(PrivateData));
  return 1;
}

int main()
{
  funcPswd();
  return 0;
}
