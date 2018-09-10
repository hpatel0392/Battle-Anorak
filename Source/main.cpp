#include "engine.h"

bool run();

int main(int, char*[]) {

   bool restart = true;
   while(restart){
      restart = run();
   }
   return 0;
}

bool run(){
   bool ret;
   Engine * engine;
   try {
      engine = new Engine();
      ret = engine->play();
      delete engine; engine = nullptr;
    }
    catch (const string& msg) { std::cout << msg << std::endl; ret = false;}
    catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl; ret = false;
    }
    return ret;
}
