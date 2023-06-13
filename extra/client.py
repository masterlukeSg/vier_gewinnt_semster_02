try:
  import vierGewinnt
except ImportError as e:
  print(f"Importing the shared library 'hangman' did not work.")
  print(f"Is (a link to) the shared library 'hangman.____.so' in the same directory as this python script?")
  print(f"The import caused the following exception '{e}'")
  print(f"Exiting")
  exit(1)


from vierGewinnt import Spielbrett
from typing import Union
import os
import uvicorn
from fastapi import FastAPI

import requests
from pprint import pprint
base_api_url = "http://127.0.0.1:8000"


def main():
    base_api_url = "http://127.0.0.1:8000"
    
    response = requests.get(base_api_url).json()
    response_json = response["information"]
    pprint(f"{response_json}")

    response_json = requests.get(f"{base_api_url}/addPlayer/Lukas/XX").json()
    current_guess = response_json['information']
    pprint(f'{current_guess}')
    
    response_json = requests.get(f"{base_api_url}/addPlayer/Clara/00").json()
    current_guess = response_json['information']
    pprint(f'{current_guess}')
    
    response_json = requests.get(f"{base_api_url}/play/setRing/Lukas/3").json()
    current_guess = response_json['information']
    pprint(f'{current_guess}')

    response_json = requests.get(f"{base_api_url}/play/Board").json()
    current_guess = response_json['information']
    print(f'{current_guess}')
    
    response_json = requests.get(f"{base_api_url}/play/whoIsWinning").json()
    current_guess = response_json['information']
    print(f'{current_guess}')
    
    
    


    print(f"Text Nachricht von den coolste: '{vierGewinnt.__doc__}'")

  
def game():
    response=requests.get(base_api_url).json()
    pprint(response["information"])

    symbols = response["symbols"]
    username = input("Gib deinen Namen ein:")

    true = True
    while(true):
        dein_symbol = str(input(f"Wähle ein Symbol{symbols}:"))
        if (dein_symbol in symbols):
           true = False ##symbol wurde hier schon gewählt
    

    
    response = requests.get(f"{base_api_url}/addPlayer/{username}/{dein_symbol}").json()
    if (not response["status"]): 
        None
        ## printe information
    run = True
    nichtspamen = 0
    while(run):
        if (nichtspamen == 0):
            response = requests.get(f"{base_api_url}/play/werIstDran").json()

        if (response["information"] == username):
            response = requests.get(f"{base_api_url}/play/Board").json()
            ### printet board 
            print(response["information"])

            position = input("In welche Spalte willst du deinen Ring platzieren:")
            response = requests.get(f"{base_api_url}/play/setRing/{username}/{position}").json()
            
            ### Wenn False, dann ist Eingabe ungültig und man bleibt in der Schleif
            while (not response["status"]):
                position = input("Deine Eingabe war fehlerhaft. Versuch es erneut:")
                response = requests.get(f"{base_api_url}/play/setRing/{username}/{position}").json()
            
            response = requests.get(f"{base_api_url}/play/Board").json()
            nichtspamen = 1
            ### printet board 
            print(response["information"])
        
        else:
            if (nichtspamen == 0):
                print("Du bist nicht dran! Warte auf den anderen Spieler sein Ring zu platzieren")
                nichtspamen = 1

            
       #response= requests.get(f"{base_api_url}/play/setRing/{username}/{dein_symbol}").json()
       
        


game()
