from flask import Flask, render_template, request, jsonify
import subprocess

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/insert', methods=['POST'])
def insert():
    data = request.json
    post_id = data['post_id']
    name = data['name']
    age = data['age']
    result = subprocess.run(['./employee_app', 'insert', post_id, name, age], capture_output=True, text=True)
    return jsonify({'output': result.stdout})

@app.route('/search/<int:post_id>')
def search(post_id):
    result = subprocess.run(['./employee_app', 'search', str(post_id)], capture_output=True, text=True)
    return jsonify({'output': result.stdout})

@app.route('/promote', methods=['POST'])
def promote():
    data = request.json
    from_id = data['from_id']
    to_id = data['to_id']
    result = subprocess.run(['./employee_app', 'promote', from_id, to_id], capture_output=True, text=True)
    return jsonify({'output': result.stdout})

@app.route('/retire/<int:post_id>')
def retire(post_id):
    result = subprocess.run(['./employee_app', 'retire', str(post_id)], capture_output=True, text=True)
    return jsonify({'output': result.stdout})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=3001, debug=True)