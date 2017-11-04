#include "h_crane.h"
class Crain : public CraneCrane

{

private:

    ev3dev::touch_sensor touch_q;

    ev3dev::motor a;

    ev3dev::motor b; 

    ev3dev::motor c;

    ev3dev::color_sensor colorSensor;

    ev3dev::ultrasonic_sensor ultra_q;

    

public:

    // Hardware Configuration. 초기화 객체에 알맞은 포트 넣어줌. 

    Crain():m_speed(0), touch_q(ev3dev::INPUT_1),a(ev3dev::OUTPUT_A), b(ev3dev::OUTPUT_B), c(ev3dev::OUTPUT_C), ultra_q(ev3dev::INPUT_2)

    

    {

        

    }

    int m_speed, pose, flag;

    

    double get_distance()

    {

        double dis;

        

        return ultra_q.distance_centimeters();

        

    }

    bool is_black()

    {

        return colorSensor.color() == 1;  //검정색이면 1==1 만족, 트루 반환?

    }

    

    bool get_touch_pressed()

    {

        return touch_q.is_pressed();

    }

    

    virtual bool get_down()

    {

        return m_down; //처음엔 다 false로 되어있음. 

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

    

    virtual int get_speed()

    {

        return 660;

    }

    

    virtual int get_speed_neck()

    {

        return 500;

    }

    // virtual int  get_speed_foot()

    // {

    //     return 600;

    // }

    

    // virtual int  get_speed_neck()

    // {

    //     return 300;

    // }

    

    virtual int get_speed_hand()

    {

        return 400;

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

    void move_foot_rfr();

    void stop_foot_rfr();

    void move_foot(int pos);

    void move_neck(int pos);

    void move_hand(int pos);

    void reset_motors();

    int position_foot();

    int position_neck();

    int position_hand();

    void practice();

    void getbackAuto();

    void execute();

    

};

 

void Crain::move_foot_rfr()

{

    c.set_speed_sp(100);

    c.run_forever();

 

}

 

void Crain::stop_foot_rfr()

{

    c.set_stop_action("hold");

    c.stop();

}

 

 

 

void Crain::getbackAuto()

{

    a.set_speed_sp(100);

    a.set_position_sp(0);

    a.run_to_abs_pos();

    sleep(1);

    

    b.set_speed_sp(100);

    b.set_position_sp(0);

    b.run_to_abs_pos();

    sleep(1);

    

    c.set_speed_sp(100);

    c.set_position_sp(0);

    c.run_to_abs_pos();

}

 

 

 

void Crain::reset_motors()

{

    a.reset();

    b.reset();

    c.reset();

}

 

 

void Crain::move_foot(int pos)

{

  

    c.set_stop_action("hold");

    c.set_position_sp(pos);

    c.set_speed_sp(get_speed());

    c.run_to_abs_pos();

   

}

 

void Crain::move_neck(int pos)

{

 

    b.set_stop_action("hold");

    b.set_position_sp(pos);

    b.set_speed_sp(get_speed_neck());

    b.run_to_abs_pos();

}

 

void Crain::move_hand(int pos)

{

   

    a.set_stop_action("hold");

    a.set_position_sp(pos);

    a.set_speed_sp(get_speed_hand());

    a.run_to_abs_pos();

    

}

 

 

int Crain::position_foot()

{

    return c.position();

}

 

int Crain::position_neck()

{

    return b.position();

}

 

int Crain::position_hand()

{

    return a.position();

}

 

 

void Crain::example_code()

{ //This function is for example, you should develop your own logics

    while(get_escape() == false)

    {

        set_down(ev3dev::button::down.pressed());

        set_up(ev3dev::button::up.pressed());

        set_right(ev3dev::button::right.pressed());

        set_left(ev3dev::button::left.pressed());

        set_escape(ev3dev::button::back.pressed());

        set_enter(ev3dev::button::enter.pressed());

        

        if(get_up())

        {   

                b.set_speed_sp(-1*get_speed());

                b.run_forever();

        }   

        if(get_down())

        {

                b.set_speed_sp(get_speed());

                b.run_forever();

        }

        if(get_left())

        {

               c.set_speed_sp(get_speed());

               c.run_forever();

        }

        if(get_right())

        {

               c.set_speed_sp(-1* get_speed());

               c.run_forever();

        }

       

       

        if(!(get_up() | get_down() | get_right() | get_left() | get_enter()))

        {

            a.set_speed_sp(0);

            a.run_forever();

            b.set_speed_sp(0);

            b.run_forever();

            c.set_speed_sp(0);

            c.run_forever();

            

        }

    }

 

}

 

 

 

 

void Crain::execute()

{

    

    double dis, position;

    int turn =0, slT = 1.3;

    //max neck= 205(short) 192(long)

    int flag = 1, max_foot = 565, max_neck = 220, max_hand = 75;

   

   

    reset_motors();

    std::cout<< "a, b, c"<<position_hand() << position_neck() << position_foot() << std::endl;

        

        for(int z = 0; z < 3; z++)

        {

            

            //scan

            while(true)

            {

                dis = get_distance();

                std::cout<<"DISTANCE1: "<< dis <<std::endl;

                //position = crain.position_foot();

                std::cout<< "POSITION B         :" << position_neck() <<std::endl;

                

                

                

                move_foot_rfr();

                if(dis < 15)

                {

                    position = position_foot();

                    std::cout<< "POSITION         :" << position <<std::endl;

                    break;

                }

                

            }
//스캔해서 잡고 올리는 과정
            stop_foot_rfr();


////x?
           // sleep(0.5);

            // if(position>){
                
            // }
            
            
           if(380){
               move_foot(position+27);
               
               
           }
            else if(position>230){
            move_foot(position+49);
             }
//gg

            else{ move_foot(position+26);}
            
            
 
            sleep(1.3);

            move_neck(max_neck);

            sleep(slT);

            move_hand(max_hand);

            sleep(slT);

            move_neck(0); 

            sleep(slT);

            move_foot(max_foot);

            sleep(slT);

            move_neck(max_neck); //내려놓기

            sleep(1);

            move_hand(0); //떨구기

            

            if(flag == 3){break;}

            

            sleep(slT); 

            move_neck(0); //목들기

            sleep(slT);
            
             if(flag == 2){
                    move_foot(position-30); 
                 
             }
            
            else{
            move_foot(position-50);  //runforever 끝지점이 0인가?
            }
            
            
           
            sleep(1);

           

            flag += 1; 

            }

    return;

}

 

 

 

 

 

 

 

 

 

 

 

 

int main()

{    

    //Crain crain;
             Crain *crain = new Crain();

    while(true)

    {

        

        if(crain->get_touch_pressed() == true)

        {

            



         

         crain->execute();

         //crain->reset_motors();

      

         break;
   
        

        }

         delete crain;
// break;
    }
  // delete crain;
}
