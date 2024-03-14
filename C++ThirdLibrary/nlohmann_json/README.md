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

# 5. How to convert the data type to the specified type?

***[Example](https://json.nlohmann.me/features/arbitrary_types/):***

```C++
namespace ns {
    // a simple struct to model a person
    struct person {
        std::string name;
        std::string address;
        int age;
    };
} // namespace ns

ns::person p = {"Ned Flanders", "744 Evergreen Terrace", 60};

// convert to JSON: copy each value into the JSON object
json j;
j["name"] = p.name;
j["address"] = p.address;
j["age"] = p.age;

// ...

// convert from JSON: copy each value from the JSON object
ns::person p {
    j["name"].template get<std::string>(),
    j["address"].template get<std::string>(),
    j["age"].template get<int>()
};
```

Also, we can directly convert json to the specified type:

```C++
// create a person
ns::person p {"Ned Flanders", "744 Evergreen Terrace", 60};

// conversion: person -> json
json j = p;

std::cout << j << std::endl;
// {"address":"744 Evergreen Terrace","age":60,"name":"Ned Flanders"}

// conversion: json -> person
auto p2 = j.template get<ns::person>();

// that's it
assert(p == p2);
```

What's more, we can provide two functions to make json Object can be constructed with our type:

```c++
#include <iomanip>
#include <iostream>
#include <json.hpp>
using json = nlohmann::json;

struct MyStruct {
    int x;
    int y;
    std::string name;
};

void to_json(json& j, const MyStruct& p) {
    j = json{{"x", p.x}, {"y", p.y}, {"name", p.name}};
}

void from_json(const json& j, MyStruct& p) {
    j.at("x").get_to(p.x);
    j.at("y").get_to(p.y);
    j.at("name").get_to(p.name);
}

std::ostream& operator << (std::ostream& os, const MyStruct& p) {
    os << "x: " << p.x << ", y: " << p.y << ", name: " << p.name;
    return os;
}

int main(int argc, char** argv) {
    MyStruct myStruct{1, 2, "hello"};
    json j = myStruct;

    MyStruct myStruct2 = j;

    std::cout << std::setw(4) << j << std::endl;
    std::cout << myStruct2 << std::endl;

    return 0;
}
```

The above output is :

```shell
{
    "name": "hello",
    "x": 1,
    "y": 2
}
x: 1, y: 2, name: hello
```

