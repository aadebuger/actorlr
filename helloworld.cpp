#include <string>
#include <iostream>

#include "caf/all.hpp"

using std::endl;
using std::string;

using namespace caf;

class HelloActor : public event_based_actor {
    string name;
public:
    HelloActor(actor_config& cfg,string name) : event_based_actor(cfg),name(name) {
        // nop
    }
    
    behavior make_behavior() override {
        return {
            [=](int i) { /*...*/
                aout(this)<<"int="<<i<<endl;
            },
            // a handler for messages containing a single string
            // that replies with a string
            [=](const string& what) -> string {
                // prints "Hello World!" via aout (thread-safe cout wrapper)
                aout(this)<<"name="<<name<<endl;
                if (what=="Hello World!")
                    aout(this)<< "find hello world"<<endl;
                aout(this) << "helloactor"<<what << endl;
                // reply "!dlroW olleH"
                return string(what.rbegin(), what.rend());
                }
                };
    }
};


behavior mirror(event_based_actor* self) {
  // return the (initial) actor behavior
  return {
    // a handler for messages containing a single string
    // that replies with a string
    [=](const string& what) -> string {
      // prints "Hello World!" via aout (thread-safe cout wrapper)
        if (what=="Hello World!")
            aout(self)<< "find hello world"<<endl;
      aout(self) << what << endl;
      // reply "!dlroW olleH"
      return string(what.rbegin(), what.rend());
    }
  };
}

void hello_world(event_based_actor* self, const actor& buddy) {
  // send "Hello World!" to our buddy ...
  self->request(buddy, std::chrono::seconds(10), "Hello World!").then(
    // ... wait up to 10s for a response ...
    [=](const string& what) {
      // ... and print it
      aout(self) << what << endl;
    }
  );
}
void hello_world1(event_based_actor* self, const actor& buddy) {
    // send "Hello World!" to our buddy ...
    self->request(buddy, std::chrono::seconds(10), "Hello World").then(
                                                                        // ... wait up to 10s for a response ...
                                                                        [=](const string& what) {
                                                                            // ... and print it
                                                                            aout(self) << what << endl;
                                                                        }
                                                                        );
}
                
void hello_worldint(event_based_actor* self, const actor& buddy) {
                    // send "Hello World!" to our buddy ...
                    self->request(buddy, std::chrono::seconds(10), 10).then(
                                                                                       // ... wait up to 10s for a response ...
                                                                                       [=](const string& what) {
                                                                                           // ... and print it
                                                                                           aout(self) << what << endl;
                                                                                       }
                                                                                       );
                }
                

int main() {
  // our CAF environment
  actor_system_config cfg;
  actor_system system{cfg};
  // create a new actor that calls 'mirror()'
  auto mirror_actor = system.spawn(mirror);
  auto mirror_actor1 = system.spawn(mirror);
    auto a5 = system.spawn<HelloActor>("aa");
    
    // create another actor that calls 'hello_world(mirror_actor)';
    system.spawn(hello_world, mirror_actor);
    
    system.spawn(hello_world1, mirror_actor);
    system.spawn(hello_world1, a5);
    system.spawn(hello_worldint, a5);
    
    
  // system will wait until both actors are destroyed before leaving main
}
