#include <fstream>
#include <iomanip>
#include <iostream>
#include <nlohmann/json.hpp>
#include <ostream>
using json = nlohmann::json;

void testfiles() {
  std::ifstream data("./files/data.json");
  if (!data.is_open()) {
    std::cerr << "Error: file was not found!" << std::endl;
  }
  json j = json::parse(data);
  std::cout << std::setw(4) << j << std::endl;
}

void testbasic() {
  // option1 to create a json
  json ex1 = json::parse(R"({
    "pi": 3.141,
    "happy": true,
    "name": "option1"
  })");

  // option2 to create a json
  json ex2 = {{"happy", true}, {"pi", 3.141}, {"name", "option2"}};
  std::cout << std::setw(4) << ex1 << std::endl;
  std::cout << std::setw(4) << ex2 << std::endl;
}

void testclass() {
  // create an empty structure
  json data;
  // examples:
  data["pi"] = 3.141;
  data["happy"] = true;
  data["name"] = "Kirito";
  data["nothing"] = nullptr;
  // add an array
  data["array"] = {1, 0, 2, 3, 4};
  data["object"] = {{"time", "2024年3月13日11:05:55"}, {"value", 1234}};
  std::cout << std::setw(4) << data << std::endl;
}

// Serialize and Deserialize
void test() {
  std::vector<std::uint8_t> a = {'t', 'r', 'u', 'e'};
  json i = json::parse(a.begin(), a.end());
  std::vector<std::uint8_t> v = {'t', 'r', 'u', 'e'};
  json j = json::parse(v);
  std::cout << std::setw(4) << j << std::endl;
  std::cout << std::setw(4) << i << std::endl;
}

void testOutputToFile() {
  std::ifstream i("./files/data.json");
  json data;
  i >> data;
  data["version"] = "new";

  std::cout << std::setw(4) << data << std::endl;
  std::ofstream out("./files/newdata.json");
  out << std::setw(4) << data << std::endl;
}

void testInput() {
  json data;
  std::cin >> data;
  std::cout << std::setw(4) << data << std::endl;
}

void testSTL() {
  json j;
  j.push_back("foo");
  j.push_back(1);
  j.push_back(true);
  j.push_back(R"({"happy": true, "pi": 3.141})"_json);

  j.emplace_back(1.788888888);

  j[1] = 32;
  std::cout << std::setw(4) << j << std::endl;

  const auto tmp = j[0].template get<std::string>();
  const auto temp = j[3]["happy"].template get<bool>();
  const auto PI = j[3]["pi"].template get<double>();
  std::cout << temp << std::endl;
  std::cout << PI << std::endl;
}

int main(int argc, char **argv) {
  testSTL();
  return 0;
}