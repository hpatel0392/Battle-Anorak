#include "gun.h"
#include "explosionManager.h"

void Gun::shoot(const Vector2f& pos, const Vector2f& vel) { 
  if ( timeSinceLastFrame < bulletInterval ) return;
  if(freeList->size() == 0) return;
  Bullet bullet = freeList->front();
  freeList->pop_front();
  bullet.reset();
  bullet.setPosition( pos );
  
  Vector2f compensation(minSpeed, 0);
  if(vel[0] < 0) compensation = -compensation; 
  bullet.setVelocity( vel + compensation );
  bulletList->push_back( bullet );
  timeSinceLastFrame = 0;
}

void Gun::draw() const { 
  for ( const Bullet & bullet : *bulletList ) {
    bullet.draw();
  }
}

void Gun::update(Uint32 ticks) {
   timeSinceLastFrame += ticks;
   std::list<Bullet>::iterator bullet = bulletList->begin();
   while(bullet != bulletList->end()){
      bullet->update(ticks);
      if(bullet->goneTooFar()){
         freeList->push_back(*bullet);
         bullet = bulletList->erase(bullet);  
      } else if(bullet->collision()){
         auto OffsetX = [](Bullet & b)->float{ if(b.getVelocityX() < 0) 
						  return -b.getScaledWidth()/2;
					       return b.getScaledWidth()/2; 
					     };
         ExplosionManager::getInstance().addExplosion( bullet->getPosition() + 
		Vector2f( OffsetX(*bullet), 0) 
 	 );
         freeList->push_back(*bullet);
         bullet = bulletList->erase(bullet); 
         // something else
        
      } else ++bullet;
   }
}

int Gun::blSize() const{
   return bulletList->size();
}

int Gun::flSize() const {
   return freeList->size();
}
