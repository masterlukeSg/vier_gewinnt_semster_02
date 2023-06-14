
import vierGewinnt
from vierGewinnt import Spielbrett
from typing import Union
import os
import uvicorn
import time
from fastapi import FastAPI

import requests
from pprint import pprint
base_api_url = "http://127.0.0.1:8000"


def game():
    response=requests.get(base_api_url).json()
    print(response["information"])
    response=requests.get(f"{base_api_url}/joinGame").json()
    print(response["information"])
    gameID= response["gameID"]

    symbols = response["symbols"]
    username = input("Gib deinen Namen ein:")

    true = True
    while(true):
        dein_symbol = str(input(f"Wähle ein Symbol{symbols}:"))
        if (dein_symbol in symbols):
           true = False ##symbol wurde hier schon gewählt
    

    nichtspamen = 0
    response = requests.get(f"{base_api_url}/addPlayer/{gameID}/{username}/{dein_symbol}").json()
    while(not response["status"]): 
        if (nichtspamen == 0):
            print(response["information"]) 
        username = input("Gib dein Nutzername nocheinmal ein:")
        response = requests.get(f"{base_api_url}/addPlayer/{gameID}/{username}/{dein_symbol}").json()
        time.sleep(3.0)
        nichtspamen = 1
    
    nichtspamen = 0
    response = requests.get(f"{base_api_url}/play/{gameID}/wartebereich").json()
    while(not response["status"]):
        if (nichtspamen == 0):
            print(response["information"])
        response = requests.get(f"{base_api_url}/play/{gameID}/wartebereich").json()
        time.sleep(3.0)
        nichtspamen = 1



    run = True
    nichtspamen = 0
    
    while(run):
        
       
        
        response = requests.get(f"{base_api_url}/play/{gameID}/werIstDran").json()

        if (response["information"] == username):
            nichtspamen = 0
            
            response = requests.get(f"{base_api_url}/play/{gameID}/gameOn_OFF").json()
            if (not response["status"]):
                run = False
                print(response)
                end()
            
            
            response = requests.get(f"{base_api_url}/play/{gameID}/Board").json()
            ### printet board 
            print(response["information"])

            position = input("In welche Spalte willst du deinen Ring platzieren:")
            response = requests.get(f"{base_api_url}/play/setRing/{gameID}/{username}/{position}").json()
            
            ### Wenn False, dann ist Eingabe ungültig und man bleibt in der Schleif
            while (not response["status"]):
                position = input("Deine Eingabe war fehlerhaft. Versuch es erneut:")
                response = requests.get(f"{base_api_url}/play/setRing/{gameID}/{username}/{position}").json()

            response = requests.get(f"{base_api_url}/play/{gameID}/whoIsWinning").json()
            if (response["status"]):
                run = False
                print(response)
                end()
        
            response = requests.get(f"{base_api_url}/play/{gameID}/Board").json()
            ### printet board 
            print(response["information"])

        
        
        else:
            time.sleep(3.0)
            if (nichtspamen == 0):
                print("Du bist nicht dran! Warte auf den anderen Spieler sein Ring zu platzieren")
                nichtspamen = 1

            
       #response= requests.get(f"{base_api_url}/play/setRing/{username}/{dein_symbol}").json()
       
        
def end():
    print("Ende")
    exit(1)

game()
