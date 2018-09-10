#include "actor.h"
#include "reactor.h"
#include "gamedata.h"
#include "renderContext.h"

Actor::Actor( const std::string& name) :
  MultiSprite(name), 
  observers()
{ }

Actor::Actor(const Actor& s) :
  MultiSprite(s), 
  observers( s.observers )
{ }

Actor & Actor::operator=(const Actor& a){
   MultiSprite::operator=(a);
   observers = a.observers;
   return *this;
}

void Actor::attach(Reactor* o) {
   observers.push_back(o);
   o->setTarget(this);
} 

void Actor::detach( Reactor* o ) {
  std::list<Reactor*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    if ( *ptr == o ) {
      (*ptr)->setTarget(nullptr);
      ptr = observers.erase(ptr);
      return;
    }
    ++ptr;
  }
}

/*
void Actor::update(Uint32 ticks) { 
  MultiSprite::update(ticks);
  std::list<Reactor*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    if(*ptr->
    (*ptr)->setPlayerPos( getPosition() );
    ++ptr;
  }
}*/
