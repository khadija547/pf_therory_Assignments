/*
    Question 3:
    Greenhouse Temperature Monitoring System

    This program:
    1. Inputs the number of sensors.
    2. Inputs the number of hourly readings.
    3. Stores temperatures in a two-dimensional array.
    4. Calculates total and average temperature.
    5. Finds maximum and minimum temperature.
    6. Counts critical readings.
    7. Counts warning readings.
    8. Finds the longest consecutive temperature streak.
    9. Identifies the sensor with the highest average.

    User-defined functions:
    - inputReadings()
    - analyzeSensor()
    - findHighestAverageSensor()
*/

#include <stdio.h>  // Provides printf() and scanf()


// Maximum array capacities used in this implementation

#define MAX_SENSORS 10
#define MAX_HOURS 24


// ==================================================
// FUNCTION 1: inputReadings()
// ==================================================

void inputReadings(int readings[][MAX_HOURS],
                   int sensors,
                   int hours)
{
    int sensor;  // Loop counter for sensors
    int hour;    // Loop counter for hourly readings

    // Loop through every sensor

    for (sensor = 0; sensor < sensors; sensor++)
    {
        printf("\nEnter readings for Sensor %d:\n", sensor + 1);

        // Loop through every hour of the current sensor

        for (hour = 0; hour < hours; hour++)
        {
            printf("Hour %d: ", hour + 1);

            // Input temperature and store it in the array

            scanf("%d", &readings[sensor][hour]);
        }
    }
}


// ==================================================
// FUNCTION 2: analyzeSensor()
// ==================================================

void analyzeSensor(int sensorReadings[],
                   int hours,
                   int sensorNumber)
{
    int hour;             // Loop counter

    int total = 0;        // Sum of all readings

    float average;        // Average temperature

    int highest;          // Maximum temperature
    int lowest;           // Minimum temperature

    int criticalCount = 0; // Readings >= 40°C
    int warningCount = 0;  // Readings between 35°C and 39°C

    int currentStreak = 0; // Current consecutive streak
    int longestStreak = 0; // Longest consecutive streak

    // ----------------------------------------------
    // INITIALIZE HIGHEST AND LOWEST
    // ----------------------------------------------

    // Assume the first reading is both highest and lowest

    highest = sensorReadings[0];
    lowest = sensorReadings[0];

    // ----------------------------------------------
    // ANALYZE ALL HOURLY READINGS
    // ----------------------------------------------

    for (hour = 0; hour < hours; hour++)
    {
        // Store the current temperature in a temporary variable

        int temperature = sensorReadings[hour];

        // ------------------------------------------
        // CALCULATE TOTAL
        // ------------------------------------------

        total = total + temperature;

        // ------------------------------------------
        // FIND HIGHEST TEMPERATURE
        // ------------------------------------------

        if (temperature > highest)
        {
            highest = temperature;
        }

        // ------------------------------------------
        // FIND LOWEST TEMPERATURE
        // ------------------------------------------

        if (temperature < lowest)
        {
            lowest = temperature;
        }

        // ------------------------------------------
        // COUNT CRITICAL READINGS
        // ------------------------------------------

        // Critical temperature is 40°C or above

        if (temperature >= 40)
        {
            criticalCount++;
        }

        // ------------------------------------------
        // COUNT WARNING READINGS
        // ------------------------------------------

        // Warning temperature is between 35°C and 39°C
        // Both 35 and 39 are included.

        if (temperature >= 35 && temperature <= 39)
        {
            warningCount++;
        }

        // ------------------------------------------
        // CALCULATE CONSECUTIVE STREAK
        // ------------------------------------------

        // A streak continues when temperature is 35°C or above

        if (temperature >= 35)
        {
            // Increase the current streak

            currentStreak++;

            // Update the longest streak if necessary

            if (currentStreak > longestStreak)
            {
                longestStreak = currentStreak;
            }
        }
        else
        {
            // Temperature below 35°C ends the streak

            currentStreak = 0;
        }
    }

    // ----------------------------------------------
    // CALCULATE AVERAGE TEMPERATURE
    // ----------------------------------------------

    average = (float)total / hours;

    // ----------------------------------------------
    // DISPLAY SENSOR REPORT
    // ----------------------------------------------

    printf("\nSensor %d: ", sensorNumber);

    printf("Total=%d ", total);

    printf("Avg=%.2f ", average);

    printf("Max=%d ", highest);

    printf("Min=%d\n", lowest);

    printf("Critical=%d ", criticalCount);

    printf("Warning=%d ", warningCount);

    printf("Longest hot streak=%d\n", longestStreak);
}


