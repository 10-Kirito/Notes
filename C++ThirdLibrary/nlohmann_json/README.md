# JSON Learning

# 1. Introduction



`nlohman/json`该`json`库相对于其他的库来讲，其最大的优点就是单头文件，我们在平时需要使用的时候只需要包含一个头文件就可以开始使用这些JSON功能。无需我们去安装额外的依赖项或者配置复杂的构建系统等。

# 2. How to read data from a *.json file？

```c++
#include <fstream>
#include <iomanip>
#include <iostream>
#include <nlohmann/json.hpp>
#include <ostream>


using json = nlohmann::json;
int main(int argc, char **argv) {
  std::ifstream data("./files/data.json");
  if (!data.is_open()) {
    std::cerr << "Error: file was not found!" << std::endl;
  }
  json j = json::parse(data);
  std::cout << std::setw(4) << j << std::endl;
  return 0;
}
```



# 3. How to create a `json` object?

```c++
// option1 to create a json
json ex1 = json::parse(R"({
  "pi": 3.141,
  "happy": true,
  "name": "option1"
})")
// option2 to create a json
json ex2 = {
  {"happy", true},
  {"pi", 3.141},
  {"name", "option2"}
};
std::cout << std::setw(4) << ex1 << std::endl;
std::cout << std::setw(4) << ex2 << std::endl;
```

# 4. How to import json from a file and export to a file?

```c++
std::ifstream i("./files/data.json");
json data;
i >> data;
data["version"] = "new";
std::cout << std::setw(4) << data << std::endl;
std::ofstream out("./files/newdata.json");
out << std::setw(4) << data << std::endl;
```

