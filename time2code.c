// time2code.c
// Assignment 1, COMP1511 18s1: Time To Code.
//
// This program by Aven Au (z5208734) on 22/03/2018
//
// Version 1.0.2: Add version numbers and header comment.
// Version 1.0.1: Fix day/time variable mix-up in main function.
// Version 1.0.0: Assignment released.

#include <stdio.h>
#include <assert.h>

// You must use these #defines - DO NOT CHANGE THEM

#define TOWN_ADELAIDE       0
#define TOWN_BRISBANE       1
#define TOWN_BROKEN_HILL    2
#define TOWN_CANBERRA       3
#define TOWN_DARWIN         4
#define TOWN_EUCLA          5
#define TOWN_HOBART         6
#define TOWN_LORD_HOWE_IS   7
#define TOWN_MELBOURNE      8
#define TOWN_PERTH          9
#define TOWN_SYDNEY         10

// New Zealand

#define TOWN_AUCKLAND       11
#define TOWN_CHRISTCHURCH   12
#define TOWN_WELLINGTON     13

// Australia

#define TIMEZONE_AWST_OFFSET  800 // Australian Western Standard Time

#define TIMEZONE_ACWST_OFFSET 845 // Australian Central Western Standard Time

#define TIMEZONE_ACST_OFFSET  930 // Australian Central Standard Time
#define TIMEZONE_ACDT_OFFSET 1030 // Australian Central Daylight Time

#define TIMEZONE_AEST_OFFSET 1000 // Australian Eastern Standard Time
#define TIMEZONE_AEDT_OFFSET 1100 // Australian Eastern Daylight Time

#define TIMEZONE_LHST_OFFSET 1030 // Lord Howe Standard Time
#define TIMEZONE_LHDT_OFFSET 1100 // Lord Howe Daylight Time

// New Zealand
#define TIMEZONE_NZST_OFFSET 1200 // NZ Standard Time
#define TIMEZONE_NZDT_OFFSET 1300 // NZ Daylight Time

// returned by get_local_time
#define INVALID_INPUT (-1)


// ADD YOUR #defines (if any) here

int get_local_time(int town, int month, int day, int time);
void run_unit_tests(void);


// ADD PROTOTYPES FOR YOUR FUNCTIONS HERE
int nz_or_aus(void);
int month, date, time, town;
int invalidtown_test(int town);
int timezone_test(int town, int day, int month, int time);
void time_date_month_checker(int rtime, int rmonth, int rday);
int daylight_test_aus(int day, int month, int time);
int daylight_test_nz(int day, int month, int time);
int invalidmonth_test(int month, int date, int time);

// DO NOT CHANGE THIS FUNCTION

// This main function won't be marked as part of the assignment
// It tests the functions you have to write.
// Do not change this main function.  If it does not work with
// your functions you have misunderstood the assignment.

int main(void) {
    int call_get_local_time = 0;

    printf("Enter 0 to call run_unit_tests()\n");
    printf("Enter 1 to call get_local_time()\n");
    printf("Call which function: ");
    scanf("%d", &call_get_local_time);

    if (!call_get_local_time) {
        printf("calling run_unit_tests()\n");
        run_unit_tests();
        printf("unit tests done\n");
        return 0;
    }

    int town = 0;
    int month = 0;
    int day = 0;
    int time = 0;

    printf("Enter %d for Adelaide\n", TOWN_ADELAIDE);
    printf("Enter %d for Brisbane\n", TOWN_BRISBANE);
    printf("Enter %d for Broken_hill\n", TOWN_BROKEN_HILL);
    printf("Enter %d for Canberra\n", TOWN_CANBERRA);
    printf("Enter %d for Darwin\n", TOWN_DARWIN);
    printf("Enter %d for Eucla\n", TOWN_EUCLA);
    printf("Enter %d for Hobart\n", TOWN_HOBART);
    printf("Enter %d for Lord Howe Island\n", TOWN_LORD_HOWE_IS);
    printf("Enter %d for Melbourne\n", TOWN_MELBOURNE);
    printf("Enter %d for Perth\n", TOWN_PERTH);
    printf("Enter %d for Sydney\n", TOWN_SYDNEY);
    printf("Enter %d for Auckland\n", TOWN_AUCKLAND);
    printf("Enter %d for Christchurch\n", TOWN_CHRISTCHURCH);
    printf("Enter %d for Wellington\n", TOWN_WELLINGTON);

    printf("Which town: ");
    scanf("%d", &town);

    printf("Enter UTC month as integer 1..12: ");
    scanf("%d", &month);

    printf("Enter UTC day as integer 1..31: ");
    scanf("%d", &day);

    printf("Enter UTC time as hour * 100 + minutes\n");
    printf("Enter UTC time as integer [0..2359]: ");
    scanf("%d", &time);

    int local_time = get_local_time(town, month, day, time);

    if (local_time == INVALID_INPUT) {
        printf("invalid input - local time could not be calculated\n");
    } else {
        printf("local_time is %d\n", local_time);
    }

    return 0;
}



