from flask import Flask, jsonify
from flask_cors import CORS  # Import the CORS module
import time
import random

app = Flask(__name__)
CORS(app)  # Add this line to enable CORS for your app

@app.route('/api', methods=['GET'])
def get_api_response():
    # Simulate a constantly changing floating-point value
    current_value = random.uniform(0, 1)
    response = {"current": current_value}
    return jsonify(response)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=80)
