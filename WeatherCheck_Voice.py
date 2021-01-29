# Rassim Yahioune - CS50 Final Project - 2019/2020
# Weather details of any city using voice  with openweathermap api
# using for the weather the source code in https://www.geeksforgeeks.org/python-find-current-weather-of-any-city-using-openweathermap-api/

import speech_recognition # module for listening
import pyttsx3 # module for talking with Pyaudio to import also.
import requests, json # for the weather program

# set the variable to recognizer
listener = speech_recognition.Recognizer()
#Set a variable for talking using pyttsx module
engine = pyttsx3.init()

#Choose the voice '0' for man and '1' for girl
voices = engine.getProperty('voices')
engine.setProperty('voice', voices[0].id)

#Function to say a text
def talk(text):
    engine.say(text)
    engine.runAndWait()

#What to tell when the program starts
talk('Hey my name is Rassim! I am here to tell you the weather of any city of your choice.')

try:
    while True:
        # To take the user city choice
        with speech_recognition.Microphone() as source:
            talk('Please, tell me which city and state: ')
            print('Listening...')
            voice = listener.listen(source)
            # input the voice and take the first word if there are many
            city = listener.recognize_google(voice).lower().split(' ')
            city = ', '.join(city)
            print(city)
            talk(city)

        # using my API key
        api_key = "de100c19c67853bddd1d62ab379a6030"

        # base_url variable to store url
        base_url = "http://api.openweathermap.org/data/2.5/weather?"

        # complete_url variable to store
        # complete url address
        complete_url = base_url + "appid=" + api_key + "&q=" + city

        # get method of requests module return response object
        response = requests.get(complete_url)

        # json method of response object convert json format data into python format data
        x = response.json()

        # Now x contains list of nested dictionaries
        # Check the value of "cod" key is equal to "404", means city is found otherwise, city is not found
        if x["cod"] != "404":

            # store the value of "main" key in variable y
            y = x["main"]

            # store the value corresponding to the "temp" key of y
            current_temperature = y["temp"]

            # Convert the temperature to celsius and fahrenheit
            celsius = round(current_temperature - 273.15)
            fahrenheit = (current_temperature - 273.15) * 9/5 + 32
            fahrenheit = round(fahrenheit)
            # store the value corresponding to the "pressure" key of y
            current_pressure = y["pressure"]

            # store the value corresponding to the "humidity" key of y
            current_humidiy = y["humidity"]

            # store the value of "weather" key in variable z
            z = x["weather"]

            # store the value corresponding to the "description" key at the 0th index of z
            weather_description = z[0]["description"]

            # print following values
            print(" Temperature (in kelvin unit) = " +
                  str(current_temperature) +
                  "\n Temperature (in celsius unit) = " +
                  str(celsius) +
                  "\n Temperature (in fahrenheit unit) = " +
                  str(fahrenheit) +
                  "\n atmospheric pressure (in hPa unit) = " +
                  str(current_pressure) +
                  "\n humidity (in percentage) = " +
                  str(current_humidiy) +
                  "\n description = " +
                  str(weather_description))
            talk(" Temperature (in celsius unit) = " +
                  str(celsius) + ", and in fahrenheit unit " +
                  str(fahrenheit) +
                  "\n atmospheric pressure (in hPa unit) = " +
                  str(current_pressure) +
                  "\n humidity (in percentage) = " +
                  str(current_humidiy) +
                  "\n description = " +
                  str(weather_description))

        else:
            print(" City Not Found ")
            talk(" City Not Found ")

        # Asking if the user wants to check the weather for another city
        with speech_recognition.Microphone() as source:
            talk('Do you want to check an other city?')
            print('Listening...')
            voice = listener.listen(source)
            command = listener.recognize_google(voice)
            if "no" in command or 'nop' in command:
                break
            else:
                talk('all right!')
    talk('Thank you! And have a good one ')

except:
    print("There is an issue. Please check your microphone")
    talk("There is an issue. Please check your microphone")