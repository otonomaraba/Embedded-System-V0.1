#include "readdata.h"
int solutionData[3];

void READ_ProcessReceivedData(int *data){
    memcpy(solutionData, data, sizeof(&data));
}

int READ_Get_Data(int index){
	return solutionData[index];
}
