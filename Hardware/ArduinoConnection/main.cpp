#include    <iostream>
using namespace std;
#include    <string>
#include    <stdlib.h>
#include    "SerialPort.h"

char output[MAX_DATA_LENGTH];
char incomingData[MAX_DATA_LENGTH];

char *port = "\\\\.\\ttpyACM0";

int main(){
	SerialPort arduino(port);
	if(arduino.isConnected()){
		cout<<"...Connected Successfully..."<<endl<<endl;
	}
	else{
		cout<<"Error in Port Name"<<endl<<endl;
	}
	while(arduino.isConnected()){

        //Here we should send solution.txt file's data to "data" string
		cout<<"Enter your command: "<<endl;
		string data;
		cin>>data;

		char *charArray = new char[data.size() + 1];
		copy(data.begin(), data.end(), charArray);

		arduino.writeSerialPort(charArray, MAX_DATA_LENGTH);

		cout<<" >> "<<output<<endl;

		delete [] charArray;
	}
	return 0;
}