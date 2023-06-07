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
playerNames = []
playerSymbols = []

allSymbols = ["XX", "OO", "++", "**"]

#@app.get("/")
#async def symbol_auswahl():
    


@app.get("/{userName}/{userSymbol}")
async def AddUser(userName : str, userSymbol: str):
    if (userName not in playerNames and len(playerNames) < 3):
        playerNames.append(userName)
        playerSymbols.append(userSymbol)

    if (len(playerNames) == 2):
        return {"information": "Spiel kann gestartet werden.",
                "status" : True}
    
    else:
        return {"information": "Warte auf weitere Spieler",
        "status" : False}



# Füge den Pfad '/user/current_user' hinzu
@app.get("/print")
async def get_current_user():
    return {"print" : playerNames,
            "print2" : playerSymbols
            }



# Füge den unspezifischeren Pfad '/user/{user id}' hinzu
@app.get("/Player/{player}")
async def get_user_by_id(position: int):
    return {"Gameboard" : sb.print()}




if __name__ == '__main__':
  this_python_file = os.path.basename(__file__)[:-3]
  instance = uvicorn.run(f"{this_python_file}:app", host="127.0.0.1", port=8000, log_level="info", reload=True)
