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

def main():
    base_api_url = "http://127.0.0.1:8000"

    response = requests.get(base_api_url)
    response_json = response.json()
    print(f"Current guess: '{response_json}'")

    pprint(f"Text Nachricht von den coolste: '{vierGewinnt.__doc__}'")

  


main()
