/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "calc.h"

float *
add_1_svc(numbers *argp, struct svc_req *rqstp)
{
	static float  result;
	result=argp->a+argp->b;
	printf("Addition\n");
	return &result;
}

float *
sub_1_svc(numbers *argp, struct svc_req *rqstp)
{
	static float  result;

	/*
	 * insert server code here
	 */
	result=argp->a-argp->b;
	
	printf("Subtraction\n");
	return &result;
}

float *
mul_1_svc(numbers *argp, struct svc_req *rqstp)
{
	static float  result;

	/*
	 * insert server code here
	 */
	 
	result=argp->a*argp->b;
	printf("Multiplication\n");
	return &result;
}

float *
div_1_svc(numbers *argp, struct svc_req *rqstp)
{
	static float  result;

	/*
	 * insert server code here
	 */
	 
	printf("Divsion\n");
	if(argp->b==0.0){
		printf("Division by zero is not possible\n");
		result = 0;
	}
	else{
		result=argp->a/argp->b;
	}
	//printf("\n")
	return &result;
}
