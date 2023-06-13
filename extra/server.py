## cd Desktop
### uvicorn server:app --reload --port 8000


import vierGewinnt
from vierGewinnt import Spielbrett, Lobby, Spieler
from typing import Union
import os
import random
import uvicorn
from fastapi import FastAPI

app = FastAPI()
lobby = Lobby()
(
    gameIdInstanz,
    gameInstanz,
    playerNamesInstanz,
    playerSymbolsInstanz,
    playerListInstanz,
    allSymbolsInstanz,
    counterInstanz,
    sbInstanz,
) = ([], [], [], [], [], [], [], [])


def onGoingFKT(gameID):
    global lobby, gameIdInstanz, sbInstanz, gameInstanz, playerNamesInstanz, playerSymbolsInstanz, playerListInstanz, allSymbolsInstanz, counterInstanz

    onGoingGame = None
    for i in range(0, len(gameIdInstanz)):
        if gameIdInstanz[i] == gameID:
            onGoingGame = i

    return onGoingGame


def neuesGameAuffuellen():
    global lobby, gameIdInstanz, sbInstanz, gameInstanz, playerNamesInstanz, playerSymbolsInstanz, playerListInstanz, allSymbolsInstanz, counterInstanz
    sb = lobby.createNewGame()

    playerNames, playerSymbols, playerList = [],[], []
    allSymbols = ["XX", "OO", "PP", "KK"]
    game = False
    counter = 0

    sbInstanz.append(sb)
    gameInstanz.append(game)
    playerNamesInstanz.append(playerNames)
    playerListInstanz.append(playerList)
    playerSymbolsInstanz.append(playerSymbols)
    allSymbolsInstanz.append(allSymbols)
    counterInstanz.append(counter)


