import requests
from pprint import pprint

def main():
  base_api_url = "http://127.0.0.1:8500"
  
  response = requests.get(base_api_url)
  response_json = response.json()
  print(f"Current guess: '{response_json}'")
  
main()
