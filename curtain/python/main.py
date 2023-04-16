from flask import (
    Flask, jsonify, render_template, request
)
import json


 

app = Flask(__name__)


@app.route("/read", methods=["GET", "POST"])
def read():
    with open('data/data.json') as json_file:
        data = json.load(json_file)
    print(data)
    return data["state"]

@app.route("/", methods=["GET", "POST"])
def index():
    
    with open('data/data.json') as json_file:
        data = json.load(json_file)
        
    if request.method == "GET":
        return render_template("index.html", state=data["state"])
    val = request.form["curtain"]

    data["state"] = val
    

    print(data)

    with open("data/data.json", "w") as outfile:
        json.dump(data, outfile)
    return render_template("index.html", state=data["state"])
    
if __name__ == "__main__":
    app.run(host="127.0.0.1", port=5000, debug=True)
