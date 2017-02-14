/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "places.h"
#include "airports.h"

const nametype FILE_NAME = "places2k.txt";
const int stateAbbreviationLength = 2;
const int NUMBER_OF_STATES = 52;

// Self Declare struct - not by rpc
typedef struct CityOrTown CityOrTown;
struct CityOrTown
{
	nametype cityOrTownName;
	double latitude;
	double longitude;
};

typedef struct State State;
struct State
{
	nametype stateName;
	nametype stateAbbreviation;
	int numberOfCityOrTown;
};

void initializeData(State listOfState[], CityOrTown listOfCityOrTownByState[52][250]);

nearest_results_place *
getnearest_place_1_svc(place *argp, struct svc_req *rqstp)
{
	static nearest_results_place result;
	static int ifNotInitialized = 0;
	static State listOfState[52];
	static CityOrTown listOfCityOrTownByState[52][250];

	if(ifNotInitialized == 0)
	{
		initializeData(listOfState, listOfCityOrTownByState);
	}

	int i,j;
	for(i = 0; i < 52; i++)
	{
		printf("%s:------------------------\n", listOfState[i].stateAbbreviation);
		for(j = 0; j < listOfState[i].numberOfCityOrTown; j++)
		{
			printf("%s\n", listOfCityOrTownByState[i][j].cityOrTownName);
		}
	}

	xdr_free((xdrproc_t)xdr_nearest_results_air, (char*)&result);

	printf("Inside nearest_results_place\n");
	printf("city: %s\n", argp->city);
	printf("state: %s\n",argp->state);

	CLIENT *clnt;
	nearest_results_air  *result_1;
	geoLocation getnearest_air_1_arg;

	getnearest_air_1_arg.longitude = 91.12;
	getnearest_air_1_arg.latitude = 12.23;

// Touch on this later
#ifndef DEBUG
	clnt = clnt_create ("localhost", airportProgram, airport_version, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror ("localhost");
		exit (1);
	}
#endif  /* DEBUG */

	result_1 = getnearest_air_1(&getnearest_air_1_arg, clnt);
	if (result_1 == (nearest_results_air *) NULL) {
		clnt_perror (clnt, "call failed");
	} else{
		if (result_1->err == 0){
			result.nearest_results_place_u.x = result_1->nearest_results_air_u.x;
		}
	}

	/*
	 * insert server code here
	 */

	return &result;

}

void initializeData(State listOfState[], CityOrTown listOfCityOrTownByState[52][250])
{
	FILE * fp = NULL;

	nametype previousState;
	previousState = malloc(MAXLEN);
	strcpy(previousState, "00");

	nametype currentState;
	currentState = malloc(MAXLEN);

	nametype line;
	line = malloc(MAXLEN);

	nametype latitude;
	latitude = malloc(MAXLEN);
	nametype longitude;
	longitude = malloc(MAXLEN);

	int stateIndex = -1;
	int cityOrTownIndex;


	CityOrTown *currentStatePointer;

	printf("Opening file: places2k.txt \n");
	fp = fopen(FILE_NAME, "r");

	
	while(fgets(line, MAXLEN, fp) != NULL)
	{
		strncpy(currentState,line,2);
		if(strcmp(previousState, currentState) != 0)
		{
			// Update condition
			strcpy(previousState,currentState);
			stateIndex++;

			// Initialize the state
			listOfState[stateIndex].stateAbbreviation = malloc(2);
			strncpy(listOfState[stateIndex].stateAbbreviation,line,2);
			cityOrTownIndex = listOfState[stateIndex].numberOfCityOrTown = 1;

			// Add a city or town
			currentStatePointer = listOfCityOrTownByState[stateIndex];
			currentStatePointer[cityOrTownIndex-1].cityOrTownName = malloc(MAXLEN);

			//line is a pointer + 9 to move to the next 10 char, if you can find a better way to do this, do it
			//cuz this is rediculously stupid
			strncpy(currentStatePointer[cityOrTownIndex-1].cityOrTownName, line + 9, 63);
			strncpy(latitude, line+(144), 9);
			strncpy(longitude, line+(154), 9);
			currentStatePointer[cityOrTownIndex-1].latitude = strtod(latitude, NULL);
			currentStatePointer[cityOrTownIndex-1].longitude = strtod(longitude, NULL);

		}
		else
		{
			cityOrTownIndex = ++listOfState[stateIndex].numberOfCityOrTown;

			// Add a city or town
			currentStatePointer = listOfCityOrTownByState[stateIndex];
			currentStatePointer[cityOrTownIndex-1].cityOrTownName = malloc(MAXLEN);

			strncpy(currentStatePointer[cityOrTownIndex-1].cityOrTownName, line + 9, 63);


			strncpy(latitude, line+(144), 9);
			strncpy(longitude, line+(154), 9);
			currentStatePointer[cityOrTownIndex-1].latitude = strtod(latitude, NULL);
			currentStatePointer[cityOrTownIndex-1].longitude = strtod(longitude, NULL);
		}
	}
}