// Given an Australian town and a 2018 UTC time
// return the local time in the Australian town
//
// time is returned as hours*100 + minutes
// INVALID_INPUT is return for invalid inputs
//
// utc_month should be 1..12
// utc_day should be 1..31
// utc_time should be 0..2359
// utc_time is hours*100 + minutes
//
// note UTC year is assumed to be 2018
// note UTC seconds is assumed to be zero
//

int get_local_time(int town, int month, int day, int time) {
    // CHANGE THIS FUNCTION
    // YOU ARE NOT PERMITTED TO USE ARRAYS, LOOPS, PRINTF OR SCANF
    // SEE THE ASSIGNMENT SPECIFICATION FOR MORE RESTRICTIONS
	int rmonth = month; //rtime, rmonth and rdate are the times after the time difference conversion
	int rday = day;
	int towntest = invalidtown_test(town);
 	int rtime = time + timezone_test(town, day, month, time);
	int minutes = rtime % 100;
	int utc_minutes = time % 100;
	int invalidmonth_test(int month, int day, int time);

	if (towntest || invalidmonth_test(month, day, time) == 1) {
		return INVALID_INPUT;
	} 
	else if (rtime >= 2400) {
		if (minutes >= 60) {
			rtime = rtime + 40;
		}
		rtime = rtime - 2400;
	} 
	else if (minutes >= 60) {
		rtime = rtime + 40;
	}

    return rtime;
}

// ADD YOUR FUNCTIONS HERE

