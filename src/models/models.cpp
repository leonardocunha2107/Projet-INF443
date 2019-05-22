#include "models.hpp"
int Models ::  s;
Bob* Models ::  bob_;
Ball* Models :: ball_;
Gary* Models :: gary_;
Models :: Models(){
   s=0;

   ball_=new Ball();
   bob_=new Bob();
   gary_ = new Gary(); 
}

void Models :: update(float t){
    bob_->update(t);
    ball_->update(t);
    gary_->update(t);
}