char * getStateName(int index)
{
	return NULL;
}


// #include "places.h"
// #include "airports.h"

// const nametype FILE_NAME = "places2k.txt";
// const int stateAbbreviationLength = 2;
// const int NUMBER_OF_STATES = 51;

// // Self Declare struct - not by rpc
// typedef struct CityOrTown CityOrTown;
// struct CityOrTown
// {
// 	nametype cityOrTownName;
// 	double latitude;
// 	double longitude;
// };

// typedef struct State State;
// struct State
// {
// 	nametype stateName;
// 	nametype stateAbbreviation;
// 	int numberOfCityOrTown;
// 	CityOrTown *listOfCityOrTown;
// };

// void initializeData(State _listOfState[]);

// nearest_results_place *
// getnearest_place_1_svc(place *argp, struct svc_req *rqstp)
// {
// 	static nearest_results_place result;
// 	static int ifNotInitialized = 0;
// 	static State listOfState[52];

// 	if(ifNotInitialized == 0)
// 	{
// 		initializeData(listOfState);
// 	}

// 	xdr_free((xdrproc_t)xdr_nearest_results_air, (char*)&result);

// 	printf("Inside nearest_results_place\n");
// 	printf("city: %s\n", argp->city);
// 	printf("state: %s\n",argp->state);

// 	CLIENT *clnt;
// 	nearest_results_air  *result_1;
// 	geoLocation  getnearest_air_1_arg;

// 	getnearest_air_1_arg.longitude = 91.12;
// 	getnearest_air_1_arg.latitude = 12.23;

// // Touch on this later
// // #ifndef DEBUG
// // 	clnt = clnt_create ("localhost", airportProgram, airport_version, "udp");
// // 	if (clnt == NULL) {
// // 		clnt_pcreateerror ("localhost");
// // 		exit (1);
// // 	}
// // #endif  /* DEBUG */

// // 	result_1 = getnearest_air_1(&getnearest_air_1_arg, clnt);
// // 	if (result_1 == (nearest_results_air *) NULL) {
// // 		clnt_perror (clnt, "call failed");
// // 	} else{
// // 		if (result_1->err == 0){
// // 			result->x = result_1->x;
// // 		}
// // 	}



// 	/*
// 	 * insert server code here
// 	 */



// 	return &result;

// }

// void initializeData(State listOfState[])
// {
// 	FILE * fp = NULL;

// 	nametype previousState;
// 	previousState = malloc(MAXLEN);
// 	strcpy(previousState, "00");

// 	nametype currentState;
// 	currentState = malloc(MAXLEN);

// 	nametype line;
// 	line = malloc(MAXLEN);

// 	int stateIndex = -1;
// 	int cityOrTownIndex;

// 	printf("Opening file: places2k.txt \n");
// 	fp = fopen(FILE_NAME, "r");

	
// 	while(fgets(line, MAXLEN, fp) != NULL)
// 	{
// 		strncpy(currentState,line,2);
// 		if(strcmp(previousState, currentState) != 0)
// 		{
// 			// Update condition
// 			strcpy(previousState,currentState);
// 			stateIndex++;

// 			// Initialize the state
// 			listOfState[stateIndex].stateAbbreviation = malloc(2);
// 			strncpy(listOfState[stateIndex].stateAbbreviation,line,2);

// 			// Add a city or town
// 			listOfState[stateIndex].listOfCityOrTown = (CityOrTown*)calloc(100, sizeof(CityOrTown));
// 			cityOrTownIndex = listOfState[stateIndex].numberOfCityOrTown = 0;
// 			listOfState[stateIndex].listOfCityOrTown[cityOrTownIndex].cityOrTownName			

// 		}
// 		else
// 		{

// 		}
// 	}
// }

// char * getStateName(int index)
// {
// 	return NULL;
// }
