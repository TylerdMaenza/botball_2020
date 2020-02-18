int desired_arm_position;
int arm;



int servo_change(){
    while(1){
        if(get_servo_position(arm) != desired_arm_position){
            servo ( int arm_port, int desired_arm_pos, int vel );
        }
        if(get_servo_position(claw) != desired_claw_pos){
            servo ( int claw_port, int desired_claw_pos, int vel );
        }
    }
}