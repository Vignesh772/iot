from flask import (
    Flask, jsonify, render_template, request, url_for
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
        
    if request.method == "GET":
        return render_template("index.html")

    if request.method == "POST":
    	data ={}
    	if request.form.get('button_on') == 'ON':
    		data["state"] = "on"
    		print("ON")
    	elif request.form.get('button_off') == 'OFF':
    		data["state"] = "off"
    		print("OFF")
    	elif request.form.get('button_18') == '18° C':
    		data["state"] = "18"
    		print("18")
    	elif request.form.get('button_24') == '24° C':
    		data["state"] = "24"
    		print("24")
    	elif request.form.get('button_30') == '30° C':
    		data["state"] = "30"
    		print("30")
    	elif request.form.get('button_reset') == 'RESET':
    		data["state"] = "reset"
    		print("reset")
    	else:
    		pass
	  

	    
	    

    	print(data)
    	with open("data/data.json", "w") as outfile:
    		json.dump(data, outfile)
    return render_template("index.html")
    
if __name__ == "__main__":
    app.run(host="127.0.0.1", port=5000, debug=True)
