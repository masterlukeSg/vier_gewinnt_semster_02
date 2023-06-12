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
playerNames, playerSymbols,playerList = [], [], []
allSymbols = ["XX", "00", "++", "**"]
playerOne, playerTwo = None, None
game = False
counter = 0

@app.get("/")
async def homePage():
    txtNachricht = f"Willkommen bei Viergewinnt. \nIn dieser Lobby sind aktuell {len(playerNames)} Spieler."
    return {"information": txtNachricht,
            "symbols" : allSymbols} 

# Spieler hinzufügen
@app.get("/addPlayer/{userName}/{userSymbol}")
async def AddUser(userName : str, userSymbol: str):
    global game, playerOne, playerTwo
    if (userName not in playerNames and len(playerNames) < 3 and userSymbol in allSymbols and userSymbol not in playerSymbols):
        if (not game):
            allSymbols.remove(userSymbol)
            playerNames.append(userName)
            playerSymbols.append(userSymbol)
        else:
            return {"information": "Spiel hat schon gestartet",
            "status" : False}
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
    if (counter == 0 and player == playerList[0].getName()):
        sb.setPlayer(playerOne)
        pos = sb.setRing(position)
        if (not pos):
            return {"information": "Der Zug war ungültig, bitte versuche es erneut",
            "status" : False}
        else:
            counter = 1
            return {"information" : "Dein Ring wird positioniert",
            "status": True}
    elif (counter == 1 and playerList[1].getName()):
        sb.setPlayer(playerTwo)
        pos = sb.setRing(position)
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
    if (counter == 0):
        return {"information": playerOne.getName()}
    return {"information": playerTwo.getName()}







if __name__ == '__main__':
  this_python_file = os.path.basename(__file__)[:-3]
  instance = uvicorn.run(f"{this_python_file}:app", host="127.0.0.1", port=8000, log_level="info", reload=True)