def main():
    # Gibt die Textnachricht und Symbole wieder
    @app.get("/")
    async def homePage():
        global lobby, gameIdInstanz, sbInstanz, gameInstanz, playerNamesInstanz, playerSymbolsInstanz, playerListInstanz, allSymbolsInstanz, counterInstanz

        txtNachricht = f"Willkommen bei Viergewinnt. \n Es gibt aktuell {len(gameIdInstanz)} Spiele"
        return {"information": txtNachricht}

    @app.get("/joinGame")
    async def joinGame():
        global lobby, gameIdInstanz, sbInstanz, gameInstanz, playerNamesInstanz, playerSymbolsInstanz, playerListInstanz, allSymbolsInstanz, counterInstanz

        for i in range (0, len(playerNamesInstanz)):
            if len(playerNamesInstanz[i]) == 1:
                return {
                    "information": "Wir verbinden dich zu einem offenen Spiel",
                    "gameID": gameIdInstanz[i],
                    "status": True,
                }

        neuesGameAuffuellen()
        spielID = random.randint(0, 1000000000)
        gameIdInstanz.append(spielID)
        onGoingGame = onGoingFKT(spielID)
        return {
            "information": "Es wurde ein neues Spiel für dich erstellt",
            "symbols" : allSymbolsInstanz[onGoingGame],
            "gameID": spielID,
            "status": False,
        }

    # Spieler hinzufügen
    @app.get("/addPlayer/{gameID}/{userName}/{userSymbol}")
    async def AddUser(userName: str, userSymbol: str, gameID: int):
        global lobby, gameIdInstanz, sbInstanz, gameInstanz, playerNamesInstanz, playerSymbolsInstanz, playerListInstanz, allSymbolsInstanz, counterInstanz

        onGoingGame = onGoingFKT(gameID)

        # Wenn Nutzername bereits existiert soll der Spieler nicht hinzugefuegt werden
        if userName in playerNamesInstanz[onGoingGame]:
            return {"information": "Spieler existiert bereits", "status": False}

        # Wenn das Symbol nicht in allSymbol drin ist soll der Spieler nicht hinzugefuegt werden
        if userSymbol not in allSymbolsInstanz[onGoingGame]:
            return {"information": "Dieses Symbol existiert nicht"}

        # Wenn ein anderer Spieler bereits das Symbol besitzt

        if userSymbol in playerSymbolsInstanz[onGoingGame]:
            return {"information": "Ein nutzer besitzt das Symbol bereits"}

        # Wenn es gar keinen oder einen Spieler gibt und das Game noch nicht gestartet hat dann:
        # entfernt er das Usersymbol aus allSymbols und fuegt er einen neuen Spieler und Symbol hinzu:
        # sonst gibt er aus, dass das Spiel schon gestartet hat
        if len(playerNamesInstanz[onGoingGame]) < 3:
            if not gameInstanz[onGoingGame]:
                allSymbolsInstanz[onGoingGame].remove(userSymbol)
                playerNamesInstanz[onGoingGame].append(userName)
                playerSymbolsInstanz[onGoingGame].append(userSymbol)
            else:
                return {"information": "Spiel hat schon gestartet", "status": False}

        # Wenn bereits zwei Spieler im Game sind, dann erstellt er zwei Spieler in c++:
        # und fuegt sie in PlayerList hinzu und setzt das game und status auf true
        if len(playerNamesInstanz[onGoingGame]) == 2:
            playerOne = lobby.createNewPlayer(playerNamesInstanz[onGoingGame][0], playerSymbolsInstanz[onGoingGame][0])
            playerTwo = lobby.createNewPlayer(playerNamesInstanz[onGoingGame][1], playerSymbolsInstanz[onGoingGame][1])

            playerListInstanz[onGoingGame].append(playerOne)
            playerListInstanz[onGoingGame].append(playerTwo)

            gameInstanz[onGoingGame] = True
            return {"information": "Spiel kann gestartet werden.", "status": True}

        else:
            return {"information": "Warte auf weitere Spieler...", "status": False}

    # Spielbrett wiedergeben
    @app.get("/play/{gameID}/Board")
    async def get_user_by_id(gameID: int):
        global lobby, gameIdInstanz, sbInstanz, gameInstanz, playerNamesInstanz, playerSymbolsInstanz, playerListInstanz, allSymbolsInstanz, counterInstanz

        onGoingGame = onGoingFKT(gameID)
        return {"information": sbInstanz[onGoingGame].print()}

    # Gewinner des Spiels
    @app.get("/play/{gameID}/whoIsWinning")
    async def getWinner(gameID: int):
        global lobby, gameIdInstanz, sbInstanz, gameInstanz, playerNamesInstanz, playerSymbolsInstanz, playerListInstanz, allSymbolsInstanz, counterInstanz

        onGoingGame = onGoingFKT(gameID)

        if not gameInstanz[onGoingGame]:
            return {"information": "Warten auf Spieler"}

        # Wenn es einen Gewinner gibt wird das Spiel beendet und Gewinner ausgegeben, sonst wird weiter gespielt
        else:
            if (
                sbInstanz[onGoingGame].whoIsWinning() != "unentschieden"
                and sbInstanz[onGoingGame].whoIsWinning() != "null"
            ):
                gameInstanz[onGoingGame] = False
                return {
                    "information": sbInstanz[onGoingGame].whoIsWinning(),
                    "status": True,
                }
            else:
                return {"information": "Es gibt noch keinen Gewinner", "status": False}

    # Spieler kann einen Ring hinzufuegen
    @app.get("/play/setRing/{gameID}/{player}/{position}")
    async def setRing(gameID: int, position: int, player: str):
        global lobby, gameIdInstanz, sbInstanz, gameInstanz, playerNamesInstanz, playerSymbolsInstanz, playerListInstanz, allSymbolsInstanz, counterInstanz

        onGoingGame = onGoingFKT(gameID)
        if onGoingGame == None:
            return {"infromation" : "Dieses Spiel konnte nicht gefunden werden", 
                    "status" : False}
            
        if gameInstanz[onGoingGame] == False:
            return {"information:": "Warten auf weitere Spieler..."}


        # Wenn der Counter auf null ist und der player der erste Spieler ist dann wird der Ring gesetzt
        if (counterInstanz[onGoingGame] == 0 and player == playerNamesInstanz[onGoingGame][0]):            
            sbInstanz[onGoingGame].setPlayer(playerListInstanz[onGoingGame][0])
            pos = sbInstanz[onGoingGame].setRing(position)

            # Wenn die Position schon besetzt ist, dann whird ausgegeben dass der Zug ungueltig ist:
            # und status auf null gesetzt, sonst wird  der counter auf eins gesetzt
            if not pos:
                return {"information": "Der Zug war ungültig, bitte versuche es erneut", "status": False }
            else:
                counterInstanz[onGoingGame] = 1
                return {"information": "Dein Ring wird positioniert", "status": True}

        # Wenn der Counter gleich eins ist und der zweite Spieler dran ist, dann wird der RIng gesetzt
        elif (counterInstanz[onGoingGame] == 1 and playerNamesInstanz[onGoingGame][1]):
     
            sbInstanz[onGoingGame].setPlayer(playerListInstanz[onGoingGame][1])
            pos = sbInstanz[onGoingGame].setRing(position)

            # Wenn die Position schon besetzt ist, dann wird ausgegeben dass der Zug ungueltig ist:
            # und status auf null gesetzt, sonst wird  der counter wieder auf null gesetzt
            if not pos:
                return {"information": "Der Zug war ungültig, bitte versuche es erneut", "status": False }
            else:
                counterInstanz[onGoingGame] = 0
                return {"information": "Dein Ring wird positioniert", "status": True}
        else:
            return {"information": "Du bist gerade nicht dran. Warte bis du dran bist"}

    @app.get("/play/{gameID}/werIstDran")
    async def setRing(gameID: int):
        global lobby, gameIdInstanz, sbInstanz, gameInstanz, playerNamesInstanz, playerSymbolsInstanz, playerListInstanz, allSymbolsInstanz, counterInstanz

        onGoingGame = onGoingFKT(gameID)
        # wenn der counter auf 1 gesetzt ist, ist der zweite Spieler dran:
        # sonst wenn der counter auf 0 ist, ist der erste Spieler dran
        if (
            counterInstanz[onGoingGame] == 1
            and len(playerNamesInstanz[onGoingGame]) == 2
        ):
            return {"information": playerNamesInstanz[onGoingGame][1], "status": True}

        elif (
            counterInstanz[onGoingGame] == 0
            and len(playerNamesInstanz[onGoingGame]) == 2
        ):
            return {"information": playerNamesInstanz[onGoingGame][0], "status": True}
        return {"information": "Warte auf weitere Spieler", "status": False}


if __name__ == "__main__":
    this_python_file = os.path.basename(__file__)[:-3]
    instance = uvicorn.run(
        f"{this_python_file}:app",
        host="127.0.0.1",
        port=8000,
        log_level="info",
        reload=True,
    )

main()
