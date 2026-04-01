
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct Weather {
    string city;
    int temperature;
    int humidity;
    int windSpeed;
};

// Function prototypes
void displayMenu();
void displayCurrentWeather(const vector<Weather>&);
void forecastWeather(vector<Weather>&);
void compareWeatherBetweenCities(const vector<Weather>&);
void saveWeatherDataToFile(const vector<Weather>&);
void loadWeatherDataFromFile(vector<Weather>&);

int main() {
    vector<Weather> weatherData;
    loadWeatherDataFromFile(weatherData);

    int choice;
    while (true) {
        displayMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                displayCurrentWeather(weatherData);
                break;
            case 2:
                forecastWeather(weatherData);
                break;
            case 3:
                compareWeatherBetweenCities(weatherData);
                break;
            case 4:
                saveWeatherDataToFile(weatherData);
                break;
            case 5:
                loadWeatherDataFromFile(weatherData);
                break;
            case 6:
                cout << "Exiting program. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}

void displayMenu() {
    cout << "South African Weather Program" << endl;
    cout << "-------------------------------" << endl;
    cout << "1. Display Current Weather" << endl;
    cout << "2. Forecast Weather" << endl;
    cout << "3. Compare Weather Between Cities" << endl;
    cout << "4. Save Weather Data to File" << endl;
    cout << "5. Load Weather Data from File" << endl;
    cout << "6. Exit" << endl;
    cout << "-------------------------------" << endl;
    cout << "Enter your choice: ";
}

void displayCurrentWeather(const vector<Weather>& weatherData) {
    cout << "Current Weather:" << endl;
    for (const auto& weather : weatherData) {
        cout << "City: " << weather.city << endl;
        cout << "Temperature: " << weather.temperature << "°C" << endl;
        cout << "Humidity: " << weather.humidity << "%" << endl;
        cout << "Wind Speed: " << weather.windSpeed << " km/h" << endl;
        cout << endl;
    }
}

void forecastWeather(vector<Weather>& weatherData) {
    cout << "Forecast Weather:" << endl;
    for (auto& weather : weatherData) {
        weather.temperature += 2;
        cout << "City: " << weather.city << endl;
        cout << "Temperature: " << weather.temperature << "°C" << endl;
        cout << "Humidity: " << weather.humidity << "%" << endl;
        cout << "Wind Speed: " << weather.windSpeed << " km/h" << endl;
        cout << endl;
    }
}

void compareWeatherBetweenCities(const vector<Weather>& weatherData) {
    string city1, city2;
    cout << "Enter first city: ";
    cin >> city1;
    cout << "Enter second city: ";
    cin >> city2;

    // Replace underscores with spaces
    for (int i = 0; i < city1.length(); ++i) {
        if (city1[i] == '_') city1[i] = ' ';
    }
    for (int i = 0; i < city2.length(); ++i) {
        if (city2[i] == '_') city2[i] = ' ';
    }

    // Convert to lowercase
    transform(city1.begin(), city1.end(), city1.begin(), ::tolower);
    transform(city2.begin(), city2.end(), city2.begin(), ::tolower);

    int city1Index = -1, city2Index = -1;
    for (int i = 0; i < weatherData.size(); ++i) {
        string currentCity = weatherData[i].city;
        transform(currentCity.begin(), currentCity.end(), currentCity.begin(), ::tolower);

        if (currentCity == city1) city1Index = i;
        if (currentCity == city2) city2Index = i;
    }

    if (city1Index != -1 && city2Index != -1) {
        cout << "Comparison:" << endl;
        cout << "City 1: " << weatherData[city1Index].city << endl;
        cout << "Temperature: " << weatherData[city1Index].temperature << "°C" << endl;
        cout << "Humidity: " << weatherData[city1Index].humidity << "%"<<endl;
        cout << "Wind Speed: " << weatherData[city1Index].windSpeed << " km/h" << endl;
        cout << endl;

        cout << "City 2: " << weatherData[city2Index].city << endl;
        cout << "Temperature: " << weatherData[city2Index].temperature << "°C" << endl;
        cout << "Humidity: " << weatherData[city2Index].humidity << "%" << endl;
        cout << "Wind Speed: " << weatherData[city2Index].windSpeed << " km/h" << endl;
        cout << endl;

        // Additional comparison details (optional)
        if (weatherData[city1Index].temperature > weatherData[city2Index].temperature) {
            cout << weatherData[city1Index].city << " is warmer than " << weatherData[city2Index].city << " by " << weatherData[city1Index].temperature - weatherData[city2Index].temperature << "°C" << endl;
        } else if (weatherData[city1Index].temperature < weatherData[city2Index].temperature) {
            cout << weatherData[city2Index].city << " is warmer than " << weatherData[city1Index].city << " by " << weatherData[city2Index].temperature - weatherData[city1Index].temperature << "°C" << endl;
        } else {
            cout << weatherData[city1Index].city << " and " << weatherData[city2Index].city << " have the same temperature." << endl;
        }
    } else {
        cout << "One or both cities not found. Please try again." << endl;
    }
}

void saveWeatherDataToFile(const vector<Weather>& weatherData) {
    ofstream outputFile("weather_data.txt");
    if (outputFile.is_open()) {
        for (const auto& weather : weatherData) {
            outputFile << weather.city << "," << weather.temperature << "," << weather.humidity << "," << weather.windSpeed << endl;
        }
        outputFile.close();
        cout << "Weather data saved to weather_data.txt" << endl;
    } else {
        cout << "Unable to open file for writing." << endl;
    }
}

void loadWeatherDataFromFile(vector<Weather>& weatherData) {
    ifstream inputFile("weather_data.txt");
    if (inputFile.is_open()) {
        string line;
        weatherData.clear();
        while (getline(inputFile, line)) {
            istringstream iss(line);
            string city;
            int temperature, humidity, windSpeed;
            getline(iss, city, ',');
            iss >> temperature;
            char comma; // Consume comma
            iss >> comma;
            iss >> humidity;
            iss >> comma; // Consume comma
            iss >> windSpeed;
            weatherData.push_back({city, temperature, humidity, windSpeed});
        }
        inputFile.close();
        cout << "Weather data loaded from weather_data.txt" << endl;
    } else {
        cout << "Unable to open file for reading." << endl;
    }
}
