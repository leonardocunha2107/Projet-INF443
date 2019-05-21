#include "models.hpp"
bool Models ::  bob_has_ball;
Bob* Models ::  bob_;
Ball* Models :: ball_;

Models :: Models(){
   bob_has_ball=true;
   ball_=new Ball();
   bob_=new Bob(); 
}

void Models :: update(float t){
    bob_->update(t);
    ball_->update(t);
}