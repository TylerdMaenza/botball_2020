double bias;

double calibrate_gyro();//{
    int i;
    double avg ;
    while( i < 50){
        avg += gyro_z();
        msleep(1);
        i++;
        printf("Gyro Z: %d\n",gyro_z());
    }
    bias = avg / 50.0;
    printf("New Bias: %f\n", bias);
    return bias;
}





void main_gyro(int distance){
float kp = 0;// start adjusting this (smaller increments = more acurate)
float ki = 0;
float kd = 0;
float power;
float currentL = 0;
float currentR = 0;  //current motor power
float circ = 5 * 3.141592653589; // circumfrence of the robot wheel

float integralActiveZone = ((1*12/circ)*360); //
float errorL;
float errorR;
float errorTl;
float errorTr;
float lastErrorL;
float lastErrorR;
float proportionL;
float proportionR;
float integralL;
float integralR;
float derivativeL;
float derivativeR;

while(true){
    calibrate_gyro();
    float theta = bias;//bias is just an avg reading of gyro in any given direction so we set
                       //theta equal to bias to create our desired direction 

    float errorL = (theta - gyro_z());//these calculate our data of where we are (gyro_z) and where we want to be 
    float errorR = (theta - gyro_z());//where we want to be is usually theta which is what we set in the beginning of our run
    if (errorL < integralActiveZone && errorL != 0){

        errorTl += errorL;

    }
    else{

        errorTl = 0;

    }
    if(errorR < (( integralActiveZone * 12 / circ ) * 360) && errorR != 0){//we only accumalate error if error is inside of active zone
        
        errorRr += errorR;

    }
    else{

        errorTr = 0;

    }
    if(errorTl > 50 / ki){// these are to cap the limit that integral can reach 

        errorTl = 50 / ki;// we have to do this cause integral acumalates over time

    }
    if(errorTr > 50 / ki){//if we didnt do this our motor would most likely kill themselves

        errorTr = 50 / ki);

    }
    if(errorL == 0){

        derivativeL = 0;

    }
    if(errorR == 0){

        derivativeR = 0;

    }

    proportionL = errorL * kp; //proportion is linear to error so error * kp is the new proportion
    proportionR = errorR * kp;// proportion adjusts based on distance from desired point in this case bias and will be very low values
    integralL = errorTl * ki;// integral picks up the extra larger movements that proportional cant do
    integralR = errorTr * ki;
    derivativeL = (errorR - lastErrorL) * kd;// this tells us wether or not that we are getting close to desired and controls speed 
    derivativeR = (errorL - lastErrorR) * kd;//negativly so we dont over shoot

    lastErrorL = errorL;
    lastErrorR = errorR;



    currentR = proportionR + integralR + derivativeR;//these are the final compilations for power output
    currentL = proportionL + integralL + derivativeL;

//////////////////////////////////////////
    if (power == 0){

        currentR = 0;
        currentL = 0;

    }
    if(currentL < 0){// this entire section is to make sure we are going backwards after we have reached destination

        currentL = 0;

    }
    if(currentR < 0){

        currentR = 0;

    }
    msleep(20);
    }
}
//////////////////////////////////////////
int main(){
    main_gyro();
    return 0;
}