// ==================================================
// FUNCTION 3: findHighestAverageSensor()
// ==================================================

int findHighestAverageSensor(int readings[][MAX_HOURS],
                            int sensors,
                            int hours)
{
    int sensor;           // Loop counter

    int highestSensor = 1; // Sensor with highest average

    int total = 0;        // Total of current sensor

    float average;        // Average of current sensor

    // ----------------------------------------------
    // CALCULATE FIRST SENSOR'S AVERAGE
    // ----------------------------------------------

    for (int hour = 0; hour < hours; hour++)
    {
        total = total + readings[0][hour];
    }

    average = (float)total / hours;

    // Assume Sensor 1 has the highest average initially

    float highestAverage = average;

    // ----------------------------------------------
    // CHECK REMAINING SENSORS
    // ----------------------------------------------

    for (sensor = 1; sensor < sensors; sensor++)
    {
        // Reset total for the current sensor

        total = 0;

        // Calculate total of current sensor

        for (int hour = 0; hour < hours; hour++)
        {
            total = total + readings[sensor][hour];
        }

        // Calculate average of current sensor

        average = (float)total / hours;

        // Compare current average with highest average

        if (average > highestAverage)
        {
            highestAverage = average;

            // Array index starts at 0,
            // sensor numbering starts at 1.

            highestSensor = sensor + 1;
        }
    }

    // Return the sensor number with highest average

    return highestSensor;
}


// ==================================================
// MAIN FUNCTION
// ==================================================

int main()
{
    int sensors;  // Number of sensors
    int hours;    // Number of hourly readings

    int highestAverageSensor; // Sensor with highest average

    // ----------------------------------------------
    // DECLARE TWO-DIMENSIONAL ARRAY
    // ----------------------------------------------

    int readings[MAX_SENSORS][MAX_HOURS];

    // ----------------------------------------------
    // INPUT NUMBER OF SENSORS
    // ----------------------------------------------

    printf("Enter number of sensors (1-%d): ", MAX_SENSORS);

    scanf("%d", &sensors);

    // Validate number of sensors

    while (sensors < 1 || sensors > MAX_SENSORS)
    {
        printf("Invalid! Enter sensors between 1 and %d: ",
               MAX_SENSORS);

        scanf("%d", &sensors);
    }

    // ----------------------------------------------
    // INPUT NUMBER OF HOURLY READINGS
    // ----------------------------------------------

    printf("Enter number of hourly readings (1-%d): ",
           MAX_HOURS);

    scanf("%d", &hours);

    // Validate number of hourly readings

    while (hours < 1 || hours > MAX_HOURS)
    {
        printf("Invalid! Enter hours between 1 and %d: ",
               MAX_HOURS);

        scanf("%d", &hours);
    }

    // ----------------------------------------------
    // INPUT TEMPERATURE READINGS
    // ----------------------------------------------

    inputReadings(readings, sensors, hours);

    // ----------------------------------------------
    // DISPLAY INDIVIDUAL SENSOR REPORTS
    // ----------------------------------------------

    for (int sensor = 0; sensor < sensors; sensor++)
    {
        // Pass the current sensor's row to analyzeSensor()

        analyzeSensor(readings[sensor],
                      hours,
                      sensor + 1);
    }

    // ----------------------------------------------
    // FIND SENSOR WITH HIGHEST AVERAGE
    // ----------------------------------------------

    highestAverageSensor =
        findHighestAverageSensor(readings, sensors, hours);

    // ----------------------------------------------
    // DISPLAY FINAL REPORT
    // ----------------------------------------------

    printf("\nHighest average: Sensor %d\n",
           highestAverageSensor);

    // Calculate its average again for display

    int total = 0;

    for (int hour = 0; hour < hours; hour++)
    {
        total = total + readings[highestAverageSensor - 1][hour];
    }

    float highestAverage = (float)total / hours;

    printf("Average temperature: %.2f\n", highestAverage);

    // End program successfully

    return 0;
}