int invalidmonth_test(int month, int day, int time) {
	int x = 0;
	if ( (month > 12) || (day > 31) || (time > 2400) ) {
		x = 1;
	} 
	else if ( (month == 2) && (day > 28) ){
		x = 1;
	} 
	else if ( (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && (day > 31) ){
		x = 1;
	} 
	else if ( (month == 4 || month == 6 || month == 9 || month == 11) && (day > 30) ){
		x = 1;
	}
return x;
}

//Check if any of the input is invalid___________________________________________________________________________
int invalidtown_test(int town){

	int x = 0;
// Check if the town selected is valid

	if ( (town == TOWN_ADELAIDE) || (town == TOWN_BRISBANE) || (town == TOWN_BROKEN_HILL) || (town == TOWN_CANBERRA) || (town == TOWN_DARWIN) ||   (town == TOWN_EUCLA) || (town == TOWN_HOBART) || (town == TOWN_LORD_HOWE_IS) || (town == TOWN_MELBOURNE) || (town == TOWN_PERTH) || (town == TOWN_SYDNEY) || (town == TOWN_AUCKLAND) || (town == TOWN_CHRISTCHURCH) || (town == TOWN_WELLINGTON) ) {
		x = 0;
	} else {
		x = 1;
	}
return x;
}

//Testing timezone differnece______________________________________________________________________________________
int timezone_test(int town, int day, int month, int time){
	int difference = 0;
	int nz, aus;
	int daylight_test_aus(int day, int month, int time);
	int daylight_test_nz(int day, int month, int time);
	int minute = time % 100;

nz = daylight_test_nz(day, month, time);
aus = daylight_test_aus(day, month, time);

	if ( ((town == TOWN_AUCKLAND) || (town == TOWN_CHRISTCHURCH) || (town == TOWN_WELLINGTON)) && nz == 1){
		difference = TIMEZONE_NZDT_OFFSET;
		} else if (town == TOWN_LORD_HOWE_IS && aus == 1){
			difference = TIMEZONE_LHDT_OFFSET;
		} else if (town == TOWN_PERTH) {
			difference = TIMEZONE_AWST_OFFSET;
		} else if ( (town == TOWN_EUCLA) && (minute >= 25) ){
			difference = TIMEZONE_ACWST_OFFSET + 40; //This is a counter measure for when 45 minutes is added when above 0025 which would serve as a problem to my minute calculations
		} else if (town == TOWN_EUCLA) {
			difference = TIMEZONE_ACWST_OFFSET;
		} else if (town == TOWN_DARWIN){
			difference = TIMEZONE_ACST_OFFSET;
		} else if (town == TOWN_BRISBANE && aus == 1){
			difference = TIMEZONE_AEST_OFFSET;
		} else if ( ((town == TOWN_BROKEN_HILL) || (town == TOWN_ADELAIDE)) && aus == 1){
			difference = TIMEZONE_ACDT_OFFSET;
		} else if ( ((town == TOWN_SYDNEY) || (town == TOWN_CANBERRA) || (town == TOWN_HOBART) || (town == TOWN_MELBOURNE)) && aus == 1 ){
			difference = TIMEZONE_AEDT_OFFSET;
		} else if ( ((town == TOWN_AUCKLAND) || (town == TOWN_CHRISTCHURCH) || (town == TOWN_WELLINGTON)) && nz == 0){
			difference = TIMEZONE_NZST_OFFSET;
		} else if (town == TOWN_LORD_HOWE_IS && aus == 0) {
			difference = TIMEZONE_LHST_OFFSET;
		} else if (town == TOWN_BRISBANE && aus == 0){
			difference = TIMEZONE_AEST_OFFSET;
		} else if (((town == TOWN_BROKEN_HILL) || (town == TOWN_ADELAIDE)) && aus == 0){
			difference = TIMEZONE_ACST_OFFSET;
		} else if ( ((town == TOWN_SYDNEY) || (town == TOWN_CANBERRA) || (town == TOWN_HOBART) || (town == TOWN_MELBOURNE)) && aus == 0 ){
			difference = TIMEZONE_AEST_OFFSET;
		}
	
	return difference;
}

//NZ's test for whether it is under daylight saving timezone____________________________________________________________________________________________

int daylight_test_nz(int day, int month, int time) { //Non Daylight saving times occur between 31st March 1400 - 29th Septempber 1300 in UTC
	int daylight = 1;
	if (day == 31 && month == 3 && time >= 1400){
		daylight = 0;
	}
	else if (day == 29 && month == 9 && time <= 1300){
		daylight = 0;
	}
	else if (month >= 4 && month <= 8){
		daylight = 0;
	} 
	else if (day >= 1 && day >= 28 && month == 9){
		daylight = 0;
	}
	else {
		daylight = 1;
	}
return daylight;
} 

//AUS's test for whether it is under daylight saving timezone________________________________________________________________________________________________
int daylight_test_aus(int day, int month, int time) { //Non Daylight saving times occur between 31st March 1400 - 6th October 1600 in UTC
	int daylight;
	if ( (day == 31) && (month == 3) && (time >= 1700) ){
		daylight = 0;	
	} else if ( (day == 6) && (month == 10) && (time <= 1600) ){
		daylight = 0;
	} else if (month >= 4 && month <= 9){
		daylight = 0;
	} else if ((day >= 1) && (month == 10) && (day <= 5)){
		daylight = 0;
	} else {
		daylight = 1;
	}
return daylight;
}




// ADD A COMMENT HERE EXPLAINING YOUR OVERALL TESTING STRATEGY

// I mainly tested the subtle problems that would happen only due to the failure of my functions. This allows be to test whether my functions worked problem and check if they need to be fixed. Random time checks are used to check whether the code would run correctly overall

// run unit tests for get_local_time

void run_unit_tests(void) {
    // 2 example unit tests

    // UTC midnight on 20th March -> time in Sydney: 11am AEDT
    assert(get_local_time(TOWN_SYDNEY, 3, 20, 0) == 1100);

    // 42 is not a valid month
    assert(get_local_time(TOWN_SYDNEY, 42, 0, 0) == INVALID_INPUT);

    // ADD YOUR ASSERT STATEMENTS HERE

	 //Just before daylight saving
    assert(get_local_time(TOWN_CHRISTCHURCH, 9, 29, 1259) == 59);

	 //UTC + time difference causes the minutes to be bigger than 100 which could mess up minute calculations and time corrections. This checks whether this is a problem.
    assert(get_local_time(TOWN_EUCLA, 2, 20, 2359) == 844);

	// Invalid Town Test
    assert(get_local_time(30, 6, 24, 945) == INVALID_INPUT);

	//Check if Daylight Saving Function works
    assert(get_local_time(TOWN_BROKEN_HILL, 1, 30, 0) == 1030);

	//Check if Daylight Saving Function works during Standard Time period
    assert(get_local_time(TOWN_BROKEN_HILL, 5, 25, 0) == 930);

	//Check if Daylight Saving Function works for ASET
    assert(get_local_time(TOWN_SYDNEY, 2, 20, 0) == 1100);

	//Check if Daylight Saving Function works for ASDT
    assert(get_local_time(TOWN_SYDNEY, 8, 14, 0) == 1000);

	//Check if Daylight Saving Function works for LHDT
    assert(get_local_time(TOWN_LORD_HOWE_IS, 12, 25, 0) == 1100);

	//Check if Daylight Saving Function works for LHST
    assert(get_local_time(TOWN_LORD_HOWE_IS, 8, 20, 0) == 1030);

	//Check if Daylight Saving Function works for NZDT
    assert(get_local_time(TOWN_CHRISTCHURCH, 10, 30, 0) == 1300);

	//Check if Daylight Saving Function works for NZST
    assert(get_local_time(TOWN_CHRISTCHURCH, 5, 30, 0) == 1200);

	//Check if Time conversions works for AWST
    assert(get_local_time(TOWN_ADELAIDE, 7, 19, 1400) == 2330);

	//Check if Time conversions works for ACWST
    assert(get_local_time(TOWN_EUCLA, 2, 22, 2300) == 745);

	//Check if Time conversions works for Darwin
    assert(get_local_time(TOWN_DARWIN, 9, 13, 1500) == 30);

	//Check if Time conversions works for Brisbane
    assert(get_local_time(TOWN_BRISBANE, 4, 20, 1315) == 2315);

	//2018 is not a leap year thus only 28 days on Febuary
    assert(get_local_time(TOWN_DARWIN, 2, 29, 2000) == INVALID_INPUT);

	//There is only 30 days on April
    assert(get_local_time(TOWN_CANBERRA, 4, 31, 500) == INVALID_INPUT);

	// There is only 30 days September
    assert(get_local_time(TOWN_MELBOURNE, 9, 31, 1800) == INVALID_INPUT);

	//Checking if the "invalidmonth_test" function is working
    assert(get_local_time(TOWN_HOBART, 1, 32,2156) == INVALID_INPUT);

	//Checking if the "invalidmonth_test" function is working 
    assert(get_local_time(TOWN_PERTH, 3, 32, 1524) == INVALID_INPUT);

	//Checking if the "invalidmonth_test" function is working
    assert(get_local_time(TOWN_SYDNEY, 5, 32, 2354) == INVALID_INPUT);

	//Checking if the "invalidmonth_test" function is working
    assert(get_local_time(TOWN_BROKEN_HILL, 7, 50, 1245) == INVALID_INPUT);

	//Checking if the "invalidmonth_test" function is working
    assert(get_local_time(TOWN_BRISBANE, 8, 32, 2345) == INVALID_INPUT);

	//Checking if the "invalidmonth_test" function is working
    assert(get_local_time(TOWN_EUCLA, 10, 30, 1340) == 2225);

	//Checking if the "invalidmonth_test" function is working
    assert(get_local_time(TOWN_MELBOURNE, 12, 31, 0) == 1100);

	//Checking if the "invalidmonth_test" function is working
    assert(get_local_time(TOWN_LORD_HOWE_IS, 6, 31, 1536) == INVALID_INPUT);

	//Checking if the "invalidmonth_test" function is working
    assert(get_local_time(TOWN_DARWIN, 9, 31, 1756) == INVALID_INPUT);

	//Checking if the "invalidmonth_test" function is working
    assert(get_local_time(TOWN_SYDNEY, 11, 31, 1934) == INVALID_INPUT);

	//Check if the 24 hour conversion working
    assert(get_local_time(TOWN_PERTH, 6, 20, 2359) == 759);

	//Normal Time Conversion Test
    assert(get_local_time(TOWN_ADELAIDE, 8, 12, 800) == 1730);

	//Normal Time Conversion Test
    assert(get_local_time(TOWN_BRISBANE, 7, 19, 1000) == 2000);

	//Normal Time Conversion Test
    assert(get_local_time(TOWN_BROKEN_HILL, 11, 11, 1100) == 2130);

	//Normal Time Conversion Test
    assert(get_local_time(TOWN_CANBERRA, 12, 25, 0) == 1100);

	//Normal Time Conversion Test
    assert(get_local_time(TOWN_DARWIN, 4, 25, 1206) == 2136);

	//Normal Time Conversion Test
    assert(get_local_time(TOWN_EUCLA, 10, 30, 900) == 1745);

	//Normal Time Conversion Test
    assert(get_local_time(TOWN_HOBART, 1, 1, 0) == 1100);

	//Normal Time Conversion Test
    assert(get_local_time(TOWN_LORD_HOWE_IS, 5, 5, 13) == 1043);

	//Normal Time Conversion Test
    assert(get_local_time(TOWN_MELBOURNE, 6, 16, 1345) == 2345);

	//Normal Time Conversion Test
    assert(get_local_time(TOWN_PERTH, 8, 7, 1236) == 2036);

	//Normal Time Conversion Test
    assert(get_local_time(TOWN_AUCKLAND, 2, 27, 800) == 2100);

	//Normal Time Conversion Test
    assert(get_local_time(TOWN_CHRISTCHURCH, 5, 15, 859) == 2059);

    // you should add at least 40 more assert statements to this function
    // with a comment for each test explaining it

    // there should be comment before this function
    // explaining your overall testing strategy
}
