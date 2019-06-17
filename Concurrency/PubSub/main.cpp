#include <iostream>
#include "pubsub.h"

using namespace std;

void foo(int i)
{
  std::cout << "foo( " <<  i << " )\n";
}
 
void bar() {
  std::cout << "bar()\n";
}

int main() {
    PubSubService<std::string> s;
  s.registerObserver("GREEN", bar);
  s.registerObserver("ORANGE", std::bind(foo, 42));
  s.registerObserver("RED", std::bind(foo, 12345));
 
  const std::string msg("Hello, RED!");
  s.registerObserver("RED", [&msg]{std::cout << msg << std::endl;});
 
  s.notify("GREEN");
  s.notify("RED");
  s.notify("ORANGE");
}

