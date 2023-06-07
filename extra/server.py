## cd Desktop
### uvicorn server:app --reload --port 8500

from typing import Union

from fastapi import FastAPI

app = FastAPI()


@app.get("/")
def read_root():
    return {"Server": "Fast API funktioniert"}


# Füge den Pfad '/user/current_user' hinzu
@app.get("/user/current_user")
async def get_current_user():
    return {"user_id" : "The current user"}

# Füge den unspezifischeren Pfad '/user/{user id}' hinzu
@app.get("/user/{userID}")
async def get_user_by_id(userID: int):
    return {"user_id" : userID}

if __name__ == '__main__':
  this_python_file = os.path.basename(__file__)[:-3]
  instance = uvicorn.run(f"{this_python_file}:app", host="127.0.0.1", port=8000, log_level="info", reload=True)
