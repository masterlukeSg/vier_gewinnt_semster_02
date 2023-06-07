## cd Desktop
### uvicorn server:app --reload --port 8500


import vierGewinnt
from vierGewinnt import Spielbrett
from typing import Union
import os
import uvicorn
from fastapi import FastAPI

app = FastAPI()

sB = Spielbrett()


@app.get("/")
def read_root():
    return {"Server": "Fast API funktioniert"}

# Füge den Pfad '/user/current_user' hinzu
@app.get("/print")
async def get_current_user():
    return {"print" : sB.print()}

# Füge den unspezifischeren Pfad '/user/{user id}' hinzu
@app.get("/Player/{player}")
async def get_user_by_id(position: int):
    return {"Gameboard" : sB.print()}

if __name__ == '__main__':
  this_python_file = os.path.basename(__file__)[:-3]
  instance = uvicorn.run(f"{this_python_file}:app", host="127.0.0.1", port=8000, log_level="info", reload=True)
