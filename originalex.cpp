#include "h_crane.h"

class Crain : public CraneCrane
{
private:
    ev3dev::touch_sensor touch_q;
    ev3dev::motor a;
    ev3dev::motor b; 
    ev3dev::motor c;
    ev3dev::color_sensor colorSensor;
public:
    // Hardware Configuration
    Crain():m_speed(0), touch_q(ev3dev::INPUT_2),a(ev3dev::OUTPUT_B), b(ev3dev::OUTPUT_C), c(ev3dev::OUTPUT_A)
    {
        
    }
    
    int m_speed;
    
    bool get_touch_pressed()
    {
        return touch_q.is_pressed();
    }
    
    virtual bool get_down()
    {
        return m_down;
    }

    virtual bool get_up()
    {
        return m_up;
    }

    virtual bool get_right()
    {
        return m_right;
    }

    virtual bool get_left()
    {
        return m_left;
    }

    virtual bool get_enter()
    {
        return m_enter;
    }

    virtual bool get_escape()
    {
        return m_escape;
    }

    virtual int  get_speed()
    {
        return 150;
    }

    virtual void set_down(bool val)
    {
        m_down = val;
    }
    
    virtual void set_up(bool val)
    {
        m_up = val;    
    }
    
    virtual void set_right(bool val)
    {
        m_right = val;   
    }
    virtual void set_left(bool val)
    {
        m_left = val; 
    } 
    
    virtual void set_enter(bool val)
    {
        m_enter = val;    
    }
    
    virtual void set_escape(bool val)
    {
        m_escape = val;    
    }
    
    virtual void set_speed(int val)
    {
        m_speed = val;    
    }
public:
    void example_code();
};

void Crain::example_code()
{ //This function is for example, you should develop your own logics
    while(get_escape() == false)
    {
      
    
        
        if (colorSensor.color() == 1)
        {
            ev3dev::sound::speak("HI");
        }
    }
       
        
}

// int main()
// {     Crain *crrain=new Crain;
//     Crain crain;
//     while(true){
//         //if(crain.get_touch_pressed()==true)
//         { 
            
        
//         crain.example_code(); //This line is for example, you should erase this ex_code in your 'real code' 
  
//         }
//     }
//     delete crrain;
// }



int main()
{     Crain *crain=new Crain;
    //Crain crain;
    while(true){
        //if(crain.get_touch_pressed()==true)
        { 
            
        
        Crain.example_code(); //This line is for example, you should erase this ex_code in your 'real code' 
  
        }
    }
    delete Crain;
}
 
 