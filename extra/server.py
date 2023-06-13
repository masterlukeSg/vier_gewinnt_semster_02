## cd Desktop
### uvicorn server:app --reload --port 8000


import vierGewinnt
from vierGewinnt import Spielbrett, Lobby, Spieler
from typing import Union
import os
import uvicorn
from fastapi import FastAPI

app = FastAPI()

lobby = Lobby()
sb = lobby.createNewGame()


## players werden hier hinzugefuegt
# wenn spiel gestartet, wird es geleert, damit ein neues Spiel gespielt werden kann
# playerList speichert, erstellte c++ spieler
playerNames, playerSymbols,playerList = [], [], []
allSymbols = ["XX", "00", "++", "**"]
playerOne, playerTwo = None, None
game = False
counter = 0

# Gibt die Textnachricht und Symbole wieder
@app.get("/")
async def homePage():
    txtNachricht = f"Willkommen bei Viergewinnt. \nIn dieser Lobby sind aktuell {len(playerNames)} Spieler."
    return {"information": txtNachricht,
            "symbols" : allSymbols} 

# 
# Spieler hinzufügen
@app.get("/addPlayer/{userName}/{userSymbol}")
async def AddUser(userName : str, userSymbol: str):
    global game, playerOne, playerTwo
   
    # Wenn Nutzername bereits existiert soll der Spieler nicht hinzugefuegt werden
    if (userName in playerNames):
        return {"information" : "Spieler existiert bereits", "status" : False}
    
    # Wenn das Symbol nicht in allSymbol drin ist soll der Spieler nicht hinzugefuegt werden
    if (userSymbol not in allSymbols):
        return {"information": "Dieses Symbol existiert nicht"}
    
    # Wenn ein anderer Spieler bereits das Symbol besitzt
    if (userSymbol in playerSymbols):
        return {"information" : "Ein nutzer besitzt das Symbol bereits"}
    
    #Wenn es gar keinen oder einen Spieler gibt und das Game noch nicht gestartet hat dann:
    #entfernt er das Usersymbol aus allSymbols und fuegt er einen neuen Spieler und Symbol hinzu:
    # sonst gibt er aus, dass das Spiel schon gestartet hat
    if (len(playerNames) < 2 ):
        if (not game):
            allSymbols.remove(userSymbol)
            playerNames.append(userName)
            playerSymbols.append(userSymbol)
        else:
            return {"information": "Spiel hat schon gestartet",
            "status" : False}
    #Wenn bereits zwei Spieler im Game sind, dann erstellt er zwei Spieler in c++:
    #und fuegt sie in PlayerList hinzu und setzt das game und status auf true
    if (len(playerNames) == 2):
        playerOne = lobby.createNewPlayer(playerNames[0], playerSymbols[0])
        playerTwo = lobby.createNewPlayer(playerNames[1], playerSymbols[1])
        playerList.append(playerOne)
        playerList.append(playerTwo)
        game = True
        return {"information": "Spiel kann gestartet werden.",
                "status" : True}
    
    else:
        return {"information": "Warte auf weitere Spieler...",
        "status" : False}



# Spielbrett wiedergeben
@app.get("/play/Board")
async def get_user_by_id():
    return {"information" : sb.print()}


# Gewinner des Spiels
@app.get("/play/whoIsWinning")
async def getWinner():
    global game
    if (not game):
        return {"information": "Warten auf Spieler"}
    #Wenn es einen Gewinner gibt wird das Spiel beendet und Gewinner ausgegeben, sonst wird weiter gespielt
    else:
        if (sb.whoIsWinning() != "unentschieden" and sb.whoIsWinning() != "null"):
            game = False
            return {"information": sb.whoIsWinning(), "status" : True}
        else:
            return {"information": "Es gibt noch keinen Gewinner", "status" : False}


# Spieler kann einen Ring hinzufuegen
@app.get("/play/setRing/{player}/{position}")
async def setRing(position: int, player: str):
    global counter
    if (not game):
        return {"information:": "Warten auf weitere Spieler..."}
    # Wenn der Counter auf null ist und der player der erste Spieler ist dann wird der Ring gesetzt
    if (counter == 0 and player == playerList[0].getName()):
        sb.setPlayer(playerOne)
        pos = sb.setRing(position)
    # Wenn die Position schon besetzt ist, dann wird ausgegeben dass der Zug ungueltig ist:
    # und status auf null gesetzt, sonst wird  der counter auf eins gesetzt
        if (not pos):
            return {"information": "Der Zug war ungültig, bitte versuche es erneut",
            "status" : False}
        else:
            counter = 1
            return {"information" : "Dein Ring wird positioniert",
            "status": True}
    #Wenn der Counter gleich eins ist und der zweite Spieler dran ist, dann wird der RIng gesetzt
    elif (counter == 1 and playerList[1].getName()):
        sb.setPlayer(playerTwo)
        pos = sb.setRing(position)
    ## Wenn die Position schon besetzt ist, dann wird ausgegeben dass der Zug ungueltig ist:
    # und status auf null gesetzt, sonst wird  der counter wieder auf null gesetzt
        if (not pos):
            return {"information": "Der Zug war ungültig, bitte versuche es erneut",
            "status" : False}
        else:
            counter = 0
            return {"information" : "Dein Ring wird positioniert",
            "status": True}
    else:
        return {"information" : "Du bist gerade nicht dran. Warte bis du dran bist"}



@app.get("/play/werIstDran")
async def setRing():
    global counter

    if (counter == 1 and len(playerNames) == 2):
        return {"information": playerNames[1]}
    return {"information": playerNames[0]}







if __name__ == '__main__':
  this_python_file = os.path.basename(__file__)[:-3]
  instance = uvicorn.run(f"{this_python_file}:app", host="127.0.0.1", port=8000, log_level="info", reload=True)
