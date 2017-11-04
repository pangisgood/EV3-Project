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

    int flag = 1, max_foot = 570, max_neck = 220, max_hand = 75;

   

   

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

            stop_foot_rfr();

            sleep(slT);

            move_foot(position+35);

            sleep(1.0);

            move_neck(max_neck);

            sleep(slT);

            move_hand(max_hand);

            sleep(slT);

            move_neck(0); 

            sleep(slT);

            move_foot(max_foot);

            sleep(slT);

            move_neck(max_neck);

            sleep(slT);

            move_hand(0);

            

            if(flag == 3){break;}

            

            sleep(slT);

            move_neck(0);

            sleep(slT);

            move_foot(position-50);  //runforever 끝지점이 0인가?

            sleep(1);

            

            flag += 1; 

            }

    return;

}

 

 

 

 

 

 

 

 

 

 

 

 

int main()

{    

    Crain crain;

    while(true)

    {

        

        if(crain.get_touch_pressed() == true)

        {

            

         Crain *crain = new Crain();

         

         crain->execute();

         

         delete crain;

        

        

        }

        

    }

}
